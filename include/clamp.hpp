#ifndef CLAMP_H_
#define CLAMP_H_

#define CLAMP_ON 1
#define CLAMP_OFF 0
#define CLAMP_PISTON_A_PORT 'H'
#define CLAMP_PISTON_B_PORT 'G'

void clamp_pistons_set(int);
void clamp_engage();
void clamp_disengage();
void clamp_toggle();

#endif  // CLAMP_H_
