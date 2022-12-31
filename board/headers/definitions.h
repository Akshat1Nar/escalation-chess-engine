
#define u64 unsigned long long

// some bit operations
#define get_bit(bitboard, index) (bitboard & (1ULL << index))
#define set_bit(bitboard, index) (bitboard |= (1ULL << index))

// color of pieces
enum {white, black};

// pieces
enum {e, p, r, n, b, q, k, P, R, N, B, Q, K, o};

// Ascii for given enums
char ascii[14] = {'e', 'p', 'r', 'n', 'b', 'q', 'k', 'P', 'R', 'N', 'B', 'Q', 'K', 'o'};

// Unicode for given enums
char *unicode[14];

// squares
enum {
	a8, b8, c8, d8, e8, f8, g8, h8,
	a7, b7, c7, d7, e7, f7, g7, h7,
	a6, b6, c6, d6, e6, f6, g6, h6,
	a5, b5, c5, d5, e5, f5, g5, h5,
	a4, b4, c4, d4, e4, f4, g4, h4,
	a3, b3, c3, d3, e3, f3, g3, h3,
	a2, b2, c2, d2, e2, f2, g2, h2,
	a1, b1, c1, d1, e1, f1, g1, h1,
};

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
