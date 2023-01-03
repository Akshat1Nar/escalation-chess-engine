#include "headers/definitions.h"
#include "headers/king.h"

u64 get_king_attack_mask(int square) {
	
	// attack bitboard
	u64 attacks = 0ULL;

	// piece bitboard
	u64 bitboard = 0ULL;

	// set piece on bitboard
	set_bit(bitboard, square);
	
	// generate king attacks
	if (bitboard >> 8) attacks |= (bitboard>>8);
	if (bitboard << 8) attacks |= (bitboard<<8);
	if (not_h_file & (bitboard >> 1)) attacks |= (bitboard >> 1);
	if (not_a_file & (bitboard << 1)) attacks |= (bitboard << 1);
	if (not_a_file & (bitboard>>7)) attacks |= (bitboard>>7);
	if (not_h_file & (bitboard>>9)) attacks |= (bitboard>>9);
	if (not_h_file & (bitboard<<7)) attacks |= (bitboard<<7);
	if (not_a_file & (bitboard<<9)) attacks |= (bitboard<<9);

	// return attack map for bishop
	return attacks;
}

void initialise_king_lookup_table() {
	
	// run through all squares
	for(int i=0; i<64; i++) {
		king_attacks[i] = get_king_attack_mask(i);
	}
}
