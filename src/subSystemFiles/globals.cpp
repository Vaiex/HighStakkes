#include "main.h"

//motors
 pros::Motor lift(4, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
 pros::Motor angler(3, pros::E_MOTOR_GEARSET_36, false, pros::E_MOTOR_ENCODER_COUNTS);
 pros::Motor intake(7, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_COUNTS);
 pros::Motor cata(8, pros::E_MOTOR_GEAR_BLUE, 1, pros::E_MOTOR_ENCODER_COUNTS);  
//  pros::ADIDigitalOut piston (DIGITAL_SENSOR_PORT);
// pros::MotorGroup left_side_motors({driveLeftFront, driveLeftBack});
// pros::MotorGroup right_side_motors({driveRightFront, driveRightBack});
// //controller
extern pros::Controller controller(pros::E_CONTROLLER_MASTER);
