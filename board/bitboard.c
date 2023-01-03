#include "headers/definitions.h"
#include "headers/bitboard.h"
#include "headers/king.h"
#include "headers/queen.h"
#include "headers/pawn.h"
#include "headers/rook.h"
#include "headers/bishop.h"
#include "headers/knight.h"

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

void initialise_bitboards() {
	
	// iterate over piece bitboards and set the global bitboards
	for(int i=1; i<7; i++)
		chessboards[black] |= bitboards[i];
	for(int i=7; i<13; i++)
		chessboards[white] |= bitboards[i];
	chessboards[whiteblack] = chessboards[black] | chessboards[white];
}

int main() {
	initialise_bitboards();
	initialise_knight_lookup_table(); 
	initialise_pawn_lookup_table();
	initialise_bishop_lookup_table();
	initialise_rook_lookup_table();
	initialise_king_lookup_table();

	return 0;
}
