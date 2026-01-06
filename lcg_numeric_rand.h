#pragma once
#include <stdlib.h>

struct lcg_numeric
{
  uint32_t state;

  void Init(uint32_t in_seed) { state = in_seed; }
  uint32_t Run() { return state = ((state * 0x0019660D) + 0x3C6EF35F) % 0x7FFFFFFF; }
};