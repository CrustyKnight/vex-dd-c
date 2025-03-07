#ifndef INTAKE_H_
#define INTAKE_H_

namespace intake {
void init();
void on();
void off();
void set_power(int);
void run_forward(int);
void run_backward(int);
void eat_donut(float);
void eat_donut();
void swallow();
void digest_donut();
void pass(int percentage);
}  // namespace intake

void intake_on();
void intake_off();
void set_intake_power(int);
void run_intake_forward(int);
void run_intake_backward(int);
void pull_up_donut(int);

#endif  // INTAKE_H_
