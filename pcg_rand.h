#pragma once
#include <stdlib.h>
#include <cmath>
#include <limits>

struct pcg
{
  uint32_t seed;
  void Init(uint32_t in_seed) { seed = in_seed; }

  uint32_t Run() { 
    static uint32_t pos = seed;
    pos = pos * 747796405u + 2891336453u;
    uint32_t res = ((pos >> ((pos >> 28u) + 4u)) ^ pos) * 277803737u;
    return (res >> 22u) ^ res;
  }
};