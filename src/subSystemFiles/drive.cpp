// #include "main.h"


// // // Helper function to set drive motors
// void setDrive(int left, int right) {
//     driveLeftBack = left;
//     driveLeftFront = left;
//     driveLeftMid = left;
//     driveRightMid = right;
//     driveRightBack = right;
//     driveRightFront = right;
// }

// // // Driver control function
// // void setDriveMotors() {
// //     int leftjoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
// //     int rightjoystick = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);

// //      if(abs(leftjoystick) < 10) {
// //         leftjoystick = 0;
// //     }

// //     if(abs(rightjoystick) < 10) {
// //         rightjoystick = 0;
// //     }
// //     setDrive(leftjoystick, rightjoystick);
// // }


// // Driver control function - Arcade Drive
// void setDriveMotors() {
//     int forwardBackward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
//     int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

//     if (abs(forwardBackward) < 10) {
//         forwardBackward = 0;
//     }

//     if (abs(turn) < 10) {
//         turn = 0;
//     }

//     int leftMotorSpeed = forwardBackward + turn;
//     int rightMotorSpeed = forwardBackward - turn;

//     setDrive(leftMotorSpeed, rightMotorSpeed);
// }


#include "main.h"

void setDrive(int leftFront, int leftBack, int leftMid, int rightFront, int rightBack, int rightMid) {
    driveLeftBack = leftBack;
    driveLeftFront = leftFront;
    driveLeftMiddle = leftMid;
    driveRightMiddle = rightMid;
    driveRightBack = rightBack;
    driveRightFront = rightFront;
}

void setDriveMotors() {
    int forwardBackward = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int turn = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    forwardBackward=(abs(forwardBackward)<10)?0:forwardBackward;
    turn=(abs(turn)<10)?0:turn;
    float ts = 0.65;
    turn*=ts; 
    int leftFrontSpeed = forwardBackward + turn;
    int leftBackSpeed = forwardBackward + turn;
    int leftMidSpeed = forwardBackward + turn;
    int rightFrontSpeed = forwardBackward - turn;
    int rightBackSpeed = forwardBackward - turn;
    int rightMidSpeed = forwardBackward - turn;

    setDrive(leftFrontSpeed, leftBackSpeed, leftMidSpeed, rightFrontSpeed, rightBackSpeed, rightMidSpeed);
}
