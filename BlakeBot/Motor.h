#ifndef MOTOR_H_
#define MOTOR_H_
// Motor.h : header file

typedef enum {
    armR = 1,
    armL = 2,
    //intakeL = 3,
    //intakeR = 4,
    driveL = 3,
    driveLIME = 4,
    driveRIME2 = 5,
    driveLIME2 = 6,
    //driveL = 7,
    //driveLIME = 8,
    intakeL = 7,
    intakeR = 8,
    driveR = 9,
    driveRIME = 10 
} MOTOR_PORTS;

typedef enum {
    MOVE  = 1,
    STOPPED = 0
} PIVOT_STATES;    

void SetDrive(int left, int right);
void SetArm(int pwr);
void SetPneumatic(unsigned char port, unsigned char shift);
void SetIntake(int pwr);
void SetPivot(int pwr);
void SetRegularDriveMotors(long l, long r);

#endif







