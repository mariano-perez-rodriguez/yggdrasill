#ifndef XSG_H__
#define XSG_H__

#include <cstddef>
#include <stdexcept>
#include <string>
#include <cstdint>

#include "BitGenerator.h"
#include "Hasher.h"
#include "Lfsr.h"
#include "Icg.h"


/**
 * XSG class
 *
 * @param M   Master LFSR size (should be an odd prime)
 * @param S0  Slave 0 LFSR size (should be prime)
 * @param S1  Slave 1 LFSR size (should be prime)
 * @param S2  Slave 2 LFSR size (should be prime)
 * @param S3  Slave 3 LFSR size (should be prime)
 */
template <std::size_t M, std::size_t S0, std::size_t S1, std::size_t S2, std::size_t S3>
class Xsg : public BitGenerator, public Hasher {
  // Ensure the master LFSR is at least odd
  static_assert(1 == M % 2, "The master LFSR size should be an odd prime");

  public:
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
    Xsg(Lfsr<M> m, bool im,
      Lfsr<S0> s0, Icg s0l1, Icg s0m1, Icg s0h1, Icg s0l2, Icg s0m2, Icg s0h2, Icg s0l3, Icg s0m3, Icg s0h3,
      Lfsr<S1> s1, Icg s1l0, Icg s1m0, Icg s1h0, Icg s1l2, Icg s1m2, Icg s1h2, Icg s1l3, Icg s1m3, Icg s1h3,
      Lfsr<S2> s2, Icg s2l0, Icg s2m0, Icg s2h0, Icg s2l1, Icg s2m1, Icg s2h1, Icg s2l3, Icg s2m3, Icg s2h3,
      Lfsr<S3> s3, Icg s3l0, Icg s3m0, Icg s3h0, Icg s3l1, Icg s3m1, Icg s3h1, Icg s3l2, Icg s3m2, Icg s3h2);

    /**
     * Get the XSG's output
     *
     * If the master's output should be included, it is XORed into the result.
     *
     * @return the XSG's output
     */
    constexpr bool get() const noexcept;

    /**
     * Step the XSG, XORing in the given value
     *
     * @param val  Value to XOR in
     * @return the current XSG
     */
    Xsg &step(bool val = false) noexcept;

    /**
     * Convenience method that advances the XSG, XORing the given value in, and returns the new output
     *
     * @param val  value to XOR in
     * @return the current value of the XRG's output
     */
    bool next(bool val) noexcept;

    /**
     * Virtual generation method
     *
     * @return the current value of the XRG's output
     */
    virtual bool next() noexcept override;

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
    Xsg &blend(std::size_t additionalRounds = 1, bool im = false);

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
    Xsg &inject(std::string key, std::size_t additionalRounds = 1) noexcept;

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
    virtual std::string hash(std::string s, std::size_t w) noexcept override;

    /**
     * Add the given string to an ongoing hashing operation
     *
     * @param s  String to add
     * @return the current XSG
     */
    virtual Xsg &hashAdd(std::string s) noexcept override;

    /**
     * Return a hash for the elements added so far, but leave the hashing context untouched
     *
     * @param w  Hash length
     * @return the calculated hash as an hexadecimal string
     */
    virtual std::string hashPartial(std::size_t w) const noexcept override;

    /**
     * Finalize the hashing operation and return the calculated hash
     *
     * @param w  Hash length
     * @return the calculated hash as an hexadecimal string
     */
    virtual std::string hashFinal(std::size_t w) noexcept override;

  protected:
    /**
     * Step Slave 0 as needed, XORing the given value in
     *
     * This method steps the slave once, XORing the given value in, then it
     * calculates the number of additional steps needed, and steps the slave
     * that many times.
     *
     * @param val  Value to XOR in
     */
    void step0(bool val = false) noexcept;

    /**
     * Step Slave 1 as needed, XORing the given value in
     *
     * This method steps the slave once, XORing the given value in, then it
     * calculates the number of additional steps needed, and steps the slave
     * that many times.
     *
     * @param val  Value to XOR in
     */
    void step1(bool val = false) noexcept;

    /**
     * Step Slave 2 as needed, XORing the given value in
     *
     * This method steps the slave once, XORing the given value in, then it
     * calculates the number of additional steps needed, and steps the slave
     * that many times.
     *
     * @param val  Value to XOR in
     */
    void step2(bool val = false) noexcept;

    /**
     * Step Slave 3 as needed, XORing the given value in
     *
     * This method steps the slave once, XORing the given value in, then it
     * calculates the number of additional steps needed, and steps the slave
     * that many times.
     *
     * @param val  Value to XOR in
     */
    void step3(bool val = false) noexcept;

    /**
     * Master LFSR
     *
     */
    Lfsr<M> master;

    /**
     * Slave 0 LFSR
     *
     */
    Lfsr<S0> slave0;

    /**
     * Slave 1 LFSR
     *
     */
    Lfsr<S1> slave1;

    /**
     * Slave 2 LFSR
     *
     */
    Lfsr<S2> slave2;

    /**
     * Slave 3 LFSR
     *
     */
    Lfsr<S3> slave3;

    /**
     * ICG into Slave 0's state for the low bit of Slave 1's additional step count
     *
     */
    Icg slave0low1;

    /**
     * ICG into Slave 0's state for the mid bit of Slave 1's additional step count
     *
     */
    Icg slave0mid1;

