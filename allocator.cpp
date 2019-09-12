#include "allocator.h"

#include <iostream>
#include <malloc.h>
#include <new>

#include<vector>
#include<map>

namespace  {
  static int counter{0};
  //static std::vector<void*>          v_mem_alloc; рекурсия
  //static std::map<void*,std::size_t> m_ptr_size;  рекурсия
}


//=================================================================================================================================//
void* operator new  ( std::size_t sz ){
  return Allocator::instance().allocate(sz);
}

void* operator new[]( std::size_t sz ){
  return ::operator new(sz);
}
//=================================================================================================================================//
void* operator new  ( std::size_t sz, std::align_val_t al){
  counter++;
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  void *p;
  std::size_t align = (std::size_t)al;

  if (sz == 0)
    sz = 1;
#if _GLIBCXX_HAVE_ALIGNED_ALLOC
  if (std::size_t rem = sz & (align - 1))
    sz += align - rem;
#endif
  while (__builtin_expect ((p = aligned_alloc (align, sz)) == nullptr, false)) {
      std::new_handler handler = std::get_new_handler ();
      if (! handler)
        _GLIBCXX_THROW_OR_ABORT(std::bad_alloc());
      handler ();
    }
  return p;
}//  	(since C++17)

void* operator new[]( std::size_t sz, std::align_val_t al){  return ::operator new(sz, al); }//  	(since C++17)

//=================================================================================================================================//
void* operator new  ( std::size_t sz, const std::nothrow_t& )noexcept{
  counter++;
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  void *p;
  if (sz == 0)
    sz = 1;
  while (__builtin_expect ((p = malloc (sz)) == nullptr, false))  {
      std::new_handler handler = std::get_new_handler ();
      if (! handler)
        return nullptr;
      try {
        handler ();
      } catch(const std::bad_alloc&)    {
        return nullptr;
      }
    }
  return p;
}
void* operator new[]( std::size_t sz, const std::nothrow_t& tag)noexcept{return ::operator new(sz, tag); }

//=================================================================================================================================//
void* operator new  ( std::size_t sz, std::align_val_t al, const std::nothrow_t&)noexcept{
  try{
    return operator new(sz, al);
  }catch(...) {
    return nullptr;
  }
} // 	(since C++17)
void* operator new[]( std::size_t sz, std::align_val_t al, const std::nothrow_t&)noexcept{
  try{
    return operator new [] (sz, al);
  }catch(...) {
    return nullptr;
  }
} //       ((since C++17))

//=================================================================================================================================//
void operator delete  (void* ptr ) noexcept {
  Allocator::instance().deallocate(ptr,0);
}

void operator delete[] (void* ptr ) noexcept {  ::operator delete (ptr); }
//=================================================================================================================================//

void operator delete  ( void* ptr, std::align_val_t )noexcept{
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter--);
#if _GLIBCXX_HAVE_ALIGNED_ALLOC || _GLIBCXX_HAVE_POSIX_MEMALIGN  || _GLIBCXX_HAVE_MEMALIGN
  std::free (ptr);
#elif _GLIBCXX_HAVE__ALIGNED_ALLOC
  _aligned_free (ptr);
#else
  if (ptr)
    std::free (((void **) ptr)[-1]); // See aligned_alloc in new_opa.cc
#endif
}//  	(since C++17)

void operator delete[]( void* ptr, std::align_val_t al)noexcept{ ::operator delete (ptr, al);  }//  	(since C++17)

//=================================================================================================================================//

void operator delete  ( void* ptr, const std::nothrow_t& )noexcept{
  counter--;
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  std::free(ptr);
}

void operator delete[]( void* ptr, const std::nothrow_t& )noexcept{  ::operator delete (ptr);  }

//=================================================================================================================================//

void operator delete  ( void* ptr, std::align_val_t al, const std::nothrow_t&)noexcept{  ::operator delete (ptr, al); } // 	(since C++17)

void operator delete[]( void* ptr, std::align_val_t al, const std::nothrow_t&)noexcept{  ::operator delete[] (ptr, al);  } //       ((since C++17))

//=================================================================================================================================//

void operator delete(void* ptr, std::size_t, std::align_val_t al) noexcept { ::operator delete (ptr, al); }

void operator delete[](void *ptr, std::size_t, std::align_val_t al) noexcept { ::operator delete[] (ptr, al); }

//=================================================================================================================================//

void operator delete(void* ptr, std::size_t) noexcept { ::operator delete (ptr); }

void operator delete[](void *ptr, std::size_t) noexcept { ::operator delete[] (ptr); }

//=================================================================================================================================//


Allocator& Allocator::instance(){
  // std::printf(" %s\n", __PRETTY_FUNCTION__);
   static Allocator example;
   return example;
 }

Allocator::Allocator() :                                /// конструктор один раз выделяет много памяти
  base_pointer(std::malloc(1000000))
{
   std::printf(" %s\n", __PRETTY_FUNCTION__);
}

Allocator::~Allocator(){

//  for (auto kvp: m_ptr_size) {
//      std::cout << " PTR: " << kvp.first << " \tSZ: " << kvp.second << "\n";
//    }
   std::printf(" %s %d \n", __PRETTY_FUNCTION__,counter);
}

std::size_t Allocator::max_size(std::size_t __n) const
{
  return std::size_t(-1) / sizeof(__n);
}

