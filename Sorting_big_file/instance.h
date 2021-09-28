#ifndef INSTANCE_H
#define INSTANCE_H

#include <initializer_list>
#include <vector>

#include <dbg.h>

namespace INST {
  // задача этого шаблона создать экземпляр объекта до
  // выпонения main(...)
  template<typename TT>
  class Pattern{
  public:

    Pattern(const TT* ptr):
      tt(ptr)
    {   who()   }

    Pattern(std::initializer_list<const TT*> il):
    v_tt(il)
    {   who()   }

    ~Pattern()
    {   who()   }

  private:

    Pattern( )                          = delete;
    Pattern(const Pattern&)             = delete;
    Pattern(Pattern&&)                  = delete;
    Pattern& operator =(const Pattern&) = delete;
    Pattern& operator = (Pattern&&)     = delete;

  protected:

    const TT*               tt;
    std::vector<const TT*>  v_tt;

  };


  //  class Instncer{
  //  public:
  //    Instncer():
  //    pf(&r_prof())
  //    {   who()   }
  //    ~Instncer()
  //    {  who()    }
  //    Profiling *pf{nullptr};
  //  };

}

#endif // INSTANCE_H
