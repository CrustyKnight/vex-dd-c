#include "main.h"
#include "clamp.hpp"

namespace clamp {

bool state = false;
pros::adi::DigitalOut piston_a(CLAMP_PISTON_A_PORT);
pros::adi::DigitalOut piston_b(CLAMP_PISTON_B_PORT);

void set_pistons(int value) {
  piston_a.set_value(value);
  piston_b.set_value(value);
}

void engage() { set_pistons(CLAMP_ON); }
void disengage() { set_pistons(CLAMP_OFF); }

}  // namespace clamp
