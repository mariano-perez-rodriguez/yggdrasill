#ifndef XSG_HPP__
#define XSG_HPP__

#include "Xsg.hpp"

#include <vector>
#include <algorithm>
#include <array>


namespace {
  /**
   * Hexadecimal characters for conversion
   *
   */
  constexpr char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

  /**
   * Turn a bool vector into an hexadecimal strings
   *
   * @param bv  Bool vector to transform
   * @return the hexadecimal string equivalent of the given bool vector
   */
  std::string boolVector2hex(std::vector<bool> bv) noexcept {
    std::string h;

    while (!bv.empty()) {
      std::size_t d = 0;
      switch (bv.size()) {
        default: d = (d << 1) | bv.back(); bv.pop_back();
        case 3:  d = (d << 1) | bv.back(); bv.pop_back();
        case 2:  d = (d << 1) | bv.back(); bv.pop_back();
        case 1:  d = (d << 1) | bv.back(); bv.pop_back();
                 h = hex[d] + h;
        case 0:  break;
      }
    }

    return h;
  }

  /**
   * Calculate the Elias-Omega code for the given number.
   *
   * If the given number is 0, the Elias-Omega code is empty.
   * See https://en.wikipedia.org/wiki/Elias_omega_coding.
   *
   * @param n  Number to encode
   * @return the Elias-Omega coding as a bit vector
   */
  std::vector<bool> eliasOmegaCode(std::uint64_t n) noexcept {
    std::vector<bool> ret;
    std::uint64_t l;
    if (n) {
      ret.push_back(false);
      while (n > 1) {
        l = 0;
        while (n) {
          ret.push_back(n % 2);
          n >>= 1;
          l++;
        }
        n = l - 1;
      }
      std::reverse(ret.begin(), ret.end());
    }
    return ret;
  }

  /**
   * Majority function of 3 inputs
   *
   * @param x  Input 1
   * @param y  Input 2
   * @param z  Input 3
   * @return true if at least two inputs are true, false otherwise
   */
  constexpr bool maj3(bool x, bool y, bool z) noexcept {
    return (x + y + z) > 1;
  }
}


