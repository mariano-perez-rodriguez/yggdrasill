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

/**
 * Generate a permutation of the given number of elements
 *
 * @param gen  Bit Generator to use
 * @param len  Number of elements to return
 * @return the permutation proper
 */
std::vector<std::size_t> generatePermutation(BitGenerator &gen, std::size_t len) noexcept {
  std::vector<std::size_t> ret;
  for (std::size_t i = 0; i < len; i++) {
    std::size_t j = randRange(gen, i + 1);
    if (j != i) {
      ret[i] = ret[j];
    }
    ret[j] = i;
  }
  return ret;
}

/**
 * Shuffle the given permutation using the given Bit Generator
 *
 * @param gen  Bit Generator to use
 * @param perm  Permutation to shuffle
 */
void shufflePermutation(BitGenerator &gen, std::vector<std::size_t> &perm) noexcept {
  std::size_t n = perm.size();
  for (std::size_t i = 0; i < n - 1; i++) {
    std::size_t j = randRange(gen, n - i);
    std::swap(perm[i], perm[i + j]);
  }
}

/**
 * Generate and shuffle a permutation of the given number of elements
 *
 * @param gen  Bit Generator to use
 * @param len  Number of elements to return
 * @param rep  Number of shuffling rounds to use
 * @return the permutation proper
 */
std::vector<std::size_t> generateAndShufflePermutation(BitGenerator &gen, std::size_t len, std::size_t rep) noexcept {
  std::vector<std::size_t> ret = generatePermutation(gen, len);
  for (std::size_t i = 0; i < rep; i++) {
    shufflePermutation(gen, ret);
  }
  return ret;
}


/**
 * Invert the given permutation
 *
 * @param fwd  Forward permutation to invert
 * @return the inverted permutation
 */
std::vector<std::size_t> invertPermutation(std::vector<std::size_t> const &fwd) noexcept {
  std::vector<std::size_t> inv;
  for (std::size_t i = 0; i < fwd.size(); i++) {
    inv[fwd[i]] = i;
  }
  return inv;
}


