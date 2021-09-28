#include "non_copyable.h"

#include <iostream>

Non_copyable::Non_copyable(){ std::cout << __PRETTY_FUNCTION__ << "\n";}

Non_copyable::~Non_copyable(){ std::cout << __PRETTY_FUNCTION__ << "\n";}
