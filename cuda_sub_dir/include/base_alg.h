#ifndef BASE_ALG_H
#define BASE_ALG_H

class Base_alg{
public:
  Base_alg()                                = default;
  Base_alg(const Base_alg&)                 = default;
  Base_alg(Base_alg&& )                     = default;
  Base_alg& operator = (const Base_alg& )   = default;
  Base_alg& operator = (Base_alg&& )        = default;
  virtual ~Base_alg()                       = default;

  virtual void apply(void *) = 0; ///применять, использовать

};

#endif // BASE_ALG_H
