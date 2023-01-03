#include "headers/definitions.h"
#include "headers/pawn.h"

u64 get_pawn_attack_mask(int square, int side) {
	
	// attack bitboard
	u64 attacks = 0ULL;

	// piece bitboard
	u64 bitboard = 0ULL;
	
	// set the piece on board
	set_bit(bitboard, square);

	// white pawn attack
	if(!side) {
		if (not_a_file & (bitboard>>7)) attacks |= (bitboard>>7);
		if (not_h_file & (bitboard>>9)) attacks |= (bitboard>>9);
	}
	else {
		if (not_h_file & (bitboard<<7)) attacks |= (bitboard<<7);
		if (not_a_file & (bitboard<<9)) attacks |= (bitboard<<9);
	}

	return attacks;
}

void initialise_pawn_lookup_table() {
	
	// iterate through all squares
	for (int i=0; i<64; i++) {
		pawn_attacks[white][i] = get_pawn_attack_mask(i, white);
		pawn_attacks[black][i] = get_pawn_attack_mask(i, black);
	}
}

u64 pawn_quiet_moves(int square, int side) {
	
	// moves bitboard
	u64 moves = 0ULL;

	// current position of pawn bitboard
	u64 bitboard = 0ULL;

	// set the pawn on bitboard
	set_bit(bitboard, square);
	
	// pawn push one step forward
	// white side
	if ( !side ) {
		if (!( (bitboard>>8) & (chessboards[whiteblack] & (bitboard>>8))) ) {
			moves |= (bitboard>>8);
		}
	}
	// black side
	else {
		if (!( (bitboard<<8) & (chessboards[whiteblack] & (bitboard<<8))) ) {
			moves |= (bitboard<<8);
		}
	}

	// double pawn push
	// white side
	if ( !side ) {
		// additional check for pawn on second rank
		// and for no obstuction, moves != 0ULL
		if ( (second_rank & bitboard) && (moves))
		if (!( (bitboard>>16) & (chessboards[whiteblack] & (bitboard>>16))) ) {
			moves |= (bitboard>>16);
		}
	}
	// black side
	else {
		if ((seventh_rank & bitboard) && (moves))
		if (!( (bitboard<<16) & (chessboards[whiteblack] & (bitboard<<16))) ) {
			moves |= (bitboard<<16);
		}
	}

	return moves;
}

u64 pawn_capture_moves(int square, int side) {
	
	// pawn captures are given by
	// pawn lookup table & opponent pieces
	return pawn_attacks[side][square] & chessboards[!side];
}

u64 get_pawn_moves(int square, int side) {
	return pawn_quiet_moves(square, side) | pawn_capture_moves(square, side);
}
