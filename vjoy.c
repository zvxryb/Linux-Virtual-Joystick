#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include "vjoy.h"
#include "vjoy_python.h"


/* globals */
static const char *uinputpaths[] = {
    "/dev/uinput",
    "/dev/misc/uinput",
    "/dev/input/uinput"
};
static vjoy_dev      **devices  = NULL; // List of devices
static int             devcount = 0;    // Number of devices currently loaded
static pthread_mutex_t pymutex;         // Global Python threading mutex

static void vjoy_parse_block(PyObject* info, char* key, int *count,
                             int *array, int max) {
    // FIXME: Replace all these assert() with _real_ error handling
    PyObject *items = PyMapping_GetItemString(info, key);
    if (items != NULL) {
        *count = PySequence_Size(items);
        assert(*count >= 0);
        assert(*count <= max);
        for (int i=0; i<*count; i++) {
            PyObject *item = PySequence_GetItem(items, i);
            assert(item != NULL);
            array[i] = PyInt_AsLong(item);
            assert(array[i] >= 0);
            Py_DECREF(item);
        }
        Py_DECREF(items);
    }
}

static void vjoy_parse_info(vjoy_dev *dev) {
    memset(&dev->devinfo, 0, sizeof(vjoy_info));

    pthread_mutex_lock(&pymutex);

    // Get info
    PyObject *pyinfo   = PyObject_CallMethod(dev->pymodule, "getVJoyInfo", NULL);
    if (PyErr_Occurred() != NULL) {
        PyErr_Print();
    }
    if (pyinfo == NULL) {
        fprintf(stderr, "Module has no getVJoyInfo() method.\n");
        return;
    }
    // Joystick name
    PyObject *pyname = PyMapping_GetItemString(pyinfo, "name");
    if (pyname != NULL) {
        char* name = PyString_AsString(pyname);
        if (name != NULL) {
            // Two names... This is kind of redundant.
            strncpy(dev->devinfo.name, name, UINPUT_MAX_NAME_SIZE);
            strncpy(dev->uidev.name, name, UINPUT_MAX_NAME_SIZE);
        }
        Py_DECREF(pyname);
    }
    // Relative axises
    vjoy_parse_block(pyinfo, "relaxis", &dev->devinfo.relaxiscount,
                     dev->devinfo.relaxis, REL_CNT);
    // Absolute axises
    vjoy_parse_block(pyinfo, "absaxis", &dev->devinfo.absaxiscount,
                     dev->devinfo.absaxis, ABS_CNT);
    // Force Feedback effects
    vjoy_parse_block(pyinfo, "feedback", &dev->devinfo.feedbackcount,
                     dev->devinfo.feedback, FF_CNT);
    PyObject *pymaxeffects  = PyMapping_GetItemString(pyinfo, "maxeffects");
    if (pymaxeffects != NULL) {
        dev->devinfo.maxeffects = PyInt_AsLong(pymaxeffects);
        Py_DECREF(pymaxeffects);
    }
    // Buttons and keys
    vjoy_parse_block(pyinfo, "buttons", &dev->devinfo.buttoncount,
                     dev->devinfo.buttons, KEY_CNT);

    Py_DECREF(pyinfo);

    pthread_mutex_unlock(&pymutex);
}

