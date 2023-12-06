#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// a -> now long to hold
// t -> time for race
// d -> distance to "beat" (is that >= or >)
// goal: d <= (t - a)a = -a^2 + at   ->   0 <= -a^2 + at - d

// use the quadratic formula to find zeros then count the number of integers between
// - we know the behaviour when a -> inf is d -> -inf
// - since largest degree is even as a -> -inf then also d -> -inf