import vjoy, struct, serial

B_SQUARE   = 0x00
B_CROSS    = 0x01
B_CIRCLE   = 0x02
B_TRIANGLE = 0x03
B_R2       = 0x04
B_R3       = 0x05
B_L3       = 0x06
B_R1       = 0x07
B_L2       = 0x08
B_L1       = 0x09
B_START    = 0x0A
B_DOWN     = 0x0B
B_SELECT   = 0x0C
B_UP       = 0x0D
B_LEFT     = 0x0E
B_RIGHT    = 0x0F

sdata = serial.Serial('/dev/ttyUSB0', 115200)

def getVJoyInfo():
	return {
		'name':     'PSX DualShock',
		'relaxis':  [],
		'absaxis':  [vjoy.ABS_X, vjoy.ABS_Y, vjoy.ABS_RX, vjoy.ABS_RY],
		'feedback': [],
		'buttons':  [vjoy.KEY_LEFT,   vjoy.KEY_RIGHT, vjoy.KEY_UP,
		             vjoy.KEY_DOWN,   vjoy.BTN_A,     vjoy.BTN_B,
		             vjoy.BTN_X,      vjoy.BTN_Y,     vjoy.BTN_TL,
		             vjoy.BTN_TR,     vjoy.BTN_TL2,   vjoy.BTN_TR2,
		             vjoy.BTN_SELECT, vjoy.BTN_START, vjoy.BTN_THUMBL,
		             vjoy.BTN_THUMBR]
	}

def remap(x):
	x = (x-512)*64
	if x > 32767:
		x = 32767
	elif x < -32768:
		x = -32768
	return x

def checkBtn(buttons, code):
	if (buttons & (1 << code)) > 0:
		return True
	return False

def doVJoyThink():
	sdata.flushInput()
	sdata.write('\x01')
	data = sdata.read(10)
	buttons, joy_l_y, joy_l_x, joy_r_y, joy_r_x = struct.unpack('<HHHHH', data)

	vjoy.send_event(VJoyID, vjoy.EV_ABS, vjoy.ABS_RX,     remap(joy_r_x))
	vjoy.send_event(VJoyID, vjoy.EV_ABS, vjoy.ABS_RY,     remap(joy_r_y))
	vjoy.send_event(VJoyID, vjoy.EV_ABS, vjoy.ABS_X,      remap(joy_l_x))
	vjoy.send_event(VJoyID, vjoy.EV_ABS, vjoy.ABS_Y,      remap(joy_l_y))

	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_X,      checkBtn(buttons, B_SQUARE))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_Y,      checkBtn(buttons, B_TRIANGLE))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_A,      checkBtn(buttons, B_CROSS))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_B,      checkBtn(buttons, B_CIRCLE))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.KEY_LEFT,   checkBtn(buttons, B_LEFT))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.KEY_RIGHT,  checkBtn(buttons, B_RIGHT))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.KEY_UP,     checkBtn(buttons, B_UP))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.KEY_DOWN,   checkBtn(buttons, B_DOWN))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_START,  checkBtn(buttons, B_START))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_SELECT, checkBtn(buttons, B_SELECT))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_TL,     checkBtn(buttons, B_L1))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_TR,     checkBtn(buttons, B_R1))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_TL2,    checkBtn(buttons, B_L2))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_TR2,    checkBtn(buttons, B_R2))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_THUMBL, checkBtn(buttons, B_L3))
	vjoy.send_event(VJoyID, vjoy.EV_KEY, vjoy.BTN_THUMBR, checkBtn(buttons, B_R3))









