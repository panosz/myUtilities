//
// Created by Panagiotis Zestanakis on 25/10/18.
//

#include <boost/math/constants/constants.hpp>



namespace PanosUtilities
{



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