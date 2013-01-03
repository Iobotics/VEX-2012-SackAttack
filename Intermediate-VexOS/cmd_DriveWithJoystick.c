// cmd_DriveWithJoystick.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(DriveWithJoystick, { });

static void constructor(va_list argp) {
    require(&Drive);
}

static void initialize() { }

static void execute() {
    Power lPower = Joystick_getY(_joystick, JoystickHand_Left);
    Power rPower = Joystick_getY(_joystick, JoystickHand_Right);
    if(_scaler) {
        lPower = PowerScaler_get(_scaler, lPower);
        rPower = PowerScaler_get(_scaler, rPower);
    }
    Drive_setPower(lPower, rPower);
}

static bool isFinished() {
    return false;
}

static void end() { 
    Drive_setPower(0, 0);
}

static void interrupted() { }

// TODO: add user code here



