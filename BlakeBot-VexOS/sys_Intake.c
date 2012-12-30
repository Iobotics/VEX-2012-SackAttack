// sys_Drive.c : implementation file
#include "Subsystem.h"
#include "Hardware.h"
#include "Robot.h"

DefineSubsystem(Intake);

static MotorGroup* motors;

static void constructor() {
    motors = MotorGroup_new("intake");
    MotorGroup_add(motors, "left intake",  PWMPort_7, MotorType_393_HT, false);
    MotorGroup_add(motors, "right intake", PWMPort_8, MotorType_393_HT, true);
}

static void initialize() { 
    setDefaultCommand(Command_new(&IntakeSet, IntakeDirection_Stop));
}

// TODO: add user code here

void Intake_setDirection(IntakeDirection dir) {
    switch(dir) {
        case IntakeDirection_Stop:
            MotorGroup_setPower(motors, 0);
            break;
        case IntakeDirection_Suck:
            MotorGroup_setPower(motors, -1);
            break;
        case IntakeDirection_Blow:
            MotorGroup_setPower(motors, 1);
            break;
    }
}

