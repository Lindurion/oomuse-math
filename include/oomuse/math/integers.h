/**
 * Copyright 2015 Eric W. Barndollar. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * =============================================================================
 * Mathematical operations on integers.
 */

#ifndef OOMUSE_MATH_INTEGERS_H
#define OOMUSE_MATH_INTEGERS_H

#include <type_traits>

namespace oomuse {
namespace integers {
namespace internal {


template<typename T>
constexpr T divFloorOffset(T divisor, T remainder) {
  // Need to correct for C++11 standard of integer division truncation toward 0
  // if the sign of the divisor and (nonzero) remainder are different.
  return (remainder == 0) || ((divisor < 0) == (remainder < 0)) ? 0 : -1;
}


template<typename T>
constexpr T modRangeCorrected(T divisor, T remainder) {
  // Correct for C++11 standard of remainder sign matching dividend sign.
  return ((remainder == 0) || ((divisor < 0) == (remainder < 0)))
      ? remainder
      : remainder + divisor;
}


}  // namespace internal


/** Returns quotient rounded toward negative infinity. */
template<typename T>
constexpr typename std::enable_if<std::is_integral<T>::value, T>::type
    divFloor(T dividend, T divisor) {
  return (dividend / divisor)
      + internal::divFloorOffset(divisor, dividend % divisor);
}


/**
 * Returns dividend % divisor in range [0, divisor - 1] for a positive divisor
 * or in range [divisor + 1, 0] for a negative divisor.
 */
template<typename T>
constexpr typename std::enable_if<std::is_integral<T>::value, T>::type
    modRangeCorrected(T dividend, T divisor) {
  return internal::modRangeCorrected(divisor, dividend % divisor);
}


}  // namespace integers
}  // namespace oomuse

#endif  // OOMUSE_MATH_INTEGERS_H
