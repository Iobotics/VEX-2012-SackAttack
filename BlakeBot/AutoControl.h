#ifndef _AUTO_H
#define _AUTO_H

#include "ArmControl.h"
#include "UserInclude.h"

// AutoControl.h : header file
typedef enum {
    FORWARD,
    TURN,
    EXECUTE_MOVE,
    CORRECT,
    STOP 
} DRIVE_STATE;

typedef enum {
    CENTER_BLOCK,
    ISO_BLOCK,
    ISO_PICKUP,
    LOW_GOAL,
    CENTER_GOAL,
    WAIT
} AUTO_MODE;

int         IsAutoActive();
void        AutonomousStartUp();
void        ResetArmEncoders();
void        AutonomousEnd();
AUTO_MODE   SetAuto();
void        Move(DRIVE_STATE state, float dist);
void        SetScorer(ARM_STATES armStateAuto, INTAKE_STATES intakeStateAuto);
//void        driveStateMachine();
//int         driveOnTarget();
//int         getIMEPIDPower(unsigned char motor);
//long        inchesToIMETicks(float inches);
//long        degreesToIMETicks(float degrees);
int         ArmOnTarget();
void        WaitForTouch();
void        WaitInMsec(unsigned long msec);
//void        waitForArm();
//void        waitForTime(float seconds);
void        SaveState();
void        RestoreState(long *encR, long *encL);
void        SetRunningMode(MODE_TYPE mode);
MODE_TYPE   GetLastMode();

#endif





