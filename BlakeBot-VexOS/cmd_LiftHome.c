// cmd_LiftHome.c : implementation file
#include "CommandClass.h"
#include "Robot.h"

DefineCommandClass(LiftHome, { });

static void constructor(va_list argp) {
    require(&Lift);
}

static void initialize() { 
    Lift_setPower(-1.0);
}

static void execute() {
}

static bool isFinished() {
    return Lift_getHomeSwitch();
}

static void end() { 
    Lift_setPower(0);
    Lift_reset();
}

static void interrupted() { 
    Lift_setPower(0);
}


