#ifndef CLONER_H__
#define CLONER_H__


/**
 * Cloner trait
 *
 * @param T  Underlying type to clone
 */
template <typename T>
class Cloner {
  public:
    /**
     * Placement-clone the current object
     *
     * @param where  Memory address where to clone
     * @return a pointer to a placement-new-allocated copy of the current object
     */
    virtual T *clone(void *where = nullptr);

    /**
     * Virtual destructor
     *
     */
    virtual ~Cloner() noexcept = default;
};


#include "Cloner.hpp"

#endif  /* CLONER_H__ */

