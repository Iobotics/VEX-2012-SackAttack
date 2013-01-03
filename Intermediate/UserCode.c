// UserCode.c : implementation file
#include "Main.h"
#include "UserInclude.h"
#include "Motor.h"
#include "ArmControl.h"
#include "AutoControl.h"
#include "ResetControl.h"

#define SCALE_SIZE 4

    float scaleErin[SCALE_SIZE][2] = { { 0.000, 0.00 },
                                 { 0.040, 0.02 },
                                 { 0.965, 0.40 },
                                 { 0.975, 1.00 }
                               }; 

    float scaleTim[SCALE_SIZE][2] = { { 0.000, 0.00 },
                                 { 0.040, 0.02 },
                                 { 0.945, 0.50 },
                                 { 0.965, 1.00 }
                               }; 
    float scaleLeah[SCALE_SIZE][2] = { { 0.000, 0.00 },
                                 { 0.040, 0.02 },
                                 { 0.945, 0.50 },
                                 { 0.965, 0.75 }
                               };
    float (*scalePtr)[SCALE_SIZE][2];

void DriveControl(void) {
    SetDrive(GetJoystickAnalog(1, 3), GetJoystickAnalog(1, 2));
}

int scalePower(int input) {
  float cmd = (float) (Abs(input)) / 127.0;
  if(cmd >= (*scalePtr)[SCALE_SIZE - 1][0]) {cmd = (*scalePtr)[SCALE_SIZE - 1][1];}
  else {
      int i;
      for(i = 0; i < SCALE_SIZE-2; i++) {
        if(cmd >= (*scalePtr)[i][0] && cmd < (*scalePtr)[i + 1][0]) {
          // cmd = ((Y2 - Y1) / (X2 - X1)) (cmd - X1) + Y1
          cmd = (((*scalePtr)[i + 1][1] - (*scalePtr)[i][1]) * (cmd - (*scalePtr)[i][0])
          / ((*scalePtr)[i + 1][0] - (*scalePtr)[i][0]))
          + (*scalePtr)[i][1];
          break;
        }
      }
  }
  if(input > 0) { return (int) (cmd * 127.0); }
  return (int) (cmd * -127.0); 
}

// set drive motors based on joystick

void scaledDrive(){
    SetDrive(scalePower(GetJoystickAnalog(1,3)), 
        scalePower(GetJoystickAnalog(1,2)));
}

void ArmControl() {
  static int prevBtn = 0;
  
  if(prevBtn) {
    if(!GetJoystickDigital(1,5, prevBtn)) {
      prevBtn = 0;
    }
  } else {
    if(GetJoystickDigital(1,5,1)) {
        prevBtn = 1;
        ArmDecrement();
    } else if(GetJoystickDigital(1,5,2)) {
        prevBtn = 2;
        ArmIncrement();
    }
  }
}

/*void ArmControl() {
    if(GetJoystickDigital(1,5,1))
        SetArm(-127);
    else if(GetJoystickDigital(1,5,2))
        SetArm(127);
    else
        SetArm(0);
}*/

void ArmResetControl() {
  static int prevBtn = 1;
  static char buttonPressed = 0;
  if(buttonPressed) {
    if(!GetJoystickDigital(1,7,prevBtn)) {      
        buttonPressed = 0;
    }
  }
  else {
    if(GetJoystickDigital(1,7,2)) {
      prevBtn = 2;
      buttonPressed = 1;
      ArmResetStateMachine();
    }
  }
}

void IntakeControl(void) {
  static int prevBtn = 0;
  
  if(prevBtn) {
    if(!GetJoystickDigital(1,6,prevBtn)) {
      prevBtn = 0;
      SetIntake(HOLD);
    }
  } else {
    if(GetJoystickDigital(1,6,1)) {
      prevBtn = 1;
      SetIntake(INTAKE);
    } else if(GetJoystickDigital(1,6,2)) {
      prevBtn = 2;
      SetIntake(RELEASE);
    }
  }
}

void _Initialize(void) {
    InitIntegratedMotorEncoders(); 

    InitArm();
    SetDigitalOutput(1, 0);
}

void _Autonomous(void) {
    AutonomousStartUp();
    #if RUN_AUTONOMOUS
        
        SetScorer(TROUGH, INTAKE);   //switch intake and outake
        WaitInMsec(3000);
        SetDrive(127,127);
        WaitInMsec(300);
        SetDrive(-127,-127);
        WaitInMsec(300);
        SetDrive(0,0);
        SetScorer(GROUND,  HOLD);
        /*SetDrive(-127,-127);
        WaitInMsec(300);
        SetDrive(127,127);
        WaitInMsec(300);*/
        SetDrive(0,0);

        SaveState();
    #else  
        SetScorer(GROUND, RELEASE); //switch intake and outake
        SetDrive(127,127);
        WaitInMsec(1000);           //Goes to the stack
        SetDrive(0, 0);
        WaitInMsec(2000);
        SetDrive(127, 127);
        WaitInMsec(100);
        SetDrive(0,0);
        WaitInMsec(2000);
        SetScorer(DESCORE, HOLD);
        WaitInMsec(3000);
        SetDrive(127, 127);
        WaitInMsec(1000);
        SetDrive(0, 127);
        WaitInMsec(700);
        SetDrive(0, 0);
        SetScorer(DESCORE, INTAKE);
        
   #endif
        AutonomousEnd();
}

void _OperatorControl(void) {
    scalePtr = &scaleLeah;
    while(1) {
        ArmControl();
        scaledDrive();
        IntakeControl();
        //ArmResetControl();
    }
}





















































