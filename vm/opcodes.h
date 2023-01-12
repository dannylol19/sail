#pragma once
#include <cstdint>
#include <array>

// todo: implement jnz, jz, movs, movsi instructions
enum e_opcode : uint32_t {
  mov = 1u,   // move dst register, src register
  movi,       // move register, value
  inc,        // increment value in register
  cmp,        // compare register, register
  cmpi,       // compare register, value
  je,         // jump to [label] if equal
  jne,        // jump to [label] if not equal
  jmp,        // jump to [label]
  out,        // output value of register
  nop,        // no operation
  xor_,       // xor register, register
  xori,       // xor register, value
  add,        // add register, register
  addi,       // add register, value
  sub,        // subtract register, register
  subi,       // subtract register, value
  mul,        // multiply register, register
  muli,       // multiply register, value
  div_,       // divide register, register
  divi,       // divide register, value
  or_,        // or register, register
  ori,        // or register, value
  and_,       // and register, register
  andi,       // and register, value
  mod,        // mod register, register
  modi,       // mod register, value
  not_,       // not register
  jl,         // jump to [label] if less than
  jle,        // jump to [label] if less than or equal to
  jg,         // jump to [label] if greater than
  jge,        // jump to [label] if greater than or equal to
  jz,         // jump to [label] if zero
  jnz,        // jump to [label] if not zero
  movs,       // move register, string
  movsi,      // move register, register (containing string) (not sure about this)
  OPCODES_END
};