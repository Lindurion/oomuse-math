/**
 * Copyright 2016 Eric W. Barndollar. All rights reserved.
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
 */

#ifndef OOMUSE_MATH_CONSTANTS_H
#define OOMUSE_MATH_CONSTANTS_H

namespace oomuse {


/** Holds mathematical constants. */
template<typename T>
struct Constants {
  /** The exponential constant. */
  static const T E;

  /** The mathematical ratio pi. */
  static const T PI;
};


template<typename T>
const T Constants<T>::E = static_cast<T>(2.71828182845904523536028747L);


template<typename T>
const T Constants<T>::PI = static_cast<T>(3.1415926535897932384626433L);


}  // namespace oomuse

#endif  // OOMUSE_MATH_CONSTANTS_H
