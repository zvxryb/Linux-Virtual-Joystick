#ifndef _VJOY_H
#define _VJOY_H

#include <linux/input.h>
#include <linux/uinput.h>
#include <Python.h>
#include <pthread.h>

#define VJOY_INPUT_RATE  60 // Loop input frequency in Hertz
#define VJOY_INPUT_DELAY 1000000/VJOY_INPUT_RATE

typedef struct _vjoy_info {
    char name[UINPUT_MAX_NAME_SIZE];
    int  relaxis[REL_CNT];
    int  relaxiscount;
    int  absaxis[ABS_CNT];
    int  absaxiscount;
    int  feedback[FF_CNT];
    int  feedbackcount;
    int  maxeffects;
    int  buttons[KEY_CNT];
    int  buttoncount;
} vjoy_info;

typedef struct _vjoy_dev {
    int                    uifd;       // UInput File Descriptor
    struct uinput_user_dev uidev;      // UInput Device Info
    PyObject              *pymodule;   // The Python script that operates this device
    vjoy_info              devinfo;    // The parsed device info
    pthread_t              evtthread;  // pthread structure for events
    pthread_t              inptthread; // pthread for device input loop
} vjoy_dev;

int       vjoy_load_module(char* name);
void     *vjoy_dev_event_loop(void *arg);
void     *vjoy_dev_input_loop(void *arg);
PyObject *vjoy_convert_ff_effect(struct ff_effect *effect);
PyObject *vjoy_convert_ff_envelope(struct ff_envelope *envelope);
int       vjoy_initialize();

#endif /* _VJOY_H */
