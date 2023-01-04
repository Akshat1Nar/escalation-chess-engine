#include "headers/definitions.h"
#include "headers/rook.h"

u64 get_rook_attack_mask(int square) {
	
	// attack bitboard
	u64 attacks = 0ULL;

	// rank and file respectively
	uint8_t r = (square>>3);
	uint8_t f = (square%8);
	
	// generate attacks
	for (int tr=r+1; tr<8; tr++)  attacks |= (1ULL << (tr*8+f));
	for (int tr=r-1; tr>=0; tr--) attacks |= (1ULL << (tr*8+f));
	for (int tf=f+1; tf<8; tf++) attacks |= (1ULL << (r*8+tf));
	for (int tf=f-1; tf>=0; tf--) attacks |= (1ULL << (r*8+tf));

	// return attack map for rook
	return attacks;
}


u64 get_dynamic_rook_attack_mask(int square, u64 block) {
	
	// attack bitboard
	u64 attacks = 0ULL;

	// rank and file respectively
	uint8_t r = (square>>3);
	uint8_t f = (square%8);
	
	// generate attacks
	for (int tr=r+1; tr<8; tr++)  {
		attacks |= (1ULL << (tr*8+f));
		if (block & (1ULL << (tr*8+f))) break;
	}
	for (int tr=r-1; tr>=0; tr--) {
		attacks |= (1ULL << (tr*8+f));
		if (block & (1ULL << (tr*8+f))) break;
	}
	for (int tf=f+1; tf<8; tf++) {
		attacks |= (1ULL << (r*8+tf));
		if (block & (1ULL << (r*8+tf))) break;
	}
	for (int tf=f-1; tf>=0; tf--) {
		attacks |= (1ULL << (r*8+tf));
		if (block & (1ULL << (r*8+tf))) break;
	}

	// return attack map for rook
	return attacks;
}

void initialise_rook_lookup_table() {
	
	// run through all squares
	for(int i=0; i<64; i++) {
		rook_attacks[i] = get_rook_attack_mask(i);
	}
}
