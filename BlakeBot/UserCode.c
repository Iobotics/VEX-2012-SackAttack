// UserCode.c : implementation file
#include "Main.h"
#include "UserInclude.h"
#include "Motor.h"
#include "ArmControl.h"
//#include "PivotControl.h"
#include "AutoControl.h"

void DriveControl(void) {
    SetDrive(GetJoystickAnalog(1, 3), GetJoystickAnalog(1, 2));
}

void ArmControl() {
  static int prevBtn = 0;
  
  if(prevBtn) {
    if(!GetJoystickDigital(1,5, prevBtn)) {
      prevBtn = 0;
    }
  } else {
    if(GetJoystickDigital(1,5,1)) {
        //if(!ArmState == GROUND) {
            prevBtn = 1;
            ArmDecrement();
        //}
    } else if(GetJoystickDigital(1,5,2)) {
        //if(!ArmState == DESCORE) {
            prevBtn = 2;
            ArmIncrement();
        //}
    }
  }
}

void ArmResetControl() {
  static int prevBtn = 1;
  static char buttonPressed = 0;
  if(buttonPressed) {
    if(!GetJoystickDigital(1,7,prevBtn)) {      
        buttonPressed = 0;                        //RESET
    }
  }
  else {
    if(GetJoystickDigital(1,7,2)) {
      prevBtn = 2;
      buttonPressed = 1;
      //SetArmResetState(STOP_PID);
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

void PivotControl() {
    static int buttonPressed = 0;
    static PIVOT_STATES pivotState = STOPPED;

    int btn = GetJoystickDigital (1, 8, 3);
    if(btn) {
        if (btn != buttonPressed) {
            if(pivotState == STOPPED) {
                pivotState = MOVE;
                SetDigitalOutput(1, 1);  
            }
            else {
                pivotState = STOPPED;
                SetDigitalOutput(1, 0); 
            }
            buttonPressed = 1; 
        }
    }
    else{
        buttonPressed = 0;
    }
}

/*void PivotControl(void) {
  if(GetJoystickDigital(1,8,3)) {
    //SetPivot(50);
    SetPivotDegrees(50);
  } else if(GetJoystickDigital(1,8,1)) {
    //SetPivot(-50);
    SetPivotDegrees(-50);
  } else {
    //SetPivot(0);
    SetPivotDegrees(0);
  }
}*/

void _Initialize(void) {
    InitIntegratedMotorEncoders(); 
    //PresetIntegratedMotorEncoder(driveLIME, 0);
    //PresetIntegratedMotorEncoder(driveRIME, 0);
    
    InitArm();
    //InitPivot();
    SetDigitalOutput(1, 0);
}

void _Autonomous(void) {
    AutonomousStartUp();

    #if RUN_AUTONOMOUS
        SetScorer(GROUND, RELEASE); //switch intake and outake
        SetDrive(127,127);
        WaitInMsec(2100);           //Goes to the stack
        SetDrive(-127, -127);           //First time back
        WaitInMsec(500);
        SetDrive(127, 127);
        WaitInMsec(500);
        SetDrive(0, 0);
        WaitInMsec(300);
        SetDrive(-127, -127);             //Second time back
        WaitInMsec(500);
        SetDrive(127, 127);
        WaitInMsec(500);
        SetDrive(0, 0);
        WaitInMsec(300);
        SetDrive(-127, -127);             //Third time back
        WaitInMsec(500);
        SetDrive(127, 127);
        WaitInMsec(500);
        SetDrive(0, 0);
        WaitInMsec(300);

        SaveState();
    #else  
        /*SetScorer(GROUND, RELEASE); //switch intake and outake
        SetDrive(127,127);
        WaitInMsec(1700);           //Goes to the stack
        SetDrive(-127, -127);           //First time back
        WaitInMsec(500);
        SetDrive(127, 127);
        WaitInMsec(500);
        SetDrive(0, 0);
        WaitInMsec(300);
        SetDrive(-127, -127);             //Second time back
        WaitInMsec(500);
        SetDrive(127, 127);
        WaitInMsec(500);
        SetDrive(0, 0);
        WaitInMsec(300);
        SetDrive(-127, -127);             //Third time back
        WaitInMsec(500);
        SetDrive(0, 0);
        SetScorer(DESCORE, HOLD);
        WaitInMsec(3000);
        SetDrive(127, 127);
        WaitInMsec(2000);
        SetDrive(127, 0);
        WaitInMsec(700);
        SetDrive(0, 0);
        SetScorer(DESCORE, INTAKE);*/
        
   #endif
        AutonomousEnd();
}

void _OperatorControl(void) {
    //StopIntegratedMotorEncoderPID(driveLIME);
    //StopIntegratedMotorEncoderPID(driveRIME);

    //int c;

    while(1) {
        ArmControl();
        DriveControl();
        //if(!(c++ % 1000)) {
            //DebugArm();
            //DebugPivot();
        //} 
        IntakeControl();
        PivotControl();
        ArmResetControl();
    }
}



















































