// cmd_LiftSet.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(LiftSet, { 
    LiftPosition pos;
});

static void constructor(va_list argp) {
    self->fields->pos = (LiftPosition) va_arg(argp, int);
    setArgs("%s", (self->fields->pos == LiftPosition_Trough)? "Trough":
                  (self->fields->pos == LiftPosition_Descore)? "Descore": "Ground");
    require(&Lift);
}

static void initialize() { 
    Lift_setPosition(self->fields->pos);
}

static void execute() {
}

static bool isFinished() {
    return true;
}

static void end() { }

static void interrupted() { }

