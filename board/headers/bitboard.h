#ifndef BITBOARD_H
#define BITBOARD_H

// function to print a chessboard for a given piece type
void print_bitboard(u64 bitboard);

// function to print the chessboard
void print_board();

// function to initialise knight attack lookup table 
void initialise_knight_lookup_table();

#endif
