#include "gmock/gmock.h"
#include "myUtilities.hpp"
#include <boost/math/constants/constants.hpp>

using namespace testing;
using namespace PanosUtilities;
using boost::math::double_constants::two_pi;
using boost::math::double_constants::pi;
using boost::math::double_constants::sixth_pi;


TEST(alinspace, throwsWhenInputPointsAreLessThanTwo)
{
  ASSERT_ANY_THROW(linspace(0,10,1));
}

TEST(alinspace, ReturnsCorrectNumberOfElements)
{
  const auto num_elements = 113;
  ASSERT_EQ((linspace(0,2.5,num_elements).size()),num_elements);
}


TEST(alinspace,returnsCorrectValues)
{
  auto mylinspace= linspace(0,1,101);
  ASSERT_DOUBLE_EQ(mylinspace.front(),0);
  ASSERT_DOUBLE_EQ(mylinspace[1],0.01);
  ASSERT_DOUBLE_EQ(mylinspace.back(),1);

}

TEST(anInterval,Works)
{
  auto my_interval = Interval(0,-3.4);
  ASSERT_FALSE(is_inside(0.1,my_interval));
  ASSERT_FALSE(is_inside(-10.0,my_interval));
  ASSERT_TRUE(is_inside(-0.1,my_interval));

  ASSERT_DOUBLE_EQ(my_interval.min(),-3.4);
  ASSERT_DOUBLE_EQ(my_interval.max(),0);
}

TEST(uniform_sample_utilities, ExcludeMinWorks)
{
  const auto my_interval = Interval(0,3.14);
  const size_t numOfsamples = 10;

  const auto full_range = uniform_samples(my_interval,numOfsamples+1);

  const auto no_min_range = uniform_samples_exclude_min(my_interval,numOfsamples);

  ASSERT_DOUBLE_EQ(no_min_range.size(),numOfsamples);
  for (int i=0;i<numOfsamples;++i)
  ASSERT_DOUBLE_EQ(full_range[i+1],no_min_range[i]);

}


TEST(uniform_sample_utilities, ExcludeMaxWorks)
{
  const auto my_interval = Interval(0,3.14);
  const size_t numOfsamples = 10;

  const auto full_range = uniform_samples(my_interval,numOfsamples+1);

  const auto no_max_range = uniform_samples_exclude_max(my_interval,numOfsamples);

  ASSERT_DOUBLE_EQ(no_max_range.size(),numOfsamples);

  for (int i=0;i<numOfsamples;++i)
    ASSERT_DOUBLE_EQ(full_range[i],no_max_range[i]);

}


TEST(wrap_2pi_behaviour, LeavesAngleBetween0and2piUnchanged)
{
  const double small_angle = 1.2323256;

  ASSERT_DOUBLE_EQ(wrap_2pi(small_angle),small_angle);
}

TEST(wrap_2pi_behaviour, Maps2piToZero)
{

  ASSERT_DOUBLE_EQ(wrap_2pi(two_pi),0);
}

TEST(wrap_2pi_behaviour, RemovesPositiveMultiplesOfTwoPiAddedToSmallPositiveAngles)
{
  const double small_angle = 1.2323256;

  const double angle = small_angle+1000*two_pi;

  ASSERT_THAT(wrap_2pi(angle),DoubleNear(small_angle,1e-12));

}

TEST(wrap_2pi_behaviour, RemovesNegativeMultiplesOfTwoPiAddedToSmallPositiveAngles)
{
  const double small_angle = 1.2323256;

  const double angle = small_angle - 1000*two_pi;

  ASSERT_THAT(wrap_2pi(angle),DoubleNear(small_angle,1e-12));

}

TEST(wrap_2pi_behaviour, MirrorsSmallNegativeAngle)
{
  const double small_negative_angle = -1.2323256;

  ASSERT_DOUBLE_EQ(wrap_2pi(small_negative_angle),two_pi+small_negative_angle);

}


TEST(wrap_2pi_behaviour, RemovesPositiveMultiplesOfTwoPiAddedToSmallNegativeAngles)
{
  const double small_negative_angle = -1.2323256;

  const double angle = small_negative_angle + 1000*two_pi;

  ASSERT_THAT(wrap_2pi(angle),DoubleNear(small_negative_angle + two_pi,1e-12));

}


