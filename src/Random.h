#ifndef RANDOM_H__
#define RANDOM_H__

#include <cstdint>
#include <cstddef>
#include <vector>

#include "BitGenerator.h"


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
std::uint64_t randRange(BitGenerator &gen, std::uint64_t max) noexcept;
std::uint64_t randRange(BitGenerator &gen, std::uint64_t min, std::uint64_t max) noexcept;

/**
 * Generate a permutation of the given number of elements
 *
 * @param gen  Bit Generator to use
 * @param len  Number of elements to return
 * @return the permutation proper
 */
std::vector<std::size_t> generatePermutation(BitGenerator &gen, std::size_t len) noexcept;

/**
 * Shuffle the given permutation using the given Bit Generator
 *
 * @param gen  Bit Generator to use
 * @param perm  Permutation to shuffle
 */
void shufflePermutation(BitGenerator &gen, std::vector<std::size_t> &perm) noexcept;

/**
 * Generate and shuffle a permutation of the given number of elements
 *
 * @param gen  Bit Generator to use
 * @param len  Number of elements to return
 * @param rep  Number of shuffling rounds to use
 * @return the permutation proper
 */
std::vector<std::size_t> generateAndShufflePermutation(BitGenerator &gen, std::size_t len, std::size_t rep = 2) noexcept;


/**
 * Invert the given permutation
 *
 * @param fwd  Forward permutation to invert
 * @return the inverted permutation
 */
std::vector<std::size_t> invertPermutation(std::vector<std::size_t> const &fwd) noexcept;

#endif  /* RANDOM_H__ */

