//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) 2001 - 2017 Twan van Laarhoven and Sean Hunt             |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

#ifndef HEADER_UTIL_SMART_PTR
#define HEADER_UTIL_SMART_PTR

/** @file util/smart_ptr.hpp
 *
 *  @brief Utilities related to boost smart pointers
 */

// ----------------------------------------------------------------------------- : Includes

#include <memory>

using std::shared_ptr;
using std::unique_ptr;
using std::static_pointer_cast;
using std::dynamic_pointer_cast;
using std::make_shared;

// TODO: remove scoped_ptr
template <typename T> using scoped_ptr = unique_ptr<T>;

// ----------------------------------------------------------------------------- : Declaring

/// Declares the type TypeP as a shared_ptr<Type>
#define DECLARE_SHARED_POINTER_TYPE(Type) \
  class Type; \
  typedef shared_ptr<Type> Type##P;

// ----------------------------------------------------------------------------- : Creating

/// Wrap a newly allocated pointer in an shared_ptr
/** Usage:
  *    return shared(new T(stuff)));
  */
template <typename T>
//[[deprecated("use make_shared")]]
inline shared_ptr<T> shared(T* ptr) {
  return shared_ptr<T>(ptr);
}
template <typename T>
//[[deprecated("use make_shared")]]
inline shared_ptr<T> intrusive(T* ptr) {
  return shared_ptr<T>(ptr);
}

// ----------------------------------------------------------------------------- : Intrusive pointers

#define DECLARE_POINTER_TYPE DECLARE_SHARED_POINTER_TYPE
#define intrusive_ptr shared_ptr

template <typename T> class IntrusivePtrBase {};

/// IntrusivePtrBase with a virtual destructor
class IntrusivePtrVirtualBase : public IntrusivePtrBase<IntrusivePtrVirtualBase> {
  public:
  virtual ~IntrusivePtrVirtualBase() {}
};

class IntrusivePtrBaseWithDelete : public IntrusivePtrBase<IntrusivePtrBaseWithDelete> {
  public:
  virtual ~IntrusivePtrBaseWithDelete() {}
  protected:
  /// Delete this object
  virtual void destroy() {
    delete this;
  }
};

/// Pointer to 'anything'
typedef intrusive_ptr<IntrusivePtrVirtualBase> VoidP;

// ----------------------------------------------------------------------------- : EOF
#endif
