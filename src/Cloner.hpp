#ifndef CLONER_HPP__
#define CLONER_HPP__

#include "Cloner.h"

#include <type_traits>
#include <new>


namespace {
  /**
   * Virtual base detection
   *
   * If Base is a virtual base of Derived, the value member will be set to
   * true, otherwise, it will be set to false.
   *
   *
   * Taken from: http://stackoverflow.com/a/3364551
   *
   * @param Base  Base class to check
   * @param Derived  Derived class to check
   */
  template <typename Base, typename Derived>
  struct is_virtual_base_of {
    private:
      /**
       * This are just stepping stone structure definitions to disambiguate
       * Base and Derived.
       *
       */
      struct ZBase    : virtual public Base    {};
      struct ZDerived :         public Derived {};

      /**
       * A class deriving virtually from base
       *
       * NOTE: the pragmas are in place to suppress spurious warnings, since
       *       this is just a testbed structure and not a real, user-defined,
       *       production one.
       */
      #pragma GCC diagnostic push
      #pragma GCC diagnostic ignored "-Wextra"
      struct X : virtual public ZDerived, public ZBase {};
      #pragma GCC diagnostic pop

    public:
      /**
       * Virtual derivation should make X and Y the same size
       *
       */
      static constexpr bool value = sizeof(Derived) == sizeof(X);
  };

  /**
   * Metaclass to select appropriate cloning method (either using a static or a dynamic cast)
   *
   * @param T  Type to select cloning method for
   */
  template <typename T>
  struct CloneSelector {
    protected:
      /**
       * Cloning method for virtual base classes (uses dynamic_cast<>())
       *
       * @param that  Cloner to use as source
       * @param where  If using placement-clone, this is where the clone should be placed
       * @return a pointer to the clone
       */
      template <typename S = T>
      static typename std::enable_if< is_virtual_base_of<Cloner<S>, S>::value, S *>::type doIt(Cloner<T> const *that, void *where) {
        return nullptr == where ? new T(*dynamic_cast<T *>(const_cast<Cloner<T> *>(that))) : new(where) T(*dynamic_cast<T *>(const_cast<Cloner<T> *>(that)));
      }

      /**
       * Cloning method for non-virtual base classes (uses static_cast<>())
       *
       * @param that  Cloner to use as source
       * @param where  If using placement-clone, this is where the clone should be placed
       * @return a pointer to the clone
       */
      template <typename S = T>
      static typename std::enable_if<!is_virtual_base_of<Cloner<S>, S>::value, S *>::type doIt(Cloner<T> const *that, void *where) {
        return nullptr == where ? new T(*static_cast<T *>(const_cast<Cloner<T> *>(that))) : new(where) T(*static_cast<T *>(const_cast<Cloner<T> *>(that)));
      }

    public:
      /**
       * Properly selected cloning method
       *
       * @param that  Cloner to use as source
       * @param where  If using placement-clone, this is where the clone should be placed
       * @return a pointer to the clone
       */
      static T *clone(Cloner<T> const *that, void *where) { return doIt(that, where); }
  };
}


/**
 * Placement-clone the current object
 *
 * @param where  Memory address where to clone
 * @return a pointer to a placement-new-allocated copy of the current object
 */
template <typename T>
T *Cloner<T>::clone(void *where) const {
  // make sure we can copy-construct objects of type T
  static_assert(std::is_copy_constructible<T>::value, "Not copy constructible");

  // select clone method and apply
  return CloneSelector<T>::clone(this, where);
}


#endif /* CLONER_HPP__ */

