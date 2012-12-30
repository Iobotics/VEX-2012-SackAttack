// cmd_AutoTurn.c : implementation file
// cmd_AutoDrive.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(AutoTurn, { 
    float angle;
});

static void constructor(va_list argp) {
    self->fields->angle = (float) va_arg(argp, double);    
    setArgs("%f", self->fields->angle);
    require(&Drive);
}

static void initialize() { 
    Drive_startTurn(self->fields->angle);
}

static void execute() { }

static bool isFinished() {
    return Drive_isDone();
}

static void end() { 
    Drive_end();
    Drive_setPower(0, 0);
}

static void interrupted() { 
    end();
}

