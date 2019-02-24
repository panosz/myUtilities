//
// Created by Panagiotis Zestanakis on 25/10/18.
//

#ifndef MYUTILITIES_ZERO_CROSSING_HPP
#define MYUTILITIES_ZERO_CROSSING_HPP
#include <algorithm>
#include <boost/range.hpp>

namespace PanosUtilities
{

    template<typename T>
    auto different_sign (T d1, T d2)
    {
      return (d1 < 0 && d2 >= 0) || (d1 > 0 && d2 <= 0);
    }

    template<class SinglePassIterator, class BinaryPredicate>
    SinglePassIterator my_adjacent_find(SinglePassIterator first, SinglePassIterator last,
                            BinaryPredicate p)
    {
      if (first == last) {
          return last;
        }
      auto previous_value = *first;

      ++first;

      while ( first != last) {
         auto cur_value = *first;
          if (p(previous_value, cur_value)) {
              return first;
            }
          previous_value = std::move(cur_value);
          ++first;
        }
      return last;
    }

    /// \brief finds first zero crossing
    /// \tparam Iterator type must satisfy the Single Pass iterator concept
    /// \param v_begin
    /// \param v_end
    /// \return iterator pointing to the last of the two elements that cross zero
    ///
    /// Iterator::value_type must be copy constructible and copy assignable
    template<typename Iterator>
    Iterator find_zero_cross (Iterator v_begin, Iterator v_end)
    {
      const auto my_fn = [] (auto x, auto y)
      { return different_sign(x, y); };

      return my_adjacent_find(v_begin, v_end, my_fn);
    }


    /// \brief finds first zero crossing. Elements are compared after applying tr_function to each
    /// \tparam Iterator type must satisfy the Single Pass iterator concept
    /// \param v_begin
    /// \param v_end
    /// \param tr_function a unary function with argument of type Iterator::value_type
    /// \return iterator pointing to the last of the two elements that cross zero
    ///
    /// Iterator::value_type must be copy constructible and copy assignable

    template<typename Iterator, typename Functor>
    Iterator find_zero_cross_transformed (Iterator v_begin, Iterator v_end, Functor tr_function)
    {

      const auto filtered_fn = [fn = tr_function] (auto x, auto y)
      {
          return different_sign(fn(x), fn(y));
      };

      return my_adjacent_find(v_begin, v_end, filtered_fn);
    }

    template<typename Iterator>
    Iterator find_zero_cross (Iterator v_begin, Iterator v_end,
                              double max_distance)
    {

      const auto not_too_far = [threshold = max_distance] (auto d1, auto d2)
      {
          return std::abs(d1 - d2) < threshold;
      };

      const auto true_zero_cross = [& not_too_far] (auto d1, auto d2)
      {
          return different_sign(d1, d2) && not_too_far(d1, d2);
      };

      return my_adjacent_find(v_begin, v_end, true_zero_cross);
    }

    template<typename Iterator, typename Functor>
    Iterator find_zero_cross_transformed (Iterator v_begin,
                                          Iterator v_end,
                                          Functor tr_function,
                                          double max_distance)
    {

      const auto not_too_far = [threshold = max_distance] (auto d1, auto d2)
      {
          return std::abs(d1 - d2) < threshold;
      };

      const auto true_zero_cross = [check_valid = not_too_far] (auto d1, auto d2)
      {
          return different_sign(d1, d2) && check_valid(d1, d2);
      };

      const auto filtered_fn =
          [transform = tr_function, fn = true_zero_cross] (auto x, auto y)
          {
              return fn(transform(x), transform(y));
          };

      return my_adjacent_find(v_begin, v_end, filtered_fn);
    }

    template<typename OutputIterator, typename InputIterator>
    void zero_cross (InputIterator v_begin, InputIterator v_end, OutputIterator out)
    {
      auto v_first = find_zero_cross(v_begin, v_end);

      if (v_first != v_end)
        {
          out = *v_first;
          zero_cross(v_first, v_end, out);
        }

    }

    template<typename OutputIterator, typename InputIterator, typename Functor>
    void zero_cross_transformed (InputIterator v_begin,
                                 InputIterator v_end,
                                 OutputIterator out,
                                 Functor tr_function)
    {
      auto v_first = find_zero_cross_transformed(v_begin, v_end, tr_function);

      if (v_first != v_end)
        {
          out = *v_first;
          zero_cross_transformed(v_first, v_end, out, tr_function);
        }

    }

    template<typename OutputIterator, typename InputIterator>
    void zero_cross (InputIterator v_begin, InputIterator v_end, OutputIterator out,
                     double max_distance)
    {
      auto v_first = find_zero_cross(v_begin, v_end, max_distance);

      if (v_first != v_end)
        {
          out = *v_first;
          zero_cross(v_first, v_end, out, max_distance);
        }

    }

    template<typename OutputIterator, typename InputIterator, typename Functor>
    void zero_cross_transformed (InputIterator v_begin,
                                 InputIterator v_end,
                                 OutputIterator out,
                                 Functor tr_function,
                                 double max_distance)
    {
      auto v_first = find_zero_cross_transformed(v_begin, v_end, tr_function, max_distance);

      if (v_first != v_end)
        {
          out = *v_first;
          zero_cross_transformed(v_first, v_end, out, tr_function, max_distance);
        }

    }

    template<typename Range, typename OutputIterator>
    void zero_cross (Range range, OutputIterator out)
    {
      zero_cross(std::cbegin(range), std::cend(range), out);
    }

    template<typename Range, typename OutputIterator, typename Functor>
    void zero_cross_transformed (Range range, OutputIterator out, Functor fn)
    {
      zero_cross_transformed(std::cbegin(range), std::cend(range), out, fn);
    }

    template<typename Range, typename OutputIterator>
    void zero_cross (Range range, OutputIterator out,
                     double max_distance)
    {
      zero_cross(std::cbegin(range), std::cend(range), out, max_distance);
    }

    template<typename Range, typename OutputIterator, typename Functor>
    void zero_cross_transformed (Range range,
                                 OutputIterator out,
                                 Functor fn,
                                 double max_distance)
    {
      zero_cross_transformed(std::cbegin(range), std::cend(range), out, fn, max_distance);
    }

}

#endif //MYUTILITIES_ZERO_CROSSING_HPP
