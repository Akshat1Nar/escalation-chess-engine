#include "headers/0x88.h"

uint8_t get_0x88_index(uint8_t sq8x8) {
	return (sq8x8 + (sq8x8 & ~7));
}

void print_board() {
	for (uint8_t i=0; i<8; i++) {
		for (uint8_t j=0; j<16; j++) {
			uint8_t dest = board[16*i+j];
			if (dest & 0x88)
				continue;

			printf("%c ", ascii[dest]);
		}
	printf("\n");
	}
}

int main() {
	print_board();
	printf("%d\n", get_0x88_index(0));
	printf("%d\n", get_0x88_index(11));
	printf("%d\n", get_0x88_index(63));
	return 0;
}
