#include "gmock/gmock.h"
#include "myUtilities.hpp"
#include <boost/math/constants/constants.hpp>
#include <boost/range/algorithm.hpp>

using namespace testing;
using namespace PanosUtilities;
using boost::math::double_constants::two_pi;
using boost::math::double_constants::pi;
using boost::math::double_constants::sixth_pi;

TEST(alinspace, throwsWhenInputPointsAreLessThanTwo)
{
  ASSERT_ANY_THROW(linspace(0, 10, 1));
}

TEST(alinspace, ReturnsCorrectNumberOfElements)
{
  const auto num_elements = 113;
  ASSERT_EQ((linspace(0, 2.5, num_elements).size()), num_elements);
}

TEST(alinspace, returnsCorrectValues)
{
  auto mylinspace = linspace(0, 1, 101);
  ASSERT_DOUBLE_EQ(mylinspace.front(), 0);
  ASSERT_DOUBLE_EQ(mylinspace[1], 0.01);
  ASSERT_DOUBLE_EQ(mylinspace.back(), 1);

}

TEST(anInterval, Works)
{
  auto my_interval = Interval(0, -3.4);
  ASSERT_FALSE(is_inside(0.1, my_interval));
  ASSERT_FALSE(is_inside(-10.0, my_interval));
  ASSERT_TRUE(is_inside(-0.1, my_interval));

  ASSERT_DOUBLE_EQ(my_interval.min(), -3.4);
  ASSERT_DOUBLE_EQ(my_interval.max(), 0);
}

TEST(uniform_sample_utilities, ExcludeMinWorks)
{
  const auto my_interval = Interval(0, 3.14);
  const size_t numOfsamples = 10;

  const auto full_range = uniform_samples(my_interval, numOfsamples + 1);

  const auto no_min_range = uniform_samples_exclude_min(my_interval, numOfsamples);

  ASSERT_DOUBLE_EQ(no_min_range.size(), numOfsamples);
  for (int i = 0; i < numOfsamples; ++i)
    ASSERT_DOUBLE_EQ(full_range[i + 1], no_min_range[i]);

}

TEST(uniform_sample_utilities, ExcludeMaxWorks)
{
  const auto my_interval = Interval(0, 3.14);
  const size_t numOfsamples = 10;

  const auto full_range = uniform_samples(my_interval, numOfsamples + 1);

  const auto no_max_range = uniform_samples_exclude_max(my_interval, numOfsamples);

  ASSERT_DOUBLE_EQ(no_max_range.size(), numOfsamples);

  for (int i = 0; i < numOfsamples; ++i)
    ASSERT_DOUBLE_EQ(full_range[i], no_max_range[i]);

}

TEST(wrap_2pi_behaviour, LeavesAngleBetween0and2piUnchanged)
{
  const double small_angle = 1.2323256;

  ASSERT_DOUBLE_EQ(wrap_2pi(small_angle), small_angle);
}

TEST(wrap_2pi_behaviour, Maps2piToZero)
{

  ASSERT_DOUBLE_EQ(wrap_2pi(two_pi), 0);
}

TEST(wrap_2pi_behaviour, RemovesPositiveMultiplesOfTwoPiAddedToSmallPositiveAngles)
{
  const double small_angle = 1.2323256;

  const double angle = small_angle + 1000 * two_pi;

  ASSERT_THAT(wrap_2pi(angle), DoubleNear(small_angle, 1e-12));

}

TEST(wrap_2pi_behaviour, RemovesNegativeMultiplesOfTwoPiAddedToSmallPositiveAngles)
{
  const double small_angle = 1.2323256;

  const double angle = small_angle - 1000 * two_pi;

  ASSERT_THAT(wrap_2pi(angle), DoubleNear(small_angle, 1e-12));

}

TEST(wrap_2pi_behaviour, MirrorsSmallNegativeAngle)
{
  const double small_negative_angle = -1.2323256;

  ASSERT_DOUBLE_EQ(wrap_2pi(small_negative_angle), two_pi + small_negative_angle);

}

TEST(wrap_2pi_behaviour, RemovesPositiveMultiplesOfTwoPiAddedToSmallNegativeAngles)
{
  const double small_negative_angle = -1.2323256;

  const double angle = small_negative_angle + 1000 * two_pi;

  ASSERT_THAT(wrap_2pi(angle), DoubleNear(small_negative_angle + two_pi, 1e-12));

}

TEST(wrap_minus_pi_pi_behaviour, LeavesAngleBetweenMinus_pi_and_pi_Unchanged)
{
  const double small_angle = sixth_pi;
  ASSERT_DOUBLE_EQ(wrap_minus_pi_pi(small_angle), small_angle);

  const double small_negative_angle = -small_angle;
  ASSERT_DOUBLE_EQ(wrap_minus_pi_pi(small_negative_angle), small_negative_angle);
}

