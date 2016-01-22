#ifndef ICG_H__
#define ICG_H__

#include <cstdint>
#include <vector>


/**
 * Inversive Congruential Generator class
 *
 * This class implements a 64-bit ICG.
 *
 */
class Icg {
  public:
    /**
     * Construct an ICG with the given parameters
     *
     * @param mod   The modulus to use (MUST be a prime number)
     * @param mult  The multiplier parameter to use
     * @param off   The offset parameter to use (MUST be non-zero)
     * @param init  Initial state to assume
     * @throws std::invalid_argument if the offset is 0
     */
    Icg(std::uint64_t mod, std::uint64_t mult, std::uint64_t off, std::uint64_t init);

    /**
     * Re-seed the ICG
     *
     * @param state  State to re-seed to
     * @return the current ICG
     */
    Icg &seed(std::uint64_t state) noexcept;

    /**
     * Step the ICG once
     *
     * @return the current ICG
     */
    Icg &step() noexcept;

    /**
     * Get the current ICG state
     *
     * @return the current ICG state
     */
    std::uint64_t get() const noexcept __attribute__((pure));

    /**
     * Convenience method that advances the ICG and returns the new output
     *
     * @return the current ICG state
     */
    std::uint64_t next() noexcept;

    /**
     * Retrieve the modulus
     *
     * @return the ICG's modulus
     */
    std::uint64_t modulus() const noexcept __attribute__((pure));

    /**
     * Retrieve the multiplier
     *
     * @return the ICG's multiplier
     */
    std::uint64_t multiplier() const noexcept __attribute__((pure));

    /**
     * Retrieve the offset
     *
     * @return the ICG's offset
     */
    std::uint64_t offset() const noexcept __attribute__((pure));

  protected:
    /**
     * Construct an inversion table for the given modulus
     *
     * Taken from: https://comeoncodeon.wordpress.com/2011/10/09/modular-multiplicative-inverse
     *
     * @param mod  Modulus to construct the table for
     * @return the generated table
     */
    static std::vector<std::uint64_t> buildInvTable(std::uint64_t mod) noexcept;

    /**
     * ICG's modulus
     *
     */
    std::uint64_t m;

    /**
     * ICG's multiplier
     *
     */
    std::uint64_t a;

    /**
     * ICG's offset
     *
     */
    std::uint64_t c;

    /**
     * ICG's state
     *
     */
    std::uint64_t x;

    /**
     * Inversion table for the given modulus
     *
     */
    std::vector<std::uint64_t> inv;

  public:
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
    static Icg deriveFromMother(std::uint64_t mod, std::uint64_t mult, std::uint64_t off, std::uint64_t ini) noexcept;
};


#endif  /* ICG_H__ */

