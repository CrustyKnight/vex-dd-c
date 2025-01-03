#ifndef INTAKE_H_
#define INTAKE_H_


void drive_intake(pros::Controller);
void intake_on();
void intake_off();
void intake_toggle();
void set_intake_power(int8_t);
extern bool intake_on_state;

void drive_clamp(pros::Controller);
void drive_extend(pros::Controller);

#endif // INTAKE_H_
