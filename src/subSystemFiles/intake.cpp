#include "main.h"


void setIntake(int power) {
    intake = power;
}

void setIntakeMotors() {
        if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) { 
            setIntake(600); 
        } 
    else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) { 
            setIntake(-600);
        }         else {
            setIntake(0); 
        }  }


// void setIntakeMotors(){
//     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1)){
//         setIntake(600);
//     }
//     if(controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)){
//         setIntake(-600);
//     }
// }
// void toggleIntake() {
//     if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_R1) ||
//         controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_L1)) {
//         intakeRunning = !intakeRunning;

//         if (!intakeRunning) {
//             intakePower = 0;
//         }
//     }

//     if (intakeRunning) {
//         if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
//             intakePower = 600;
//         } else if (controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
//             intakePower = (intakePower == 0) ? -600 : 0;
//         }
//     }

//     setIntake(intakePower);
// }

// void setIntakeMotors() {
//     toggleIntake();
// }