// sys_Drive.c : implementation file
#include "Subsystem.h"
#include "Hardware.h"
#include "Robot.h"

DefineSubsystem(Drive);

static MotorGroup* leftMotors;
static MotorGroup* rightMotors;

static DebugValue* lValue;
static DebugValue* rValue;

static void debugUpdate(EventType type, void* state) {
    DebugValue_set(lValue, MotorGroup_getPosition(leftMotors));
    DebugValue_set(rValue, MotorGroup_getPosition(rightMotors));
}

static void constructor() {
    lValue = DebugValue_new("left drive",  DebugValueType_Float);
    rValue = DebugValue_new("right drive", DebugValueType_Float);
    VexOS_addEventHandler(EventType_OperatorPeriodic, debugUpdate, NULL);

    leftMotors = MotorGroup_new("left");
    MotorGroup_addWithIME(leftMotors, "left top", PWMPort_10, MotorType_393_HT, true, 1);
    MotorGroup_add(leftMotors, "left middle", PWMPort_9, MotorType_393_HT, false);
    MotorGroup_add(leftMotors, "left middle", PWMPort_8, MotorType_393_HT, true);
    MotorGroup_setFeedbackEnabled(leftMotors, true);

    rightMotors = MotorGroup_new("right");
    MotorGroup_addWithIME(rightMotors, "right top", PWMPort_1, MotorType_393_HT, false, 2);
    MotorGroup_add(rightMotors, "right middle", PWMPort_2, MotorType_393_HT, true);
    MotorGroup_add(rightMotors, "right middle", PWMPort_3, MotorType_393_HT, false);
    MotorGroup_setFeedbackEnabled(rightMotors, true);
}

static void initDefaultCommand() {
    setDefaultCommand(Command_new(&DriveWithJoystick));
}

// TODO: add user code here

void Drive_setPower(Power left, Power right) {
    MotorGroup_setPower(leftMotors, left);
    MotorGroup_setPower(rightMotors, right);
}




