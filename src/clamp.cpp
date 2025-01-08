#include "main.h"
#include "clamp.hpp"

bool clamp_on_state = false;

pros::adi::DigitalOut clamp_piston_a(CLAMP_PISTON_A_PORT);
pros::adi::DigitalOut clamp_piston_b(CLAMP_PISTON_B_PORT);

void clamp_pistons_set(int value) {
  clamp_piston_a.set_value(value);
  clamp_piston_b.set_value(value);
}
void clamp_engage() {
  clamp_on_state = true;
  clamp_pistons_set(CLAMP_ON);
}
void clamp_disengage() {
  clamp_on_state = false;
  clamp_pistons_set(CLAMP_OFF);
}
void clamp_toggle() {
  if (clamp_on_state) {
    clamp_disengage();
  } else {
    clamp_engage();
  }
}
