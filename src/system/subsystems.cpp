#include "pros/misc.h"
#include "pros/rtos.hpp"
#include "robot/autonomous.h"
#include "robot/subsystems.h"
#include "globals.h"
#include "lemlib/api.hpp"

using namespace lemlib;
using namespace robot::globals;
using namespace robot;

#define delayTime 10

// Static variables for boost function
static int boostLevel = 0; // 0 = normal, 1 = medium boost, 2 = max boost
static bool l1WasPressed = false;

robot::Subsystems::Subsystems() {}

void robot::Subsystems::initialize() {
    printf("[SUBSYSTEMS] Initializing subsystems...\n");
    
    
    // Set initial pneumatic states
    descore.retract();
    matchLoader.retract();
    
    // Stop all motors initially
    chainHoist1.move_voltage(0);
    chainHoist2.move_voltage(0);
    chainHoist3.move_voltage(0);

    regularVoltage = 111.01; // Default voltage

    printf("[SUBSYSTEMS] Subsystems initialized successfully\n");
    printf("[SUSBSYTEMS] Regular Voltage set to 111.01");
    printf("[SUBSYSTEMS] Ready for operation\n");
}

pros::Task robot::Subsystems::update() {
    // This function can be used for periodic updates of subsystem states
    // For now, it's mainly used for monitoring and diagnostics
    
    // Monitor motor temperatures
    double chainHoist1Temp = chainHoist1.get_temperature();
    double chainHoist2Temp = chainHoist2.get_temperature();
    double chainHoist3Temp = chainHoist3.get_temperature();

    
    // Warning if any motor gets too hot (above 50°C)
    if (chainHoist1Temp > 50 || chainHoist2Temp > 50 || 
        chainHoist3Temp > 50) {
        printf("[SUBSYSTEMS] WARNING: Chain hoist motor temperature high!\n");
    }
    
    // Monitor motor voltages for debugging
    

}

void robot::Subsystems::stop() {
    printf("[SUBSYSTEMS] Emergency stop - stopping all subsystems\n");
    
    // Stop all chain hoist motors
    chainHoist1.move_voltage(0);
    chainHoist2.move_voltage(0);
    chainHoist3.move_voltage(0);

    chainHoist1.brake();
    chainHoist2.brake();
    chainHoist3.brake();


    
    // Retract all pneumatics to safe position
    //helperIntake1.retract();
    //helperIntake2.retract();
    //flapPneumatic.retract();
    //isExtended = false;
    
    printf("[SUBSYSTEMS] All subsystems stopped and in safe state\n");
}

void robot::Subsystems::start() {
    // Get controller inputs
    bool l2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2);
    bool r1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    bool r2 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2);
    bool l1 = controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    bool x = controller.get_digital(pros::E_CONTROLLER_DIGITAL_X);
    bool b = controller.get_digital(pros::E_CONTROLLER_DIGITAL_B);
    bool a = controller.get_digital(pros::E_CONTROLLER_DIGITAL_A);



    printf("[CHAINHOIST] Button states - L1:%d L2:%d R1:%d R2:%d\n", l2, r1, r2);

    // Calculate voltage values based on regularVoltag 
    int voltageInt = (int)regularVoltage;
    int negativeVoltageInt = -voltageInt;

    // Only move if buttons are actually pressed (prevents drift)
    if (r1) {
        printf("[CHAINHOIST] R1 PRESSED - Top rack mode\n");
        chainHoist1.move_voltage(-voltageInt);
        chainHoist2.move_voltage(-voltageInt);
        chainHoist3.move_voltage(-voltageInt);
        printf("[CHAINHOIST] Motors set - ChainHoist: %d mV\n", -voltageInt);

    } else if (r2) {
        printf("[CHAINHOIST] R2 PRESSED - Middle rack mode\n");
        chainHoist1.move_voltage(-voltageInt);
        chainHoist2.move_voltage(-voltageInt);
        chainHoist3.move_voltage(voltageInt);
        printf("[CHAINHOIST] Motors set - ChainHoist1,2: %d mV, ChainHoist3: %d mV\n", 
               -voltageInt, voltageInt);

    } else if (l2) {
        printf("[CHAINHOIST] L2 PRESSED - Custom mode\n");
        chainHoist1.move_voltage(voltageInt);
        printf("[CHAINHOIST] Motors set - ChainHoist1: %d mV\n", voltageInt);
    
    } else if (x) {
        printf("[CHAINHOIST] X PRESSED - Intake Only\n");
        chainHoist1.move_voltage(-voltageInt);
        printf("[CHAINHOIST] Motors set - ChainHoist1: %d mV\n", voltageInt);

    } else if (b) {
        printf("[CHAINHOIST] B PRESSED - Stall\n");
        chainHoist1.move_voltage(negativeVoltageInt);
        chainHoist2.move_voltage(negativeVoltageInt);
        chainHoist3.move_voltage(negativeVoltageInt);
        printf("[CHAINHOIST] Motors set - ChainHoist: %d mV\n", negativeVoltageInt);

    } else if (a) {
        printf("[CHAINHOIST] A PRESSED - Descoring\n");
        descore.extend();
        printf("[DESCORE] Pneumatic extended\n");

    }
}


void robot::Subsystems::run() {
    pros::delay(delayTime);
    start();

    if (controller.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y)) {
        while(true) {
            update();
            pros::delay(10000);
        }
    }
}