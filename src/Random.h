#ifndef RANDOM_H__
#define RANDOM_H__

#include <cstdint>
#include <cstddef>

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

#endif  /* RANDOM_H__ */

