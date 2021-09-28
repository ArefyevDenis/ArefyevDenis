#ifndef CPP_SHARED_LIB_H
#define CPP_SHARED_LIB_H

class Cpp_shared_lib
{
public:
  Cpp_shared_lib();

  Cpp_shared_lib(const Cpp_shared_lib&) = delete;
  Cpp_shared_lib& operator = (const Cpp_shared_lib&) = delete;

  Cpp_shared_lib(Cpp_shared_lib&&) = delete;
  Cpp_shared_lib& operator = (Cpp_shared_lib&&) = delete;

  ~Cpp_shared_lib();

  bool init();

  void start();

  void stop();

};

#endif // CPP_SHARED_LIB_H
