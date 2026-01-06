#pragma once
#include <random>

struct cpp_mt
{
  std::mt19937 generator;

  void Init(uint32_t in_seed) { generator = std::mt19937(in_seed); }
  uint32_t Run() { return generator(); }
};