    /**
     * ICG into Slave 0's state for the high bit of Slave 1's additional step count
     *
     */
    Icg slave0high1;

    /**
     * ICG into Slave 0's state for the low bit of Slave 2's additional step count
     *
     */
    Icg slave0low2;

    /**
     * ICG into Slave 0's state for the mid bit of Slave 2's additional step count
     *
     */
    Icg slave0mid2;

    /**
     * ICG into Slave 0's state for the high bit of Slave 2's additional step count
     *
     */
    Icg slave0high2;

    /**
     * ICG into Slave 0's state for the low bit of Slave 3's additional step count
     *
     */
    Icg slave0low3;

    /**
     * ICG into Slave 0's state for the mid bit of Slave 3's additional step count
     *
     */
    Icg slave0mid3;

    /**
     * ICG into Slave 0's state for the high bit of Slave 3's additional step count
     *
     */
    Icg slave0high3;

    /**
     * ICG into Slave 1's state for the low bit of Slave 0's additional step count
     *
     */
    Icg slave1low0;

    /**
     * ICG into Slave 1's state for the mid bit of Slave 0's additional step count
     *
     */
    Icg slave1mid0;

    /**
     * ICG into Slave 1's state for the high bit of Slave 0's additional step count
     *
     */
    Icg slave1high0;

    /**
     * ICG into Slave 1's state for the low bit of Slave 2's additional step count
     *
     */
    Icg slave1low2;

    /**
     * ICG into Slave 1's state for the mid bit of Slave 2's additional step count
     *
     */
    Icg slave1mid2;

    /**
     * ICG into Slave 1's state for the high bit of Slave 2's additional step count
     *
     */
    Icg slave1high2;

    /**
     * ICG into Slave 1's state for the low bit of Slave 3's additional step count
     *
     */
    Icg slave1low3;

    /**
     * ICG into Slave 1's state for the mid bit of Slave 3's additional step count
     *
     */
    Icg slave1mid3;

    /**
     * ICG into Slave 1's state for the high bit of Slave 3's additional step count
     *
     */
    Icg slave1high3;

    /**
     * ICG into Slave 2's state for the low bit of Slave 0's additional step count
     *
     */
    Icg slave2low0;

    /**
     * ICG into Slave 2's state for the mid bit of Slave 0's additional step count
     *
     */
    Icg slave2mid0;

    /**
     * ICG into Slave 2's state for the high bit of Slave 0's additional step count
     *
     */
    Icg slave2high0;

    /**
     * ICG into Slave 2's state for the low bit of Slave 1's additional step count
     *
     */
    Icg slave2low1;

    /**
     * ICG into Slave 2's state for the mid bit of Slave 1's additional step count
     *
     */
    Icg slave2mid1;

    /**
     * ICG into Slave 2's state for the high bit of Slave 1's additional step count
     *
     */
    Icg slave2high1;

    /**
     * ICG into Slave 2's state for the low bit of Slave 3's additional step count
     *
     */
    Icg slave2low3;

    /**
     * ICG into Slave 2's state for the mid bit of Slave 3's additional step count
     *
     */
    Icg slave2mid3;

    /**
     * ICG into Slave 2's state for the high bit of Slave 3's additional step count
     *
     */
    Icg slave2high3;

    /**
     * ICG into Slave 3's state for the low bit of Slave 0's additional step count
     *
     */
    Icg slave3low0;

    /**
     * ICG into Slave 3's state for the mid bit of Slave 0's additional step count
     *
     */
    Icg slave3mid0;

    /**
     * ICG into Slave 3's state for the high bit of Slave 0's additional step count
     *
     */
    Icg slave3high0;

    /**
     * ICG into Slave 3's state for the low bit of Slave 1's additional step count
     *
     */
    Icg slave3low1;

    /**
     * ICG into Slave 3's state for the mid bit of Slave 1's additional step count
     *
     */
    Icg slave3mid1;

    /**
     * ICG into Slave 3's state for the high bit of Slave 1's additional step count
     *
     */
    Icg slave3high1;

    /**
     * ICG into Slave 3's state for the low bit of Slave 2's additional step count
     *
     */
    Icg slave3low2;

    /**
     * ICG into Slave 3's state for the mid bit of Slave 2's additional step count
     *
     */
    Icg slave3mid2;

    /**
     * ICG into Slave 3's state for the high bit of Slave 2's additional step count
     *
     */
    Icg slave3high2;

    /**
     * Whether to include the master in the XSG's output
     *
     */
    bool includeMaster;
};

/**
 * Xsg512 is the canonical XSG of 512-like width
 *
 */
using Xsg512 = Xsg<521, 523, 541, 547, 557>;

/**
 * Return a distilled XSG from a key
 *
 * Distillation works by accepting or creating a bootstrap XSG, feeding it
 * the given key, and using it as a PRNG to generate (in order):
 *  - LFSR initial states,
 *  - mother multipliers,
 *  - offsets, and
 *  - initial values,
 * the generators used are the canonical ones of orders 521, 523, 541, 547,
 * and 557.
 *
 * @param key   The key to use for distilling
 * @param boot  The bootstrap XSG to use (the canonical one if none given)
 * @return the created bootstrap XSG
 */
Xsg512 distillXsg(std::string key) noexcept;
Xsg512 distillXsg(std::string key, Xsg512 &boot) noexcept;


#include "Xsg.hpp"

#endif  /* XSG_H__ */

