// ArmControl.h : header file
#ifndef ARM_H_
#define ARM_H_

typedef enum {
  STOP_PID,
  LOWER_ARM,
  START_PID,
  DONE
} ARM_RESET_STATE;

typedef enum {
    GROUND  = 0,
    DESCORE  = 35,
    TROUGH = 45
} ARM_STATES;

ARM_STATES ArmState;

typedef enum {
    HOLD = 0,
    INTAKE = 127,
    RELEASE = -127
} INTAKE_STATES;

void ArmResetStateMachine();
void InitArm();
void SetArmPID();
void SetArmState(ARM_STATES state);
void ArmDecrement();
void ArmIncrement();
void DebugArm();

#endif




