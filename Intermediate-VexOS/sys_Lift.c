// sys_Drive.c : implementation file
#include "Subsystem.h"
#include "Hardware.h"
#include "Robot.h"

DefineSubsystem(Lift);

#define KP 0.5
#define KI 0.0
#define KD 0.3

static MotorGroup* leftMotor;
static MotorGroup* rightMotor;
static LiftPosition position;

static DebugValue* lValue;
static DebugValue* rValue;
static DebugValue* liftPos;

static void setPosition(LiftPosition pos) {
    position = pos;
    MotorGroup_setSetpoint(leftMotor,  -position);
    MotorGroup_setSetpoint(rightMotor, position);
}

static void debugUpdate(EventType type, void* state) {
    DebugValue_set(lValue, MotorGroup_getPosition(leftMotor));
    DebugValue_set(rValue, MotorGroup_getPosition(rightMotor));
    DebugValue_set(liftPos, (position == LiftPosition_Trough)? "Trough":
                            (position == LiftPosition_Descore)? "Descore": "Ground");
    // FIXME //
    //Power power = Joystick_getX(_joystick, JoystickHand_Left);
    //MotorGroup_setPower(leftMotor,  power);
    //MotorGroup_setPower(rightMotor, power);
}

static void constructor() {
    lValue  = DebugValue_new("left lift",  DebugValueType_Float);
    rValue  = DebugValue_new("right lift", DebugValueType_Float);
    liftPos = DebugValue_new("lift pos", DebugValueType_String);
    VexOS_addEventHandler(EventType_OperatorPeriodic, debugUpdate, NULL);

    leftMotor = MotorGroup_new("left lift");
    MotorGroup_addWithIME(leftMotor, "left lift", PWMPort_7, MotorType_393_HT, true, 4);
    MotorGroup_setPID(leftMotor, KP, KI, KD);
    MotorGroup_setOutputScaleFactor(leftMotor, 12.0 / 84.0);
    //MotorGroup_setFeedbackEnabled(leftMotor, true);
    MotorGroup_setPIDEnabled(leftMotor, true);

    rightMotor = MotorGroup_new("right lift");
    MotorGroup_addWithIME(rightMotor, "right lift", PWMPort_4, MotorType_393_HT, false, 3); 
    MotorGroup_setPID(rightMotor, KP, KI, KD);
    MotorGroup_setOutputScaleFactor(rightMotor, 12.0 / 84.0);
    //MotorGroup_setFeedbackEnabled(rightMotor, true);
    MotorGroup_setPIDEnabled(rightMotor, true);

    setPosition(LiftPosition_Ground);
}

static void initDefaultCommand() { }

// TODO: add user code here

LiftPosition Lift_getPosition() {
    return position;
}

void Lift_setPosition(LiftPosition pos) {
    setPosition(pos);
}
