#include "headers/definitions.h"
#include "headers/knight.h"

u64 get_knight_attack_mask(uint8_t square) {
	// attack bitboard
	u64 attacks = 0ULL;

	// piece bitboard
	u64 bitboard = 0ULL;

	// put the piece on board
	set_bit(bitboard, square);

	// generate attacks
	if (not_h_file & (bitboard>>17)) attacks |= (bitboard>>17);
	if (not_a_file & (bitboard>>15)) attacks |= (bitboard>>15);
	if (not_hg_file & (bitboard>>10)) attacks |= (bitboard>>10);
	if (not_ab_file & (bitboard>>6)) attacks |= (bitboard>>6);

	if (not_a_file & (bitboard<<17)) attacks |= (bitboard<<17);
	if (not_h_file & (bitboard<<15)) attacks |= (bitboard<<15);
	if (not_ab_file & (bitboard<<10)) attacks |= (bitboard<<10);
	if (not_hg_file & (bitboard<<6)) attacks |= (bitboard<<6);

	return attacks;
	
}

void initialise_knight_lookup_table() {

	// iterate through every square on chessboard
	for (int i=0; i<64; i++)
		// get knight attack mask for square i
		knight_attacks[i] = get_knight_attack_mask(i);	
}

u64 knight_quiet_moves(int square) {

	// knight's possible moves & empty squares
	return (knight_attacks[square] & (~ chessboards[whiteblack]) );
}

u64 knight_attack_moves(int square, int side) {
	
	// knight's possible moves & opponent pieces
	return (knight_attacks[square] & (chessboards[!side]));
}

u64 get_knight_moves(int square, int side) {

	// union of quiet moves and attack moves
	return (knight_quiet_moves(square) | knight_attack_moves(square, side) );
}
