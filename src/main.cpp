#include "main.h"
#include "lemlib/api.hpp"
#include "pros/llemu.hpp"
#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "lemlib/api.hpp"
#include "pros/motors.h"
#include "pros/motor_group.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "globals.h"
#include "pros/rotation.hpp"
#include "robot/drivetrain.h"
#include "robot/subsystems.h"
#include <cmath>
#include <string>

using namespace robot;
using namespace robot::globals;

struct robotSubsystems {
    robot::Subsystems subsystems;
    robot::drive drive;
} subsystem;

void initialize() {
    chassis.calibrate();

    chassis.setPose(0,0,0);

    // print robot location to the brain screen
    pros::lcd::print(0, "X: %f", chassis.getPose().x);         // x
    pros::lcd::print(1, "Y: %f", chassis.getPose().y);         // y
    pros::lcd::print(2, "Theta: %f", chassis.getPose().theta); // heading
    pros::delay(100);
    subsystem.subsystems.initialize();
    subsystem.drive.initialize(); // This now calls initializeMotors() internally
    // Removed subsystem.subsystems.update() - should not be called during initialization
}

void disabled() {
    subsystem.drive.disabled();
    subsystem.subsystems.stop();
}

void autonomous() {
    chassis.tank(0, 0);
}
void opcontrol() {
    while (true) {

        if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_LEFT)) {
            std::string name = subsystem.drive.toggleDrive();
            // Output the current drive mode to the controller screen
            controller.print(0, 0, name.c_str());
         }

        subsystem.drive.run();
        subsystem.subsystems.run();
        pros::delay(20); // Increased from 5 to 20ms for better performance
    }
}

