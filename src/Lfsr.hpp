#ifndef LFSR_HPP__
#define LFSR_HPP__

#include "Lfsr.h"

#include <stdexcept>


namespace {
  /**
   * Build a bitset from the hexadecimal string description
   *
   * @param N  Bitset's length
   * @param str  String to use for construction
   * @return the constructed bitset
   */
  template <std::size_t N>
  std::bitset<N> hex2bitset(std::string str) noexcept {
    std::bitset<N> ret;
    for (auto c : str) {
      switch (c) {
        case '0'           /* 0000 */:                                           break;
        case '1'           /* 0001 */:                            ret[0] = true; break;
        case '2'           /* 0010 */:                   ret[1]          = true; break;
        case '3'           /* 0011 */:                   ret[1] = ret[0] = true; break;
        case '4'           /* 0100 */:          ret[2]                   = true; break;
        case '5'           /* 0101 */:          ret[2]          = ret[0] = true; break;
        case '6'           /* 0110 */:          ret[2] = ret[1]          = true; break;
        case '7'           /* 0111 */:          ret[2] = ret[1] = ret[0] = true; break;
        case '8'           /* 1000 */: ret[3]                            = true; break;
        case '9'           /* 1001 */: ret[3]                   = ret[0] = true; break;
        case 'a': case 'A' /* 1010 */: ret[3]          = ret[1]          = true; break;
        case 'b': case 'B' /* 1011 */: ret[3]          = ret[1] = ret[0] = true; break;
        case 'c': case 'C' /* 1100 */: ret[3] = ret[2]                   = true; break;
        case 'd': case 'D' /* 1101 */: ret[3] = ret[2]          = ret[0] = true; break;
        case 'e': case 'E' /* 1110 */: ret[3] = ret[2] = ret[1]          = true; break;
        case 'f': case 'F' /* 1111 */: ret[3] = ret[2] = ret[1] = ret[0] = true; break;
        default:                                                                 break;
      }
      ret <<= 4;
    }
    return ret;
  }
}


/**
 * Initializing constructor
 *
 * @param s  State to initialize the LFSR to, if everywhere-0, change to everywhere-1
 * @param g  Generator to use, must not be everywhere-0
 * @throws std::domain_error  In case the given generator is everywhere-0
 */
template <std::size_t N>
Lfsr<N>::Lfsr(std::bitset<N> s, std::bitset<N> g) : state(s.none() ? s.flip() : s), generator(g) {
  if (g.none()) {
    throw new std::domain_error("Zero generator");
  }
}
template <std::size_t N>
Lfsr<N>::Lfsr(std::bitset<N> s, std::string g) : Lfsr<N>(s, hex2bitset<N>(g)) {}
template <std::size_t N>
Lfsr<N>::Lfsr(std::string s, std::bitset<N> g) : Lfsr<N>(hex2bitset<N>(s), g) {}
template <std::size_t N>
Lfsr<N>::Lfsr(std::string s, std::string g) : Lfsr<N>(hex2bitset<N>(s), hex2bitset<N>(g)) {}

/**
 * Re-seed the LFSR
 *
 * @param s  State to re-seed to
 * @return the current LFSR
 */
template <std::size_t N>
Lfsr<N> &Lfsr<N>::seed(std::bitset<N> s) noexcept {
  state = s;
  return *this;
}
template <std::size_t N>
Lfsr<N> &Lfsr<N>::seed(std::string s) noexcept { return seed(hex2bitset<N>(s)); }

/**
 * Step the LFSR once, XORing the given value in, it the result is an all-0 state, flip it to an all-1 one
 *
 * @param val  value to XOR in
 * @return the current LFSR
 */
template <std::size_t N>
Lfsr<N> &Lfsr<N>::step(bool val) noexcept {
  bool lsb = get(); state >>= 1;
  if (lsb) { state ^= generator; }
  if (val) { state.flip(N - 1); }
  if (state.none()) { state.flip(); }
  return *this;
}

/**
 * Get the current bit output (or the one asked for)
 *
 * @param i  Index to return, defaults to 0
 * @return the current value of the LFSR's output bit
 */
template <std::size_t N>
constexpr bool Lfsr<N>::get(std::size_t i) const noexcept {
  return state[i];
}

/**
 * Convenience method that advances the LFSR, XORing the given value in, and returns the new output
 *
 * @param val  value to XOR in
 * @return the current value of the LFSR's output bit
 */
template <std::size_t N>
bool Lfsr<N>::next(bool val) noexcept {
  return step(val).get();
}


#endif  /* LFSR_HPP__ */

