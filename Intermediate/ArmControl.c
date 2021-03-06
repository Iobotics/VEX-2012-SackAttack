// Arm.c : implementation file
#include "Main.h"
#include "ArmControl.h"
#include "Motor.h"
#include "AutoControl.h"

#define ARM_kP 0.75
#define ARM_kI 0
#define ARM_kD 0.3
#define ARM_pidTOL 36

void ArmResetStateMachine() {
    StopIntegratedMotorEncoderPID(armR);
    StopIntegratedMotorEncoderPID(armL);
    while(GetDigitalInput(armResetSwitch) && GetJoystickDigital (1, 7, 2)) {
        SetArm(-75);
    }
    WaitInMsec(150);
    PresetIntegratedMotorEncoder(armR, 0);
    PresetIntegratedMotorEncoder(armL, 0);
    StartIntegratedMotorEncoderPID(armR, 0); 
    StartIntegratedMotorEncoderPID(armL, 0);
    SetArmState(GROUND);
}

static long degreesToIMEticks(long degrees) {
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
    if(ArmState == DESCORE)
        ArmState = GROUND;
    if(ArmState == TROUGH)
        ArmState = DESCORE;
    setArmPID();
}

void ArmIncrement() {
    if(ArmState == TROUGH) 
        return;
    if(ArmState == DESCORE)
        ArmState = TROUGH;
    if(ArmState == GROUND)
        ArmState = DESCORE;
    setArmPID();
}

void DebugArm() {
    long l, r;
    l = GetIntegratedMotorEncoder(armL); 
    r = GetIntegratedMotorEncoder(armR);
    PrintToScreen("arm encs: %ld, %ld\n", l, r);
}







