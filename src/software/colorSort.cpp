#include "pros/ai_vision.hpp"
#include "pros/vision.h"
#include "globals.h"
#include "software/colorSort.h"
#include <cstddef>
#include <iostream>
#include <vector>
#include <chrono>

using namespace robot::globals;
using namespace robot;

bool colorSort::isSorting = false;
uint32_t colorSort::lastDetectionTime = 0;
int colorSort::lastObjectId = -1;
int32_t objectCount, lastObjectCount;

void colorSort::resetValues() {
    isSorting = false; 
    lastDetectionTime = 0;
    lastObjectId = -1;
    objectCount = 0;
    lastObjectCount = 0;
}

void colorSort::initialize() {

    resetValues();

    imComingForU.reset();

    imComingForU.enable_detection_types(pros::AivisionModeType::objects, pros::AivisionModeType::colors);

    std::cout << "[ColorSort] Color sorting system initialized." << std::endl;
}

void colorSort::runSortColor() {
    colorSort::isSorting = true;
    
    std::cout << "[ColorSort] Color sorting started." << std::endl;

    if (isSorting) {
        auto objects = imComingForU.get_all_objects();
        for (auto &object : objects) {
            if (pros::AIVision::is_type(object, pros::AivisionDetectType::color)) {
                printf("color\n");
                printf("id %d\n", object.id);
                printf("%d %d %d %d %d\n", object.object.color.xoffset, object.object.color.yoffset, object.object.color.width, object.object.color.height, object.object.color.angle);
                lastObjectId = object.id;
                lastDetectionTime = pros::millis();
                objectCount = imComingForU.get_object_count();
                lastObjectCount = objectCount;
                printf("%d %d %d %d %d\n", lastObjectId, lastDetectionTime, objectCount, lastObjectCount, isSorting);
            }
    }
}
}

void colorSort::runSortObject() {

    colorSort::isSorting = true;

    std::cout << "[ColorSort] Object sorting started." << std::endl;

    while (true) {
        auto objects = imComingForU.get_all_objects();
        for (auto &object : objects) {
            if (pros::AIVision::is_type(object, pros::AivisionDetectType::object)) {
                printf("object\n");
                printf("id %d\n", object.id);
                printf("%d %d %d %d %d\n", object.object.element.xoffset, object.object.element.yoffset, object.object.element.width, object.object.element.height, object.object.element.score);
                lastObjectId = object.id;
                lastDetectionTime = pros::millis();
                objectCount = imComingForU.get_object_count();
                lastObjectCount = objectCount;
                printf("%d %d %d %d %d\n", lastObjectId, lastDetectionTime, objectCount, lastObjectCount, isSorting);
            }
        }
}
}