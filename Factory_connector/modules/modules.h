#ifndef MODULES_H
#define MODULES_H

#include <base_factory.h>

class Mod_a :
    public Base_factory
{
public:
  Mod_a();
  ~Mod_a();
  void b_apply(void *);
  void b_start(void *) override ;
  void b_stop(void *) override {}
  const char* b_type_name() override ;
};

class Mod_b :
    public Base_factory
{
public:
  Mod_b();
  ~Mod_b();
  void b_apply(void *);
  void b_start(void *) override ;
  void b_stop(void *) override {}
  const char* b_type_name() override ;
};

class Mod_c :
    public Base_factory
{
public:
  Mod_c();
  ~Mod_c();
  void b_apply(void *);
  void b_start(void *) override ;
  void b_stop(void *) override {}
  const char* b_type_name() override ;
};

#endif // MODULES_H
