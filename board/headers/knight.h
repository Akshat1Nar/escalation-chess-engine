#ifndef KNIGHT_H
#define KNIGHT_H

u64 get_knight_attack_mask(uint8_t square);
void initialise_knight_lookup_table();
u64 get_quiet_moves(int square);
u64 get_capture_moves(int square, int side);
u64 get_knight_moves(int square, int side);

#endif
