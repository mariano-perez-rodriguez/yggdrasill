#include "Icg.h"

#include <stdexcept>


/**
 * Construct an ICG with the given parameters
 *
 * @param mod   The modulus to use (MUST be a prime number)
 * @param mult  The multiplier parameter to use
 * @param off   The offset parameter to use (MUST be non-zero)
 * @param init  Initial state to assume
 * @throws std::invalid_argument if the offset is 0
 */
Icg::Icg(std::uint64_t mod, std::uint64_t mult, std::uint64_t off, std::uint64_t init)
: m(mod), a(mult % mod), c(off % mod), x(init % mod), inv(buildInvTable(mod)) {
  if (0 == c) {
    throw new std::invalid_argument("Zero offset found in ICG initialization");
  }
}

/**
 * Re-seed the ICG
 *
 * @param state  State to re-seed to
 * @return the current ICG
 */
Icg &Icg::seed(std::uint64_t state) noexcept {
  x = state % m;
  return *this;
}

/**
 * Step the ICG once
 *
 * @return the current ICG
 */
Icg &Icg::step() noexcept {
  x = (a * inv[x] + c) % m;
  return *this;
}

/**
 * Get the current ICG state
 *
 * @return the current ICG state
 */
std::uint64_t Icg::get() const noexcept {
  return x;
}

/**
 * Convenience method that advances the ICG and returns the new output
 *
 * @return the current ICG state
 */
std::uint64_t Icg::next() noexcept {
  return step().get();
}

/**
 * Retrieve the modulus
 *
 * @return the ICG's modulus
 */
std::uint64_t Icg::modulus() const noexcept {
  return m;
}

/**
 * Retrieve the multiplier
 *
 * @return the ICG's multiplier
 */
std::uint64_t Icg::multiplier() const noexcept {
  return a;
}

/**
 * Retrieve the offset
 *
 * @return the ICG's offset
 */
std::uint64_t Icg::offset() const noexcept {
  return c;
}

/**
 * Construct an inversion table for the given modulus
 *
 * Taken from: https://comeoncodeon.wordpress.com/2011/10/09/modular-multiplicative-inverse
 *
 * @param mod  Modulus to construct the table for
 * @return the generated table
 */
std::vector<std::uint64_t> Icg::buildInvTable(std::uint64_t mod) noexcept {
  std::vector<std::uint64_t> ret(mod, 0u); ret[1] = 1;

  for(std::uint64_t i = 2; i < mod; i++) {
    ret[i] = ((-(mod / i) * ret[mod % i]) % mod) + mod;
  }

  return ret;
}

/**
 * Return a new ICG for the given modulus, given a "mother" multiplier, an offset and an initial state
 *
 * If the ICG using the given multiplier and an offset of 1 has maximum
 * period, then the ICG returned will have maximum period.
 *
 * @param mod   Modulus to use
 * @param mult  Mother multiplier to use
 * @param off   Offset to use
 * @param ini   Initial state to use
 */
Icg Icg::deriveFromMother(std::uint64_t mod, std::uint64_t mult, std::uint64_t off, std::uint64_t ini) noexcept {
  return Icg(mod, ((((mult % mod) * (off % mod)) % mod) * (off % mod)) % mod, off, ini);
}

