#include "DynSub.h"

#include <vector>

#include "Random.h"


/**
 * Construct a new Dynamic Substitution from a Bit Generator
 *
 * @param g  Bit Generator to use
 */
DynSub::DynSub(BitGenerator const &g) : gen(g.clone()), fwd(generateRandomPermutation(*gen)) {}

/**
 * Transform the given character through the Dynamic Substitution
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t DynSub::xfrm(std::uint8_t c) {
  std::uint8_t result = fwd[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(fwd[c], fwd[rnd]);
  return result;
}

/**
 * Generate a random permutation using the given Bit Generator
 *
 * @param g  Bit Generator to use
 * @return the permuted array
 */
std::array<std::uint8_t, 256> DynSub::generateRandomPermutation(BitGenerator &gen) noexcept {
  std::vector<std::size_t> perm = generateAndShufflePermutation(gen, 256, 2);
  std::array<std::uint8_t, 256> ret;

  for (std::size_t i = 0; i < 256; i++) {
    ret[i] = static_cast<std::uint8_t>(perm[i]);
  }

  return ret;
}


/**
 * Construct a new Dynamic Substitution's Inverse from a Bit Generator
 *
 * @param g  Bit Generator to use
 */
InvDynSub::InvDynSub(BitGenerator const &g) : DynSub(g), inv(generateInversePermutation(fwd)) {}

/**
 * Transform the given character through the Dynamic Substitution's Inverse
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t InvDynSub::xfrm(std::uint8_t c) {
  std::uint8_t result = inv[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(inv[c], inv[fwd[rnd]]);
  std::swap(fwd[inv[c]], fwd[rnd]);
  return result;
}

/**
 * Invert the given substitution
 *
 * @param f  the substitution to use
 * @return the inverted substitution
 */
std::array<std::uint8_t, 256> InvDynSub::generateInversePermutation(std::array<std::uint8_t, 256> const &f) noexcept {
  std::array<std::uint8_t, 256> ret;
  for (std::size_t i = 0; i < 256; i++) {
    ret[f[i]] = static_cast<std::uint8_t>(i);
  }
  return ret;
}


/**
 * Transform the given character through the Dynamic Substitution
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t DynSubDD::xfrm(std::uint8_t c) {
  std::uint8_t result = fwd[fwd[c]], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(fwd[fwd[c]], fwd[rnd]);
  return result;

}

/**
 * Transform the given character through the Dynamic Substitution's Inverse
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t InvDynSubDD::xfrm(std::uint8_t c) {
  std::uint8_t result = inv[inv[c]], tmp = inv[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256));
  std::swap(inv[c], inv[fwd[rnd]]);
  std::swap(fwd[tmp], fwd[rnd]);
  return result;
}


/**
 * Transform the given character through the Dynamic Substitution
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t DynSubDR::xfrm(std::uint8_t c) {
  std::uint8_t result = fwd[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256)) ^ fwd[static_cast<std::uint8_t>(randRange(*gen, 256))];
  std::swap(fwd[c], fwd[rnd]);
  return result;
}

/**
 * Transform the given character through the Dynamic Substitution's Inverse
 *
 * @param c  Character to transform
 * @return the transformed character
 */
std::uint8_t InvDynSubDR::xfrm(std::uint8_t c) {
  std::uint8_t result = inv[c], rnd = static_cast<std::uint8_t>(randRange(*gen, 256)) ^ fwd[static_cast<std::uint8_t>(randRange(*gen, 256))];
  std::swap(inv[c], inv[fwd[rnd]]);
  std::swap(fwd[result], fwd[rnd]);
  return result;
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

