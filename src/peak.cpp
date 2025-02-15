#include "peak.hpp"
#include "config.hpp"
#include "lemlib/api.hpp"  // IWYU pragma: keep
#include <math.h>
#include <cstdio>
#include <stdexcept>

/// All functions for now will be written based off the fact that our intake has a angle to the horizontal of ~55*
// For now all these constants ARE ESTIMATES, THEY MUST BE REPLACED WITH REAL NUMBERS NEXT.
// Constants are estimated heights that are needed

// Peak power/direction & Different peak heights' constant declarations (in inches)
int peak_power = 100;
int peak_dir = 1;
// float DEFAULT_HEIGHT = 0.0;
// float ALLIANCE_STAKE_HEIGHT = 5.0;
// float WALL_STAKE_HEIGHT = 10.0;
// float ENDGAME_HEIGHT = 7.5;
int PEAK_LENGTH = 14;
int peak_current_level = 0;

// Motor declaration
pros::Motor peak_motor(8, pros::MotorGearset::red);
// Functions written out here
void set_peak_power(int power) {
  peak_power = power;
}

void peak_init() {
  peak_motor.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS);
}
// In a right triangle, height is y, and peak length is hypotenuse. Therefore, sin function must be used
void adjust_intake_level(int height, int power) {
  if (height < 0) {
    peak_dir = -1;
  } else {
    peak_dir = 1;
  }
  while (PEAK_LENGTH * sin((double)(peak_motor.get_position())) != height) {
    peak_motor.move(peak_dir * peak_power);
  }
}

bool peak_is_moving() { return (std::floor(peak_motor.get_actual_velocity()) != 0); }
bool peak_is_still() { return (std::floor(peak_motor.get_actual_velocity()) == 0); }

void peak_up_level() {
  peak_motor.move_relative(7 * (LINEAR_SLIDE_SECTION_TEETH / PEAK_GEAR_TEETH), 100);
  peak_current_level++;
}
void peak_down_level() {
  peak_motor.move_relative(-7 * (LINEAR_SLIDE_SECTION_TEETH / PEAK_GEAR_TEETH), 100);
  peak_current_level++;
}

namespace peak {
double height = 0;        // inches
double teeth_height = 0;  // teeth

pros::Motor motor(PEAK_MOTOR_PORT, pros::MotorGearset::red);
void init() { motor.set_encoder_units(pros::E_MOTOR_ENCODER_ROTATIONS); }
bool moving() { return (std::floor(motor.get_actual_velocity()) != 0); }
bool still() { return (std::floor(motor.get_actual_velocity()) == 0); }

void extend_teeth(double teeth) {
  double revs = teeth / PEAK_GEAR_TEETH;
  double possible_teeth_height = teeth_height + teeth;
  if (possible_teeth_height > LINEAR_SLIDE_MAX_TEETH_HEIGHT) {
    throw std::invalid_argument("Attempt to extend too high: " + std::to_string(possible_teeth_height) + "teeth.");
  } else if (possible_teeth_height < 0) {
    throw std::invalid_argument("Attempt to extend too low");
  }
  teeth_height = possible_teeth_height;
  motor.move_relative(revs, 100);
}

void extend(double inches) {
  double teeth = inches * LINEAR_SLIDE_TEETH_PER_INCH;
  extend_teeth(teeth);
}

void extend_to(double inches) {
  double teeth_target = inches * LINEAR_SLIDE_TEETH_PER_INCH;
  std::printf("%f\n", teeth_target);
  double teeth_difference = teeth_target - teeth_height;
  double teeth = teeth_difference;
  extend_teeth(teeth);
  // double revs = teeth / PEAK_GEAR_TEETH;
  // int possible_teeth_height = teeth_height + teeth;
  // if (possible_teeth_height > LINEAR_SLIDE_MAX_TEETH_HEIGHT) {
  //   throw std::invalid_argument("Attempt to extend too high: " + std::to_string(possible_teeth_height) + "teeth.");
  // } else if (possible_teeth_height < 0) {
  //   throw std::invalid_argument("Attempt to extend too low");
  // }
  // teeth_height = possible_teeth_height;
  // motor.move_relative(revs, 100);
}

void extend_to_revs(double revs) {
  // 2.169 revolutions to mogo.
  double teeth_target = std::floor(revs * PEAK_GEAR_TEETH);
  double teeth_difference = teeth_target - teeth_height;
  double teeth = teeth_difference;
  extend_teeth(teeth);
}

void raise_vertical(double inches) { extend(inches * PEAK_COSECANT); }

void raise_to(double inches) {
  extend_to(inches * PEAK_COSECANT);
}

void raise_to_level(int level) {
  switch (level) {
    case 0:
      extend_to(PEAK_LEVEL_REST);
      break;
    case 1:
      // 2.169 revolutions to mogo.
      extend_to(PEAK_LEVEL_MOGO);
      // extend_to_revs(2.169);
      break;
    case 2:
      extend_to(PEAK_LEVEL_ALLIANCE);
      break;
    case 3:
      extend_to(PEAK_LEVEL_WALL);
      break;
    case -1:  // go down
      motor.move(-100);
      // teeth_height = 0;
      break;
    case -2:
      motor.move(100);
      // teeth_height = 0;
      break;
    case -3:
      motor.move(0);
      break;
  }
}
int inc_level(int level) {
  if (level == 3) {
    throw std::invalid_argument("Level already at max!");
  }
  raise_to_level(level + 1);
  return level + 1;
}
int dec_level(int level) {
  if (level == 0) {
    throw std::invalid_argument("Level already at min!");
  }
  raise_to_level(level - 1);
  return level - 1;
}

}  // namespace peak
