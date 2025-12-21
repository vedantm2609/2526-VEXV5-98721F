#pragma once
#include "lemlib/api.hpp"
#include "robot/autonomous.h"

namespace software {
    class autonSelect {
        public: 
            autonSelect();


            enum AUTON_SELECTOR {BLUE_LEFT = 0, BLUE_RIGHT = 1, RED_LEFT = 2, RED_RIGHT = 3};

            AUTON_SELECTOR autonSelector;

            void switchAuton();

            std::string toggleAuton;

            void runSelector();


    };
}