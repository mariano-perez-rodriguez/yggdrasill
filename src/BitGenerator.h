#ifndef BIT_GENERATOR_H__
#define BIT_GENERATOR_H__


/**
 * Interface for boolean generators
 *
 */
class BitGenerator {
  public:
    /**
     * Pure virtual placement clone
     *
     * @param where  Memory position where to emplace
     * @return the cloned object
     */
    virtual BitGenerator *clone(void *where = nullptr) const = 0;

    /**
     * Pure virtual method to return the current output and advance the generator
     *
     * @return the generator's output bit
     */
    virtual bool next() noexcept = 0;

    /**
     * Virtual destructor
     *
     */
    virtual ~BitGenerator() = default;
};


#endif  /* BIT_GENERATOR_H__ */

