#include "myUtilities.hpp"
#include <boost/range/counting_range.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/math/constants/constants.hpp>

#include <algorithm>
namespace PanosUtilities
{

    std::vector<double> linspace (double begin, double end, size_t numOfsamples)
    {
      std::vector<double> output;
      output.reserve(numOfsamples);

      if (numOfsamples < 2)
        throw std::domain_error("linspace: number of samples must be greater than 1");

      auto cRange = boost::counting_range(static_cast<size_t >(0), numOfsamples);

      auto transform = [begin, end, numOfsamples] (int i)
      { return begin + i * (end - begin) / (numOfsamples - 1); };

      boost::push_back(output, cRange | boost::adaptors::transformed(transform));

      return output;
    }


    Interval::Interval (double a, double b) noexcept
    {

      std::tie(min_,max_) = std::minmax(a,b);
    }

    double Interval::min () const noexcept
    {
      return min_;
    }
    double Interval::max () const noexcept
    {
      return max_;
    }

    bool is_inside (double x, const Interval& interval)
    {
      return ( x>= interval.min() && x<= interval.max());
    }


    std::vector<double> uniform_samples (const Interval& interval, size_t numOfsamples)
    {
      return linspace(interval.min(),interval.max(),numOfsamples);
    }


    std::vector<double> uniform_samples_exclude_min (const Interval& interval, size_t numOfsamples)
    {
     const double distance = interval.max()-interval.min();

     const double min_increase_factor = distance/(numOfsamples);

     const double new_min = interval.min() + min_increase_factor;

     const Interval new_interval(new_min, interval.max());

     return uniform_samples(new_interval,numOfsamples);
    }


    std::vector<double> uniform_samples_exclude_max (const Interval& interval, size_t numOfsamples)
    {
      const double distance = interval.max()-interval.min();

      const double max_decrease_factor = distance/(numOfsamples);

      const double new_max = interval.max() - max_decrease_factor;

      const Interval new_interval(interval.min(), new_max);

      return uniform_samples(new_interval,numOfsamples);
    }


    double wrap_2pi (double angle) noexcept
    {
      using boost::math::double_constants::one_div_two_pi;
      using boost::math::double_constants::two_pi;



      return angle - two_pi * floor(angle *one_div_two_pi);
    }


    double wrap_minus_pi_pi (double angle) noexcept
    {
      using boost::math::double_constants::pi;

      return wrap_2pi(angle + pi) - pi;
    }
}