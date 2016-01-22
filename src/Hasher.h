#ifndef HASHER_H__
#define HASHER_H__

#include <string>
#include <cstddef>


/**
 * Interface for hashers
 *
 */
class Hasher {
  public:
    /**
     * Generate a variable length hash
     *
     * @param s    String to hash
     * @param w    Width of the hash to be generated
     * @return the generated hash, as an hexadecimal string
     */
    virtual std::string hash(std::string s, std::size_t w) noexcept = 0;

    /**
     * Add the given string to an ongoing hashing operation
     *
     * @param s  String to add
     * @return the current Hasher
     */
    virtual Hasher &hashAdd(std::string s) noexcept = 0;

    /**
     * Return a hash for the elements added so far, but leave the hashing context untouched
     *
     * @param w  Hash length
     * @return the calculated hash as an hexadecimal string
     */
    virtual std::string hashPartial(std::size_t w) const noexcept = 0;

    /**
     * Finalize the hashing operation and return the calculated hash
     *
     * @param w  Hash length
     * @return the calculated hash as an hexadecimal string
     */
    virtual std::string hashFinal(std::size_t w) noexcept = 0;

    /**
     * Virtual destructor
     *
     */
    virtual ~Hasher() = default;
};


#endif  /* HASHER_H__ */

