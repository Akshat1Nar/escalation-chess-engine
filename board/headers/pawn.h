#ifndef PAWN_H
#define PAWN_H

u64 get_pawn_attack_mask(int square, int side);
void initialise_pawn_lookup_table();
u64 pawn_quiet_moves(int square, int side);
u64 pawn_capture_moves(int square, int side);

#endif
