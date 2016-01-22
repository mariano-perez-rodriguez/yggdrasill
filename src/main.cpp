#include <iostream>

#include "Cloner.h"


int main(int argc, char *argv[]) {
  // dump arguments to cerr
  std::cerr << "Arguments:" << std::endl; for (int i = 0; i < argc; i++) { std::cerr << "  " << i << ": " << argv[i] << std::endl; } std::cerr << std::endl;
}

