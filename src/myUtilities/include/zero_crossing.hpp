//
// Created by Panagiotis Zestanakis on 25/10/18.
//

#ifndef MYUTILITIES_ZERO_CROSSING_HPP
#define MYUTILITIES_ZERO_CROSSING_HPP
#include <algorithm>

namespace PanosUtilities
{
    template<typename Iterator>
    Iterator find_zero_cross (Iterator v_begin, Iterator v_end)
    {

      const auto different_sign = [] (auto d1, auto d2)
      {
          return (d1 < 0 && d2 >= 0) || (d1 > 0 && d2 <= 0);
      };

      return std::adjacent_find(v_begin, v_end, different_sign);
    }

    template<typename Iterator, typename DiffType>
    Iterator find_zero_cross (Iterator v_begin, Iterator v_end, DiffType max_distance)
    {

      const auto different_sign = [] (auto d1, auto d2)
      {
          return (d1 < 0 && d2 >= 0) || (d1 > 0 && d2 <= 0);
      };

      const auto not_too_far = [threshold = max_distance] (auto d1, auto d2)
      {
          return std::abs(d1 - d2) < threshold;
      };

      const auto true_zero_cross = [&different_sign,
                                    & not_too_far] (auto d1, auto d2)
      {
          return different_sign(d1, d2) && not_too_far(d1, d2);
      };

      return std::adjacent_find(v_begin, v_end, true_zero_cross);
    }

    template<typename OutputIterator, typename InputIterator>
    void zero_cross (InputIterator v_begin, InputIterator v_end, OutputIterator out)
    {
      auto v_first = find_zero_cross(v_begin, v_end);

      if (v_first != v_end)
        {
          out = *v_first;
          zero_cross(++v_first, v_end, out);
        }

    }

    template<typename OutputIterator, typename InputIterator, typename DiffType>
    void zero_cross (InputIterator v_begin, InputIterator v_end, OutputIterator out, DiffType max_distance)
    {
      auto v_first = find_zero_cross(v_begin, v_end, max_distance);

      if (v_first != v_end)
        {
          out = *v_first;
          zero_cross(++v_first, v_end, out, max_distance);
        }

    }
}

#endif //MYUTILITIES_ZERO_CROSSING_HPP
