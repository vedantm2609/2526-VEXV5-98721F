#pragma once
#include "pros/rtos.hpp"
#include <string>
    

/**
 * @file subsystems.h
 * @brief Contains the declaration of the robot subsystems.
 */


/**
 * @namespace robot
 * 
 * This namespace is responsible to encapsulate
 * all classes and functions other than the drivetrain.
 * 
 */
namespace robot {

    class Subsystems {

    public:

        Subsystems();
        /**
         * @brief Initializes all robot subsystems.
         * 
         * This function initializes all the subsystems of the robot,
         * such as the arm, intake, and other mechanisms.
         */


        void initialize();


       
        /**
         * @brief Updates all robot subsystems.
         * 
         * This function updates the state of all the subsystems of the robot.
         * It should be called periodically in the main control loop.
         */
        pros::Task update();

        /**
         * @brief Stops all robot subsystems.
         * 
         * This function stops all the subsystems of the robot,
         * bringing them to a safe state.
         */
        void stop();

        /**
         * @brief Runs all mechanisms of subsysytems.
         * 
         * This function runs all the mechanisms of the subsystems, 
         * excluding the drivetrain. 
         *
         *
         */
        
        void start();

        void run();
        
    }; // namespace Subsystems


}

