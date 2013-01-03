// Motor.c : implementation file
#include "Main.h"
#include "Motor.h"

void SetDrive(int left, int right) {
    SetMotor(driveL, left);
    SetMotor(driveLIME, left);
    SetMotor(driveLIME2, left);                 //change directions
    SetMotor(driveR, right);
    SetMotor(driveRIME, -right);
    SetMotor(driveRIME2, right);                //change directions
}

void SetArm(int pwr) {
    SetMotor(armL, pwr);
    SetMotor(armR, -pwr);
}

void SetIntake(int pwr) {
    SetMotor(intakeL, pwr);
    SetMotor(intakeR, -pwr);
}

void SetPneumatic(unsigned char port, unsigned char shift) {
    SetDigitalOutput(port, shift);
}

void ShiftPivot(PIVOT_STATES shift) {
    SetPneumatic(pneumaticPivot, shift);
}

/*void SetPivot(int pwr) {
    SetMotor(pivotL, pwr);
    SetMotor(pivotR, -pwr);
}*/

void SetRegularDriveMotors(long l, long r) {
    SetMotor(driveL, l);
    SetMotor(driveR, r);
}
