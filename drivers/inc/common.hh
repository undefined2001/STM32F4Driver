#ifndef __COMMON_HH__
#define __COMMON_HH__

#define SCAST_UINT(val) (static_cast<uint32_t>(val))
#define CLEAR_BITS(reg, mask) ((reg) &= ~(mask))
#define SET_BITS(reg, mask, value) ((reg) |= ((value) & (mask)))

#endif