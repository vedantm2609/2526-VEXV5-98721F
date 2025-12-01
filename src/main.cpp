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

// left button arrow controls the toggleing of the drive mode, y sets up an update loop, 
// and l1 toggles boost levels for all subsytems. The scoring layers are the same as the 
// ones on 


/**
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

    void robot::Subsystems::start() {
    // Get controller inputs
    bool l1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    bool l2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    bool r1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    bool r2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    bool up = controller.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
    bool down = controller.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    
    // Mode switching with adaptive velocity
    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_UP)) {
        velocityController.setMode(AdaptiveVelocityController::SPORT);
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN)) {
        velocityController.setMode(AdaptiveVelocityController::PRECISION);
    } else if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_RIGHT)) {
        velocityController.setMode(AdaptiveVelocityController::NORMAL);
    }
    
    // Get adaptive velocity for subsystems
    double maxVel = velocityController.getSubsystemVelocity();
    
    if (useAdaptiveVelocity) {
        // Adaptive velocity control for subsystems
        if (l2) {
            chainHoist1.move_velocity(maxVel);
            chainHoist2.move_velocity(0);
            chainHoist3.move_velocity(0);
        } else if (r1) {
            // Top rack mode
            chainHoist1.move_velocity(-maxVel);
            chainHoist2.move_velocity(-maxVel);
            chainHoist3.move_velocity(-maxVel);
        } else if (r2) {
            // Middle rack mode  
            chainHoist1.move_velocity(-maxVel);
            chainHoist2.move_velocity(-maxVel);
            chainHoist3.move_velocity(maxVel);
        } else {
            // Stop all motors
            chainHoist1.move_velocity(0);
            chainHoist2.move_velocity(0);
            chainHoist3.move_velocity(0);
        }
    } else {
        // Keep existing voltage control as fallback
        // ... existing voltage code ...
    }
    
    // Display velocity info periodically
    static uint32_t lastDisplayTime = 0;
    if (pros::millis() - lastDisplayTime > 500) {
        controller.print(0, 0, "V:%.0f S:%.0f", 
            velocityController.getDriveVelocity(),
            velocityController.getSubsystemVelocity());
        lastDisplayTime = pros::millis();
    }
}
} */