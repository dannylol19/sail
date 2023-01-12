#include <cstdio>
#include <vector>
#include <cstdint>
#include "vm.h"

int main() {
  /*
  ; test program: outputs 1 to 10 on seperate lines

  movi rax, 1

  for_loop:
    out rax
    inc rax
    cmpi rax, 10
    jle for_loop
  */
  //                               0     1   2   3    4    5    6    7     8   9   10   11 (goto3)
  std::vector<int32_t> program = {movi, rax, 1, out, rax, inc, rax, cmpi, rax, 10, jle, INT_MAX-3};

  sail::vm test_vm(program);
  test_vm.run();

  return 0;
}