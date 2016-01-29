#include "DynSub.h"

#include <new>

#include "Random.h"


namespace {
  /**
   * Generate a random permutation using the given Bit Generator
   *
   * @param g  Bit Generator to use
   * @return the permuted array
   */
  std::array<std::uint8_t, 256> generateRandomPermutation(BitGenerator &gen) noexcept {
    std::vector<std::size_t> perm = generateAndShufflePermutation(gen, 256, 2);
    std::array<std::uint8_t, 256> ret;

    for (std::size_t i = 0; i < 256; i++) {
      ret[i] = static_cast<std::uint8_t>(perm[i]);
    }

    return ret;
  }

  /**
   * Invert the given substitution
   *
   * @param fwd  the substitution to use
   * @return the inverted substitution
   */
  std::array<std::uint8_t, 256> generateInversePermutation(std::array<std::uint8_t, 256> const &fwd) noexcept {
    std::array<std::uint8_t, 256> ret;
    for (std::size_t i = 0; i < 256; i++) {
      ret[fwd[i]] = static_cast<std::uint8_t>(i);
    }
    return ret;
  }
}


/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
DynSubSRSD *DynSubSRSD::clone(void *where) const {
  return nullptr == where ? new DynSubSRSD(*this) : new(where) DynSubSRSD(*this);
}

/**
 * Construct a new Dynamic Substitution from a Bit Generator
 *
 * @param g  Bit Generator to use
 */
DynSubSRSD::DynSubSRSD(BitGenerator const &g) : gen(g.clone()), fwd(generateRandomPermutation(*gen)) {}

/**
 * Transform the given character through the Dynamic Substitution
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t DynSubSRSD::xfrm(std::uint8_t c) {
  std::uint8_t result = fwd[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(fwd[c], fwd[rnd]);
  return result;
}


/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
InvDynSubSRSD *InvDynSubSRSD::clone(void *where) const {
  return nullptr == where ? new InvDynSubSRSD(*this) : new(where) InvDynSubSRSD(*this);
}

/**
 * Construct a new Dynamic Substitution's Inverse from a Bit Generator
 *
 * @param g  Bit Generator to use
 */
InvDynSubSRSD::InvDynSubSRSD(BitGenerator const &g) : DynSubSRSD(g), inv(generateInversePermutation(fwd)) {}

/**
 * Transform the given character through the Dynamic Substitution's Inverse
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t InvDynSubSRSD::xfrm(std::uint8_t c) {
  std::uint8_t result = inv[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(inv[c], inv[fwd[rnd]]);
  std::swap(fwd[inv[c]], fwd[rnd]);
  return result;
}


/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
DynSubSRDD *DynSubSRDD::clone(void *where) const {
  return nullptr == where ? new DynSubSRDD(*this) : new(where) DynSubSRDD(*this);
}

/**
 * Transform the given character through the Dynamic Substitution
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t DynSubSRDD::xfrm(std::uint8_t c) {
  std::uint8_t result = fwd[fwd[c]], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(fwd[fwd[c]], fwd[rnd]);
  return result;

}

/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
InvDynSubSRDD *InvDynSubSRDD::clone(void *where) const {
  return nullptr == where ? new InvDynSubSRDD(*this) : new(where) InvDynSubSRDD(*this);
}

/**
 * Transform the given character through the Dynamic Substitution's Inverse
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t InvDynSubSRDD::xfrm(std::uint8_t c) {
  std::uint8_t result = inv[inv[c]], tmp = inv[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(inv[c], inv[fwd[rnd]]);
  std::swap(fwd[tmp], fwd[rnd]);
  return result;
}


/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
DynSubDRSD *DynSubDRSD::clone(void *where) const {
  return nullptr == where ? new DynSubDRSD(*this) : new(where) DynSubDRSD(*this);
}

/**
 * Transform the given character through the Dynamic Substitution
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t DynSubDRSD::xfrm(std::uint8_t c) {
  std::uint8_t result = fwd[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256)) ^ fwd[static_cast<std::uint8_t>(randRange(*gen, 256))];
  std::swap(fwd[c], fwd[rnd]);
  return result;
}

/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
InvDynSubDRSD *InvDynSubDRSD::clone(void *where) const {
  return nullptr == where ? new InvDynSubDRSD(*this) : new(where) InvDynSubDRSD(*this);
}

/**
 * Transform the given character through the Dynamic Substitution's Inverse
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t InvDynSubDRSD::xfrm(std::uint8_t c) {
  std::uint8_t result = inv[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256)) ^ fwd[static_cast<std::uint8_t>(randRange(*gen, 256))];
  std::swap(inv[c], inv[fwd[rnd]]);
  std::swap(fwd[result], fwd[rnd]);
  return result;
}


/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
DynSubDRDD *DynSubDRDD::clone(void *where) const {
  return nullptr == where ? new DynSubDRDD(*this) : new(where) DynSubDRDD(*this);
}

/**
 * Transform the given character through the Dynamic Substitution
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t DynSubDRDD::xfrm(std::uint8_t c) {
  std::uint8_t result = fwd[fwd[c]], rnd = static_cast<std::uint8_t>(randRange(*gen, 256)) ^ fwd[static_cast<std::uint8_t>(randRange(*gen, 256))];
  std::swap(fwd[fwd[c]], fwd[rnd]);
  return result;
}

/**
 * Virtual placement clone
 *
 * @param where  Memory position where to emplace
 * @return the cloned object
 */
InvDynSubDRDD *InvDynSubDRDD::clone(void *where) const {
  return nullptr == where ? new InvDynSubDRDD(*this) : new(where) InvDynSubDRDD(*this);
}

/**
 * Transform the given character through the Dynamic Substitution's Inverse
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t InvDynSubDRDD::xfrm(std::uint8_t c) {
  std::uint8_t result = inv[inv[c]], tmp = inv[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256)) ^ fwd[static_cast<std::uint8_t>(randRange(*gen, 256))];
  std::swap(inv[c], inv[fwd[rnd]]);
  std::swap(fwd[tmp], fwd[rnd]);
  return result;
}

