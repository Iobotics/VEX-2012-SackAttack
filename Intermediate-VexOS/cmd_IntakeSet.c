// cmd_IntakeSet.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(IntakeSet, { 
    IntakeDirection dir;
});

static void constructor(va_list argp) {
    self->fields->dir = (IntakeDirection) va_arg(argp, int);
    setArgs("%s", (self->fields->dir == IntakeDirection_Suck)? "Suck":
                  (self->fields->dir == IntakeDirection_Blow)? "Blow": "Stop");
    require(&Intake);
}

static void initialize() { 
    Intake_setDirection(self->fields->dir);
}

static void execute() {
}

static bool isFinished() {
    return false;
}

static void end() { 
    Intake_setDirection(IntakeDirection_Stop);
}

static void interrupted() { }

