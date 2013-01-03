// Robot.h : header file
#ifndef ROBOT_H_
#define ROBOT_H_

#include "VexOS.h"

// global variables //
extern Joystick*    _joystick;
extern PowerScaler* _scaler;

// subsystems //
DeclareSubsystem(Drive);
void Drive_setPower(Power left, Power right);

DeclareSubsystem(Lift);
typedef enum {
    LiftPosition_Ground  = 0,
    LiftPosition_Trough  = 45,
    LiftPosition_Descore = 90
} LiftPosition;
LiftPosition Lift_getPosition();
void Lift_setPosition(LiftPosition);

DeclareSubsystem(Intake);
typedef enum {
    IntakeDirection_Stop,
    IntakeDirection_Suck,
    IntakeDirection_Blow
} IntakeDirection;
void Intake_setDirection(IntakeDirection);

// commands //
DeclareCommandClass(DriveWithJoystick);
DeclareCommandClass(IntakeSet);
DeclareCommandClass(LiftSet);
DeclareCommandClass(LiftJog);

#endif // ROBOT_H_

