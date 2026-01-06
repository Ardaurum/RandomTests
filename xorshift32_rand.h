#pragma once
#include <stdlib.h>

struct xorshift32
{
  uint32_t state;

  void Init(uint32_t in_seed) { state = in_seed; }
  uint32_t Run() { 
    state ^= (state << 13);
    state ^= (state >> 17);  
    state ^= (state << 5);  
    return state;
  }
};