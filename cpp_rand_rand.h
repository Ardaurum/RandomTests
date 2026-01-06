#pragma once
#include <stdlib.h>

struct cpp_rand
{
  void Init(uint32_t in_seed) { srand(in_seed); }
  uint32_t Run() { return uint32_t(rand()); }
};