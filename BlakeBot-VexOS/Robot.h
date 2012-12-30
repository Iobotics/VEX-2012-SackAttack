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
void Drive_startMove(float distance);
void Drive_startTurn(float angle);
bool Drive_isDone();
void Drive_end();

DeclareSubsystem(Lift);
typedef enum {
    LiftPosition_Ground  = 0,
    LiftPosition_Trough  = 85,
    LiftPosition_Descore = 105
} LiftPosition;
LiftPosition Lift_getPosition();
void Lift_setPosition(LiftPosition);
bool Lift_onTarget();
void Lift_setPower(Power power);
bool Lift_getHomeSwitch();
void Lift_reset();

DeclareSubsystem(Intake);
typedef enum {
    IntakeDirection_Stop,
    IntakeDirection_Suck,
    IntakeDirection_Blow
} IntakeDirection;
void Intake_setDirection(IntakeDirection);

DeclareSubsystem(Pivot);
typedef enum {
    PivotPosition_Up,
    PivotPosition_Down
} PivotPosition;
void Pivot_setPosition(PivotPosition);

// commands //
DeclareCommandClass(DriveWithJoystick);
DeclareCommandClass(AutoDrive);
DeclareCommandClass(AutoTurn);
DeclareCommandClass(LiftSet);
DeclareCommandClass(LiftJog);
DeclareCommandClass(LiftHome);
DeclareCommandClass(IntakeSet);
DeclareCommandClass(PivotSet);

#endif // ROBOT_H_




