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