TEST(wrap_minus_pi_pi_behaviour, Maps_pi_to_minus_pi)
{
  ASSERT_DOUBLE_EQ(wrap_minus_pi_pi(pi), -pi);

}

TEST(wrap_minus_pi_pi_behaviour, MapsCorrectlyPositiveAngles)
{
  const double small_angle = sixth_pi;
  const double angle1 = small_angle + 31 * pi;

  ASSERT_THAT(wrap_minus_pi_pi(angle1), DoubleNear(small_angle - pi, 1e-13));

  const double angle2 = small_angle + 30 * pi;
  ASSERT_THAT(wrap_minus_pi_pi(angle2), DoubleNear(small_angle, 1e-13));
}

TEST(wrap_minus_pi_pi_behaviour, MapsCorrectlyNegativeAngles)
{
  const double small_negative_angle = -sixth_pi;
  const double angle1 = small_negative_angle - 31 * pi;

  ASSERT_THAT(wrap_minus_pi_pi(angle1), DoubleNear(pi + small_negative_angle, 1e-13));

  const double angle2 = small_negative_angle - 30 * pi;
  ASSERT_THAT(wrap_minus_pi_pi(angle2), DoubleNear(small_negative_angle, 1e-13));
}

TEST(zero_cross_behaviour, FindsSecondOfTwoElementsWhenChangeOfSign)
{
  auto values = std::vector<double>{-1, 1};
  auto zeros = std::vector<double>{};

  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros));

  ASSERT_EQ(zeros.size(), 1);
  ASSERT_EQ(zeros[0], 1);
}
TEST(zero_cross_behaviour, FindsNoneOfTwoElementsWhenChangeOfSignWrongDirection)
{
  auto values = std::vector<double>{-1, 1};
  auto zeros = std::vector<double>{};

  int direction = -1;
  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros), direction);

  ASSERT_TRUE(zeros.empty());
}

TEST(zero_cross_transformed_behaviour, FindsSecondOfTwoElementsWhenChangeOfSign)
{
  using State = std::array<double, 2>;

  auto values = std::vector<State>{{-1, 0},
                                   {1,  0}};

  auto zeros = std::vector<State>{};

  auto pick_first = [] (State s)
  { return s[0]; };

  zero_cross_transformed(std::cbegin(values), std::cend(values), std::back_inserter(zeros), pick_first);

  ASSERT_EQ(zeros.size(), 1);
  ASSERT_EQ(zeros[0], (State{1, 0}));
}

TEST(zero_cross_transformed_behaviour, FindsNoneOfTwoElementsWhenChangeOfSignWrongDirection)
{
  using State = std::array<double, 2>;

  auto values = std::vector<State>{{-1, 0},
                                   {1,  0}};

  auto zeros = std::vector<State>{};

  auto pick_first = [] (State s)
  { return s[0]; };

  int direction = -1;

  zero_cross_transformed(std::cbegin(values),
                         std::cend(values),
                         std::back_inserter(zeros),
                         pick_first, direction);

  ASSERT_TRUE(zeros.empty());
}

TEST(zero_cross_behaviour, FindsNoneOfTwoElementsWhenBothPositive)
{
  auto values = std::vector<double>{1, 2};
  auto zeros = std::vector<double>{};

  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());

}

TEST(zero_cross_behaviour, FindsNoneOfOneElementWhenNonZero)
{

  auto values = std::vector<double>{1};
  auto zeros = std::vector<double>{};

  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());
}

TEST(zero_cross_behaviour, FindsNoneOfOneElementWhenZero)
{

  auto values = std::vector<double>{0};
  auto zeros = std::vector<double>{};

  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());
}

TEST(zero_cross_behaviour, FindsNoneWhenAllZero)
{

  auto values = std::vector<double>{0, 0, 0, 0};
  auto zeros = std::vector<double>{};

  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());
}

