#ifndef MOTOR_H_
#define MOTOR_H_
// Motor.h : header file

typedef enum {
    driveR1 = 1,
    driveR2 = 2,
    driveR3 = 3,
    armL    = 4,
    intake1 = 5,
    intake2 = 6,
    armR    = 7,
    driveL1 = 8,
    driveL2 = 9,
    driveL3 = 10 
} MOTOR_PORTS;

void SetDrive(int left, int right);
void SetArm(int pwr);
void SetIntake(int pwr);

#endif


