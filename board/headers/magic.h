#ifndef MAGIC_H
#define MAGIC_H

// state i.e. seed for random number generation
extern unsigned int state;

// 32 bit pseudo random number generation algorithm (XOR shift algo)
unsigned int generate_random_number();

// generate random 64 bit number
u64 random_u64();

// get random few bits
// used for magic number generation
u64 random_fewbits();

#endif // MAGIC_H
