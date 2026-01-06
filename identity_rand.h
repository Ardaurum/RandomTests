#pragma once
#include <stdlib.h>

struct identity
{
  uint32_t state;

  void Init(uint32_t in_seed) { state = in_seed; }
  uint32_t Run() { return ++state; }
};