void*  Allocator::allocate(std::size_t sz, void * ) /// запрос на размещение объекта в памяти
{
  counter++;
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  void *p;
  if (sz == 0)
    sz = 1;
  while (__builtin_expect ((p = malloc (sz)) == nullptr, false)){
      std::new_handler handler = std::get_new_handler ();
      if (! handler)
        _GLIBCXX_THROW_OR_ABORT(std::bad_alloc());
      handler ();
    }
 // v_mem_alloc.push_back(p);
  //m_ptr_size[p] = sz;
  return p;
}

void   Allocator::deallocate(void *ptr, std::size_t )
{
  counter--;
  //v_mem_alloc.pop_back();
  //m_ptr_size.erase(ptr);
  std::free(ptr);
}
















































/*

//=================================================================================================================================//
void* operator new  ( std::size_t sz ){
  counter++;
  //std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  void *p;
  if (sz == 0)
    sz = 1;
  while (__builtin_expect ((p = malloc (sz)) == nullptr, false)){
      std::new_handler handler = std::get_new_handler ();
      if (! handler)
        _GLIBCXX_THROW_OR_ABORT(std::bad_alloc());
      handler ();
    }
  return p;
}

void* operator new[]( std::size_t sz ){
  return ::operator new(sz);
}
//=================================================================================================================================//
void* operator new  ( std::size_t sz, std::align_val_t al){
  counter++;
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  void *p;
  std::size_t align = (std::size_t)al;

  if (sz == 0)
    sz = 1;
#if _GLIBCXX_HAVE_ALIGNED_ALLOC
  if (std::size_t rem = sz & (align - 1))
    sz += align - rem;
#endif
  while (__builtin_expect ((p = aligned_alloc (align, sz)) == 0, false)) {
      std::new_handler handler = std::get_new_handler ();
      if (! handler)
        _GLIBCXX_THROW_OR_ABORT(std::bad_alloc());
      handler ();
    }
  return p;
}//  	(since C++17)

void* operator new[]( std::size_t sz, std::align_val_t al){  return ::operator new(sz, al); }//  	(since C++17)

//=================================================================================================================================//
void* operator new  ( std::size_t sz, const std::nothrow_t& tag)noexcept{
  counter++;
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  void *p;
  if (sz == 0)
    sz = 1;
  while (__builtin_expect ((p = malloc (sz)) == nullptr, false))  {
      std::new_handler handler = std::get_new_handler ();
      if (! handler)
        return 0;
      try {
        handler ();
      } catch(const std::bad_alloc&)    {
        return nullptr;
      }
    }
  return p;
}
void* operator new[]( std::size_t sz, const std::nothrow_t& tag){return ::operator new(sz, tag); }

//=================================================================================================================================//
void* operator new  ( std::size_t sz, std::align_val_t al, const std::nothrow_t&){
  try{
    return operator new(sz, al);
  }catch(...) {
    return nullptr;
  }
} // 	(since C++17)
void* operator new[]( std::size_t sz, std::align_val_t al, const std::nothrow_t&){
  try{
    return operator new [] (sz, al);
  }catch(...) {
    return nullptr;
  }
} //       ((since C++17))

//=================================================================================================================================//
void operator delete  (void* ptr ) noexcept {
  counter--;
  //std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  std::free(ptr);
}

void operator delete[] (void* ptr ) noexcept {  ::operator delete (ptr); }
//=================================================================================================================================//

void operator delete  ( void* ptr, std::align_val_t al)noexcept{
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter--);
#if _GLIBCXX_HAVE_ALIGNED_ALLOC || _GLIBCXX_HAVE_POSIX_MEMALIGN  || _GLIBCXX_HAVE_MEMALIGN
  std::free (ptr);
#elif _GLIBCXX_HAVE__ALIGNED_ALLOC
  _aligned_free (ptr);
#else
  if (ptr)
    std::free (((void **) ptr)[-1]); // See aligned_alloc in new_opa.cc
#endif
}//  	(since C++17)

void operator delete[]( void* ptr, std::align_val_t al)noexcept{ ::operator delete (ptr, al);  }//  	(since C++17)

//=================================================================================================================================//

void operator delete  ( void* ptr, const std::nothrow_t& tag)noexcept{
  counter--;
  std::printf(" %s %d \n", __PRETTY_FUNCTION__ ,counter);
  std::free(ptr);
}

void operator delete[]( void* ptr, const std::nothrow_t& tag)noexcept{  ::operator delete (ptr);  }

//=================================================================================================================================//

void operator delete  ( void* ptr, std::align_val_t al, const std::nothrow_t&)noexcept{  ::operator delete (ptr, al); } // 	(since C++17)

void operator delete[]( void* ptr, std::align_val_t al, const std::nothrow_t&)noexcept{  ::operator delete[] (ptr, al);  } //       ((since C++17))

//=================================================================================================================================//

void operator delete(void* ptr, std::size_t, std::align_val_t al) noexcept { ::operator delete (ptr, al); }

void operator delete[](void *ptr, std::size_t, std::align_val_t al) noexcept { ::operator delete[] (ptr, al); }

//=================================================================================================================================//

void operator delete(void* ptr, std::size_t) noexcept { ::operator delete (ptr); }

void operator delete[](void *ptr, std::size_t) noexcept { ::operator delete[] (ptr); }

//=================================================================================================================================//


*/
