#ifndef CLAMP_H_
#define CLAMP_H_

#define CLAMP_ON 1
#define CLAMP_OFF 0
#define CLAMP_PISTON_A_PORT 'H'
#define CLAMP_PISTON_B_PORT 'G'

namespace clamp {
void set_pistons(int);
void engage();
void disengage();
}  // namespace clamp

#endif  // CLAMP_H_
