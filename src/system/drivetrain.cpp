#include "robot/drivetrain.h"
#include "globals.h"
#include <cmath>
#define DEFAULT_DELAY_LENGTH 15

using namespace robot;
using namespace robot::globals;

drive::DRIVE_MODE drive::driveMode = robot::drive::CURVATURE_DRIVE;

bool isReversed = false;

drive::drive() {}

void drive::initialize() {
    // Initialize motor brake modes first
    initializeMotors();
    
    // Calibrate the chassis
    chassis.calibrate();
    
    // Set initial pose to origin
    chassis.setPose(0, 0, 0);

    // Set initial drive mode
    drive::driveMode = CURVATURE_DRIVE;

    isReversed = false;
    
    // Stop any potential movement
    chassis.tank(0, 0);
    
    std::cout << "Drivetrain initialized - Default mode: Curvature Drive" << std::endl;
    pros::delay(100);
}

void drive::initializeMotors() {
    // Add safety check
    if (!RightFront.is_installed() || !RightBack.is_installed() || 
        !LeftFront.is_installed() || !LeftBack.is_installed()) {
        std::cout << "ERROR: Not all drive motors are properly connected!" << std::endl;
        return;
    }
    
    RightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    RightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    
    chainHoist1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chainHoist2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    chainHoist3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    
    std::cout << "Motor brake modes initialized" << std::endl;
}

void drive::disabled() {
    // Stop all drivetrain movement
    chassis.tank(0, 0);
    
    // Reset drive mode to default
    drive::driveMode = CURVATURE_DRIVE;
    
    // Reset any state variables
    isReversed = false;
    
    // Print disabled status
    std::cout << "Drivetrain disabled - All movement stopped" << std::endl;
}

void drive::TankDrive() {
     // get joystick positions
     int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
     int rightY = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
     // move the chassis with tank controls
     chassis.tank(leftY, rightY);
     // delay to save resources
     pros::delay(25);
}

void drive::ArcadeDrive() {
    // get joystick positions
    int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
    // move the chassis with arcade controls
    chassis.arcade(leftY, // throttle
                   rightX, // steer
                   false, // enable drive curves
                   0.75 // slightly prioritize steering
    );
    // delay to save resources
    pros::delay(25);
}

void drive::CurvatureDrive() {
   // get joystick positions
   int leftY = controller.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
   int rightX = controller.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);
   // move the chassis with curvature controls
   chassis.curvature(leftY, rightX);
   // delay to save resources
   pros::delay(25);
}

// Run the drive depending on the control mode
void drive::run() {
   switch (drive::driveMode) {
   case CURVATURE_DRIVE:
      drive::CurvatureDrive();
      break;
   case ARCADE_DRIVE:
      drive::ArcadeDrive();
      break;
   case TANK_DRIVE:
      drive::TankDrive();
      break;
   }
}

// Cycle through each drive control mode, overflows back to 0
std::string drive::toggleDrive() {
   int driveMode = (drive::driveMode + 1) % (TANK_DRIVE + 1);
   return SwitchDrive(driveMode);
}



// Switch the drive control mode between arcade and tank drive with the down button(between 1 and 2)
std::string drive::SwitchDrive(int driveMode) {
   switch (driveMode) {
   case 0:
      drive::driveMode = CURVATURE_DRIVE;
      std::cout << "Curvature Drive" << std::endl;
      return "Curvature Drive";
   case 1:
      drive::driveMode = ARCADE_DRIVE;
      std::cout << "Arcade Drive" << std::endl;
      return "Arcade Drive";
   case 2:
      drive::driveMode = TANK_DRIVE;
      std::cout << "Tank Drive" << std::endl;
      return "Tank Drive";
   
       default:
      std::cout << "Not a valid drive control mode!" << std::endl;
      return "Not a valid driveMode!";
   }
}
