#ifndef DYN_SUB_H__
#define DYN_SUB_H__

#include <cstddef>
#include <array>

#include "BitGenerator.h"

#include "vendors/value_ptr/value_ptr.h"


/**
 * Dynamic Substitution class
 *
 */
class DynSub {
  public:
    /**
     * Construct a new Dynamic Substitution from a Bit Generator
     *
     * @param g  Bit Generator to use
     */
    DynSub(BitGenerator const &g);

    /**
     * Virtual destructor
     *
     */
    virtual ~DynSub() noexcept = default;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c);

  protected:
    /**
     * Generate a random permutation using the given Bit Generator
     *
     * @param g  Bit Generator to use
     * @return the permuted array
     */
    static std::array<std::uint8_t, 256> generateRandomPermutation(BitGenerator &gen) noexcept;

    /**
     * Bit Generator (wrapped into a value_ptr)
     *
     */
    value_ptr<BitGenerator> gen;

    /**
     * Current substitution being used
     *
     */
    std::array<std::uint8_t, 256> fwd;
};


/**
 * Dynamic Substitution's Inverse class
 *
 */
class InvDynSub : public DynSub {
  public:
    /**
     * Construct a new Dynamic Substitution's Inverse from a Bit Generator
     *
     * @param g  Bit Generator to use
     */
    InvDynSub(BitGenerator const &g);

    /**
     * Virtual destructor
     *
     */
    virtual ~InvDynSub() noexcept = default;

    /**
     * Transform the given character through the Dynamic Substitution's Inverse
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;

  protected:
    /**
     * Invert the given substitution
     *
     * @param f  the substitution to use
     * @return the inverted substitution
     */
    static std::array<std::uint8_t, 256> generateInversePermutation(std::array<std::uint8_t, 256> const &f) noexcept;

    /**
     * Current substitution's inverse
     *
     */
    std::array<std::uint8_t, 256> inv;
};


/**
 * Dynamic Substitution class - Double-Data version
 *
 */
class DynSubDD : public DynSub {
  public:
    /**
     * Import all constructors
     *
     */
    using DynSub::DynSub;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


/**
 * Dynamic Substitution class - Double-Data version's Inverse
 *
 */
class InvDynSubDD : public InvDynSub {
  public:
    /**
     * Import all constructors
     *
     */
    using InvDynSub::InvDynSub;

    /**
     * Transform the given character through the Dynamic Substitution's Inverse
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


/**
 * Dynamic Substitution class - Double-Random version
 *
 */
class DynSubDR : public DynSub {
  public:
    /**
     * Import all constructors
     *
     */
    using DynSub::DynSub;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


/**
 * Dynamic Substitution class - Double-Random version's Inverse
 *
 */
class InvDynSubDR : public InvDynSub {
  public:
    /**
     * Import all constructors
     *
     */
    using InvDynSub::InvDynSub;

    /**
     * Transform the given character through the Dynamic Substitution's Inverse
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


/**
 * Dynamic Substitution class - Double-Random-Double-Data version
 *
 */
class DynSubDRDD : public DynSub {
  public:
    /**
     * Import all constructors
     *
     */
    using DynSub::DynSub;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


/**
 * Dynamic Substitution class - Double-Random version's Inverse
 *
 */
class InvDynSubDRDD : public InvDynSub {
  public:
    /**
     * Import all constructors
     *
     */
    using InvDynSub::InvDynSub;

    /**
     * Transform the given character through the Dynamic Substitution's Inverse
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


#endif /* DYN_SUB_H__ */

