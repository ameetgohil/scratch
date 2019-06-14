#include <iostream>

union WideSignal {
  uint64_t *sig64;
  uint32_t *sig32;
};



int main() {
  std::cout << "Hello World" << std::endl;

  union WideSignal sig;

  uint64_t data = 0x1234567887654231;
  std::cout << std::hex << data << std::endl;
  
  sig.sig64 = &data;
  std::cout << std::hex << sig.sig64[0] << std::endl;
  std::cout << std::hex << sig.sig32[0] << std::endl;
  std::cout << std::hex << sig.sig32[1] << std::endl;

  return 0;
}
    
