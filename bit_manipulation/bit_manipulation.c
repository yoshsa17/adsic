// ref: https://www.youtube.com/watch?v=7jkIUgLC29I

// & AND:  Only true if both input are true
//
// x = 193;        /* 1100 0001 */
// y = x & 0xf0;   /* 1111 0000 */
// y == 192;       /* 1100 0000 */

// | OR:  True if any input is true
//
// x = 193;        /* 1100 0001 */
// y = x | 0xf0;   /* 1111 0000 */
// x == 241;       /* 1111 0001 */

// ^ Exclusive OR:  True if only one input bit is true
//
// x = 193;        /* 1100 0001 */
// y = x | 0xf0;   /* 1111 0000 */
// x == 62;        /* 0011 0001 */

// << Left Shift:  Each shift is a multiply by 2
//
// x = 193;        /* 1100 0001 */
// y = x << 2;
// x == 4;         /* 0000 0100 */

// >> Right Shift:  Each shift is a divided by 2 with round towards negative
// infinity
//
// x = 193;        /* 1100 0001 */
// y = x >> 2;
// x == 48;        /* 0011 0000 */

// ~ NOT:  One's Complement
//         Flip the input bit
//
// x = 193;        /* 1100 0001 */
// y = ~x;         /* 0011 1110 */
// x == 62;        /* 0011 1110 */

#include <stdio.h>

// Functions

int set_bit(int x, int position) {
  // e.g.)
  // x        = 0000 0110
  // position = 0000 0101
  // mask     = 0010 0000
  return x |= 1UL << position;
}

int clear_bit(int x, int position) { return x &= ~(1UL << position); }

int flip_bit(unsigned int x, int position) { return x ^= 1UL << position; }

int check_bit(unsigned int x, int position) { return (x >> position) & 1U; }

int modify_bit(unsigned int x, int position, int state) {
  unsigned int mask = 1UL << position;
  return (x & ~mask) | (-state & mask);
}

// main

int main(int argc, char **argv) {
  // set 3rd bit  0000 => 0100(4)
  int a = 0;
  printf("%d\n", set_bit(a, 2));

  // clear 2rd bit 0110 => 0100(4)
  int b = 6;
  printf("%d\n", clear_bit(b, 1));

  // flip 3rd bit 0111 => 0011(3)
  int c = 7;
  printf("%d\n", flip_bit(c, 2));

  // check 1st bit 0111 => 1
  int d = 7;
  printf("%d\n", check_bit(d, 0));

  // modify 1st bit 0110 => 0111(7);
  int e = 6;
  printf("%d\n", modify_bit(e, 0, 1));

  // TODO::count bits

  return 0;
}
