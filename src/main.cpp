#include "main.h"
#include "lemlib/api.hpp"
#include<bits/stdc++.h>

#define DIGITAL_SENSOR_PORT 'E' 
#define DIGITAL_SENSOR_PORT2 'A' 
#define DIGITAL_SENSOR_PORT3 'B' 
 pros::Motor driveLeftFront(1, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_COUNTS);
 pros::Motor driveLeftBack(10, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_COUNTS);
 pros::Motor driveLeftMiddle(2, pros::E_MOTOR_GEAR_BLUE,1,pros::E_MOTOR_ENCODER_COUNTS);   
 pros::Motor driveRightMiddle(12, pros::E_MOTOR_GEAR_BLUE,0,pros::E_MOTOR_ENCODER_COUNTS);
 pros::Motor driveRightFront(11, pros::E_MOTOR_GEAR_BLUE, 0, pros::E_MOTOR_ENCODER_COUNTS);
 pros::Motor driveRightBack(20, pros::E_MOTOR_GEAR_BLUE, 0, pros::E_MOTOR_ENCODER_COUNTS);
pros::MotorGroup lsm({driveLeftFront, driveLeftBack, driveLeftMiddle});
pros::MotorGroup rsm({driveRightFront, driveRightBack, driveRightMiddle});

pros::ADIDigitalOut wingsLeft (DIGITAL_SENSOR_PORT,false);
pros::ADIDigitalOut wingsRight (DIGITAL_SENSOR_PORT2,false);
pros::ADIDigitalOut sidePiston(DIGITAL_SENSOR_PORT3,false);

lemlib::Drivetrain drivetrain (&lsm, // left motor group
                              &rsm, // right motor group
                              13.5, // 10 inch track width
                              3.25, // using new 3.25" omnis
                              450, // drivetrain rpm is 360
                              8 // chase power is 2. If we had traction wheels, it would have been 8
);
 
// left tracking wheel encoder
//pros::ADIEncoder left_enc('A', 'B', true); // ports A and B, reversed
// right tracking wheel encoder
//pros::Rotation right_rot(1, false); // port 1, not reversed
// back tracking wheel encoder
//pros::ADIEncoder back_enc('C', 'D', false); // ports C and D, not reversed
// inertial sensor
pros::Imu imu(2); // port 2

/*
// left tracking wheel
lemlib::TrackingWheel left_tracking_wheel(&left_enc, 2.75, -4.6); // 2.75" wheel diameter, -4.6" offset from tracking center
// right tracking wheel
lemlib::TrackingWheel right_tracking_wheel(&right_rot, 2.75, 1.7); // 2.75" wheel diameter, 1.7" offset from tracking center
lemlib::TrackingWheel back_tracking_wheel(&back_enc, 2.75, 4.5); // 2.75" wheel diameter, 4.5" offset from tracking center
 
*/
// odometry struct
lemlib::OdomSensors sensors {
    nullptr, 
    nullptr, 
    nullptr,  
    nullptr,
    &imu // inertial sensor
};
// forward/backward PID
/*
lemlib::ControllerSettings lateralController {
    34, // kP
    33, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    20 // slew rate
};
 
// turning PID
lemlib::ControllerSettings angularController {
    4, // kP
    34, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    20 // slew rate
};
*/

lemlib::ControllerSettings lateralController {
    17, // kP
    36, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    3, // largeErrorRange
    500, // largeErrorTimeout
    20 // slew rate
};
 
// turning PID
lemlib::ControllerSettings angularController {
    4, // kP
    40, // kD
    1, // smallErrorRange
    100, // smallErrorTimeout
    2, // largeErrorRange
    500, // largeErrorTimeout
    18 // slew rate
};
lemlib::Chassis chassis(drivetrain, lateralController, angularController, sensors);

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}
void initialize() {
    pros::lcd::initialize(); // initialize brain screen
    chassis.calibrate(); // calibrate sensors
     // X: 0, Y: 0, Heading: 0
    pros::Task screenTask([&]() {
        lemlib::Pose pose(0, 0, 0);
        while (true) {
            // print robot location to the brain screen
            pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
            pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
            pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
            // log position telemetry
            lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
            // delay to save resources
            pros::delay(50);
        }
    });
}
// int main() {
//     while (true) {
//             // print robot location to the brain screen
//             pros::lcd::print(0, "X: %f", chassis.getPose().x); // x
//             pros::lcd::print(1, "Y: %f", chassis.getPose().y); // y
//             pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
//             // log position telemetry
//             lemlib::telemetrySink()->info("Chassis pose: {}", chassis.getPose());
//             // delay to save resources
//             pros::delay(50);
//         }
//     return 0;
// }

void disabled() {} 

void competition_initialize() {}

void opcontrol() {
    bool sideOn = false;
    bool leftOn = false;
    bool rightOn = false;
     while (true) {
         if (controller.get_digital_new_press(DIGITAL_L2)) {
            leftOn = !leftOn;
             wingsLeft.set_value(leftOn);
         }
         if (controller.get_digital_new_press(DIGITAL_R2)) {
             rightOn = !rightOn; 
             wingsRight.set_value(rightOn);
         }
         if(controller.get_digital_new_press(DIGITAL_Y)){
             sidePiston.set_value(!sideOn);
         }
          if(controller.get_digital_new_press(DIGITAL_B)){
             sidePiston.set_value(sideOn);
         }
 		setDriveMotors();
        setIntakeMotors();
        // autonomous();

        pros::delay(20);
     }

}

void autonomous() { 
 
    //9123c skills

    chassis.setPose(-42.053,-59.507,327,false);
    chassis.moveTo(-56.917,-35.04,365,10000,true);
    chassis.moveTo(-56.917,-35.04,165,10000,true);
    chassis.turnTo(-52.816,-49.222,10000,true);
    chassis.setPose(-52.816,-49.222,75,false);
    chassis.moveTo(-52.816,-49.222,75,10000,true);
    chassis.moveTo(-8.2,-32.957,0,10000,true);
    chassis.setPose(-8.2,-32.957,0,false);
    chassis.moveTo(-8.2,-4.641,0,10000,true);//remove later
    chassis.moveTo(-8.2,34.283,255,10000,true);
    chassis.turnTo(-24.543,31.78,10000,true);
    chassis.moveTo(-24.543,31.78,276,10000,true);
    chassis.moveTo(-56.061,36.216,8,10000,true);
    chassis.moveTo(-54.427,47.656,42,4000,true);
    chassis.turnTo(-40.185,59.563,4000,true);
    chassis.moveTo(-40.185,59.563, 77, 4000,true);
    chassis.moveTo(-22.208,62.132,90, 4000,true);
    chassis.moveTo(-2.129,61.868,90, 4000,true);//remove later
    chassis.moveTo(40.83,61.868,90, 4000,true);
    chassis.turnTo(53.904,48.824,4000,true);
    chassis.moveTo(53.904,48.824,159, 4000,true);
    chassis.turnTo(59.274,33.881,4000,true);
    chassis.moveTo(59.274,33.881,176, 4000,true);
    chassis.moveTo(60.208,22.441,180,4000,true);
    chassis.moveTo(56.239,36.683,180,4000,false);
    chassis.turnTo(13.261,29.213,4000,true);
    chassis.moveTo(13.261,29.213,186,4000,true);
    


}