TEST(wrap_minus_pi_pi_behaviour, LeavesAngleBetweenMinus_pi_and_pi_Unchanged)
{
  const double small_angle = sixth_pi;
  ASSERT_DOUBLE_EQ(wrap_minus_pi_pi(small_angle),small_angle);

  const double small_negative_angle = -small_angle;
  ASSERT_DOUBLE_EQ(wrap_minus_pi_pi(small_negative_angle),small_negative_angle);
}

TEST(wrap_minus_pi_pi_behaviour, Maps_pi_to_minus_pi)
{
  ASSERT_DOUBLE_EQ(wrap_minus_pi_pi(pi),-pi);

}


TEST(wrap_minus_pi_pi_behaviour, MapsCorrectlyPositiveAngles)
{
  const double small_angle = sixth_pi;
  const double angle1 = small_angle + 31*pi;

  ASSERT_THAT(wrap_minus_pi_pi(angle1),DoubleNear(small_angle-pi,1e-13));

  const double angle2 = small_angle + 30*pi;
  ASSERT_THAT(wrap_minus_pi_pi(angle2),DoubleNear(small_angle,1e-13));
}

TEST(wrap_minus_pi_pi_behaviour, MapsCorrectlyNegativeAngles)
{
  const double small_negative_angle = -sixth_pi;
  const double angle1 = small_negative_angle - 31*pi;

  ASSERT_THAT(wrap_minus_pi_pi(angle1),DoubleNear(pi+small_negative_angle,1e-13));

  const double angle2 = small_negative_angle - 30*pi;
  ASSERT_THAT(wrap_minus_pi_pi(angle2),DoubleNear(small_negative_angle,1e-13));
}


TEST(zero_cross_behaviour,FindsFirstOfTwoElementsWhenChangeOfSign)
{
  auto values = std::vector<double>{-1,1};
  auto zeros = std::vector<double>{};

  zero_cross(std::begin(values),std::end(values),std::back_inserter(zeros));

  ASSERT_EQ(zeros.size(),1);
  ASSERT_EQ(zeros[0],-1);
}

TEST(zero_cross_behaviour,FindsNoneOfTwoElementsWhenBothPositive)
{
  auto values = std::vector<double>{1,2};
  auto zeros = std::vector<double>{};

  zero_cross(std::begin(values),std::end(values),std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());

}

TEST(zero_cross_behaviour,FindsNoneOfOneElementWhenNonZero)
{

  auto values = std::vector<double>{1};
  auto zeros = std::vector<double>{};

  zero_cross(std::begin(values),std::end(values),std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());
}


TEST(zero_cross_behaviour,FindsNoneOfOneElementWhenZero)
{

  auto values = std::vector<double>{0};
  auto zeros = std::vector<double>{};

  zero_cross(std::begin(values),std::end(values),std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());
}

TEST(zero_cross_behaviour,FindsNoneWhenAllZero)
{

  auto values = std::vector<double>{0,0,0,0};
  auto zeros = std::vector<double>{};

  zero_cross(std::begin(values),std::end(values),std::back_inserter(zeros));
  ASSERT_TRUE(zeros.empty());
}

TEST(zero_cross_behaviour,FindsMultipleCrossings)
{
  auto values = std::vector<int>{-2,-1,1,-3};
  auto expected_zeros = std::vector<int>{-1,1};
  auto zeros = std::vector<int>{};
  zero_cross(std::begin(values),std::end(values),std::back_inserter(zeros));

  auto are_equal = std::equal(std::begin(expected_zeros),std::end(expected_zeros),std::begin(zeros));
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_behaviour,DiscardsCrossingsWhenDifferenceGreaterThanThreshold)
{
  auto values = std::vector<int>{-2,-1,1,-30};
  auto expected_filtered_zeros = std::vector<int>{-1};
  auto filtered_zeros = std::vector<int>{};
  zero_cross(std::begin(values),std::end(values),std::back_inserter(filtered_zeros),5);

  auto are_equal = std::equal(std::begin(expected_filtered_zeros),std::end(expected_filtered_zeros),std::begin(filtered_zeros));
  ASSERT_TRUE(are_equal);
}

TEST(zero_cross_behaviour, SupportsRanges)
{
  auto values = std::vector<int>{-2,-1,1,-30};
  auto expected_filtered_zeros = std::vector<int>{-1};
  auto filtered_zeros = std::vector<int>{};
  zero_cross(values,std::back_inserter(filtered_zeros),5);
  auto are_equal = std::equal(std::begin(expected_filtered_zeros),std::end(expected_filtered_zeros),std::begin(filtered_zeros));
  ASSERT_TRUE(are_equal);

}


int main (int argc, char **argv)
{

  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
