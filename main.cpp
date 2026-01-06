#include <chrono>
#include <limits>

#include "rnd_tests.generated.h"

int32_t main()
{
  constexpr size_t INIT_ITERATIONS = 32;
  constexpr size_t ITERATIONS = 500000;
  constexpr size_t CHI_BINS = 64;
  constexpr size_t MAX_LAG = 16;

  printf("%-5s %-16s %17s %17s %7s %7s %7s %7s %7s %7s %7s\n", "Test", "Name", "Init (calls/ms)", "Run (calls/ms)", "Score", "Mean", "Var", "BitAvg", "Incr", "Corr", "Bin64"); 
  printf("%s\n", "-------------------------------------------------------------------------------------------------------------------");
  
  size_t const test_count = GetRndTestCount();
  for (size_t index = 0; index < test_count; ++index)
  {
    // Initialize Test
    size_t bit_count[32] = {};
    size_t chi_count[CHI_BINS] = {};
    size_t number_higher_count = 0;
    double mean = 0, mean_sq = 0, mean_prod_lag1 = 0, mean_prod_lag4 = 0, mean_prod_lag15 = 0;

    // Test seed/initialization speed
    auto init_start = std::chrono::high_resolution_clock::now();
    for (size_t run = 0; run < ITERATIONS; ++run)
    {
      RunRndTestInit(index, run);
    }

    // Test random algorithm speed
    auto main_start = std::chrono::high_resolution_clock::now();
    for (size_t run = 0; run < ITERATIONS; ++run)
    {
      RunRndTestBody(index);
    }
    auto main_end = std::chrono::high_resolution_clock::now();

    // Various random check tests
    for (size_t init = 0; init < INIT_ITERATIONS; ++init)
    {
      // Some algortihms are bad with seed=0, so we avoid that one, but this is also an important part of testing random algorithms
      RunRndTestInit(index, init + 17);
      uint32_t prev_value = RunRndTestBody(index);
      double norm_val_history[MAX_LAG] = {};
      int16_t norm_val_index = 0;

      for (size_t run = 0; run < ITERATIONS; ++run)
      {
        uint32_t value = RunRndTestBody(index);
        
        // Bit balance test
        for (uint8_t bit_offset = 0; bit_offset < 32; ++bit_offset)
        {
          bit_count[bit_offset] += (value >> bit_offset) & 1;
        }

        // Incremental values test
        if (value > prev_value)
        {
          number_higher_count++;
        }
        prev_value = value;

        // Mean, Variance and Correlation test
        double norm_val = double(value) / std::numeric_limits<uint32_t>::max();
        mean += norm_val;
        mean_sq += norm_val * norm_val;
        if (run > 0)
        {
          mean_prod_lag1 += norm_val_history[(norm_val_index - 1) % MAX_LAG] * norm_val;
        }
        if (run > 3) 
        {
          mean_prod_lag4 += norm_val_history[(norm_val_index - 4) % MAX_LAG] * norm_val;
        }
        if (run > 14) 
        {
          mean_prod_lag15 += norm_val_history[(norm_val_index - 15) % MAX_LAG] * norm_val;
        }
        norm_val_history[norm_val_index] = norm_val;
        norm_val_index = (norm_val_index + 1) % MAX_LAG;

        // Chi-Square Test
        chi_count[value % CHI_BINS]++;
      }
    }

    size_t init_time = size_t((ITERATIONS) / std::chrono::duration<double, std::milli>(main_start - init_start).count());
    size_t main_time = size_t((ITERATIONS) / std::chrono::duration<double, std::milli>(main_end - main_start).count());
    double bit_avg = 0;
    for (uint8_t bit_offset = 0; bit_offset < 32; ++bit_offset)
    {
      bit_avg += 2.0 * abs(0.5 - (double(bit_count[bit_offset]) / double(INIT_ITERATIONS * ITERATIONS)));
      //printf("Bit %u: %llu\n", bit_offset, bit_count[bit_offset]);
    }
    bit_avg = 100.0 * (1.0 - bit_avg / 32);
    uint32_t bit_avg_score = uint32_t(bit_avg);
    uint32_t incr = 200.0 * (0.5 - abs(0.5 - double(number_higher_count) / double(INIT_ITERATIONS * ITERATIONS)));
    mean /= INIT_ITERATIONS * ITERATIONS;
    mean_sq /= INIT_ITERATIONS * ITERATIONS;
    mean_prod_lag1 /= INIT_ITERATIONS * ITERATIONS;
    mean_prod_lag4 /= INIT_ITERATIONS * ITERATIONS;
    mean_prod_lag15 /= INIT_ITERATIONS * ITERATIONS;
    double var = mean_sq - mean * mean;
    double corr_lag1 = double(abs((mean_prod_lag1 - mean * mean) / var));
    double corr_lag4 = double(abs((mean_prod_lag4 - mean * mean) / var));
    double corr_lag15 = double(abs((mean_prod_lag15 - mean * mean) / var));
    //printf("lag1: %f, lag4: %f, lag15: %f\n", corr_lag1, corr_lag4, corr_lag15);
    uint32_t corr_score = uint32_t(100.0 * ((1.0 - corr_lag1) + (1.0 - corr_lag4) + (1.0 - corr_lag15)) / 3.0);
    //printf("mean: %f, mean_sq: %f, mean_prod: %f, var: %f\n", mean, mean_sq, mean_prod_lag1, var);
    uint32_t mean_score = uint32_t(100.0 * (1.0 - 2.0 * abs(0.5 - mean)));
    uint32_t var_score = uint32_t(std::clamp(100.0 * (1.0 - abs(1.0 - abs(var) / 0.08333)), 0.0, 100.0));

    constexpr double CHI_EXPECTED = double(INIT_ITERATIONS * ITERATIONS) / CHI_BINS;
    double chi_square = 0.0;
    for (size_t bin = 0; bin < CHI_BINS; ++bin)
    {
      size_t chi_observed = chi_count[bin];
      //printf("chi_value[%zu]: %zu\n", bin, chi_observed);
      chi_square += ((chi_observed - CHI_EXPECTED) * (chi_observed - CHI_EXPECTED)) / CHI_EXPECTED;
    }
    constexpr double chi_sigma = 3.0;
    double z_value = abs(chi_square - CHI_BINS - 1.0) / std::sqrt(2.0 * (CHI_BINS - 1.0));
    uint32_t chi_score = 100.0 * std::exp(-(z_value * z_value) / (2.0 * chi_sigma * chi_sigma));
    //printf("chi_square: %f, chi_score: %u\n", chi_square, chi_score);

    uint32_t final_score = (mean_score + var_score + bit_avg_score + incr + corr_score + chi_score) / 6.0;

    printf("%2llu/%-2llu %-16s: %16llu, %16llu, %6u, %6u, %6u, %6u, %6u, %6u, %6u\n", 
      index + 1, test_count, GetRndTestName(index), init_time, main_time, final_score, mean_score, var_score, bit_avg_score, incr, corr_score, chi_score);
  }

  do 
  {
    printf("\nPress enter to continue...");
  } while (getchar() != '\n');
  return 0;
}