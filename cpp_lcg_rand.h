#pragma once
#include <random>

struct cpp_lcg
{
  std::minstd_rand generator;

  void Init(uint32_t in_seed) { generator = std::minstd_rand(in_seed); }
  uint32_t Run() { return generator(); }
};