/**
 * Construct an XSG from its components
 *
 * @param m     Master LFSR
 * @param im    Whether to include the master LFSR in the output
 * @param s0    Slave 0 LFSR
 * @param s0l1  Slave 0 ICG for the low-bit of Slave 1
 * @param s0m1  Slave 0 ICG for the mid-bit of Slave 1
 * @param s0h1  Slave 0 ICG for the high-bit of Slave 1
 * @param s0l2  Slave 0 ICG for the low-bit of Slave 2
 * @param s0m2  Slave 0 ICG for the mid-bit of Slave 2
 * @param s0h2  Slave 0 ICG for the high-bit of Slave 2
 * @param s0l3  Slave 0 ICG for the low-bit of Slave 3
 * @param s0m3  Slave 0 ICG for the mid-bit of Slave 3
 * @param s0h3  Slave 0 ICG for the high-bit of Slave 3
 * @param s1    Slave 1 LFSR
 * @param s1l0  Slave 1 ICG for the low-bit of Slave 0
 * @param s1m0  Slave 1 ICG for the mid-bit of Slave 0
 * @param s1h0  Slave 1 ICG for the high-bit of Slave 0
 * @param s1l2  Slave 1 ICG for the low-bit of Slave 2
 * @param s1m2  Slave 1 ICG for the mid-bit of Slave 2
 * @param s1h2  Slave 1 ICG for the high-bit of Slave 2
 * @param s1l3  Slave 1 ICG for the low-bit of Slave 3
 * @param s1m3  Slave 1 ICG for the mid-bit of Slave 3
 * @param s1h3  Slave 1 ICG for the high-bit of Slave 3
 * @param s2    Slave 2 LFSR
 * @param s2l0  Slave 2 ICG for the low-bit of Slave 0
 * @param s2m0  Slave 2 ICG for the mid-bit of Slave 0
 * @param s2h0  Slave 2 ICG for the high-bit of Slave 0
 * @param s2l1  Slave 2 ICG for the low-bit of Slave 1
 * @param s2m1  Slave 2 ICG for the mid-bit of Slave 1
 * @param s2h1  Slave 2 ICG for the high-bit of Slave 1
 * @param s2l3  Slave 2 ICG for the low-bit of Slave 3
 * @param s2m3  Slave 2 ICG for the mid-bit of Slave 3
 * @param s2h3  Slave 2 ICG for the high-bit of Slave 3
 * @param s3    Slave 3 LFSR
 * @param s3l0  Slave 3 ICG for the low-bit of Slave 0
 * @param s3m0  Slave 3 ICG for the mid-bit of Slave 0
 * @param s3h0  Slave 3 ICG for the high-bit of Slave 0
 * @param s3l1  Slave 3 ICG for the low-bit of Slave 1
 * @param s3m1  Slave 3 ICG for the mid-bit of Slave 1
 * @param s3h1  Slave 3 ICG for the high-bit of Slave 1
 * @param s3l2  Slave 3 ICG for the low-bit of Slave 2
 * @param s3m2  Slave 3 ICG for the mid-bit of Slave 2
 * @param s3h2  Slave 3 ICG for the high-bit of Slave 2
 * @throws std::invalid_argument if s0l1's modulus is not S0
 * @throws std::invalid_argument if s0m1's modulus is not S0
 * @throws std::invalid_argument if s0h1's modulus is not S0
 * @throws std::invalid_argument if s0l2's modulus is not S0
 * @throws std::invalid_argument if s0m2's modulus is not S0
 * @throws std::invalid_argument if s0h2's modulus is not S0
 * @throws std::invalid_argument if s0l3's modulus is not S0
 * @throws std::invalid_argument if s0m3's modulus is not S0
 * @throws std::invalid_argument if s0h3's modulus is not S0
 * @throws std::invalid_argument if s1l0's modulus is not S1
 * @throws std::invalid_argument if s1m0's modulus is not S1
 * @throws std::invalid_argument if s1h0's modulus is not S1
 * @throws std::invalid_argument if s1l2's modulus is not S1
 * @throws std::invalid_argument if s1m2's modulus is not S1
 * @throws std::invalid_argument if s1h2's modulus is not S1
 * @throws std::invalid_argument if s1l3's modulus is not S1
 * @throws std::invalid_argument if s1m3's modulus is not S1
 * @throws std::invalid_argument if s1h3's modulus is not S1
 * @throws std::invalid_argument if s2l0's modulus is not S2
 * @throws std::invalid_argument if s2m0's modulus is not S2
 * @throws std::invalid_argument if s2h0's modulus is not S2
 * @throws std::invalid_argument if s2l1's modulus is not S2
 * @throws std::invalid_argument if s2m1's modulus is not S2
 * @throws std::invalid_argument if s2h1's modulus is not S2
 * @throws std::invalid_argument if s2l3's modulus is not S2
 * @throws std::invalid_argument if s2m3's modulus is not S2
 * @throws std::invalid_argument if s2h3's modulus is not S2
 * @throws std::invalid_argument if s3l0's modulus is not S3
 * @throws std::invalid_argument if s3m0's modulus is not S3
 * @throws std::invalid_argument if s3h0's modulus is not S3
 * @throws std::invalid_argument if s3l1's modulus is not S3
 * @throws std::invalid_argument if s3m1's modulus is not S3
 * @throws std::invalid_argument if s3h1's modulus is not S3
 * @throws std::invalid_argument if s3l2's modulus is not S3
 * @throws std::invalid_argument if s3m2's modulus is not S3
 * @throws std::invalid_argument if s3h2's modulus is not S3
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
Xsg<M, S0, S1, S2, S3>::Xsg(Lfsr<M> m, bool im,
  Lfsr<S0> s0, Icg s0l1, Icg s0m1, Icg s0h1, Icg s0l2, Icg s0m2, Icg s0h2, Icg s0l3, Icg s0m3, Icg s0h3,
  Lfsr<S1> s1, Icg s1l0, Icg s1m0, Icg s1h0, Icg s1l2, Icg s1m2, Icg s1h2, Icg s1l3, Icg s1m3, Icg s1h3,
  Lfsr<S2> s2, Icg s2l0, Icg s2m0, Icg s2h0, Icg s2l1, Icg s2m1, Icg s2h1, Icg s2l3, Icg s2m3, Icg s2h3,
  Lfsr<S3> s3, Icg s3l0, Icg s3m0, Icg s3h0, Icg s3l1, Icg s3m1, Icg s3h1, Icg s3l2, Icg s3m2, Icg s3h2) :
  master(m),
  slave0(s0), slave1(s1), slave2(s2), slave3(s3),
  slave0low1(s0l1), slave0mid1(s0m1), slave0high1(s0h1), slave0low2(s0l2), slave0mid2(s0m2), slave0high2(s0h2), slave0low3(s0l3), slave0mid3(s0m3), slave0high3(s0h3),
  slave1low0(s1l0), slave1mid0(s1m0), slave1high0(s1h0), slave1low2(s1l2), slave1mid2(s1m2), slave1high2(s1h2), slave1low3(s1l3), slave1mid3(s1m3), slave1high3(s1h3),
  slave2low0(s2l0), slave2mid0(s2m0), slave2high0(s2h0), slave2low1(s2l1), slave2mid1(s2m1), slave2high1(s2h1), slave2low3(s2l3), slave2mid3(s2m3), slave2high3(s2h3),
  slave3low0(s3l0), slave3mid0(s3m0), slave3high0(s3h0), slave3low1(s3l1), slave3mid1(s3m1), slave3high1(s3h1), slave3low2(s3l2), slave3mid2(s3m2), slave3high2(s3h2),
  includeMaster(im)
{
  if (S0 != s0l1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0L1"); }
  if (S0 != s0m1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0M1"); }
  if (S0 != s0h1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0H1"); }
  if (S0 != s0l2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0L2"); }
  if (S0 != s0m2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0M2"); }
  if (S0 != s0h2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0H2"); }
  if (S0 != s0l3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0L3"); }
  if (S0 != s0m3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0M3"); }
  if (S0 != s0h3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S0H3"); }
  if (S1 != s1l0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1L0"); }
  if (S1 != s1m0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1M0"); }
  if (S1 != s1h0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1H0"); }
  if (S1 != s1l2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1L2"); }
  if (S1 != s1m2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1M2"); }
  if (S1 != s1h2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1H2"); }
  if (S1 != s1l3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1L3"); }
  if (S1 != s1m3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1M3"); }
  if (S1 != s1h3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S1H3"); }
  if (S2 != s2l0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2L0"); }
  if (S2 != s2m0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2M0"); }
  if (S2 != s2h0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2H0"); }
  if (S2 != s2l1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2L1"); }
  if (S2 != s2m1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2M1"); }
  if (S2 != s2h1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2H1"); }
  if (S2 != s2l3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2L3"); }
  if (S2 != s2m3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2M3"); }
  if (S2 != s2h3.modulus()) { throw new std::invalid_argument("Modulus mismatch for S2H3"); }
  if (S3 != s3l0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3L0"); }
  if (S3 != s3m0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3M0"); }
  if (S3 != s3h0.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3H0"); }
  if (S3 != s3l1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3L1"); }
  if (S3 != s3m1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3M1"); }
  if (S3 != s3h1.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3H1"); }
  if (S3 != s3l2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3L2"); }
  if (S3 != s3m2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3M2"); }
  if (S3 != s3h2.modulus()) { throw new std::invalid_argument("Modulus mismatch for S3H2"); }
}

/**
 * Get the XSG's output
 *
 * If the master's output should be included, it is XORed into the result.
 *
 * @return the XSG's output
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
constexpr bool Xsg<M, S0, S1, S2, S3>::get() const noexcept {
  return slave0.get() ^ slave1.get() ^ slave2.get() ^ slave3.get() ^ (includeMaster && master.get());
}

/**
 * Step the XSG, XORing in the given value
 *
 * @param val  Value to XOR in
 * @return the current XSG
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
Xsg<M, S0, S1, S2, S3> &Xsg<M, S0, S1, S2, S3>::step(bool val) noexcept {
  switch (master.next() + 2 * master.next()) {
    case 0: step0(val); break;
    case 1: step1(val); break;
    case 2: step2(val); break;
    case 3: step3(val); break;
    default:            break;
  }
  if (includeMaster) { master.step(); }
  return *this;
}

/**
 * Convenience method that advances the XSG, XORing the given value in, and returns the new output
 *
 * @param val  value to XOR in
 * @return the current value of the XRG's output
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
bool Xsg<M, S0, S1, S2, S3>::next(bool val) noexcept {
  return step(val).get();
}

/**
 * Virtual generation method
 *
 * @return the current value of the XRG's output
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
bool Xsg<M, S0, S1, S2, S3>::next() noexcept {
  return next(false);
}

/**
 * Blend the slaves and, optionally, the master as well
 *
 * This method steps the slaves by one plus the given number of times to
 * ensure proper propagation of any XORed-in value.
 *
 * It also steps the master likewise if either the master is to be included
 * in the output, or forced by the optional parameter.
 *
 * @param additionalRounds  Additional rounds to apply
 * @param im                Whether to forcibly include the master in the blending
 * @return the current XSG
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
Xsg<M, S0, S1, S2, S3> &Xsg<M, S0, S1, S2, S3>::blend(std::size_t additionalRounds, bool im) {
  if (includeMaster || im) { for (std::size_t i = 0; i < (additionalRounds + 1) * M; i++) { master.step(); } }
  for (std::size_t i = 0; i < (additionalRounds + 1) * S0; i++) { slave0.step(); }
  for (std::size_t i = 0; i < (additionalRounds + 1) * S1; i++) { slave1.step(); }
  for (std::size_t i = 0; i < (additionalRounds + 1) * S2; i++) { slave2.step(); }
  for (std::size_t i = 0; i < (additionalRounds + 1) * S3; i++) { slave3.step(); }
  return *this;
}

/**
 * Inject the given key unambiguously into the XSG
 *
 * Injection entails:
 *  - feeding the key MSB first,
 *  - blending,
 *  - feeding the Elias-Omega code for the key's length,
 *  - blending,
 *  - feeding the key MSB first (again),
 *  - blending.
 *
 * All blending includes the master.
 *
 * @param key               Key to inject into the XSG
 * @param additionalRounds  Additional blending rounds to use
 * @return the current XSG
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
Xsg<M, S0, S1, S2, S3> &Xsg<M, S0, S1, S2, S3>::inject(std::string key, std::size_t additionalRounds) noexcept {
  // feed each bit in the key
  for (char c : key) { for (std::size_t i = 0; i < 8; i++) { step((c >> (7 - i)) % 2); } }
  // blend
  blend(1, true);
  // feed each bit of the Elias-Omega coding of the key's length
  for (bool b : eliasOmegaCode(key.length())) { step(b); }
  // blend
  blend(1, true);
  // feed each bit in the key
  for (char c : key) { for (std::size_t i = 0; i < 8; i++) { step((c >> (7 - i)) % 2); } }
  // blend
  blend(additionalRounds, true);

  return *this;
}

/**
 * Generate a variable length hash
 *
 * Hashing with this method entails:
 *  - feeding each byte of the given string, MSB-first,
 *  - blending,
 *  - feeding each bit of the Elias-Omega coding for the width (see below),
 *  - blending,
 *  - extracting as many bits as needed.
 *
 * The Elias-Omega coding step is in place to avoid different length hashes
 * of the same string to share a prefix, it was chosen because it is a prefix
 * free code with an elegant description.
 *
 * @param s    String to hash
 * @param w    Width of the hash to be generated
 * @return the generated hash, as an hexadecimal string
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
std::string Xsg<M, S0, S1, S2, S3>::hash(std::string s, std::size_t w) noexcept {
  return hashAdd(s).hashFinal(w);
}

/**
 * Add the given string to an ongoing hashing operation
 *
 * @param s  String to add
 * @return the current XSG
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
Xsg<M, S0, S1, S2, S3> &Xsg<M, S0, S1, S2, S3>::hashAdd(std::string s) noexcept {
  // feed each bit in the string
  for (char c : s) { for (std::size_t i = 0; i < 8; i++) { step((c >> (7 - i)) % 2); } }
  return *this;
}

/**
 * Return a hash for the elements added so far, but leave the hashing context untouched
 *
 * @param w  Hash length
 * @return the calculated hash as an hexadecimal string
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
std::string Xsg<M, S0, S1, S2, S3>::hashPartial(std::size_t w) const noexcept {
  // copy and return finalization
  return Xsg(*this).hashFinal(w);
}

/**
 * Finalize the hashing operation and return the calculated hash
 *
 * @param w  Hash length
 * @return the calculated hash as an hexadecimal string
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
std::string Xsg<M, S0, S1, S2, S3>::hashFinal(std::size_t w) noexcept {
  // blend it
  blend(1);

  // accumulator vector
  std::vector<bool> tmp;
  // extract as many bits as the hash will have (pseudohash)
  for (std::size_t i = 0; i < w; i++) { tmp.push_back(next()); }
  // feed each bit of the Elias-Omega coding of the hash's length and blend it
  for (bool b : eliasOmegaCode(w)) { step(b); } blend(1);
  // seal with the pseudohash, blend it, and clear the accumulator
  for (bool b : tmp) { step(b); } blend(1); tmp.clear();
  // extract as many bits as needed
  for (std::size_t i = 0; i < w; i++) { tmp.push_back(next()); }

  // return the hex representation
  return boolVector2hex(tmp);
}

/**
 * Step Slave 0 as needed, XORing the given value in
 *
 * This method steps the slave once, XORing the given value in, then it
 * calculates the number of additional steps needed, and steps the slave
 * that many times.
 *
 * @param val  Value to XOR in
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
void Xsg<M, S0, S1, S2, S3>::step0(bool val) noexcept {
  slave0.step(val);
  std::size_t as = 4u * maj3(slave1.get(slave1high0.next()), slave2.get(slave2high0.next()), slave3.get(slave3high0.next()))
                 + 2u * maj3(slave1.get( slave1mid0.next()), slave2.get( slave2mid0.next()), slave3.get( slave3mid0.next()))
                 + 1u * maj3(slave1.get( slave1low0.next()), slave2.get( slave2low0.next()), slave3.get( slave3low0.next()));
  for (std::size_t i = 0; i < as; i++) { slave0.step(); }
}

/**
 * Step Slave 1 as needed, XORing the given value in
 *
 * This method steps the slave once, XORing the given value in, then it
 * calculates the number of additional steps needed, and steps the slave
 * that many times.
 *
 * @param val  Value to XOR in
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
void Xsg<M, S0, S1, S2, S3>::step1(bool val) noexcept {
  slave1.step(val);
  std::size_t as = 4u * maj3(slave0.get(slave0high1.next()), slave2.get(slave2high1.next()), slave3.get(slave3high1.next()))
                 + 2u * maj3(slave0.get( slave0mid1.next()), slave2.get( slave2mid1.next()), slave3.get( slave3mid1.next()))
                 + 1u * maj3(slave0.get( slave0low1.next()), slave2.get( slave2low1.next()), slave3.get( slave3low1.next()));
  for (std::size_t i = 0; i < as; i++) { slave1.step(); }
}

/**
 * Step Slave 2 as needed, XORing the given value in
 *
 * This method steps the slave once, XORing the given value in, then it
 * calculates the number of additional steps needed, and steps the slave
 * that many times.
 *
 * @param val  Value to XOR in
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
void Xsg<M, S0, S1, S2, S3>::step2(bool val) noexcept {
  slave2.step(val);
  std::size_t as = 4u * maj3(slave0.get(slave0high2.next()), slave1.get(slave1high2.next()), slave3.get(slave3high2.next()))
                 + 2u * maj3(slave0.get( slave0mid2.next()), slave1.get( slave1mid2.next()), slave3.get( slave3mid2.next()))
                 + 1u * maj3(slave0.get( slave0low2.next()), slave1.get( slave1low2.next()), slave3.get( slave3low2.next()));
  for (std::size_t i = 0; i < as; i++) { slave2.step(); }
}

/**
 * Step Slave 3 as needed, XORing the given value in
 *
 * This method steps the slave once, XORing the given value in, then it
 * calculates the number of additional steps needed, and steps the slave
 * that many times.
 *
 * @param val  Value to XOR in
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
void Xsg<M, S0, S1, S2, S3>::step3(bool val) noexcept {
  slave3.step(val);
  std::size_t as = 4u * maj3(slave0.get(slave0high3.next()), slave1.get(slave1high3.next()), slave2.get(slave2high3.next()))
                 + 2u * maj3(slave0.get( slave0mid3.next()), slave1.get( slave1mid3.next()), slave2.get( slave2mid3.next()))
                 + 1u * maj3(slave0.get( slave0low3.next()), slave1.get( slave1low3.next()), slave2.get( slave2low3.next()));
  for (std::size_t i = 0; i < as; i++) { slave3.step(); }
}


#endif  /* XSG_HPP__ */