TEST(zero_cross_behaviour, FindsMultipleCrossings)
{
  auto values = std::vector<int>{-2, -1, 1, -3, -2, 1};
  auto expected_zeros = std::vector<int>{1, -3, 1};
  auto zeros = std::vector<int>{};
  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros));

  auto are_equal = boost::range::equal(expected_zeros, zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_behaviour, FindsMultipleCrossingsOnSpecifiedDirection)
{
  auto values = std::vector<int>{-2, -1, 1, -3, -2, 1};
  auto expected_zeros = std::vector<int>{1, 1};
  auto zeros = std::vector<int>{};

  int direction = 1;

  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(zeros), direction);

  auto are_equal = boost::range::equal(expected_zeros, zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_transformed_behaviour, FindsMultipleCrossings)
{
  using State = std::array<double, 2>;

  const auto values = std::vector<State>{{-2, 1},
                                         {-1, -1},
                                         {1,  -1}, // first element crossed zero
                                         {-3, -2}, // first element crossed zero
                                         {-2, 1},
                                         {1,  1}};   // first element crossed zero

  //Going to check for when the first element of State crosses zero
  const auto expected_zeros = std::vector<State>{{1,  -1},
                                                 {-3, -2},
                                                 {1,  1}};

  auto zeros = std::vector<State>{};
  const auto pick_first = [] (State s)
  { return s[0]; };

  zero_cross_transformed(std::cbegin(values), std::cend(values), std::back_inserter(zeros), pick_first);

  auto are_equal = boost::range::equal(expected_zeros, zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_transformed_behaviour, FindsMultipleCrossingsOnDesiredDirection)
{
  using State = std::array<double, 2>;

  const auto values = std::vector<State>{{-2, 1},
                                         {-1, -1},
                                         {1,  -1}, // first element crossed zero positive direction
                                         {-3, -2}, // first element crossed zero negative direction
                                         {-2, 1},
                                         {1,  1}};   // first element crossed zero positive direction

  //Going to check for when the first element of State crosses zero
  const auto expected_zeros = std::vector<State>{{-3, -2}};

  auto zeros = std::vector<State>{};
  const auto pick_first = [] (State s)
  { return s[0]; };

  int negative_direction = -1;

  zero_cross_transformed(std::cbegin(values), std::cend(values),
                         std::back_inserter(zeros), pick_first,
                         negative_direction);

  auto are_equal = boost::range::equal(expected_zeros, zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_behaviour, DiscardsCrossingsWhenDifferenceGreaterThanThreshold)
{
  const auto values = std::vector<int>{-2, -1, 1, -30};
  auto expected_filtered_zeros = std::vector<int>{1};
  auto filtered_zeros = std::vector<int>{};

  const double threshold = 5.0;

  zero_cross(std::cbegin(values), std::cend(values), std::back_inserter(filtered_zeros), threshold);

  auto are_equal = boost::range::equal(expected_filtered_zeros, filtered_zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_behaviour, DiscardsCrossingsWhenDifferenceGreaterThanThresholdAndDesiredDirection)
{
  const auto values = std::vector<int>{-2, -1, 1, 2, -1, 1, -30};
  auto expected_filtered_zeros = std::vector<int>{-1};
  auto filtered_zeros = std::vector<int>{};

  const double threshold = 5.0;
  const int negative_direction = -1;

  zero_cross(std::cbegin(values),
             std::cend(values),
             std::back_inserter(filtered_zeros),
             threshold,
             negative_direction);

  auto are_equal = boost::range::equal(expected_filtered_zeros, filtered_zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_transformed_behaviour, DiscardsCrossingsWhenDifferenceGreaterThanThreshold)
{
  using State = std::array<double, 2>;

  const auto values = std::vector<State>{{-2,  1},
                                         {-1,  -1},
                                         {1,   -1},
                                         {-30, -2}};
  //Going to check for when the first element of State crosses zero
  const auto expected_zeros = std::vector<State>{{1, -1}};

  auto zeros = std::vector<State>{};
  const auto pick_first = [] (State s)
  { return s[0]; };

  const double threshold = 5.0;

  zero_cross_transformed(std::cbegin(values),
                         std::cend(values),
                         std::back_inserter(zeros),
                         pick_first,
                         threshold);

  const auto are_equal = boost::range::equal(expected_zeros, zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_transformed_behaviour, DiscardsCrossingsWhenDifferenceGreaterThanThresholdAndDesiredDirection)
{
  using State = std::array<double, 2>;

  const auto values = std::vector<State>{{-2,  1},
                                         {-1,  -1},
                                         {1,   -1}, // positive zero cross (first element)
                                         {-1,  0},  // negative zero cross (first element)
                                         {1,   3},  // positive zero cross (first element)
                                         {-30, -2}};// negative zero cross (first element)

  //Going to check for when the first element of State crosses zero
  const auto expected_zeros = std::vector<State>{{-1, 0}};

  auto zeros = std::vector<State>{};
  const auto pick_first = [] (State s)
  { return s[0]; };

  const double threshold = 5.0;

  const int negative_direction = -1;

  zero_cross_transformed(std::cbegin(values),
                         std::cend(values),
                         std::back_inserter(zeros),
                         pick_first,
                         threshold,
                         negative_direction);

  const auto are_equal = boost::range::equal(expected_zeros, zeros);
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_behaviour, SupportsRanges)
{
  const auto values = std::vector<int>{-2, -1, 1, -30};
  const auto expected_filtered_zeros = std::vector<int>{1};
  auto filtered_zeros = std::vector<int>{};
  zero_cross(values, std::back_inserter(filtered_zeros), 5);
  const auto are_equal = boost::range::equal(expected_filtered_zeros, filtered_zeros);
  ASSERT_TRUE(are_equal);

}

int main (int argc, char **argv)
{

  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
