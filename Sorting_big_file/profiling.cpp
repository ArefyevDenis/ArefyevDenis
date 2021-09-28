#include "profiling.h"

#include <instance.h>

//#define r_prof() Profiling::instance()

//namespace {
//  static int                      count{0};
//  static INST::Pattern<Profiling> inst_{&r_prof()};

//}

//Profiling::Profiling(QObject *parent) : QObject(parent)
//{
//  LOG(++count);
//}

//Profiling::~Profiling()
//{
//  LOG(--count);
//}

//Profiling& Profiling::instance()
//{
//  static Profiling pf;
//  return pf;
//}
