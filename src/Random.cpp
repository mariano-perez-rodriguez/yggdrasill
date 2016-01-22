#include "Random.h"


/**
 * Generate a random number using the minimum possible bits
 *
 * This function generates a random number between 0 and the given limit
 * using the minimum possible bits using the given generator.
 *
 * @param gen  Generator to use
 * @param min  Minimum number (inclusive)
 * @param max  Maximum number (exclusive)
 * @return the generated number
 */
std::uint64_t randRange(BitGenerator &gen, std::uint64_t max) noexcept {
  return randRange(gen, 0, max);
}
std::uint64_t randRange(BitGenerator &gen, std::uint64_t min, std::uint64_t max) noexcept {
  std::uint64_t d = max - min;
  // immediately return on 0
  if (0 == d) { return min; }
  // calculate logarithm
  std::uint64_t l = 0, m = d, v; while (m >>= 1) { l++; }
  // perform rejection sampling
  do { v = 0; for (std::size_t i = 0; i < l; i++) { v = (v << 1) | gen.next(); } } while (v >= d);

  return min + v;
}

