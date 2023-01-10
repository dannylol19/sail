#include "vm.h"
#include <cstring>

namespace sail {
  vm::vm(std::vector<int32_t> program) : program(std::move(program)) {}

  void vm::run() {
    while (pc < program.size()) {
      auto at = program.at(pc);
      if (at > 0 && at < OPCODES_END) {
        decode_opcode(at);
        ++pc;
        continue;
      }
      panic("invalid opcode", at);
    }
  }

  // returns index of next register
  int32_t vm::next_reg() {
    const int32_t reg = program.at(pc++);
    if (reg < a0 || reg > REGISTERS_END-1) {
      panic("invalid register", reg);
    }
    return reg-255;
  }

  // returns next value
  int32_t vm::next_val() {
    return program.at(pc++);
  }

  // returns index of next label
  int32_t vm::next_lbl() {
    return INT32_MAX-program.at(pc++);
  }

  pair_int32 vm::next_reg_reg() {
    return {next_reg(), next_reg()};
  }

  pair_int32 vm::next_reg_val() {
    return {next_reg(), next_val()};
  }

  void vm::set_cmp_flags(int32_t x, int32_t y) {
    flags[eq] = (x == y);
    flags[lt] = (x < y);
    flags[gt] = (x > y);
  }

  void vm::decode_opcode(int32_t oc) {
    switch (oc) {
      case nop:
        return;
      case mov: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] = registers.at(src);
        return;
      }
      case movi: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] = val;
        return;
      }
      case inc: {
        // operands: register
        auto dst = next_reg();
        ++registers[dst];
        return;
      }
      case cmp: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        set_cmp_flags(registers.at(dst), registers.at(src));
        return;
      }
      case cmpi: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        set_cmp_flags(registers.at(dst), val);
        return;
      }
      case je: {
        // operands: label
        auto lbl = next_lbl();
        if (flags.at(eq)) {
          pc = lbl-1;
        }
        return;
      }
      case jne: {
        // operands: label
        auto lbl = next_lbl();
        if (!flags.at(eq)) {
          pc = lbl-1;
        }
        return;
      }
      case jmp: {
        // operands: label
        // 1 is subtracted from jmps because right after we parse the opcode the pc is incremented.
        pc = next_lbl()-1; // todo: check if you have an edge case when pc=0 on jumping instructions
        return;
      }
      case out: {
        // operands: register
        auto reg = next_reg();
        printf("%i\n", registers.at(reg));
        return;
      }
      case xor_: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] ^= registers.at(src);
        return;
      }
      case xori: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] ^= val;
        return;
      }
      case add: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] += registers.at(src);
        return;
      }
      case addi: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] += val;
        return;
      }
      case sub: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] -= registers.at(src);
        return;
      }
      case subi: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] -= val;
        return;
      }
      case mul: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] *= registers.at(src);
        return;
      }
      case muli: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] *= val;
        return;
      }
      case div_: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] /= registers.at(src);
        return;
      }
      case divi: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] /= val;
        return;
      }
      case or_: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] |= src;
      }
      case ori: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] |= val;
      }
      case and_: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] &= src;
      }
      case andi: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] &= val;
      }
      case mod: {
        // operands: register, register
        auto [dst, src] = next_reg_reg();
        registers[dst] %= src;
      }
      case modi: {
        // operands: register, value
        auto [dst, val] = next_reg_val();
        registers[dst] %= val;
      }
      case not_: {
        // operands: register
        auto reg = next_reg();
        registers[reg] = ~registers.at(reg);
      }
      case jl: {
        // operands: label
        auto lbl = next_lbl();
        if (flags.at(lt)) {
          pc = lbl-1;
        }
      }
      case jle: {
        // operands: label
        auto lbl = next_lbl();
        if (flags.at(lt) || flags.at(eq)) {
          pc = lbl-1;
        }
      }
      case jg: {
        // operands: label
        auto lbl = next_lbl();
        if (flags.at(gt)) {
          pc = lbl-1;
        }
      }
      case jge: {
        // operands: label
        auto lbl = next_lbl();
        if (flags.at(gt) || flags.at(eq)) {
          pc = lbl-1;
        }
      }
      default: // this should never happen
        panic("invalid opcode", oc);
        return;
    }
  }

  void vm::panic(const char* msg, int32_t x = 0) const {
    fprintf(stderr, "%s! found: %i, pc: %zu", msg, x, pc);
    exit(-1);
  }
}