// TODO: A seperate interpreter for each individual device
int vjoy_load_module(char* name) {
    // Create device
    printf("Creating device:\n");
    vjoy_dev *dev = malloc(sizeof(vjoy_dev));
    memset(dev, 0, sizeof(vjoy_dev));

    // Start up Python
    printf("\tImporting module.\n");
    pthread_mutex_lock(&pymutex);
    dev->pymodule = PyImport_ImportModule(name);
    if (PyErr_Occurred() != NULL) {
        PyErr_Print();
    }
    if (dev->pymodule == NULL) {
        fprintf(stderr, "Failed to load module %s\n", name);
        pthread_mutex_unlock(&pymutex);
        free(dev);
        return -1;
    }
    pthread_mutex_unlock(&pymutex);

    // Append device to device list
    printf("\tAppending to device list.\n");
    devcount++;
    devices             = realloc(devices, devcount*sizeof(vjoy_dev*));
    devices[devcount-1] = dev;

    // Open a connection to UInput
    printf("\tInitializing uinput.\n");
    int paths = sizeof(uinputpaths)/sizeof(char*);
    for (int i=0; i<paths; i++) {
        printf("\t\tTrying %s\n", uinputpaths[i]);
        dev->uifd = open(uinputpaths[i], O_RDWR);
        if (dev->uifd >= 0) break;
    }
    if (dev->uifd < 0) {
        printf("\tFailed to initialize uinput\n");
        return -1;
    }
    printf("\tSucceeded!\n");

    // Read device info from the Python module
    vjoy_parse_info(dev);
    
    // Configure uinput device
    dev->uidev.id.bustype = BUS_VIRTUAL;

    if (dev->devinfo.relaxiscount > 0) {
        ioctl(dev->uifd, UI_SET_EVBIT, EV_REL);
        for (int i=0; i<dev->devinfo.relaxiscount; i++) {
            printf("\tAdding relative axis: %x\n", dev->devinfo.relaxis[i]);
            ioctl(dev->uifd, UI_SET_RELBIT, dev->devinfo.relaxis[i]);
        }
    }
    if (dev->devinfo.absaxiscount > 0) {
        ioctl(dev->uifd, UI_SET_EVBIT, EV_ABS);
        for (int i=0; i<dev->devinfo.absaxiscount; i++) {
            printf("\tAdding absolute axis: %x\n", dev->devinfo.absaxis[i]);
            ioctl(dev->uifd, UI_SET_ABSBIT, dev->devinfo.absaxis[i]);
        }
    }
    if (dev->devinfo.feedbackcount > 0) {
        ioctl(dev->uifd, UI_SET_EVBIT, EV_FF);
        for (int i=0; i<dev->devinfo.feedbackcount; i++) {
            printf("\tAdding feedback effect: %x\n", dev->devinfo.feedback[i]);
            ioctl(dev->uifd, UI_SET_FFBIT, dev->devinfo.feedback[i]);
        }
    }
    if (dev->devinfo.buttoncount > 0) {
        ioctl(dev->uifd, UI_SET_EVBIT, EV_KEY);
        for (int i=0; i<dev->devinfo.buttoncount; i++) {
            printf("\tAdding key/button: %x\n", dev->devinfo.buttons[i]);
            ioctl(dev->uifd, UI_SET_KEYBIT, dev->devinfo.buttons[i]);
        }
    }

    for (int i=0; i<ABS_MAX; i++) {
        dev->uidev.absmin[i] = SHRT_MIN;
        dev->uidev.absmax[i] = SHRT_MAX;
    }
    printf("\tMax concurrent effects: %i\n", dev->devinfo.maxeffects);
    dev->uidev.ff_effects_max = dev->devinfo.maxeffects;

    write(dev->uifd, &dev->uidev, sizeof(struct uinput_user_dev));
    
    int err = ioctl(dev->uifd, UI_DEV_CREATE);
    if (err != 0) {
        fprintf(stderr, "Device creation failed.\n");
        exit(1);
    }

    printf("Device created.\n");

    printf("Starting device control threads.\n");
    pthread_create(&dev->inptthread, NULL, vjoy_dev_input_loop, dev);
    pthread_create(&dev->evtthread,  NULL, vjoy_dev_event_loop, dev);

    return 0;
}

void *vjoy_dev_event_loop(void *arg) {
    vjoy_dev               *dev = arg;
    int                     s;
    struct input_event      evt;
    struct uinput_ff_upload ureq;
    struct uinput_ff_erase  ereq;
    PyObject               *res;
    while (1) {
	printf("Waiting for events.\n");
        s = read(dev->uifd, &evt, sizeof(struct input_event));
        if (s != sizeof(struct input_event)) {
            fprintf(stderr, "Error reading event structure.\n");
            continue;
        }
        printf("Event recieved.\n\tType: %x\n\tCode: %x\n\tValue: %x\n", evt.type, evt.code, evt.value);
        switch (evt.type) {
            case EV_UINPUT:
                switch (evt.code) {
                    case UI_FF_UPLOAD:
                        memset(&ureq, 0, sizeof(struct uinput_ff_upload));
                        ureq.request_id = evt.value;
                        ioctl(dev->uifd, UI_BEGIN_FF_UPLOAD, &ureq);
                        pthread_mutex_lock(&pymutex);
                            PyObject *pyeffect = vjoy_convert_ff_effect(&ureq.effect);
                            PyObject *res = PyObject_CallMethod(dev->pymodule, "doVJoyUploadFeedback", "O", pyeffect);
                            Py_XDECREF(res);
                            if (PyErr_Occurred() != NULL) {
                                PyErr_Print();
                            }
                        pthread_mutex_unlock(&pymutex);
                        ioctl(dev->uifd, UI_END_FF_UPLOAD, &ureq);
                        break;
                    case UI_FF_ERASE:
                        memset(&ereq, 0, sizeof(struct uinput_ff_erase));
                        ereq.request_id = evt.value;
                        ioctl(dev->uifd, UI_BEGIN_FF_ERASE, &ereq);
                        pthread_mutex_lock(&pymutex);
                            res = PyObject_CallMethod(dev->pymodule, "doVJoyEraseFeedback", "i", ereq.effect_id);
                            Py_XDECREF(res);
                            if (PyErr_Occurred() != NULL) {
                                PyErr_Print();
                            }
                        pthread_mutex_unlock(&pymutex);
                        ioctl(dev->uifd, UI_END_FF_ERASE, &ereq);
                        break;
                    default:
                        break;
                }
                break;
            default:
                pthread_mutex_lock(&pymutex);
                    res = PyObject_CallMethod(dev->pymodule, "doVJoyEvent", "iii", evt.type, evt.code, evt.value);
                    Py_XDECREF(res);
                    if (PyErr_Occurred() != NULL) {
                        PyErr_Print();
                    }
                pthread_mutex_unlock(&pymutex);
                break;
        }
    }
}

