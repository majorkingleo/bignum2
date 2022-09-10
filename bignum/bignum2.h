/*
 * bignum2.h
 *
 *  Created on: 31.08.2022
 *      Author: martin
 */

#ifndef SRC_BIGNUM2_H_
#define SRC_BIGNUM2_H_

#include "vchar.h"

namespace BigNum2 {

/**
 * value_a: A
 * value_b: B
 * value_return: result
 * flag: +, or -
 * returns: value_return
 */
pchar addsub( pchar value_a, pchar value_b, pchar value_return, char flag);

/**
 * parameter : ay * by ... result cy
 *             returns pointer to cy
 */
pchar mult( pchar ay, pchar by, pchar cy);


//===============================================================
//
//                       function div
//  slow version of div
//
//===============================================================
// parameter : ay / by ... result cy , mod dy
//             returns pointer to cy
//             ay = cy * by + dy
// attention : ay and by is modified, must be stored
//===============================================================
//  attention : ouput of sign not finished, add from divf
//===============================================================
pchar div( pchar ay, pchar by, pchar cy, pchar dy);

} // namespace BigNum2

#endif /* SRC_BIGNUM2_H_ */
