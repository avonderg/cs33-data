#if 0
INTEGER CODING RULES:

	Complete the body of each function with one
	or more lines of C code that implements the function. Your code
	must consist of a sequence of variable declarations, followed by
	a sequence of assignment statements, followed by a return statement.

	The general style is as follows:

	int funct(...) {
		/* brief description of how your implementation works */
		int var1 = expr1;
		...
		int varM = exprM;

		varJ = exprJ;
		...
		varN = exprN;

		return exprR;
	}

	Each "expr" is an expression using ONLY the following:
	1. Integer constants 0 through 255 (0xFF), inclusive. You are
	   not allowed to use big constants such as 0xFFFFFFFF.
	2. Function arguments and local variables (no global variables).
	3. Unary integer operations ! ~
	4. Binary integer operations & ^ | + << >>

	Some of the problems restrict the set of allowed operators even further.
	Each "expr" may consist of multiple operators. You are not restricted to
	one operator per line.

	You are expressly forbidden to:
	1. Use any control constructs such as if, do, while, for, switch, etc.
	2. Define or use any macros.
	3. Define any additional functions in this file.
	4. Call any functions.
	5. Use any other operations, such as &&, ||, -, or ?:
	6. Use any form of casting.
	7. Use any data type other than int.  This implies that you
	   cannot use arrays, structs, or unions.


	You may assume that your machine:
	1. Uses 2s complement, 32-bit representations of integers.
	2. Performs right shifts arithmetically.
	3. Has unpredictable behavior when shifting an integer by more
	   than the word size.

EXAMPLES OF ACCEPTABLE CODING STYLE:
	/*
	 * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
	 */
	int pow2plus1(int x) {
		/* exploit ability of shifts to compute powers of 2 */
		return (1 << x) + 1;
	}

	/*
	 * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
	 */
	int pow2plus4(int x) {
		/* exploit ability of shifts to compute powers of 2 */
		int result = (1 << x);
		result += 4;
		return result;
	}
#endif
/* Copyright (C) 1991-2016 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 9.0.0.  Version 9.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2014, fourth edition, plus
   Amd. 1  and Amd. 2 and 273 characters from forthcoming  10646, fifth edition.
   (Amd. 2 was published 2016-05-01,
   see https://www.iso.org/obp/ui/#iso:std:iso-iec:10646:ed-4:v1:amd:2:v1:en) */
/* We do not support C11 <threads.h>.  */


/*
 * bit_and - Compute x&y using only ~ and |
 *   Examples: bit_and(6, 5) = 4
 *             bit_and(3, 12) = 0
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bit_and(int x, int y) { 
	/* flips every binary value in both inputs, uses bitwise OR to compare both flipped values,
	and returns the flipped version of that result */
	int z; // store result of bitwise OR here
	int result; // store result here
	z = (~x | ~y); // flips both x and y and compares both using bitwise OR
	result = ~z; // flips that result
	return result; 
}


/*
 * negate - Return -x
 *   Examples: negate(1) = -1
 *             negate(0) = 0
 *             negate(-33) = 33
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { 
	/* given input x, flips the bits of x, and since the flipped version of x
	is the negation (x+1), 1 is added to that negation  */
	int y; // stores flipped value of x
	int result; // stores result
	y = ~x; // flips x
	result = 1 + y; // adds one to flipped value, since flipped value is a negation of (x+1)
	return result;
}


/*
 * is_equal - Return 1 if x == y, else return 0
 *   Examples: is_equal(5, 5) = 1
 *             is_equal(4, 5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int is_equal(int x, int y) {
	/* After applying bitwise XOR to both x and y, 0 is returned if both are the same,
	and another value otherwise. applying the logical NOT returns 1 if XOR gives a value other than 1.
	applying the logical NOT one more time to this result converts 0 to 1, and 1 to 0, so that the correct
	value is returned.
	*/
	int z;
	z = (x^y); // XORs both x and y
	return !z; // z is 1 if x^y is 0 (i.e., the same), and 0 otherwise
 }


/*
 * div_pwr_2 - Compute x/(2^n), for 0 <= n <= 30
 *   Round toward zero
 *   Examples: div_pwr_2(15, 1) = 7
 *             div_pwr_2(-33, 4) = -2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int div_pwr_2(int x, int n) { 
/* Uses a bit mask to check if the input is value (mask = -1 if negative, 0 otherwise), and, 
using the mask, computes a power-of-two divide, adding (1 >>n) - 1 only if the input
is negative by using logical AND with the mask and (1 >>n) - 1. Then, an arithmetic shift to the right
by n gives the final result.*/
int mask;
int mask_checked;
mask = (x>>31); // gets the leftmost bits: 1111 if negative, 0000 if positive
mask_checked = (1 << n) + (~1 + 1); // computes rest of power-of-two formula 
return (x + (mask_checked&mask) >> n); // mask_checked is only added if the mask is 1111
}


/*
 * leastBitPos - Return a mask that marks the position of the
 *   least significant 1 bit. If x == 0, return 0
 *   Example: leastBitPos(96) = 0x20
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 4
 */
int leastBitPos(int x) {
/* Finds the position of the least significant bit by negating the input, and then 
AND'ing it to the input-- setting only one bit (the least significant one) */
int negative;
int mask;
negative = ~x + 1; // gets the negated value of x
mask = negative&x; // returns the negated value of x AND'ed to x
return mask;
}


/*
 * conditional - Compute the result of x ? y : z
 *   Examples: conditional(2, 4, 5) = 4
 *             conditional(0, 1, 2) = 2
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) { 
/* Using bit masks, returns z if the first arg is zero, and y otherwise. */
int mask_start;
int add_holder;
int fixed_mask;
int negated_mask;
int result;
mask_start = !(x); // returns 1 if it x is zero, and 0 otherwise
add_holder = (~1 + 1); // placeholder for addition- is value of (-1)
fixed_mask = mask_start + add_holder; // if mask_start is 1, then fixed = 0; if mask_start is 0, then fixed = -1
negated_mask = ~(fixed_mask); // negates fixed_mask so that only the correct variable is returned
result = fixed_mask&y; // if x is zero, result is zero, otherwise gives the value of y
return result + (negated_mask&z); // if x is zero, then returns the value of z. otherwise, returns y
}



/*
 * add_ok - Return 0 if x+y will overflow, 1 otherwise
 *   Examples: add_ok(0x80000000, 0x80000000) = 0
 *             add_ok(0x80000000, 0x70000000) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int add_ok(int x, int y) { return 2; }


/*
 * abs_val - Return the absolute value of x
 *   Examples: abs_val(-1) = 1
 *             abs_val(33) = 33
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 5
 */
int abs_val(int x) { 
	/* Using two's complement values of bits, a mask of the input is created by computing a 
	right shift of 31 bits- which gives 1111 if x is negative, and 0000 if x is positive.
	Then, the mask is added to the input, and this value is XOR'ed to the mask. So, if it is
	positive, zero is added to the input, and XOR'ing this to the mask gives the input. If it is 
	odd, adding the mask to the input decreases the input by 1, but XOR'ing this decreased val
	to the mask gives the input, but positive. */
	int mask;
	int added;
	int result;
	mask = x >> 31; // extracts mask (i.e., whether or not input is positive or negative)
	added = mask + x; // adds mask to input
	result = added^mask; // XORs this added value to the mask
	return result;
}


/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 5
 */
int bang(int x) { return 2; }
