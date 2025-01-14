#include "peak.hpp"
#include "config.hpp"
#include "lemlib/api.hpp"  // IWYU pragma: keep
#include <math.h>
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
int level = 0;
int height = 0;        // inches
int teeth_height = 0;  // teeth

pros::Motor motor(PEAK_MOTOR_PORT, pros::MotorGearset::red);
bool moving() { return (std::floor(motor.get_actual_velocity()) != 0); }
bool still() { return (std::floor(motor.get_actual_velocity()) == 0); }
void extend(double inches) {
  double teeth = inches * LINEAR_SLIDE_TEETH_PER_INCH;
  double revs = teeth / PEAK_GEAR_TEETH;
  int possible_teeth_height = teeth_height + teeth;
  if (possible_teeth_height > LINEAR_SLIDE_MAX_TEETH_HEIGHT) {
    throw std::invalid_argument("Attempt to extend too high");
  } else if (possible_teeth_height < 0) {
    throw std::invalid_argument("Attempt to extend too low");
  }
  teeth_height = possible_teeth_height;
  motor.move_relative(revs, 100);
}

void extend_to(double inches) {
  int teeth_target = inches * LINEAR_SLIDE_TEETH_PER_INCH;
  int teeth_difference = teeth_target - teeth_height;
  int teeth = teeth_difference;
  double revs = teeth / PEAK_GEAR_TEETH;
  int possible_teeth_height = teeth_height + teeth;
  if (possible_teeth_height > LINEAR_SLIDE_MAX_TEETH_HEIGHT) {
    throw std::invalid_argument("Attempt to extend too high");
  } else if (possible_teeth_height < 0) {
    throw std::invalid_argument("Attempt to extend too low");
  }
  teeth_height = possible_teeth_height;
  motor.move_relative(revs, 100);
}
void level_up() {
  // motor.move_relative(7 * (LINEAR_SLIDE_SECTION_TEETH / PEAK_GEAR_TEETH), 100);
  extend(17.5);
  level++;
}
void level_down() {
  // motor.move_relative(-7 * (LINEAR_SLIDE_SECTION_TEETH / PEAK_GEAR_TEETH), 100);
  extend(-17.5);
  level--;
}

void raise_vertical(double inches) { extend(inches * PEAK_COSECANT); }

void raise_to(double inches) {
  extend_to(inches * PEAK_COSECANT);
}

}  // namespace peak
