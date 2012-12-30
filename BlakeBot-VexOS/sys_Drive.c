// sys_Drive.c : implementation file
#include "Subsystem.h"
#include "Hardware.h"
#include "Robot.h"

DefineSubsystem(Drive);

#define KP 1.0
#define KI 0.0
#define KD 0.3

static MotorGroup* leftMotors;
static MotorGroup* rightMotors;

/*static DebugValue* lValue;
static DebugValue* rValue;

static void debugUpdate(EventType type, void* state) {
    DebugValue_set(lValue, MotorGroup_getPosition(leftMotors));
    DebugValue_set(rValue, MotorGroup_getPosition(rightMotors));
}*/

#define DRIVE_WIDTH 16

static void constructor() {
    /*lValue = DebugValue_new("left drive",  DebugValueType_Float);
    rValue = DebugValue_new("right drive", DebugValueType_Float);
    VexOS_addEventHandler(EventType_OperatorPeriodic, debugUpdate, NULL);*/

    leftMotors = MotorGroup_new("left");
    MotorGroup_add(leftMotors, "left top", PWMPort_6, MotorType_393_HT, true);
    MotorGroup_add(leftMotors, "left middle", PWMPort_3, MotorType_393_HT, false);
    MotorGroup_addWithIME(leftMotors, "left bottom", PWMPort_4, MotorType_393_HT, true, 3);
    MotorGroup_setOutputScaleFactor(leftMotors, 4.0 * (M_PI / 360.0));

    rightMotors = MotorGroup_new("right");
    MotorGroup_add(rightMotors, "right top", PWMPort_5, MotorType_393_HT, false);
    MotorGroup_add(rightMotors, "right middle", PWMPort_9, MotorType_393_HT, true);
    MotorGroup_addWithIME(rightMotors, "right bottom", PWMPort_10, MotorType_393_HT, false, 4);
    MotorGroup_setOutputScaleFactor(rightMotors, 4.0 * (M_PI / 360.0));
}

static void initialize() {
    setDefaultCommand(Command_new(&DriveWithJoystick));

    MotorGroup_setPID(leftMotors,  KP, KI, KD);
    MotorGroup_setTolerance(leftMotors, 0.25);
    MotorGroup_setPID(rightMotors, KP, KI, KD);
    MotorGroup_setTolerance(rightMotors, 0.25);

    MotorGroup_setFeedbackEnabled(leftMotors,  true);
    MotorGroup_setFeedbackEnabled(rightMotors, true);
}

// TODO: add user code here

void Drive_setPower(Power left, Power right) {
    MotorGroup_setPower(leftMotors, left);
    MotorGroup_setPower(rightMotors, right);
}

void Drive_startMove(float distance) {
    MotorGroup_presetPosition(leftMotors,  0.0);
    MotorGroup_presetPosition(rightMotors, 0.0);
    
    // set the setpoints for drive //
    MotorGroup_setSetpoint(leftMotors,  distance);
    MotorGroup_setSetpoint(rightMotors, distance);

    // enable PID //
    MotorGroup_setPIDEnabled(leftMotors,  true);
    MotorGroup_setPIDEnabled(rightMotors, true);
}

void Drive_startTurn(float angle) {
    MotorGroup_presetPosition(leftMotors,  0.0);
    MotorGroup_presetPosition(rightMotors, 0.0);

    // set the setpoints for turn (counter-clockwise) //
    float distance = angle * M_PI * DRIVE_WIDTH / 360.0;
    MotorGroup_setSetpoint(leftMotors,  -distance);
    MotorGroup_setSetpoint(rightMotors, distance);

    // enabled PID //
    MotorGroup_setPIDEnabled(leftMotors,  true);
    MotorGroup_setPIDEnabled(rightMotors, true);
}

bool Drive_isDone() {
    return MotorGroup_onTarget(leftMotors)
        && MotorGroup_onTarget(rightMotors);
}

void Drive_end() {
    MotorGroup_setPIDEnabled(leftMotors,  false);
    MotorGroup_setPIDEnabled(rightMotors, false);
}
