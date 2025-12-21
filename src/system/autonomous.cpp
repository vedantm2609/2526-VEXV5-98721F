#include "robot/autonomous.h"
#include "globals.h"

using namespace robot;
using namespace robot::globals;

void autonomous::initialize() {
    chassis.calibrate();
    chassis.setPose(0, 0, 0);
    
    // Set brake mode for all drive motors
    RightFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    RightBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LeftFront.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LeftBack.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    RightMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    LeftMiddle.set_brake_mode(pros::E_MOTOR_BRAKE_BRAKE);
    
    std::cout << "[AUTONOMOUS] Autonomous system initialized" << std::endl;
}

void autonomous::blueLeft() {
    std::cout << "[AUTONOMOUS] Starting Blue Left autonomous routine..." << std::endl;
    
    // Set starting pose to first point from blueLeft.txt
    chassis.setPose(66.335, -13.49, 270); // Start facing west
    
    // Phase 1: Fast straight movement using moveToPoint
    std::cout << "[PHASE 1] Fast approach phase" << std::endl;
    chassis.moveToPoint(60.17, -18.589, 2000, {
        .forwards = true,
        .maxSpeed = 100,
        .minSpeed = 30
    });
    
    chassis.moveToPoint(55.547, -22.413, 2000, {
        .forwards = true,
        .maxSpeed = 100,
        .minSpeed = 30
    });
    
    chassis.moveToPoint(50.923, -26.237, 2000, {
        .forwards = true,
        .maxSpeed = 100,
        .minSpeed = 30
    });
    
    // Phase 2: Curve section with heading control using moveToPose
    std::cout << "[PHASE 2] Curve navigation with heading control" << std::endl;
    chassis.moveToPose(46.299, -30.061, 225, 3000, {
        .forwards = true,
        .maxSpeed = 98,
        .minSpeed = 25
    });
    
    chassis.moveToPose(43.217, -32.61, 200, 3000, {
        .forwards = true,
        .maxSpeed = 93,
        .minSpeed = 25
    });
    
    // Phase 3: Sharp direction change using swing movements
    std::cout << "[PHASE 3] Direction change with swing maneuvers" << std::endl;
    chassis.swingToPoint(39.625, -31.674, lemlib::DriveSide::RIGHT, 2500, {
        .forwards = true,
        .maxSpeed = 87,
        .minSpeed = 20
    });
    
    chassis.swingToPoint(36.004, -29.977, lemlib::DriveSide::LEFT, 2500, {
        .forwards = true,
        .maxSpeed = 82,
        .minSpeed = 20
    });
    
    // Phase 4: Precision control with moveToPose
    std::cout << "[PHASE 4] Precision navigation" << std::endl;
    chassis.moveToPose(32.665, -27.778, 60, 3000, {
        .forwards = true,
        .maxSpeed = 80,
        .minSpeed = 20
    });
    
    chassis.moveToPose(29.276, -25.654, 75, 3000, {
        .forwards = true,
        .maxSpeed = 74,
        .minSpeed = 20
    });
    
    chassis.moveToPose(25.811, -23.656, 90, 3000, {
        .forwards = true,
        .maxSpeed = 67,
        .minSpeed = 18
    });
    
    // Phase 5: Final approach with turn and move combinations
    std::cout << "[PHASE 5] Final approach sequence" << std::endl;
    
    // Turn to optimal angle for final approach
    chassis.turnToHeading(120, 2000, {
        .direction = lemlib::AngularDirection::AUTO,
        .maxSpeed = 60
    });
    
    // Swing maneuvers for tight navigation (CORRECTED - only swingToPoint exists)
    chassis.turnToHeading(135, 1500); // Turn first, then swing
    chassis.swingToPoint(22.31, -21.721, lemlib::DriveSide::RIGHT, 2500, {
        .forwards = true,
        .maxSpeed = 59,
        .minSpeed = 15
    });
    
    chassis.swingToPoint(18.999, -19.558, lemlib::DriveSide::LEFT, 2500, {
        .forwards = true,
        .maxSpeed = 49,
        .minSpeed = 15
    });
    
    // Phase 6: Very precise final positioning
    std::cout << "[PHASE 6] Final positioning" << std::endl;
    
    // Turn to face final target
    chassis.turnToPoint(13.343, -13.212, 2000);
    
    // Slow, precise movement to penultimate position
    chassis.moveToPoint(15.007, -15.079, 3000, {
        .forwards = true,
        .maxSpeed = 30,
        .minSpeed = 10
    });
    
    // Another turn for final alignment
    chassis.turnToHeading(90, 1500, {
        .direction = lemlib::AngularDirection::AUTO,
        .maxSpeed = 40
    });
    
    // Final precise positioning
    chassis.moveToPose(13.343, -13.212, 90, 3000, {
        .forwards = true,
        .maxSpeed = 20,
        .minSpeed = 8
    });
    
    // Ensure complete stop
    chassis.tank(0, 0);
    
    // Final position report
    lemlib::Pose finalPose = chassis.getPose();
    std::cout << "[AUTONOMOUS] Blue Left complete! Final position: (" 
              << finalPose.x << ", " << finalPose.y << ", " << finalPose.theta << "°)" << std::endl;
}