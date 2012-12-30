// sys_Drive.c : implementation file
#include "Subsystem.h"
#include "Hardware.h"
#include "Robot.h"

DefineSubsystem(Lift);

#define KP 0.75
#define KI 0.0
#define KD 0.3

static MotorGroup* leftMotor;
static MotorGroup* rightMotor;
static DigitalIn*  homeSwitch;

static LiftPosition position;

/*static DebugValue* lValue;
static DebugValue* rValue;
static DebugValue* homeSw;
static DebugValue* liftPos;*/

static void setPosition(LiftPosition pos) {
    position = pos;
    MotorGroup_setSetpoint(leftMotor,  position);
    MotorGroup_setSetpoint(rightMotor, position);
}

/*static void debugUpdate(EventType type, void* state) {
    DebugValue_set(lValue, MotorGroup_getPosition(leftMotor));
    DebugValue_set(rValue, MotorGroup_getPosition(rightMotor));
    DebugValue_set(homeSw, DigitalIn_get(homeSwitch));
    DebugValue_set(liftPos, (position == LiftPosition_Trough)? "Trough":
                            (position == LiftPosition_Descore)? "Descore": "Ground");
}*/

static void constructor() {
    /*lValue  = DebugValue_new("left lift",  DebugValueType_Float);
    rValue  = DebugValue_new("right lift", DebugValueType_Float);
    homeSw  = DebugValue_new("lift home", DebugValueType_Bool);
    liftPos = DebugValue_new("lift pos", DebugValueType_String);
    VexOS_addEventHandler(EventType_OperatorPeriodic, debugUpdate, NULL);*/

    leftMotor = MotorGroup_new("left lift");
    MotorGroup_addWithIME(leftMotor, "left lift", PWMPort_2, MotorType_393_HS, false, 2);
    MotorGroup_setOutputScaleFactor(leftMotor, (12.0 / 60.0) * (12.0 / 60.0));

    rightMotor = MotorGroup_new("right lift");
    MotorGroup_addWithIME(rightMotor, "right lift", PWMPort_1, MotorType_393_HS, true, 1); 
    MotorGroup_setOutputScaleFactor(rightMotor, (12.0 / 60.0) * (12.0 / 60.0));

    homeSwitch = DigitalIn_newLimit("home switch", DigitalPort_7);
}

static void initialize() { 
    MotorGroup_setPID(leftMotor,  KP, KI, KD);
    MotorGroup_setTolerance(leftMotor, 1.0);
    MotorGroup_setPID(rightMotor, KP, KI, KD);
    MotorGroup_setTolerance(rightMotor, 1.0);
    //MotorGroup_setFeedbackEnabled(leftMotor,  true);
    //MotorGroup_setFeedbackEnabled(rightMotor, true);

    setPosition(LiftPosition_Ground);
    MotorGroup_setPIDEnabled(leftMotor,  true);
    MotorGroup_setPIDEnabled(rightMotor, true);
}

// TODO: add user code here

LiftPosition Lift_getPosition() {
    return position;
}

void Lift_setPosition(LiftPosition pos) {
    setPosition(pos);
}

bool Lift_onTarget() {
    return MotorGroup_onTarget(leftMotor)
        && MotorGroup_onTarget(rightMotor);
}

bool Lift_getHomeSwitch() {
    return DigitalIn_get(homeSwitch);
}

void Lift_setPower(Power power) {
    MotorGroup_setPower(leftMotor,  power);
    MotorGroup_setPower(rightMotor, power);
}

void Lift_reset() {
    MotorGroup_presetPosition(leftMotor,  LiftPosition_Ground);
    MotorGroup_presetPosition(rightMotor, LiftPosition_Ground);
    position = LiftPosition_Ground;
    if(  !MotorGroup_isPIDEnabled(leftMotor) 
      || !MotorGroup_isPIDEnabled(rightMotor)) 
    {
        MotorGroup_setPIDEnabled(leftMotor,  true);
        MotorGroup_setPIDEnabled(rightMotor, true);
    }
}

