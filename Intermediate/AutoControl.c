// AutoControl.c : implementation file
#include "Main.h"
#include "Motor.h"
#include "AutoControl.h"
#include "ArmControl.h"

DRIVE_STATE driveState = FORWARD;
long        distance   = 0;
unsigned char autoAbort;
unsigned char tripWatch;

int IsAutoActive() {
    #if RUN_AUTONOMOUS
        return !autoAbort && (GetTimer(GAME_TIMER) < AUTO_END_MILLIS);
    #else
        return 1;
    #endif
}

void AutonomousEnd() {
    StopTimer(GAME_TIMER);
}

AUTO_MODE SetAuto() {
    return WAIT;
}

void SetScorer(ARM_STATES armStateAuto, INTAKE_STATES intakeStateAuto) {
    //if(!IsAutoActive()) return;
    SetIntake(intakeStateAuto);
    SetArmState(armStateAuto);
    PrintToScreen("armState: %d", ArmState); 
}

void WaitInMsec(unsigned long msec) {
    unsigned long stopTime = GetMsClock() + msec;
    while ((GetMsClock() < stopTime) && IsAutoActive()) {
    }   
}

void SaveState() {
    SetSaveCompetitionIme(armL);
    SetSaveCompetitionIme(armR);
    GlobalData(GDATA_ARM) = ArmState;
    PrintToScreen("save: %d, %d\n", ArmState);
}

/*void RestoreState(long *encR, long *encL) {
    ArmState = GlobalData(GDATA_ARM);
    *encR = GetSavedCompetitionIme(armR);
    *encL = GetSavedCompetitionIme(armL);
    PrintToScreen("restore: %d, %d\n", ArmState);
}
*/
//saves the robot state to be passed from auto to user control
void SetRunningMode(MODE_TYPE mode) {
    GlobalData(GDATA_LAST_MODE) = mode;
    PrintToScreen("run mode: %d\n", mode);
}

//restores robot state from autonomous
MODE_TYPE GetLastMode() {
    MODE_TYPE mode = (MODE_TYPE) GlobalData(GDATA_LAST_MODE);
    PrintToScreen("last mode: %d\n", mode);
    return mode;
}

void ResetArmEncoders() {
    SetArm(-75);
    while(GetDigitalInput(armResetSwitch)){
    }
    PresetIntegratedMotorEncoder(armR, 0);
    PresetIntegratedMotorEncoder(armL, 0);
}

void AutonomousStartUp() {
    StartTimer(GAME_TIMER);
    autoAbort = 0;
    tripWatch = 0;
    SetArmState(GROUND);
    //StartIntegratedMotorEncoderPID(driveRIME, 0);
    //StartIntegratedMotorEncoderPID(driveLIME, 0);
    StartIntegratedMotorEncoderPID(armR, 0); 
    StartIntegratedMotorEncoderPID(armL, 0);
    SetRunningMode(MODE_AUTO);
    //ResetArmEncoders();
}

int ArmOnTarget() {
    if(OnTargetIntegratedMotorEncoderPID(armR) 
        && OnTargetIntegratedMotorEncoderPID(armL)) {
        return 1;
    }
    return 0;
}











