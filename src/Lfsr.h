#ifndef LFSR_H__
#define LFSR_H__

#include <cstddef>
#include <bitset>
#include <string>


/**
 * LFSR class (Galois type)
 *
 * This class allows injection of bits through the most-significant LFSR stage,
 * consequently, if the state reaches an all-0 value, it it reset to an all-1
 * one.
 *
 * @param N  LFSR register size
 */
template <std::size_t N>
class Lfsr {
  public:
    /**
     * Initializing constructor
     *
     * @param s  State to initialize the LFSR to, if everywhere-0, change to everywhere-1
     * @param g  Generator to use, must not be everywhere-0
     * @throws std::domain_error  In case the given generator is everywhere-0
     */
    Lfsr(std::bitset<N> s, std::bitset<N> g);
    Lfsr(std::bitset<N> s, std::string g);
    Lfsr(std::string s, std::bitset<N> g);
    Lfsr(std::string s, std::string g);

    /**
     * Re-seed the LFSR
     *
     * @param s  State to re-seed to
     * @return the current LFSR
     */
    Lfsr &seed(std::bitset<N> s) noexcept;
    Lfsr &seed(std::string s) noexcept;

    /**
     * Step the LFSR once, XORing the given value in, it the result is an all-0 state, flip it to an all-1 one
     *
     * @param val  value to XOR in
     * @return the current LFSR
     */
    Lfsr &step(bool val = false) noexcept;

    /**
     * Get the current bit output (or the one asked for)
     *
     * @param i  Index to return, defaults to 0
     * @return the current value of the LFSR's output bit
     */
    constexpr bool get(std::size_t i = 0) const noexcept;

    /**
     * Convenience method that advances the LFSR, XORing the given value in, and returns the new output
     *
     * @param val  value to XOR in
     * @return the current value of the LFSR's output bit
     */
    bool next(bool val = false) noexcept;

  protected:
    /**
     * LFSR register proper
     *
     */
    std::bitset<N> state;

    /**
     * LFSR generator
     *
     */
    std::bitset<N> generator;
};


#include "Lfsr.hpp"

#endif  /* LFSR_H__ */

