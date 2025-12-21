#pragma once

/**
 * @file autonomous.h
 * @brief Contains the declaration of autonomous routines.
 */

namespace robot {
    /**
     * @namespace autonomous
     * @brief Contains autonomous routines for the robot.
     *
     * This namespace encapsulates various autonomous routines that the robot can
     * execute during the autonomous phase of a competition. Each routine is
     * implemented as a separate function.
     */
    class autonomous {
        public:
        /**
         * @brief Executes the default autonomous routine.
         *
         * This function contains the logic for the default autonomous routine.
         * It is called during the autonomous phase of a competition.
         */
        void initialize();
        void disabled();
        /**
         * @brief Executes the red left autonomous routine.
         *
         *
         * This function contains the logic for the red left autonomous routine.
         *
          */

        void redLeft();

          /**
         * @brief Executes the red right autonomous routine.
         *
         *
         * This function contains the logic for the red right autonomous routine.
         *
          */
        
        void redRight();

          /**
         * @brief Executes the blueleft autonomous routine.
         *
         *
         * This function contains the logic for the blue left autonomous routine.
         *
          */

        void blueLeft();

          /**
         * @brief Executes the blue right autonomous routine.
         *
         *
         * This function contains the logic for the blue right autonomous routine.
         *
          */

        void blueRight();

        private:
        
        bool allianceColor;


    }; // namespace autonomous
}