// UserInclude.h : header file
#ifndef USERINCLUDE_H_
#define USERINCLUDE_H_

typedef enum {
pneumaticPivot         = 1,
armResetSwitch         = 2,
button                 = 3
} DIGITAL_SENSORS;

typedef enum {
    GDATA_LAST_MODE = 1,
    GDATA_ARM,
    GDATA_SHIFTER,
    GDATA_RAMP
} GDATA_STATES;

typedef enum {
    MODE_DRIVER,
    MODE_AUTO
} MODE_TYPE;

void DriveControl(void);
void ArmControl(void);
void IntakeControl(void);
void PivotControl(void);
void _Initialize(void);
void _OperatorControl(void);
void _Autonomous(void);


#endif // USERINCLUDE_H_



















