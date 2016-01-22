#ifndef CLONER_HPP__
#define CLONER_HPP__

#include "Cloner.h"

#include <type_traits>
#include <new>


/**
 * Placement-clone the current object
 *
 * @param where  Memory address where to clone
 * @return a pointer to a placement-new-allocated copy of the current object
 */
template <typename T>
T *Cloner<T>::clone(void *where) {
  // Make sure we can copy-construct objects of type T
  static_assert(std::is_copy_constructible<T>::value, "Not copy constructible");

  return nullptr == where ? new T(*static_cast<T *>(this)) : new(where) T(*static_cast<T *>(this));
}


#endif /* CLONER_HPP__ */

