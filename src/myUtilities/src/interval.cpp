//
// Created by Panagiotis Zestanakis on 25/10/18.
//
#include<algorithm>
#include <tuple>
#include "interval.hpp"
#include "linspace.hpp"


namespace PanosUtilities
{
    Interval::Interval (double a, double b) noexcept
    {

      std::tie(min_, max_) = std::minmax(a, b);
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
      return (x >= interval.min() && x <= interval.max());
    }

    std::vector<double> uniform_samples (const Interval& interval, size_t numOfsamples)
    {
      return linspace(interval.min(), interval.max(), numOfsamples);
    }

    std::vector<double> uniform_samples_exclude_min (const Interval& interval, size_t numOfsamples)
    {
      const double distance = interval.max() - interval.min();

      const double min_increase_factor = distance / (numOfsamples);

      const double new_min = interval.min() + min_increase_factor;

      const Interval new_interval(new_min, interval.max());

      return uniform_samples(new_interval, numOfsamples);
    }

    std::vector<double> uniform_samples_exclude_max (const Interval& interval, size_t numOfsamples)
    {
      const double distance = interval.max() - interval.min();

      const double max_decrease_factor = distance / (numOfsamples);

      const double new_max = interval.max() - max_decrease_factor;

      const Interval new_interval(interval.min(), new_max);

      return uniform_samples(new_interval, numOfsamples);
    }
}