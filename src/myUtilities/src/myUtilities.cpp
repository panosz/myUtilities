#include "myUtilities.hpp"
#include <boost/range/counting_range.hpp>
#include <boost/range/adaptor/transformed.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

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
}