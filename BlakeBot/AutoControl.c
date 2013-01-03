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

//Controls the button switching for autonomous.
AUTO_MODE SetAuto() {
    //if(!GetDigitalInput(lowGoal)) {return LOW_GOAL;}
    //if(!GetDigitalInput(centerGoal)) {return CENTER_GOAL;}
    //if(!GetDigitalInput(isoPickup)) {return ISO_PICKUP;}
    //if(!GetDigitalInput(isoBlock)) {return ISO_BLOCK;}
    //if(!GetDigitalInput(centerBlock)) {return CENTER_BLOCK;}
    return WAIT;
}

// autonomous command to set the intake and arm to specific states
void SetScorer(ARM_STATES armStateAuto, INTAKE_STATES intakeStateAuto) {
    //if(!IsAutoActive()) return;
    SetIntake(intakeStateAuto);
    SetArmState(armStateAuto);
    PrintToScreen("armState: %d", ArmState); 
}

//Converts inches to be travelled by bot into big IME (high torque)
//ticks for drive PID when going forward.
/*long inchesToIMETicks(float inches) {
    return (long) (inches * ENCODER_TO_WHEEL_RATIO * ENCODER_TICKS_PER_ROTATION
        / (3.141 * WHEEL_DM));
}*/

//Converts degrees that the bot will turn into big IME (high torque)
//ticks for drive PID when turning.
long degreesToIMETicks(float degrees) {
    return (long) (degrees * DRIVE_BASE_DM * ENCODER_TO_WHEEL_RATIO 
        * ENCODER_TICKS_PER_ROTATION / (360 * WHEEL_DM));
}

int driveOnTarget() {
    return (OnTargetIntegratedMotorEncoderPID(driveLIME)
        && OnTargetIntegratedMotorEncoderPID(driveRIME));
}

int getIMEPIDPower(unsigned char motor) {
    unsigned char unusedChar;
    long unusedLong; // needed to fill in the IME_GetPIDControlData params
    int power;
    IME_GetPIDControlData(motor, &unusedChar, &unusedLong, 
        &power, &unusedLong, &unusedLong, &unusedLong);
    return power;
}

/*unsigned char tripWatch;
void driveStateMachine() {
    switch(driveState) {
        case FORWARD: //sets PID to perform forward move
            distance = inchesToIMETicks(distance);
            PresetIntegratedMotorEncoder(driveRIME,0);
            PresetIntegratedMotorEncoder(driveLIME,0);
            UpdateSetpointIntegratedMotorEncoderPID (driveRIME, -distance);
            UpdateSetpointIntegratedMotorEncoderPID (driveLIME, distance);
            driveState = EXECUTE_MOVE;
            break;
        case TURN: //sets PID to perform turn move
            distance = degreesToIMETicks(distance); 
            PresetIntegratedMotorEncoder(driveRIME,0);
            PresetIntegratedMotorEncoder(driveLIME,0);
            UpdateSetpointIntegratedMotorEncoderPID (driveRIME,  distance);
            UpdateSetpointIntegratedMotorEncoderPID (driveLIME,   distance);
            driveState = EXECUTE_MOVE;
            break;
        case EXECUTE_MOVE: //performs move
            if(!driveOnTarget()){
                SetRegularDriveMotors(getIMEPIDPower(driveLIME), 
                    getIMEPIDPower(driveRIME));
                
                // stall detection //
                float lspeed = GetIntegratedMotorEncoderSpeed(driveLIME);
                float rspeed = GetIntegratedMotorEncoderSpeed(driveRIME);
                if(Abs(lspeed) < TRIP_THRESHOLD || Abs(rspeed) < TRIP_THRESHOLD) {
                    if(tripWatch) {
                        if(GetTimer(TRIP_TIMER) > TRIP_WAIT) {
                            driveState = STOP;
                            autoAbort  = 1;
                            StopTimer(TRIP_TIMER);
                            SetRegularDriveMotors(0,0);
                        }
                    } else {
                        tripWatch = 1;
                        PresetTimer(TRIP_TIMER, 0);
                        StartTimer(TRIP_TIMER);
                    }
                } else {
                    StopTimer(TRIP_TIMER);
                    tripWatch = 0;
                }
            }
            else {
                driveState = CORRECT;
                StartTimer(1); //starts timer for correcting moves
            }
            break;
        case CORRECT: //gives robot time to adjust
            if(GetTimer(1) > DRIVE_CORRECTION_TIME) {
                StopTimer(1);
                driveState = STOP;
            }
            else {
                SetRegularDriveMotors(getIMEPIDPower(driveLIME), 
                    getIMEPIDPower(driveRIME));    
            }
            break;
        case STOP:
            break;
    }
}

// drive motor FSM interface.  sets the FSM machine state and distance
void Move(DRIVE_STATE state, float dist) {
    driveState = state;
    distance   = dist; 
    while(driveState != STOP && IsAutoActive()) {
        driveStateMachine();
    }
}*/

void WaitInMsec(unsigned long msec) {
    unsigned long stopTime = GetMsClock() + msec;
    while ((GetMsClock() < stopTime) && IsAutoActive()) {
    }   
}

void WaitForTouch() {
    int pressed = !GetDigitalInput(button);
    while(pressed == 1 && IsAutoActive()) {
        SetDrive(0,0);
    }
    PrintToScreen ("Pressed!\n");
}

void waitForArm() {
    while(!ArmOnTarget() && IsAutoActive()) {
        SetRegularDriveMotors(getIMEPIDPower(driveLIME), 
                    getIMEPIDPower(driveRIME));
    }
}

void waitForTime(float seconds) {
    while(GetTimer(GAME_TIMER) < (seconds * 1000) && IsAutoActive()) {
        SetRegularDriveMotors(getIMEPIDPower(driveLIME), 
                    getIMEPIDPower(driveRIME));
    }
}

void SaveState() {
    SetSaveCompetitionIme(armL);
    SetSaveCompetitionIme(armR);
    GlobalData(GDATA_ARM) = ArmState;
    PrintToScreen("save: %d, %d\n", ArmState);
}

void RestoreState(long *encR, long *encL) {
    ArmState = GlobalData(GDATA_ARM);
    *encR = GetSavedCompetitionIme(armR);
    *encL = GetSavedCompetitionIme(armL);
    PrintToScreen("restore: %d, %d\n", ArmState);
}

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

void ResetArmEncoders() {       //asdfadsf
    SetArm(-75);
    while(GetDigitalInput(armResetSwitch)){
    }
    PresetIntegratedMotorEncoder(armR, 0);
    PresetIntegratedMotorEncoder(armL, 0);
}

void AutonomousStartUp() {
    StartTimer(GAME_TIMER); //starts game timer
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














