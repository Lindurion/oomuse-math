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
 */

#include "oomuse/math/Constants.h"

#include "gtest/gtest.h"

using oomuse::Constants;

namespace {


TEST(Constants, withFloat) {
  EXPECT_NEAR(2.71828, Constants<float>::E, 0.00001F);
  EXPECT_NEAR(3.14159, Constants<float>::PI, 0.00001F);
}


TEST(Constants, withDouble) {
  EXPECT_NEAR(2.718281828459045, Constants<double>::E, 0.000000000000001);
  EXPECT_NEAR(3.141592653589793, Constants<double>::PI, 0.000000000000001);
}


TEST(Constants, withLongDouble) {
  EXPECT_NEAR(2.718281828459045L, Constants<long double>::E,
              0.000000000000001L);
  EXPECT_NEAR(3.141592653589793L, Constants<long double>::PI,
              0.000000000000001L);
}


}  // namespace
