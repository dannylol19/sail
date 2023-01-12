#pragma once
#include <cstdint>

enum e_register : uint32_t {
  /*! x registers */
  rax = 255, rbx, rcx, rdx, rex, rfx, rgx, rhx, rix, rjx, rkx, rlx, rmx, rnx, rox, rpx, rqx, rrx, rsx, rtx, rux, rvx, rwx, rxx, ryx, rzx,

  /* if we need more registers
  // y registers: \\
  ray, rby, rcy, rdy, rey, rfy, rgy, rhy, riy, rjy, rky, rly, rmy, rny, roy, rpy, rqy, rry, rsy, rty, ruy, rvy, rwy, rxy, ryy, rzy,

  // z registers: \\
  raz, rbz, rcz, rdz, rez, rfz, rgz, rhz, riz, rjz, rkz, rlz, rmz, rnz, roz, rpz, rqz, rrz, rsz, rtz, ruz, rvz, rwz, rxz, ryz, rzz,
  */

  REGISTERS_END
};