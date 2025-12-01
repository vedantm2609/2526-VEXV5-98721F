#pragma once
#include "lemlib/api.hpp"

/**
 * @file colorSort.h
 * @brief Contains color sorting utility functions.
 */

namespace robot {
    class colorSort {
        public:
            /**
             * @brief Sorts colors based on predefined criteria.
             * 
             * This function takes an array of colors and sorts them
             * according to specific rules defined within the method.
             * 
             * @param colors An array of color values to be sorted.
             * @return A sorted array of color values.
             */
            static void initialize();

            static void sortColors();

            static void stopSort();

    private:
            static bool isSorting;

            
    };
}