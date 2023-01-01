#include "headers/bitboard.h"

void print_bitboard(u64 bitboard) {
	printf("\n");
	
	// iterating over ranks
	for(int rank=0; rank<8; rank++) {
		// iterating over files
		for(int file = 0; file<8; file++) {
			// square index
			int square = rank*8+file;
			
			// print ranks
			if (!file)
				printf(" %d ", 8 - rank);

			// print bit at current square
			printf(" %d", get_bit(bitboard, square) ? 1 : 0);
		}

		printf("\n");
	}

	// print files
	printf("\n    a b c d e f g h\n\n");

	// print the decimal equivalent of bitboard
	printf("      bitboard: %llu\n\n", bitboard);
}

void print_board() {
	printf("\n");
	
	// iterating over ranks
	for(int rank=0; rank<8; rank++) {
		// iterating over files
		for(int file = 0; file<8; file++) {
			// square index
			int square = rank*8+file;
			
			// print ranks
			if (!file)
				printf(" %d ", 8 - rank);

			// iterate over the pieces
			for (int i=1; i<13; i++) {
				if (get_bit(bitboards[i], square))
					printf (" %c", ascii[i]);	
			}

		}

		printf("\n");
	}

	// print files
	printf("\n    a b c d e f g h\n\n");
}

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

u64 get_pawn_attack_mask(int square, int side) {
	
	// attack bitboard
	u64 attacks = 0ULL;

	// piece bitboard
	u64 bitboard = 0ULL;
	
	// set the piece on board
	set_bit(bitboard, square);

	// white pawn attack
	if(side) {
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

void initialise_bishop_lookup_table() {
	
	// run through all squares
	for(int i=0; i<64; i++) {
		bishop_attacks[i] = get_bishop_attack_mask(i);
	}
}


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

	// return attack map for bishop
	return attacks;
}

void initialise_rook_lookup_table() {
	
	// run through all squares
	for(int i=0; i<64; i++) {
		rook_attacks[i] = get_rook_attack_mask(i);
	}
}


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
	attacks |= get_pawn_attack_mask(square, white);
	attacks |= get_pawn_attack_mask(square, black);

	// return attack map for bishop
	return attacks;
}

void initialise_king_lookup_table() {
	
	// run through all squares
	for(int i=0; i<64; i++) {
		king_attacks[i] = get_king_attack_mask(i);
		print_bitboard(king_attacks[i]);
	}
}

int main() {
	
	initialise_knight_lookup_table(); 
	initialise_pawn_lookup_table();
	initialise_bishop_lookup_table();
	initialise_rook_lookup_table();
	initialise_king_lookup_table();

	return 0;
}
