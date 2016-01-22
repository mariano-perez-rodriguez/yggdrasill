#include <iostream>

#include "Cloner.h"
#include "BitGenerator.h"
#include "Hasher.h"
#include "Icg.h"
#include "Lfsr.h"
#include "Xsg.h"


int main(int argc, char *argv[]) {
  // dump arguments to cerr
  std::cerr << "Arguments:" << std::endl; for (int i = 0; i < argc; i++) { std::cerr << "  " << i << ": " << argv[i] << std::endl; } std::cerr << std::endl;


  // example XSG using typical parameters
  Xsg512 gen1 = distillXsg("lakakona");
  Xsg512 gen2 = *gen1.clone(), gen3 = gen1;

  std::string s0 = "The quick brown fox";
  std::string s1 = s0 + " jumps over the lazy dog";
  std::string s2 = s0 + " jumps over the lazy doq";
  std::string s3 = " jumps over the lazy dog";

  // output example hashes
  std::cout << s1 << ": " << gen1.hash(s1, 128) << std::endl
            << s2 << ": " << gen2.hash(s2, 128) << std::endl;

  std::cout << std::endl;

  gen3.hashAdd(s0); std::cout << s0 << ": " << gen3.hashPartial(128) << std::endl;
  gen3.hashAdd(s3); std::cout << s3 << ": " << gen3.hashFinal(128)   << std::endl;

  return 0;

  // generate infinite stream
  while (true) {
    unsigned char c = 0;
    for (std::size_t j = 0; j < 8; j++) {
      c = static_cast<unsigned char>(c << 1);
      c = static_cast<unsigned char>(c | gen1.next());
    }
    std::cout << c;
  }


  return 0;}

