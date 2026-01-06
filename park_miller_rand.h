#pragma once
#include <stdlib.h>

struct park_miller
{
  uint32_t state;

  void Init(uint32_t in_seed) { state = in_seed; }
  uint32_t Run() { return state = (state * 0x0000BC8F) % 0x7FFFFFFF; }
};