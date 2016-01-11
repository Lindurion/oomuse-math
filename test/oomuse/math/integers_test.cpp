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

#include "oomuse/math/integers.h"

#include "gtest/gtest.h"

using oomuse::integers::divFloor;
using oomuse::integers::modRangeCorrected;

namespace {


TEST(integers, divFloor_positiveDivisor) {
  EXPECT_EQ(-3, divFloor(-25, 12));
  EXPECT_EQ(-2, divFloor(-24, 12));
  EXPECT_EQ(-2, divFloor(-23, 12));
  EXPECT_EQ(-2, divFloor(-13, 12));
  EXPECT_EQ(-1, divFloor(-12, 12));
  EXPECT_EQ(-1, divFloor(-11, 12));
  EXPECT_EQ(-1, divFloor(-1, 12));
  EXPECT_EQ(0, divFloor(0, 12));
  EXPECT_EQ(0, divFloor(1, 12));
  EXPECT_EQ(0, divFloor(11, 12));
  EXPECT_EQ(1, divFloor(12, 12));
  EXPECT_EQ(1, divFloor(13, 12));
  EXPECT_EQ(1, divFloor(23, 12));
  EXPECT_EQ(2, divFloor(24, 12));
  EXPECT_EQ(2, divFloor(25, 12));
  EXPECT_EQ(2, divFloor(35, 12));
  EXPECT_EQ(3, divFloor(36, 12));
  EXPECT_EQ(3, divFloor(37, 12));
}


TEST(integers, divFloor_negativeDivisor) {
  EXPECT_EQ(2, divFloor(-25, -12));
  EXPECT_EQ(2, divFloor(-24, -12));
  EXPECT_EQ(1, divFloor(-23, -12));
  EXPECT_EQ(1, divFloor(-13, -12));
  EXPECT_EQ(1, divFloor(-12, -12));
  EXPECT_EQ(0, divFloor(-11, -12));
  EXPECT_EQ(0, divFloor(-1, -12));
  EXPECT_EQ(0, divFloor(0, -12));
  EXPECT_EQ(-1, divFloor(1, -12));
  EXPECT_EQ(-1, divFloor(11, -12));
  EXPECT_EQ(-1, divFloor(12, -12));
  EXPECT_EQ(-2, divFloor(13, -12));
  EXPECT_EQ(-2, divFloor(23, -12));
  EXPECT_EQ(-2, divFloor(24, -12));
  EXPECT_EQ(-3, divFloor(25, -12));
  EXPECT_EQ(-3, divFloor(35, -12));
  EXPECT_EQ(-3, divFloor(36, -12));
  EXPECT_EQ(-4, divFloor(37, -12));
}


TEST(integers, modRangeCorrected_positiveDivisor) {
  EXPECT_EQ(1, modRangeCorrected(-302, 3));
  EXPECT_EQ(2, modRangeCorrected(-7, 3));
  EXPECT_EQ(0, modRangeCorrected(-6, 3));
  EXPECT_EQ(1, modRangeCorrected(-5, 3));
  EXPECT_EQ(2, modRangeCorrected(-4, 3));
  EXPECT_EQ(0, modRangeCorrected(-3, 3));
  EXPECT_EQ(1, modRangeCorrected(-2, 3));
  EXPECT_EQ(2, modRangeCorrected(-1, 3));
  EXPECT_EQ(0, modRangeCorrected(0, 3));
  EXPECT_EQ(1, modRangeCorrected(1, 3));
  EXPECT_EQ(2, modRangeCorrected(2, 3));
  EXPECT_EQ(0, modRangeCorrected(3, 3));
  EXPECT_EQ(1, modRangeCorrected(4, 3));
  EXPECT_EQ(2, modRangeCorrected(302, 3));
}


TEST(integers, modRangeCorrected_negativeDivisor) {
  EXPECT_EQ(-2, modRangeCorrected(-302, -3));
  EXPECT_EQ(-1, modRangeCorrected(-7, -3));
  EXPECT_EQ(0, modRangeCorrected(-6, -3));
  EXPECT_EQ(-2, modRangeCorrected(-5, -3));
  EXPECT_EQ(-1, modRangeCorrected(-4, -3));
  EXPECT_EQ(0, modRangeCorrected(-3, -3));
  EXPECT_EQ(-2, modRangeCorrected(-2, -3));
  EXPECT_EQ(-1, modRangeCorrected(-1, -3));
  EXPECT_EQ(0, modRangeCorrected(0, -3));
  EXPECT_EQ(-2, modRangeCorrected(1, -3));
  EXPECT_EQ(-1, modRangeCorrected(2, -3));
  EXPECT_EQ(0, modRangeCorrected(3, -3));
  EXPECT_EQ(-2, modRangeCorrected(4, -3));
  EXPECT_EQ(-1, modRangeCorrected(302, -3));
}


}  // namespace
