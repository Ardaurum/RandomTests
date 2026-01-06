#pragma once
#include <stdlib.h>

struct xorshift128
{
  uint32_t state[4];

  void Init(uint32_t in_seed) { 
    state[0] = in_seed << 13;
    state[1] = (in_seed >> 9) ^ (in_seed << 6); 
    state[2] = in_seed >> 7;
    state[3] = in_seed; 
  }
  uint32_t Run() { 
    uint32_t t = state[0] ^ (state[0] << 11);
    state[0] = state[1];
    state[1] = state[2];
    state[2] = state[3];
    return state[3] = (state[3] ^ (state[3] >> 19)) ^ (t ^ (t >> 8));
  }
};