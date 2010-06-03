#include "vjoy_python.h"

static PyMethodDef vjoy_py_module_methods[] = {
    {NULL, NULL, 0, NULL}
};

#define VJOY_PY_CONST(m,v) assert(PyObject_SetAttrString(m, #v, \
                            PyLong_FromLong(v)) >= 0)

void vjoy_py_initialize() {
    PyObject *module = Py_InitModule("vjoy", vjoy_py_module_methods);

    // Import C constants into module
    VJOY_PY_CONST(module, EV_SYN);
    VJOY_PY_CONST(module, EV_KEY);
    VJOY_PY_CONST(module, EV_REL);
    VJOY_PY_CONST(module, EV_ABS);
    VJOY_PY_CONST(module, EV_FF);
    VJOY_PY_CONST(module, EV_FF_STATUS);

    VJOY_PY_CONST(module, SYN_REPORT);
    VJOY_PY_CONST(module, SYN_CONFIG);

    VJOY_PY_CONST(module, KEY_ESC);
    VJOY_PY_CONST(module, KEY_1);
    VJOY_PY_CONST(module, KEY_2);
    VJOY_PY_CONST(module, KEY_3);
    VJOY_PY_CONST(module, KEY_4);
    VJOY_PY_CONST(module, KEY_5);
    VJOY_PY_CONST(module, KEY_6);
    VJOY_PY_CONST(module, KEY_7);
    VJOY_PY_CONST(module, KEY_8);
    VJOY_PY_CONST(module, KEY_9);
    VJOY_PY_CONST(module, KEY_0);
    VJOY_PY_CONST(module, KEY_MINUS);
    VJOY_PY_CONST(module, KEY_EQUAL);
    VJOY_PY_CONST(module, KEY_BACKSPACE);
    VJOY_PY_CONST(module, KEY_TAB);
    VJOY_PY_CONST(module, KEY_Q);
    VJOY_PY_CONST(module, KEY_W);
    VJOY_PY_CONST(module, KEY_E);
    VJOY_PY_CONST(module, KEY_R);
    VJOY_PY_CONST(module, KEY_T);
    VJOY_PY_CONST(module, KEY_Y);
    VJOY_PY_CONST(module, KEY_U);
    VJOY_PY_CONST(module, KEY_I);
    VJOY_PY_CONST(module, KEY_O);
    VJOY_PY_CONST(module, KEY_P);
    VJOY_PY_CONST(module, KEY_LEFTBRACE);
    VJOY_PY_CONST(module, KEY_RIGHTBRACE);
    VJOY_PY_CONST(module, KEY_ENTER);
    VJOY_PY_CONST(module, KEY_LEFTCTRL);
    VJOY_PY_CONST(module, KEY_A);
    VJOY_PY_CONST(module, KEY_S);
    VJOY_PY_CONST(module, KEY_D);
    VJOY_PY_CONST(module, KEY_F);
    VJOY_PY_CONST(module, KEY_G);
    VJOY_PY_CONST(module, KEY_H);
    VJOY_PY_CONST(module, KEY_J);
    VJOY_PY_CONST(module, KEY_K);
    VJOY_PY_CONST(module, KEY_L);
    VJOY_PY_CONST(module, KEY_SEMICOLON);
    VJOY_PY_CONST(module, KEY_APOSTROPHE);
    VJOY_PY_CONST(module, KEY_GRAVE);
    VJOY_PY_CONST(module, KEY_LEFTSHIFT);
    VJOY_PY_CONST(module, KEY_BACKSLASH);
    VJOY_PY_CONST(module, KEY_Z);
    VJOY_PY_CONST(module, KEY_X);
    VJOY_PY_CONST(module, KEY_C);
    VJOY_PY_CONST(module, KEY_V);
    VJOY_PY_CONST(module, KEY_B);
    VJOY_PY_CONST(module, KEY_N);
    VJOY_PY_CONST(module, KEY_M);
    VJOY_PY_CONST(module, KEY_COMMA);
    VJOY_PY_CONST(module, KEY_DOT);
    VJOY_PY_CONST(module, KEY_SLASH);
    VJOY_PY_CONST(module, KEY_RIGHTSHIFT);
    VJOY_PY_CONST(module, KEY_KPASTERISK);
    VJOY_PY_CONST(module, KEY_LEFTALT);
    VJOY_PY_CONST(module, KEY_SPACE);
    VJOY_PY_CONST(module, KEY_CAPSLOCK);
    VJOY_PY_CONST(module, KEY_F1);
    VJOY_PY_CONST(module, KEY_F2);
    VJOY_PY_CONST(module, KEY_F3);
    VJOY_PY_CONST(module, KEY_F4);
    VJOY_PY_CONST(module, KEY_F5);
    VJOY_PY_CONST(module, KEY_F6);
    VJOY_PY_CONST(module, KEY_F7);
    VJOY_PY_CONST(module, KEY_F8);
    VJOY_PY_CONST(module, KEY_F9);
    VJOY_PY_CONST(module, KEY_F10);
    VJOY_PY_CONST(module, KEY_NUMLOCK);
    VJOY_PY_CONST(module, KEY_SCROLLLOCK);
    VJOY_PY_CONST(module, KEY_KP7);
    VJOY_PY_CONST(module, KEY_KP8);
    VJOY_PY_CONST(module, KEY_KP9);
    VJOY_PY_CONST(module, KEY_KPMINUS);
    VJOY_PY_CONST(module, KEY_KP4);
    VJOY_PY_CONST(module, KEY_KP5);
    VJOY_PY_CONST(module, KEY_KP6);
    VJOY_PY_CONST(module, KEY_KPPLUS);
    VJOY_PY_CONST(module, KEY_KP1);
    VJOY_PY_CONST(module, KEY_KP2);
    VJOY_PY_CONST(module, KEY_KP3);
    VJOY_PY_CONST(module, KEY_KP0);
    VJOY_PY_CONST(module, KEY_KPDOT);

    VJOY_PY_CONST(module, KEY_ZENKAKUHANKAKU);
    VJOY_PY_CONST(module, KEY_102ND);
    VJOY_PY_CONST(module, KEY_F11);
    VJOY_PY_CONST(module, KEY_F12);
    VJOY_PY_CONST(module, KEY_RO);
    VJOY_PY_CONST(module, KEY_KATAKANA);
    VJOY_PY_CONST(module, KEY_HIRAGANA);
    VJOY_PY_CONST(module, KEY_HENKAN);
    VJOY_PY_CONST(module, KEY_KATAKANAHIRAGANA);
    VJOY_PY_CONST(module, KEY_MUHENKAN);
    VJOY_PY_CONST(module, KEY_KPJPCOMMA);
    VJOY_PY_CONST(module, KEY_KPENTER);
    VJOY_PY_CONST(module, KEY_RIGHTCTRL);
    VJOY_PY_CONST(module, KEY_KPSLASH);
    VJOY_PY_CONST(module, KEY_SYSRQ);
    VJOY_PY_CONST(module, KEY_RIGHTALT);
    VJOY_PY_CONST(module, KEY_LINEFEED);
    VJOY_PY_CONST(module, KEY_HOME);
    VJOY_PY_CONST(module, KEY_UP);
    VJOY_PY_CONST(module, KEY_PAGEUP);
    VJOY_PY_CONST(module, KEY_LEFT);
    VJOY_PY_CONST(module, KEY_RIGHT);
    VJOY_PY_CONST(module, KEY_END);
    VJOY_PY_CONST(module, KEY_DOWN);
    VJOY_PY_CONST(module, KEY_PAGEDOWN);
    VJOY_PY_CONST(module, KEY_INSERT);
    VJOY_PY_CONST(module, KEY_DELETE);
    VJOY_PY_CONST(module, KEY_MACRO);
    VJOY_PY_CONST(module, KEY_MUTE);
    VJOY_PY_CONST(module, KEY_VOLUMEDOWN);
    VJOY_PY_CONST(module, KEY_VOLUMEUP);
    VJOY_PY_CONST(module, KEY_POWER);
    VJOY_PY_CONST(module, KEY_KPEQUAL);
    VJOY_PY_CONST(module, KEY_KPPLUSMINUS);
    VJOY_PY_CONST(module, KEY_PAUSE);

    VJOY_PY_CONST(module, KEY_KPCOMMA);
    VJOY_PY_CONST(module, KEY_HANGEUL);
    VJOY_PY_CONST(module, KEY_HANGUEL);
    VJOY_PY_CONST(module, KEY_HANJA);
    VJOY_PY_CONST(module, KEY_YEN);
    VJOY_PY_CONST(module, KEY_LEFTMETA);
    VJOY_PY_CONST(module, KEY_RIGHTMETA);
    VJOY_PY_CONST(module, KEY_COMPOSE);

    VJOY_PY_CONST(module, KEY_STOP);
    VJOY_PY_CONST(module, KEY_AGAIN);
    VJOY_PY_CONST(module, KEY_PROPS);
    VJOY_PY_CONST(module, KEY_UNDO);
    VJOY_PY_CONST(module, KEY_FRONT);
    VJOY_PY_CONST(module, KEY_COPY);
    VJOY_PY_CONST(module, KEY_OPEN);
    VJOY_PY_CONST(module, KEY_PASTE);
    VJOY_PY_CONST(module, KEY_FIND);
    VJOY_PY_CONST(module, KEY_CUT);
    VJOY_PY_CONST(module, KEY_HELP);
    VJOY_PY_CONST(module, KEY_MENU);
    VJOY_PY_CONST(module, KEY_CALC);
    VJOY_PY_CONST(module, KEY_SETUP);
    VJOY_PY_CONST(module, KEY_SLEEP);
    VJOY_PY_CONST(module, KEY_WAKEUP);
    VJOY_PY_CONST(module, KEY_FILE);
    VJOY_PY_CONST(module, KEY_SENDFILE);
    VJOY_PY_CONST(module, KEY_DELETEFILE);
    VJOY_PY_CONST(module, KEY_XFER);
    VJOY_PY_CONST(module, KEY_PROG1);
    VJOY_PY_CONST(module, KEY_PROG2);
    VJOY_PY_CONST(module, KEY_WWW);
    VJOY_PY_CONST(module, KEY_MSDOS);
    VJOY_PY_CONST(module, KEY_COFFEE);
    VJOY_PY_CONST(module, KEY_SCREENLOCK);
    VJOY_PY_CONST(module, KEY_DIRECTION);
    VJOY_PY_CONST(module, KEY_CYCLEWINDOWS);
    VJOY_PY_CONST(module, KEY_MAIL);
    VJOY_PY_CONST(module, KEY_BOOKMARKS);
    VJOY_PY_CONST(module, KEY_COMPUTER);
    VJOY_PY_CONST(module, KEY_BACK);
    VJOY_PY_CONST(module, KEY_FORWARD);
    VJOY_PY_CONST(module, KEY_CLOSECD);
    VJOY_PY_CONST(module, KEY_EJECTCD);
    VJOY_PY_CONST(module, KEY_EJECTCLOSECD);
    VJOY_PY_CONST(module, KEY_NEXTSONG);
    VJOY_PY_CONST(module, KEY_PLAYPAUSE);
    VJOY_PY_CONST(module, KEY_PREVIOUSSONG);
    VJOY_PY_CONST(module, KEY_STOPCD);
    VJOY_PY_CONST(module, KEY_RECORD);
    VJOY_PY_CONST(module, KEY_REWIND);
    VJOY_PY_CONST(module, KEY_PHONE);
    VJOY_PY_CONST(module, KEY_ISO);
    VJOY_PY_CONST(module, KEY_CONFIG);
    VJOY_PY_CONST(module, KEY_HOMEPAGE);
    VJOY_PY_CONST(module, KEY_REFRESH);
    VJOY_PY_CONST(module, KEY_EXIT);
    VJOY_PY_CONST(module, KEY_MOVE);
    VJOY_PY_CONST(module, KEY_EDIT);
    VJOY_PY_CONST(module, KEY_SCROLLUP);
    VJOY_PY_CONST(module, KEY_SCROLLDOWN);
    VJOY_PY_CONST(module, KEY_KPLEFTPAREN);
    VJOY_PY_CONST(module, KEY_KPRIGHTPAREN);
    VJOY_PY_CONST(module, KEY_NEW);
    VJOY_PY_CONST(module, KEY_REDO);

    VJOY_PY_CONST(module, KEY_F13);
    VJOY_PY_CONST(module, KEY_F14);
    VJOY_PY_CONST(module, KEY_F15);
    VJOY_PY_CONST(module, KEY_F16);
    VJOY_PY_CONST(module, KEY_F17);
    VJOY_PY_CONST(module, KEY_F18);
    VJOY_PY_CONST(module, KEY_F19);
    VJOY_PY_CONST(module, KEY_F20);
    VJOY_PY_CONST(module, KEY_F21);
    VJOY_PY_CONST(module, KEY_F22);
    VJOY_PY_CONST(module, KEY_F23);
    VJOY_PY_CONST(module, KEY_F24);

    VJOY_PY_CONST(module, KEY_PLAYCD);
    VJOY_PY_CONST(module, KEY_PAUSECD);
    VJOY_PY_CONST(module, KEY_PROG3);
    VJOY_PY_CONST(module, KEY_PROG4);
    VJOY_PY_CONST(module, KEY_SUSPEND);
    VJOY_PY_CONST(module, KEY_CLOSE);
    VJOY_PY_CONST(module, KEY_PLAY);
    VJOY_PY_CONST(module, KEY_FASTFORWARD);
    VJOY_PY_CONST(module, KEY_BASSBOOST);
    VJOY_PY_CONST(module, KEY_PRINT);
    VJOY_PY_CONST(module, KEY_HP);
    VJOY_PY_CONST(module, KEY_CAMERA);
    VJOY_PY_CONST(module, KEY_SOUND);
    VJOY_PY_CONST(module, KEY_QUESTION);
    VJOY_PY_CONST(module, KEY_EMAIL);
    VJOY_PY_CONST(module, KEY_CHAT);
    VJOY_PY_CONST(module, KEY_SEARCH);
    VJOY_PY_CONST(module, KEY_CONNECT);
    VJOY_PY_CONST(module, KEY_FINANCE);
    VJOY_PY_CONST(module, KEY_SPORT);
    VJOY_PY_CONST(module, KEY_SHOP);
    VJOY_PY_CONST(module, KEY_ALTERASE);
    VJOY_PY_CONST(module, KEY_CANCEL);
    VJOY_PY_CONST(module, KEY_BRIGHTNESSUP);
    VJOY_PY_CONST(module, KEY_BRIGHTNESSDOWN);
    VJOY_PY_CONST(module, KEY_MEDIA);

    VJOY_PY_CONST(module, KEY_SWITCHVIDEOMODE);

    VJOY_PY_CONST(module, KEY_KBDILLUMTOGGLE);
    VJOY_PY_CONST(module, KEY_KBDILLUMDOWN);
    VJOY_PY_CONST(module, KEY_KBDILLUMUP);

    VJOY_PY_CONST(module, KEY_SEND);
    VJOY_PY_CONST(module, KEY_REPLY);
    VJOY_PY_CONST(module, KEY_FORWARDMAIL);
    VJOY_PY_CONST(module, KEY_SAVE);
    VJOY_PY_CONST(module, KEY_DOCUMENTS);

    VJOY_PY_CONST(module, KEY_BATTERY);

    VJOY_PY_CONST(module, KEY_BLUETOOTH);
    VJOY_PY_CONST(module, KEY_WLAN);
    VJOY_PY_CONST(module, KEY_UWB);

    VJOY_PY_CONST(module, KEY_UNKNOWN);

    VJOY_PY_CONST(module, KEY_VIDEO_NEXT);
    VJOY_PY_CONST(module, KEY_VIDEO_PREV);
    VJOY_PY_CONST(module, KEY_BRIGHTNESS_CYCLE);
    VJOY_PY_CONST(module, KEY_BRIGHTNESS_ZERO);
    VJOY_PY_CONST(module, KEY_DISPLAY_OFF);

    VJOY_PY_CONST(module, KEY_WIMAX);

    VJOY_PY_CONST(module, BTN_MISC);
    VJOY_PY_CONST(module, BTN_0);
    VJOY_PY_CONST(module, BTN_1);
    VJOY_PY_CONST(module, BTN_2);
    VJOY_PY_CONST(module, BTN_3);
    VJOY_PY_CONST(module, BTN_4);
    VJOY_PY_CONST(module, BTN_5);
    VJOY_PY_CONST(module, BTN_6);
    VJOY_PY_CONST(module, BTN_7);
    VJOY_PY_CONST(module, BTN_8);
    VJOY_PY_CONST(module, BTN_9);

    VJOY_PY_CONST(module, BTN_MOUSE);
    VJOY_PY_CONST(module, BTN_LEFT);
    VJOY_PY_CONST(module, BTN_RIGHT);
    VJOY_PY_CONST(module, BTN_MIDDLE);
    VJOY_PY_CONST(module, BTN_SIDE);
    VJOY_PY_CONST(module, BTN_EXTRA);
    VJOY_PY_CONST(module, BTN_FORWARD);
    VJOY_PY_CONST(module, BTN_BACK);
    VJOY_PY_CONST(module, BTN_TASK);

    VJOY_PY_CONST(module, BTN_JOYSTICK);
    VJOY_PY_CONST(module, BTN_TRIGGER);
    VJOY_PY_CONST(module, BTN_THUMB);
    VJOY_PY_CONST(module, BTN_THUMB2);
    VJOY_PY_CONST(module, BTN_TOP);
    VJOY_PY_CONST(module, BTN_TOP2);
    VJOY_PY_CONST(module, BTN_PINKIE);
    VJOY_PY_CONST(module, BTN_BASE);
    VJOY_PY_CONST(module, BTN_BASE2);
    VJOY_PY_CONST(module, BTN_BASE3);
    VJOY_PY_CONST(module, BTN_BASE4);
    VJOY_PY_CONST(module, BTN_BASE5);
    VJOY_PY_CONST(module, BTN_BASE6);
    VJOY_PY_CONST(module, BTN_DEAD);

    VJOY_PY_CONST(module, BTN_GAMEPAD);
    VJOY_PY_CONST(module, BTN_A);
    VJOY_PY_CONST(module, BTN_B);
    VJOY_PY_CONST(module, BTN_C);
    VJOY_PY_CONST(module, BTN_X);
    VJOY_PY_CONST(module, BTN_Y);
    VJOY_PY_CONST(module, BTN_Z);
    VJOY_PY_CONST(module, BTN_TL);
    VJOY_PY_CONST(module, BTN_TR);
    VJOY_PY_CONST(module, BTN_TL2);
    VJOY_PY_CONST(module, BTN_TR2);
    VJOY_PY_CONST(module, BTN_SELECT);
    VJOY_PY_CONST(module, BTN_START);
    VJOY_PY_CONST(module, BTN_MODE);
    VJOY_PY_CONST(module, BTN_THUMBL);
    VJOY_PY_CONST(module, BTN_THUMBR);

    VJOY_PY_CONST(module, BTN_DIGI);
    VJOY_PY_CONST(module, BTN_TOOL_PEN);
    VJOY_PY_CONST(module, BTN_TOOL_RUBBER);
    VJOY_PY_CONST(module, BTN_TOOL_BRUSH);
    VJOY_PY_CONST(module, BTN_TOOL_PENCIL);
    VJOY_PY_CONST(module, BTN_TOOL_AIRBRUSH);
    VJOY_PY_CONST(module, BTN_TOOL_FINGER);
    VJOY_PY_CONST(module, BTN_TOOL_MOUSE);
    VJOY_PY_CONST(module, BTN_TOOL_LENS);
    VJOY_PY_CONST(module, BTN_TOUCH);
    VJOY_PY_CONST(module, BTN_STYLUS);
    VJOY_PY_CONST(module, BTN_STYLUS);
    VJOY_PY_CONST(module, BTN_TOOL_DOUBLETAP);
    VJOY_PY_CONST(module, BTN_TOOL_TRIPLETAP);

    VJOY_PY_CONST(module, BTN_WHEEL);
    VJOY_PY_CONST(module, BTN_GEAR_DOWN);
    VJOY_PY_CONST(module, BTN_GEAR_UP);

    /* There are many, _many_ more keys, but my hands 
     * are starting to cramp up.   ;_;
     */

    VJOY_PY_CONST(module, REL_X);
    VJOY_PY_CONST(module, REL_Y);
    VJOY_PY_CONST(module, REL_Z);
    VJOY_PY_CONST(module, REL_RX);
    VJOY_PY_CONST(module, REL_RY);
    VJOY_PY_CONST(module, REL_RZ);
    VJOY_PY_CONST(module, REL_HWHEEL);
    VJOY_PY_CONST(module, REL_DIAL);
    VJOY_PY_CONST(module, REL_WHEEL);
    VJOY_PY_CONST(module, REL_MISC);

    VJOY_PY_CONST(module, ABS_X);
    VJOY_PY_CONST(module, ABS_Y);
    VJOY_PY_CONST(module, ABS_Z);
    VJOY_PY_CONST(module, ABS_RX);
    VJOY_PY_CONST(module, ABS_RY);
    VJOY_PY_CONST(module, ABS_RZ);
    VJOY_PY_CONST(module, ABS_THROTTLE);
    VJOY_PY_CONST(module, ABS_RUDDER);
    VJOY_PY_CONST(module, ABS_WHEEL);
    VJOY_PY_CONST(module, ABS_GAS);
    VJOY_PY_CONST(module, ABS_BRAKE);
    VJOY_PY_CONST(module, ABS_HAT0X);
    VJOY_PY_CONST(module, ABS_HAT0Y);
    VJOY_PY_CONST(module, ABS_HAT1X);
    VJOY_PY_CONST(module, ABS_HAT1Y);
    VJOY_PY_CONST(module, ABS_HAT2X);
    VJOY_PY_CONST(module, ABS_HAT2Y);
    VJOY_PY_CONST(module, ABS_HAT3X);
    VJOY_PY_CONST(module, ABS_HAT3Y);
    VJOY_PY_CONST(module, ABS_PRESSURE);
    VJOY_PY_CONST(module, ABS_DISTANCE);
    VJOY_PY_CONST(module, ABS_TILT_X);
    VJOY_PY_CONST(module, ABS_TILT_Y);
    VJOY_PY_CONST(module, ABS_TOOL_WIDTH);
    VJOY_PY_CONST(module, ABS_VOLUME);
    VJOY_PY_CONST(module, ABS_MISC);

    VJOY_PY_CONST(module, FF_STATUS_STOPPED);
    VJOY_PY_CONST(module, FF_STATUS_PLAYING);
    VJOY_PY_CONST(module, FF_STATUS_MAX);

    VJOY_PY_CONST(module, FF_RUMBLE);
    VJOY_PY_CONST(module, FF_PERIODIC);
    VJOY_PY_CONST(module, FF_CONSTANT);
    VJOY_PY_CONST(module, FF_SPRING);
    VJOY_PY_CONST(module, FF_FRICTION);
    VJOY_PY_CONST(module, FF_DAMPER);
    VJOY_PY_CONST(module, FF_INERTIA);
    VJOY_PY_CONST(module, FF_RAMP);

    VJOY_PY_CONST(module, FF_SQUARE);
    VJOY_PY_CONST(module, FF_TRIANGLE);
    VJOY_PY_CONST(module, FF_SINE);
    VJOY_PY_CONST(module, FF_SAW_UP);
    VJOY_PY_CONST(module, FF_SAW_DOWN);
    VJOY_PY_CONST(module, FF_CUSTOM);

    VJOY_PY_CONST(module, FF_GAIN);
    VJOY_PY_CONST(module, FF_AUTOCENTER);
}
