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

int main() {

	 // Print all piece encodings	
	 // for(uint8_t i=1; i<13; i++) 
	 //	print_bitboard(bitboards[i]);
	 print_board();
	return 0;
}
