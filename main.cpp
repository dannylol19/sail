#include <cstdio>
#include <vector>
#include <cstdint>
#include "vm.h"

int main() {
  std::vector<int32_t> program = {2, 255, 69, 5, 255, 69, 7, INT32_MAX-10, 9, 255, 2, 255, 420, 9, 255};

  vm test_vm(program);
  test_vm.run();

  return 0;
}