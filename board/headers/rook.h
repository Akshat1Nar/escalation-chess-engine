#ifndef ROOK_H
#define ROOK_H

u64 get_rook_attack_mask(int square);
void initialise_rook_lookup_table();
u64 get_dynamic_rook_attack_mask(int square, u64 block) {

#endif
