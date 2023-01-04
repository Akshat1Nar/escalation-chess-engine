#include "headers/definitions.h"
#include "headers/bishop.h"

u64 get_bishop_attack_mask(int square) {

	// attack bitboard
	u64 attacks = 0ULL;

	// rank and file respectively
	uint8_t r = (square>>3);
	uint8_t f = (square%8);
	
	// generate attacks
	for (int tr=r+1, tf=f+1; tr<8 && tf<8; tr++, tf++) attacks |= (1ULL << (tr*8+tf));
	for (int tr=r+1, tf=f-1; tr<8 && tf>=0; tr++, tf--) attacks |= (1ULL << (tr*8+tf));
	for (int tr=r-1, tf=f+1; tr>=0 && tf<8; tr--, tf++) attacks |= (1ULL << (tr*8+tf));
	for (int tr=r-1, tf=f-1; tr>=0 && tf>=0; tr--, tf--) attacks |= (1ULL << (tr*8+tf));

	// return attack map for bishop
	return attacks;
}

u64 get_dynamic_bishop_attack_mask(int square, int block) {

	// attack bitboard
	u64 attacks = 0ULL;

	// rank and file respectively
	uint8_t r = (square>>3);
	uint8_t f = (square%8);
	
	// generate attacks
	for (int tr=r+1, tf=f+1; tr<8 && tf<8; tr++, tf++) {
		attacks |= (1ULL << (tr*8+tf));
		if (block & (1ULL << (tr*8+tf))) break;
	}
	for (int tr=r+1, tf=f-1; tr<8 && tf>=0; tr++, tf--) {
		attacks |= (1ULL << (tr*8+tf));
		if (block & (1ULL << (tr*8+tf))) break;
	}
	for (int tr=r-1, tf=f+1; tr>=0 && tf<8; tr--, tf++) {
		attacks |= (1ULL << (tr*8+tf));
		if (block & (1ULL << (tr*8+tf))) break;
	for (int tr=r-1, tf=f-1; tr>=0 && tf>=0; tr--, tf--) {
		attacks |= (1ULL << (tr*8+tf));
		if (block & (1ULL << (tr*8+tf)));
	}

	// return attack map for bishop
	return attacks;
}

void initialise_bishop_lookup_table() {
	
	// run through all squares
	for(int i=0; i<64; i++) {
		bishop_attacks[i] = get_bishop_attack_mask(i);
	}
}
