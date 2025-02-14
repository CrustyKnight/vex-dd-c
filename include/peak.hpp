#ifndef PEAK_H_
#define PEAK_H_

void set_peak_power(int power);
void adjust_intake_level(int height, int power);

namespace peak {
void raise_to_level(int level);
int inc_level(int level);
int dec_level(int level);
void init();
}  // namespace peak

#endif
