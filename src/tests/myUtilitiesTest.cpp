#include "gmock/gmock.h"
#include "myUtilities.hpp"

using namespace testing;
using namespace PanosUtilities;



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


int main (int argc, char **argv)
{

  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);

  return RUN_ALL_TESTS();
}
