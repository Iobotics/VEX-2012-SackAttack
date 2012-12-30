// cmd_PivotSet.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(PivotSet, { 
    PivotPosition pos;
});

static void constructor(va_list argp) {
    self->fields->pos = (PivotPosition) va_arg(argp, int);
    setArgs("%s", (self->fields->pos == PivotPosition_Up)? "Up": "Down");
    require(&Pivot);
}

static void initialize() { 
    Pivot_setPosition(self->fields->pos);
}

static void execute() {
}

static bool isFinished() {
    return false;
}

static void end() { }

static void interrupted() { }



