// Arm.c : implementation file
#include "Main.h"
#include "ArmControl.h"
#include "Motor.h"
#include "AutoControl.h"

#define ARM_kP 0.75
#define ARM_kI 0
#define ARM_kD 0.3
#define ARM_pidTOL 36

//ARM_RESET_STATE armResetState = STOP_PID;

long getArmIMEdegrees(unsigned char motorPort) {
    long encVal = GetIntegratedMotorEncoder(motorPort);
    return encVal * 360/627;
}

void printArmIMEdegrees() {
    PrintToScreen("%d\n", getArmIMEdegrees(armL));
}

/*ARM_RESET_STATE getArmResetState() {
    return armResetState;
}

void SetArmResetState(ARM_RESET_STATE state) {
    armResetState = state;   
}*/

void ArmResetStateMachine() {
//    switch(armResetState) {
 //       case STOP_PID:
            StopIntegratedMotorEncoderPID(armR);
            StopIntegratedMotorEncoderPID(armL);
//            armResetState = LOWER_ARM;
//            break;
//        case LOWER_ARM:
            while(GetDigitalInput(armResetSwitch)
                && GetJoystickDigital (1, 7, 2)){
                SetArm(-75);
            }
            WaitInMsec(150);
//            armResetState = START_PID;
//            break;
//        case START_PID:
            PresetIntegratedMotorEncoder(armR, 0);
            PresetIntegratedMotorEncoder(armL, 0);
            StartIntegratedMotorEncoderPID(armR, 0); 
            StartIntegratedMotorEncoderPID(armL, 0);
            SetArmState(GROUND);
//            armResetState = DONE;
//            break;
//        case DONE:
//            break;
//    }
}
//const long ArmPositions [3] = {0, 75, 90};

static long degreesToIMEticks(long degrees){
    return (degrees * 392 * (5 * 5))/360;
}

void InitArm() {
    long groundTicks = degreesToIMEticks(ArmState);
    PresetIntegratedMotorEncoder(armL, groundTicks);
    PresetIntegratedMotorEncoder(armR, groundTicks);
    DefineIntegratedMotorEncoderPID(armR, ARM_kP, ARM_kI, ARM_kD, ARM_pidTOL); 
    DefineIntegratedMotorEncoderPID(armL, ARM_kP, ARM_kI, ARM_kD, ARM_pidTOL);
    StartIntegratedMotorEncoderPID(armR, groundTicks); 
    StartIntegratedMotorEncoderPID(armL, groundTicks);

    ArmState = GROUND;
}

static void setArmPID() {
    long armDegrees = ArmState;
    long armPIDPosition = degreesToIMEticks(armDegrees);

    PrintToScreen("SetArmPID: %d, %d\n", armDegrees, armPIDPosition); 
    UpdateSetpointIntegratedMotorEncoderPID(armL, armPIDPosition); 
    UpdateSetpointIntegratedMotorEncoderPID(armR, -armPIDPosition);
}

void SetArmState(ARM_STATES state) {
    ArmState = state;
    setArmPID();
}

void ArmDecrement() {
    if(ArmState == GROUND) 
        return;
    if(ArmState == TROUGH)
        ArmState = GROUND;
    if(ArmState == DESCORE)
        ArmState = TROUGH;
    setArmPID();
}

void ArmIncrement() {
    if(ArmState == DESCORE) 
        return;
    if(ArmState == TROUGH)
        ArmState = DESCORE;
    if(ArmState == GROUND)
        ArmState = TROUGH;
    setArmPID();
}

void DebugArm() {
    long l, r;
    l = GetIntegratedMotorEncoder(armL); 
    r = GetIntegratedMotorEncoder(armR);
    PrintToScreen("arm encs: %ld, %ld\n", l, r);
}




