all: bitboard 0x88
bitboard: board/bitboard.c
	cc board/bitboard.c -o builds/bitboard
0x88: board/0x88.c
	cc board/0x88.c -o builds/0x88