void *vjoy_dev_input_loop(void *arg) {
    vjoy_dev           *dev = arg;
    PyObject           *pyevents;
    struct input_event  evt;
    while (1) {
        pthread_mutex_lock(&pymutex);
            pyevents = PyObject_CallMethod(dev->pymodule, "doVJoyThink", NULL);
            if (PyErr_Occurred() != NULL) {
                PyErr_Print();
            }
            if (pyevents != NULL) {
                int eventcount = PySequence_Size(pyevents);
                if (eventcount > 0) {
                    memset(&evt, 0, sizeof(struct input_event));
                    gettimeofday(&evt.time, NULL);
                    // TODO: This all needs more error checking
                    for (int i=0; i<eventcount; i++) {
                        PyObject *pyevent = PySequence_GetItem(pyevents, i);
                        if (pyevent != NULL) {
                            if (PySequence_Size(pyevent) != 3) {
                                fprintf(stderr, "Event lists must have exactly three items in the form (type, code, value)\n");
                                continue;
                            }
                            PyObject *pytype = PySequence_GetItem(pyevent, 0);
                            if (pytype != NULL) {
                                evt.type = PyInt_AsLong(pytype);
                                Py_DECREF(pytype);
                            }
                            PyObject *pycode = PySequence_GetItem(pyevent, 1);
                            if (pycode != NULL) {
                                evt.code = PyInt_AsLong(pycode);
                                Py_DECREF(pycode);
                            }
                            PyObject *pyvalue = PySequence_GetItem(pyevent, 2);
                            if (pyvalue != NULL) {
                                evt.value = PyInt_AsLong(pyvalue);
                                Py_DECREF(pyvalue);
                            }
                            Py_DECREF(pyevent);
                        }
                        write(dev->uifd, &evt, sizeof(struct input_event));
                    }
                    evt.type  = EV_SYN;
                    evt.code  = SYN_REPORT;
                    evt.value = 0;
                    write(dev->uifd, &evt, sizeof(struct input_event));
                }
                Py_DECREF(pyevents);
            }
        pthread_mutex_unlock(&pymutex);
        usleep(VJOY_INPUT_DELAY);
    }
}

PyObject *vjoy_convert_ff_envelope(struct ff_envelope *envelope) {
    PyObject *pyenvelope = PyDict_New();
    PyDict_SetItemString(pyenvelope, "attack_length", PyInt_FromLong(envelope->attack_length));
    PyDict_SetItemString(pyenvelope, "attack_level",  PyInt_FromLong(envelope->attack_level));
    PyDict_SetItemString(pyenvelope, "fade_length",   PyInt_FromLong(envelope->fade_length));
    PyDict_SetItemString(pyenvelope, "fade_level",    PyInt_FromLong(envelope->fade_level));
    return pyenvelope;
}

