
// state at which random number generation begins
// seed
unsigned int state = 1804289383;

unsigned int generate_random_number() {
	
	// xor shift algorithms
	unsigned int x = state;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;

	// update the state
	state = x;
	return state;
}

u64 random_u64() {

	// 64 bit numbers
	u64 x1, x2, x3, x4;

	// this sets only first 16 bits
	x1 = (u64)(generate_random_number()) & 0xFFFF; 
	x2 = (u64)(generate_random_number()) & 0xFFFF; 
	x3 = (u64)(generate_random_number()) & 0xFFFF; 
	x4 = (u64)(generate_random_number()) & 0xFFFF; 

	// convert four 16-bit numbers to one 64 bit number
	return (x1<<48) | (x<<32) | (x1<<16) | x1;
}

u64 random_fewbits() {
	return random_u64() & random_u64() & random_u64();
}
