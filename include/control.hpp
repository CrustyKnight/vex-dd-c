#ifndef CONTROL_H_
#define CONTROL_H_

#include "main.h"
#include "config.hpp"

#ifdef _DEBUG_
void drivePIDTest(pros::Controller);
#endif  // _DEBUG_

void drive_intake(pros::Controller);

void drive_clamp(pros::Controller);
void drive_extend(pros::Controller);
void drive_extend_test(pros::Controller);
void drive_peak_levels(pros::Controller);
void drive_arcade(pros::Controller, pros::MotorGroup* left_motors, pros::MotorGroup* right_motors);

#endif  // CONTROL_H_
