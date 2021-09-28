#include "cpp_shared_lib.h"

#include <iostream>

Cpp_shared_lib::Cpp_shared_lib() { std::cout << __PRETTY_FUNCTION__ << "\n"; }

Cpp_shared_lib::~Cpp_shared_lib() { std::cout << __PRETTY_FUNCTION__ << "\n"; }
