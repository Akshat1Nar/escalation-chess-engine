all: bitboard
bitboard: board/*
	cc board/*.c -o builds/bitboard
