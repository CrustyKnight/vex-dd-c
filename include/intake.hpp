#ifndef INTAKE_H_
#define INTAKE_H_


void drive_intake(pros::Controller);
void intake_on();
void intake_off();
void intake_toggle();
extern bool intake_on_state;

void drive_clamp(pros::Controller);

#endif // INTAKE_H_
