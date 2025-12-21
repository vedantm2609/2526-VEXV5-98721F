#pragma once

/**
 * @file odometry.h
 * @brief Contains the declaration of the Odometry class.
 */

namespace robot {
    /**
     * @class Odometry
     * @brief Represents the odometry system of the robot.
     *
     * The Odometry class is responsible for tracking the position and orientation
     * of the robot using sensors such as encoders and IMUs. It provides functions
     * to update the robot's pose based on sensor readings and retrieve the current
     * position and orientation.
     */
    class Odometry {
    public:
        /**
         * @brief Initializes the Odometry object.
         *
         * This constructor is responsible for initializing the Odometry object
         * and setting default values.
         */
        Odometry();

        /**
         * @brief Updates the robot's pose.
         *
         * This function updates the robot's position and orientation based on
         * sensor readings from encoders and IMUs.
         */
        void updatePose();

        /**
         * @brief Retrieves the current position of the robot.
         *
         * @return A structure containing the x and y coordinates of the robot.
         */
        void getPosition(); 

        /**
         * @brief Retrieves the current orientation of the robot.
         *
         * @return The heading angle of the robot in degrees.
         */
        double getOrientation();

    };

}