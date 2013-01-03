// PivotControl.c : implementation file
/*#include "Main.h"
#include "Motor.h"
#include "PivotControl.h"

// TODO: add user code here

#define PIVOT_kP 0.2
#define PIVOT_kI 0
#define PIVOT_kD 0
#define PIVOT_pidTOL 50

static long degreesToIMEticks(long degrees){
    return (degrees * 627 * 9 * 3)/(360 * 5);
}

void InitPivot() {
    PivotDegrees = 0;

    long groundTicks = degreesToIMEticks(PivotDegrees);
    DefineIntegratedMotorEncoderPID(pivotR, PIVOT_kP, PIVOT_kI, PIVOT_kD, PIVOT_pidTOL); 
    DefineIntegratedMotorEncoderPID(pivotL, PIVOT_kP, PIVOT_kI, PIVOT_kD, PIVOT_pidTOL);
    StartIntegratedMotorEncoderPID(pivotR, -groundTicks); 
    StartIntegratedMotorEncoderPID(pivotL, groundTicks);
}

static void setPivotPID(void) {
    long pivotPIDPosition = degreesToIMEticks(PivotDegrees);
    //PrintToScreen("SetPivotPID: %d, %d\n", PivotDegrees, pivotPIDPosition); 
    UpdateSetpointIntegratedMotorEncoderPID(pivotL, -pivotPIDPosition); 
    UpdateSetpointIntegratedMotorEncoderPID(pivotR, pivotPIDPosition);
}

void SetPivotDegrees(long degrees) {
    PivotDegrees = degrees;
    setPivotPID();
}

void DebugPivot() {
    long l, r;
    l = GetIntegratedMotorEncoder(pivotL); 
    r = GetIntegratedMotorEncoder(pivotR);
    PrintToScreen("pivot encs: %ld, %ld\n", l, r);
}

void SetPivotPID() {
  long posL = GetIntegratedMotorEncoder(pivotL);
  long posR = GetIntegratedMotorEncoder(pivotR);

  UpdateSetpointIntegratedMotorEncoderPID(pivotL, posL);
  UpdateSetpointIntegratedMotorEncoderPID(pivotR, posR);
  DebugPivot();
}*/

