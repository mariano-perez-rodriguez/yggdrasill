#ifndef DYN_SUB_H__
#define DYN_SUB_H__

#include <cstddef>
#include <array>
#include <vector>

#include "BitGenerator.h"

#include "vendors/value_ptr/value_ptr.h"


/**
 * Dynamic Substitution class - Single-Random-Single-Data version
 *
 */
class DynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual DynSubSRSD *clone(void *where = nullptr) const;

    /**
     * Construct a new Dynamic Substitution from a Bit Generator
     *
     * @param g  Bit Generator to use
     */
    DynSubSRSD(BitGenerator const &g);

    /**
     * Virtual destructor
     *
     */
    virtual ~DynSubSRSD() noexcept = default;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c);

  protected:
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
 * Dynamic Substitution class - Single-Random-Single-Data's Inverse
 *
 */
class InvDynSubSRSD : public DynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual InvDynSubSRSD *clone(void *where = nullptr) const override;

    /**
     * Construct a new Dynamic Substitution's Inverse from a Bit Generator
     *
     * @param g  Bit Generator to use
     */
    InvDynSubSRSD(BitGenerator const &g);

    /**
     * Virtual destructor
     *
     */
    virtual ~InvDynSubSRSD() noexcept = default;

    /**
     * Transform the given character through the Dynamic Substitution's Inverse
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;

  protected:
    /**
     * Current substitution's inverse
     *
     */
    std::array<std::uint8_t, 256> inv;
};


/**
 * Dynamic Substitution class - Single-Random-Double-Data version
 *
 */
class DynSubSRDD : public DynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual DynSubSRDD *clone(void *where = nullptr) const override;

    /**
     * Import all constructors
     *
     */
    using DynSubSRSD::DynSubSRSD;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};

/**
 * Dynamic Substitution class - Single-Random-Double-Data version's Inverse
 *
 */
class InvDynSubSRDD : public InvDynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual InvDynSubSRDD *clone(void *where = nullptr) const override;

    /**
     * Import all constructors
     *
     */
    using InvDynSubSRSD::InvDynSubSRSD;

    /**
     * Transform the given character through the Dynamic Substitution's Inverse
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


/**
 * Dynamic Substitution class - Double-Random-Single-Data version
 *
 */
class DynSubDRSD : public DynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual DynSubDRSD *clone(void *where = nullptr) const override;

    /**
     * Import all constructors
     *
     */
    using DynSubSRSD::DynSubSRSD;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};

/**
 * Dynamic Substitution class - Double-Random-Single-Data version's Inverse
 *
 */
class InvDynSubDRSD : public InvDynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual InvDynSubDRSD *clone(void *where = nullptr) const override;

    /**
     * Import all constructors
     *
     */
    using InvDynSubSRSD::InvDynSubSRSD;

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
class DynSubDRDD : public DynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual DynSubDRDD *clone(void *where = nullptr) const override;

    /**
     * Import all constructors
     *
     */
    using DynSubSRSD::DynSubSRSD;

    /**
     * Transform the given character through the Dynamic Substitution
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};

/**
 * Dynamic Substitution class - Double-Random-Double-Data version's Inverse
 *
 */
class InvDynSubDRDD : public InvDynSubSRSD {
  public:
    /**
     * Virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual InvDynSubDRDD *clone(void *where = nullptr) const override;

    /**
     * Import all constructors
     *
     */
    using InvDynSubSRSD::InvDynSubSRSD;

    /**
     * Transform the given character through the Dynamic Substitution's Inverse
     *
     * @param c  Character to transform
     * @return the transformed character
     */
    virtual std::uint8_t xfrm(std::uint8_t c) override;
};


/**
 * Enum class for each type of Dynamic Substitution supported
 *
 * Four letter acronym shorthands are provided.
 *
 */
enum class DynSubType {
  SingleRandomSingleData, SRSD = SingleRandomSingleData,
  SingleRandomDoubleData, SRDD = SingleRandomDoubleData,
  DoubleRandomSingleData, DRSD = DoubleRandomSingleData,
  DoubleRandomDoubleData, DRDD = DoubleRandomDoubleData,
};


/**
 * Block-level Dynamic Substitution class
 *
 */
class DynSub {
  public:
    /**
     * Construct a Dynamic Substitution of the given type, using the given Bit Generator
     *
     * @param gens  Bit Generators to use
     * @param type  Type to create
     */
    DynSub(DynSubType const type, std::vector<BitGenerator> &gens);

    /**
     * Apply the Dynamic Substitution to the given byte block
     *
     * @param input  Input byte block
     * @return the transformed byte block
     * @throws
     */
    std::vector<std::uint8_t> xfrm(std::vector<std::uint8_t> const &input);

  protected:
    /**
     * Dynamic Substitutions to use
     *
     */
    std::vector<value_ptr<DynSubSRSD>> subs;
};


#endif /* DYN_SUB_H__ */

