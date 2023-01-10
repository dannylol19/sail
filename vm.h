#pragma once
#include <cstdio>
#include <vector>
#include <array>
#include <cstdint>

#include "opcodes.h"
#include "flags.h"
#include "registers.h"

/*!
@REGISTERS
Registers start at 255 and end at e_registers::REGISTERS_END - 1.

@FLAGS
Flags are in the array of bool "flags". The cmp and cmpi instructions modify these flags todo: REVIEW THIS! IT MAY CHANGE
You can index this array with the flag enum, which contains the indexes of specific flags.
For example: the equality flag is at index e_flag::eq of the flags array.

@LABELS
Labels start from INT32_MAX and subtract 1 for every new label.
Values 512 and below are reserved for the VM. Label declaration should be a problem
for the assembler to solve, not the VM.
*/

namespace sail {
  struct pair_int32 {
    int32_t x;
    int32_t y;
  };

  struct vm {
    size_t pc = 0u;
    std::array<int32_t, REGISTERS_END-255> registers {};
    std::array<bool, FLAGS_END> flags = {false, false, false};

    std::vector<int32_t> program;
    explicit vm(std::vector<int32_t> program);

    void run();
    void panic(const char* msg, int32_t x) const;

    void decode_opcode(int32_t oc);
    int32_t next_reg();
    int32_t next_val();
    int32_t next_lbl();
    pair_int32 next_reg_reg();
    pair_int32 next_reg_val();

  private:
    void set_cmp_flags(int32_t x, int32_t y);
  };
}