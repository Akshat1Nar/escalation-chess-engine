#include "headers/definitions.h"

// color of pieces
// enum colors{white, black, whiteblack};

// pieces
// enum pieces{e, p, r, n, b, q, k, P, R, N, B, Q, K, o};

// squares
/* enum square_names{
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1,
}; */

// Ascii for given enums
char ascii[14] = {'e', 'p', 'r', 'n', 'b', 'q', 'k', 'P', 'R', 'N', 'B', 'Q', 'K', 'o'};

// Unicode for given enums
char *unicode[14];

// boards, black pieces, white pieces, and a complete board
u64 chessboards[] = { 0ULL, 0ULL, 0ULL };

/*
--------------------------------------------------------------------------------
This below is section to generate attack lookup tables for various piece types
and store them. The idea is to save all those board configurations and help with
on the way move generation.
--------------------------------------------------------------------------------

Knight Lookup tables
offsets of bit = {17, 15, 10, 6} 

Pawn Lookup tables
offsets of bit = {9, 7}

*/
u64 knight_attacks[64];  // array for knight attacks for all positions
u64 pawn_attacks[2][64]; // array for pawn attacks for all positions 
u64 bishop_attacks[64];  // array for bishop attacks for all positions
u64 rook_attacks[64];	 // array for rook attacks for all positions
u64 king_attacks[64];	 // array for king attacks for all positions

/*
BLACK PIECES BITMASKS

Black Pawns

 8  0 0 0 0 0 0 0 0
 7  1 1 1 1 1 1 1 1
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 65280

Black Rooks

 8  1 0 0 0 0 0 0 1
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 129


Black Knights

 8  0 1 0 0 0 0 1 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 66


Black Bishops

 8  0 0 1 0 0 1 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 36


Black Queen

 8  0 0 0 1 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 8


Black King

 8  0 0 0 0 1 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 16

*/

/*
WHITE PIECES BITMASK


White Pawns

 8  0 0 0 0 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  1 1 1 1 1 1 1 1
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 71776119061217280


White Rooks

 8  0 0 0 0 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  1 0 0 0 0 0 0 1

    a b c d e f g h

      bitboard: 9295429630892703744


White Knights

 8  0 0 0 0 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 1 0 0 0 0 1 0

    a b c d e f g h

      bitboard: 4755801206503243776


White Bishops

 8  0 0 0 0 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 1 0 0 1 0 0

    a b c d e f g h

      bitboard: 2594073385365405696


White Queen

 8  0 0 0 0 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 1 0 0 0 0

    a b c d e f g h

      bitboard: 576460752303423488


White King

 8  0 0 0 0 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 1 0 0 0

    a b c d e f g h

      bitboard: 1152921504606846976


*/
// 64 bit numbers to contain position of pieces
u64 bitboards[] = {
	0ULL,                     // empty squares
	65280ULL,                 // black pawns
	129ULL,			  // black rooks
	66ULL,			  // black knights
	36ULL,			  // black bishops
	8ULL,			  // black queen
	16ULL,			  // black king
	71776119061217280ULL,     // white pawns
	9295429630892703744ULL,   // white rooks
	4755801206503243776ULL,   // white knights
	2594073385365405696ULL,   // white bishops
	576460752303423488ULL,	  // white queen
	1152921504606846976ULL,	  // white king
	0ULL                      // invalid square
};


/*

Not A file

 8  0 1 1 1 1 1 1 1
 7  0 1 1 1 1 1 1 1
 6  0 1 1 1 1 1 1 1
 5  0 1 1 1 1 1 1 1
 4  0 1 1 1 1 1 1 1
 3  0 1 1 1 1 1 1 1
 2  0 1 1 1 1 1 1 1
 1  0 1 1 1 1 1 1 1

    a b c d e f g h

      bitboard: 18374403900871474942

*/
u64 not_a_file = 18374403900871474942ULL; 

/*

Not H file

 8  1 1 1 1 1 1 1 0
 7  1 1 1 1 1 1 1 0
 6  1 1 1 1 1 1 1 0
 5  1 1 1 1 1 1 1 0
 4  1 1 1 1 1 1 1 0
 3  1 1 1 1 1 1 1 0
 2  1 1 1 1 1 1 1 0
 1  1 1 1 1 1 1 1 0

    a b c d e f g h

      bitboard: 9187201950435737471

*/
u64 not_h_file = 9187201950435737471ULL;

/*

Not AB file 

 8  0 0 1 1 1 1 1 1
 7  0 0 1 1 1 1 1 1
 6  0 0 1 1 1 1 1 1
 5  0 0 1 1 1 1 1 1
 4  0 0 1 1 1 1 1 1
 3  0 0 1 1 1 1 1 1
 2  0 0 1 1 1 1 1 1
 1  0 0 1 1 1 1 1 1

    a b c d e f g h

      bitboard: 18229723555195321596

*/
u64 not_ab_file = 18229723555195321596ULL;

/*

Not HG file

 8  1 1 1 1 1 1 0 0
 7  1 1 1 1 1 1 0 0
 6  1 1 1 1 1 1 0 0
 5  1 1 1 1 1 1 0 0
 4  1 1 1 1 1 1 0 0
 3  1 1 1 1 1 1 0 0
 2  1 1 1 1 1 1 0 0
 1  1 1 1 1 1 1 0 0

    a b c d e f g h

      bitboard: 4557430888798830399

*/
u64 not_hg_file = 4557430888798830399ULL;

/*
Second rank
 8  0 0 0 0 0 0 0 0
 7  0 0 0 0 0 0 0 0
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  1 1 1 1 1 1 1 1
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 71776119061217280
*/
u64 second_rank = 71776119061217280ULL;

/*
Seventh Rank
 8  0 0 0 0 0 0 0 0
 7  1 1 1 1 1 1 1 1
 6  0 0 0 0 0 0 0 0
 5  0 0 0 0 0 0 0 0
 4  0 0 0 0 0 0 0 0
 3  0 0 0 0 0 0 0 0
 2  0 0 0 0 0 0 0 0
 1  0 0 0 0 0 0 0 0

    a b c d e f g h

      bitboard: 65280
*/
u64 seventh_rank = 65280ULL;
