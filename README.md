Simply stupid random algorithms test
====================================

This project is **NOT** to create a ranking of different random algorithm tests. The purpose of this is to showcase that using standard cpp `rand()` or similar, is not a good idea. It's always better to implement something else like a simple pcg, murmur or xorshift. Second purpose was to try myself in implementing some statistical checks :).

## Building and running

Download the repo, run the build.bat (requires g++) and then run the created rnd_test.exe file. That's all. To add more algorithms just add another `.h` file with the name ending with `_rand.h` and then implement your algorithm similarly to the other algorithms. All tests are in `main.cpp`, so if you want to change values or implement more tests, look there.

## Tests

There are a couple of tests implemented. Time is measured in how many calls in a millisecond of the method we can do (the higher the better). All the others have a score (0-100) where the higher value the better.

Name   | Description
-------|-------------
Init   | Time to initialize the seed.
Run    | Time to run main body of the algorithm.
Score  | Overall score which is just an average of all score (not great, but it's simply stupid)
Mean   | If we calculate mean from all the random values, is it close to the mean values of the whole range.
Var    | Variance - How spreaded the values are from the mean value.
BitAvg | Are all the 32 bits on or off 50% of the time.
Incr   | Are values too monotonic
Corr   | Perason Correlation of values, based on 3 different lags (1, 4, 15). Checks if the next random values are corelated with previous ones.
Bin64  | Chi-Square test to check if the values are spread uniformly across multiple bins. Here we test a spread of 64 different bins.

## Results

These are the results I got from running the test on the implemented random algorithms. This doesn't exhaust the possibilities in which you can test random algorithms, so take it with a grain of salt. But already with this simple test you can see which ones are really terrible and which are fast while still being quite good.

Test  | Name         | Init (calls/ms) | Run (calls/ms) | Score | Mean | Var | BitAvg | Incr | Corr | Bin64
------|--------------|-----------------|----------------|-------|------|-----|--------|------|------|-------
 1/15 | cpp_lcg:     | 195771          | 101502         | 76    | 49   | 24  | 96     | 99   | 99   | 90 
 2/15 | cpp_mt:      | 427             | 53803          | 99    | 99   | 99  | 99     | 99   | 99   | 99 
 3/15 | cpp_rand:    | 124078          | 120307         | 56    | 0    | 0   | 46     | 99   | 99   | 95 
 4/15 | identity:    | 554877          | 691850         | 12    | 0    | 0   | 58     | 0    | 0    | 15 
 5/15 | jenkins:     | 627510          | 246293         | 83    | 99   | 99  | 99     | 99   | 99   | 6  
 6/15 | lcg_numeric: | 238231          | 213110         | 61    | 49   | 24  | 96     | 99   | 99   | 0  
 7/15 | murmur:      | 640779          | 357653         | 99    | 99   | 99  | 99     | 99   | 99   | 99 
 8/15 | park_miller: | 636537          | 217004         | 61    | 50   | 25  | 96     | 99   | 99   | 0  
 9/15 | pcg:         | 301005          | 261602         | 99    | 99   | 99  | 99     | 99   | 99   | 99 
10/15 | shader_sin:  | 499251          | 29587          | 97    | 99   | 99  | 99     | 99   | 99   | 89 
11/15 | splitmix32:  | 400608          | 403681         | 95    | 99   | 99  | 99     | 99   | 99   | 78 
12/15 | squirrel:    | 531011          | 286188         | 94    | 99   | 99  | 99     | 99   | 99   | 69 
13/15 | wang:        | 622277          | 370919         | 82    | 99   | 99  | 99     | 99   | 99   | 0  
14/15 | xorshift128: | 446588          | 473440         | 98    | 99   | 99  | 99     | 99   | 99   | 98 
15/15 | xorshift32:  | 640204          | 235704         | 97    | 99   | 99  | 99     | 99   | 99   | 90 