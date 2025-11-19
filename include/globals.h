#include <vector>
#include <string>
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/misc.hpp"
#include "pros/motor_group.hpp"
#include "lemlib/api.hpp" // IWYU pragma: keep
#include "pros/motors.hpp"
#include "pros/motors.h"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"
#include "pros/vision.h"
#include "main.h"
#include "lemlib/chassis/chassis.hpp"


namespace robot {
namespace globals {

extern pros::Controller controller;

extern pros::Motor RightFront;
extern pros::Motor RightBack;
extern pros::Motor LeftFront;
extern pros::Motor LeftBack;

// Function to initialize motor brake modes

extern pros::MotorGroup driveRight;
extern pros::MotorGroup driveLeft;

extern pros::adi::Pneumatics helperIntake1; 
extern pros::adi::Pneumatics helperIntake2; 
extern pros::adi::Pneumatics flapPneumatic;

extern pros::Motor chainHoist1;
extern pros::Motor chainHoist2;
extern pros::Motor chainHoist3;
extern pros::MotorGroup chainHoistMotors;

extern pros::Imu mainIMU;
extern pros::Rotation horizontalRotation;
extern pros::Rotation verticalRotation;

extern pros::AIVision imComingForU; // AI vision sensor
extern lemlib::TrackingWheel horizontal_tracking_wheel;
extern lemlib::TrackingWheel vertical_tracking_wheel;

extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors odomSensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::ExpoDriveCurve throttle_curve;
extern lemlib::ExpoDriveCurve steer_curve;
extern lemlib::ExpoDriveCurve arcade_turn_curve;
extern lemlib::Chassis chassis;

extern int MotorVoltage;
extern int HalfMotorVoltage;
extern double regularVoltage;
extern int boostVoltage;
}

}