PyObject *vjoy_convert_ff_effect(struct ff_effect *effect) {
    PyObject *pyeffect  = PyDict_New();
    PyDict_SetItemString(pyeffect,  "type",      PyInt_FromLong(effect->type));
    PyDict_SetItemString(pyeffect,  "id",        PyInt_FromLong(effect->id));
    PyDict_SetItemString(pyeffect,  "direction", PyInt_FromLong(effect->direction));
    PyObject *pytrigger = PyDict_New();
    PyDict_SetItemString(pytrigger, "button",    PyInt_FromLong(effect->trigger.button));
    PyDict_SetItemString(pytrigger, "interval",  PyInt_FromLong(effect->trigger.interval));
    PyDict_SetItemString(pyeffect,  "trigger",   pytrigger);
    PyObject *pyreplay  = PyDict_New();
    PyDict_SetItemString(pyreplay,  "length",    PyInt_FromLong(effect->replay.length));
    PyDict_SetItemString(pyreplay,  "delay",     PyInt_FromLong(effect->replay.delay));
    PyDict_SetItemString(pyeffect,  "replay",    pyreplay);

    PyObject *pysubeffect[2] = {NULL, NULL};
    switch (effect->type) {
        case FF_CONSTANT:
            pysubeffect[0] = PyDict_New();
            PyDict_SetItemString(pysubeffect[0], "level",    PyInt_FromLong(effect->u.constant.level));
            PyDict_SetItemString(pysubeffect[0], "envelope", vjoy_convert_ff_envelope(&effect->u.constant.envelope));
            PyDict_SetItemString(pyeffect,   "constant", pysubeffect[0]);
            break;
        case FF_PERIODIC:
            pysubeffect[0] = PyDict_New();
            PyDict_SetItemString(pysubeffect[0], "waveform",  PyInt_FromLong(effect->u.periodic.waveform));
            PyDict_SetItemString(pysubeffect[0], "period",    PyInt_FromLong(effect->u.periodic.period));
            PyDict_SetItemString(pysubeffect[0], "magnitude", PyInt_FromLong(effect->u.periodic.magnitude));
            PyDict_SetItemString(pysubeffect[0], "offset",    PyInt_FromLong(effect->u.periodic.offset));
            PyDict_SetItemString(pysubeffect[0], "phase",     PyInt_FromLong(effect->u.periodic.phase));
            PyDict_SetItemString(pysubeffect[0], "envelope",  vjoy_convert_ff_envelope(&effect->u.periodic.envelope));
            PyDict_SetItemString(pyeffect,   "periodic",  pysubeffect[0]);
            break;
        case FF_RAMP:
            pysubeffect[0] = PyDict_New();
            PyDict_SetItemString(pysubeffect[0],   "start_level", PyInt_FromLong(effect->u.ramp.start_level));
            PyDict_SetItemString(pysubeffect[0],   "end_level",   PyInt_FromLong(effect->u.ramp.end_level));
            PyDict_SetItemString(pysubeffect[0],   "envelope",    vjoy_convert_ff_envelope(&effect->u.ramp.envelope));
            PyDict_SetItemString(pyeffect, "ramp",        pysubeffect[0]);
            break;
        case FF_SPRING:
        case FF_FRICTION:
            pysubeffect[0] = PyDict_New();
            pysubeffect[1] = PyDict_New();
            PyDict_SetItemString(pysubeffect[0], "right_saturation", PyInt_FromLong(effect->u.condition[0].right_saturation));
            PyDict_SetItemString(pysubeffect[0], "left_saturation",  PyInt_FromLong(effect->u.condition[0].left_saturation));
            PyDict_SetItemString(pysubeffect[0], "right_coeff",      PyInt_FromLong(effect->u.condition[0].right_coeff));
            PyDict_SetItemString(pysubeffect[0], "left_coeff",       PyInt_FromLong(effect->u.condition[0].left_coeff));
            PyDict_SetItemString(pysubeffect[0], "deadband",         PyInt_FromLong(effect->u.condition[0].deadband));
            PyDict_SetItemString(pysubeffect[0], "center",           PyInt_FromLong(effect->u.condition[0].center));
            PyDict_SetItemString(pysubeffect[1], "right_saturation", PyInt_FromLong(effect->u.condition[1].right_saturation));
            PyDict_SetItemString(pysubeffect[1], "left_saturation",  PyInt_FromLong(effect->u.condition[1].left_saturation));
            PyDict_SetItemString(pysubeffect[1], "right_coeff",      PyInt_FromLong(effect->u.condition[1].right_coeff));
            PyDict_SetItemString(pysubeffect[1], "left_coeff",       PyInt_FromLong(effect->u.condition[1].left_coeff));
            PyDict_SetItemString(pysubeffect[1], "deadband",         PyInt_FromLong(effect->u.condition[1].deadband));
            PyDict_SetItemString(pysubeffect[1], "center",           PyInt_FromLong(effect->u.condition[1].center));
            PyDict_SetItemString(pyeffect,       "condition",        PyTuple_Pack(2, pysubeffect[0], pysubeffect[1]));
            break;
        case FF_RUMBLE:
            pysubeffect[0] = PyDict_New();
            PyDict_SetItemString(pysubeffect[0], "strong_magnitude", PyInt_FromLong(effect->u.rumble.strong_magnitude));
            PyDict_SetItemString(pysubeffect[0], "weak_magnitude",   PyInt_FromLong(effect->u.rumble.weak_magnitude));
            PyDict_SetItemString(pyeffect, "rumble",           pysubeffect[0]);
            break;
        default:
            break;
     }
     return pyeffect;
}

int  vjoy_initialize() {
    printf("Initializing...\n");
    Py_Initialize();
    assert(pthread_mutex_init(&pymutex, NULL) == 0);
    char modulepath[4096];
    snprintf(modulepath, 4096, "%s:%s/.config/vjoy/modules/", Py_GetPath(), getenv("HOME"));
    printf("Searching for modules in %s/.config/vjoy/modules/ (as well as other Python paths)\n", getenv("HOME"));
    PySys_SetPath(modulepath);
    vjoy_py_initialize();
    printf("Finished initialization.\n");
    return 0;
}
