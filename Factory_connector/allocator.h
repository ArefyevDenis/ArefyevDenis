#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <cstddef>
#include <stddef.h>
#include <exception>
#include <iostream>

class Allocator
{
public:

  static Allocator& instance();

protected:

  Allocator() ;//{std::cout <<__PRETTY_FUNCTION__<<'\n';}

  Allocator(const Allocator&)               = delete;
  Allocator( Allocator&&)                   = delete;
  Allocator& operator = (const Allocator&)  = delete;
  Allocator& operator = (Allocator&&)       = delete;

  void* base_pointer{nullptr};

public:

  ~Allocator() ;//{std::cout <<__PRETTY_FUNCTION__<<'\n';}

  std::size_t max_size(std::size_t __n) const ;

  void*  allocate(std::size_t __n, void* = static_cast<void*>(nullptr));

  void   deallocate(void *__p, std::size_t __n);

//  template<typename TP>
//  std::size_t  max_size() const
//  {
//    return std::size_t(-1) / sizeof(TP);
//  }

  template<typename _Up, typename... _Args>
  void     construct(_Up* __p, _Args&&... __args) {
    ::new((void *)__p) _Up(std::forward<_Args>(__args)...);
  }

  template<typename _Up>
  void    destroy(_Up* __p) {
    __p->~_Up();
  }

};

template<typename _Tp>
class new_allocator
{
public:
  typedef std::size_t     size_type;
  typedef ptrdiff_t  difference_type;
  typedef _Tp*       pointer;
  typedef const _Tp* const_pointer;
  typedef _Tp&       reference;
  typedef const _Tp& const_reference;
  typedef _Tp        value_type;

  template<typename _Tp1>
  struct rebind
  {
    typedef new_allocator<_Tp1> other;
  };

  new_allocator()  { }

  new_allocator(const new_allocator&)  { }

  template<typename _Tp1>
  new_allocator(const new_allocator<_Tp1>&)  { }

  ~new_allocator()  { }

  pointer    address(reference __x) const
  {
    return std::__addressof(__x);
  }

  const_pointer   address(const_reference __x) const
  {
    return std::__addressof(__x);
  }




  pointer   allocate(size_type __n, const void* = static_cast<const void*>(0))
  {
    if (__n > this->max_size())
      std::bad_alloc();

    return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
  }

  void   deallocate(pointer __p, size_type)
  {
    ::operator delete(__p);
  }

  size_type     max_size() const
  {
    return size_t(-1) / sizeof(_Tp);
  }

  template<typename _Up, typename... _Args>
  void construct(_Up* __p, _Args&&... __args)
  {
    ::new((void *)__p) _Up(std::forward<_Args>(__args)...);
  }

  template<typename _Up>
  void destroy(_Up* __p)
  {
    __p->~_Up();
  }

};
































   /*




 template<typename _Tp>
    class new_allocator
    {
    public:
      typedef size_t     size_type;
      typedef ptrdiff_t  difference_type;
      typedef _Tp*       pointer;
      typedef const _Tp* const_pointer;
      typedef _Tp&       reference;
      typedef const _Tp& const_reference;
      typedef _Tp        value_type;
      template<typename _Tp1>
        struct rebind
        { typedef new_allocator<_Tp1> other; };
#if __cplusplus >= 201103L
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 2103. propagate_on_container_move_assignment
      typedef std::true_type propagate_on_container_move_assignment;
#endif
      new_allocator() _GLIBCXX_USE_NOEXCEPT { }
      new_allocator(const new_allocator&) _GLIBCXX_USE_NOEXCEPT { }
      template<typename _Tp1>
        new_allocator(const new_allocator<_Tp1>&) _GLIBCXX_USE_NOEXCEPT { }
      ~new_allocator() _GLIBCXX_USE_NOEXCEPT { }
      pointer
      address(reference __x) const _GLIBCXX_NOEXCEPT
      { return std::__addressof(__x); }
      const_pointer
      address(const_reference __x) const _GLIBCXX_NOEXCEPT
      { return std::__addressof(__x); }
      // NB: __n is permitted to be 0.  The C++ standard says nothing
      // about what the return value is when __n == 0.
      pointer
      allocate(size_type __n, const void* = static_cast<const void*>(0))
      {
        if (__n > this->max_size())
          std::__throw_bad_alloc();
#if __cpp_aligned_new
        if (alignof(_Tp) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
          {
            std::align_val_t __al = std::align_val_t(alignof(_Tp));
            return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp), __al));
          }
#endif
        return static_cast<_Tp*>(::operator new(__n * sizeof(_Tp)));
      }
      // __p is not permitted to be a null pointer.
      void
      deallocate(pointer __p, size_type)
      {
#if __cpp_aligned_new
        if (alignof(_Tp) > __STDCPP_DEFAULT_NEW_ALIGNMENT__)
          {
            ::operator delete(__p, std::align_val_t(alignof(_Tp)));
            return;
          }
#endif
        ::operator delete(__p);
      }
      size_type
      max_size() const _GLIBCXX_USE_NOEXCEPT
      { return size_t(-1) / sizeof(_Tp); }
#if __cplusplus >= 201103L
      template<typename _Up, typename... _Args>
        void
        construct(_Up* __p, _Args&&... __args)
        { ::new((void *)__p) _Up(std::forward<_Args>(__args)...); }
      template<typename _Up>
        void
        destroy(_Up* __p) { __p->~_Up(); }
#else
      // _GLIBCXX_RESOLVE_LIB_DEFECTS
      // 402. wrong new expression in [some_] allocator::construct
      void
      construct(pointer __p, const _Tp& __val)
      { ::new((void *)__p) _Tp(__val); }
      void
      destroy(pointer __p) { __p->~_Tp(); }
#endif
    };

*/

#endif // ALLOCATOR_H
