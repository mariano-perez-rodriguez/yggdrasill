#ifndef DYN_TRANS__
#define DYN_TRANS__

#include <cstddef>
#include <cstdint>
#include <vector>

#include "BitGenerator.h"


/**
 * Dynamic Transposition class
 *
 */
class DynTrans {
  public:
    /**
     * Construct a Dynamic Transposition of the given with using the given Bit Generator
     *
     * @param gen  Bit Generator to use
     * @param w  Transposition width
     * @throws std::out_of_range  if w bigger than 8192
     */
    DynTrans(BitGenerator &gen, std::size_t w);

    /**
     * Transform the given input block
     *
     * @param input  The input block to transform
     * @return the transformed block
     */
    std::vector<std::uint8_t> xfrm(std::vector<std::uint8_t> const &input) const;

  protected:
    /**
     * Bit transposition to use
     *
     */
    std::vector<std::size_t> trans;
};


/**
 * Inverse Dynamic Transposition class
 *
 */
class InvDynTrans {
  public:
    /**
     * Construct a Dynamic Transposition's inverse of the given with using the given Bit Generator
     *
     * @param gen  Bit Generator to use
     * @param w  Transposition width
     * @throws std::out_of_range  if w bigger than 8192
     */
    InvDynTrans(BitGenerator &gen, std::size_t w);

    /**
     * Transform the given input block
     *
     * @param input  The input block to transform
     * @return the transformed block
     */
    std::vector<std::uint8_t> xfrm(std::vector<std::uint8_t> const &input) const;

  protected:
    /**
     * Bit transposition's inverse to use
     *
     */
    std::vector<std::size_t> trans;
};


#endif  /* DYN_TRANS__ */

