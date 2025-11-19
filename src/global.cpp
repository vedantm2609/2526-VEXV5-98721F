#include <vector>
#include <string>
#include "lemlib/chassis/trackingWheel.hpp"
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
// Removed redundant include for 'lemlib/api.h'
#include "pros/motors.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include "pros/vision.h"
#include "main.h"
#include "lemlib/chassis/chassis.hpp"


namespace robot {

namespace globals {
    pros::Controller controller(pros::E_CONTROLLER_MASTER);

    pros::Motor RightFront(2, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor RightBack(1, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor LeftFront(-3, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    pros::Motor LeftBack(-4, pros::v5::MotorGears::blue, pros::v5::MotorUnits::degrees);
    
    // Set brake modes to prevent coasting/drift
   
    pros::MotorGroup driveRight({RightFront.get_port(), RightBack.get_port()}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::rotations);
    pros::MotorGroup driveLeft({LeftFront.get_port(), LeftBack.get_port()}, pros::v5::MotorGears::blue, pros::v5::MotorUnits::rotations);

    pros::adi::Pneumatics helperIntake1('a', false);
    pros::adi::Pneumatics helperIntake2('a', false);
    pros::adi::Pneumatics flapPneumatic('b', false);

    // ChainHoist2 is the motor that is the lowest gear fixing
    // ChainHoist1 is the motor that is required for all instances
    // ChainHoist3 is the motor that spins counterclockwise for middle and clockwise for higher

    pros::Motor chainHoist1(12  , pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::Motor chainHoist2(18, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
    pros::Motor chainHoist3(6, pros::v5::MotorGears::green, pros::v5::MotorUnits::degrees);
// Fixed motor group to only include motors that are actually defined
    pros::MotorGroup chainHoistMotors({12, 18, 6}, pros::v5::MotorGears ::green, pros::v5::MotorUnits::degrees);

    lemlib::Drivetrain drivetrain{
        &driveLeft,
        &driveRight,
        13.785, // wheel diameter in inches
        lemlib::Omniwheel::NEW_325,
        11.5, // wheel track in inches (distance between left and right wheels)
        1     // external gear ratio (1 if directly driven)
    };

    

   
    
    pros::Rotation horizontalRotation(10);
    pros::Rotation verticalRotation(19);
    pros::Imu mainIMU(7); // Port 
    pros::AIVision imComingForU(13); // AI vision sensor
    lemlib::TrackingWheel horizontal_tracking_wheel(&horizontalRotation, 2.75, 7.25, 0); // (rotation sensor, wheel diameter, distance from center
    lemlib::TrackingWheel vertical_tracking_wheel(&verticalRotation, 2.75, -7.25, 90); // (rotation sensor, wheel diameter, distance from center, angle offset)

    int MotorVoltage = 12000;
    int HalfMotorVoltage = MotorVoltage / 2;
    double regularVoltage = 111.01;
    int boostVoltage = 128;


    lemlib::OdomSensors odomSensors{   
        &vertical_tracking_wheel, // vertical tracking wheel
        nullptr,                  // no second vertical tracking wheel, set to nullptr
        &horizontal_tracking_wheel, // horizontal tracking wheel
        nullptr,                  // no second horizontal tracking wheel, set to nullptr
        &mainIMU                // IMU
    };

    lemlib::ControllerSettings lateral_controller(10, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              3, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in inches
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in inches
                                              500, // large error range timeout, in milliseconds
                                              20 // maximum acceleration (slew)
);


// angular PID controller
lemlib::ControllerSettings angular_controller(2, // proportional gain (kP)
                                              0, // integral gain (kI)
                                              10, // derivative gain (kD)
                                              3, // anti windup
                                              1, // small error range, in degrees
                                              100, // small error range timeout, in milliseconds
                                              3, // large error range, in degrees
                                              500, // large error range timeout, in milliseconds
                                              0 // maximum acceleration (slew)
);

    // 2, // small error range, in degrees
    // 80, // small error range timeout, in milliseconds
    // 3,   // large error range, in degrees
    // 500, // large error range timeout, in milliseconds
    // 0

    lemlib::ExpoDriveCurve throttle_curve(1,    // joystick deadband out of 127
    35,   // minimum output where drivetrain will move out of 127
    1.002 // expo curve gain
    );

    // input curve for steer input during driver control
    lemlib::ExpoDriveCurve steer_curve(1,   // joystick deadband out of 127
    16,  // minimum output where drivetrain will move out of 127
    1.0084 // expo curve gain
    );

    lemlib::ExpoDriveCurve arcade_turn_curve(1,   // joystick deadband out of 127
    8,  // minimum output where drivetrain will move out of 127
    1.016 // expo curve gain
    );

    lemlib::Chassis chassis{
        drivetrain,
        lateral_controller, 
        angular_controller, 
        odomSensors, 
        &throttle_curve, 
        &steer_curve};
    

}

}






