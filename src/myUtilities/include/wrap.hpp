//
// Created by Panagiotis Zestanakis on 25/10/18.
//

#ifndef MYUTILITIES_WRAP_HPP
#define MYUTILITIES_WRAP_HPP
namespace PanosUtilities
{


    /// \brief wrap2_pi maps angle on the range [0,2*pi) substracting any integer multiples of 2*pi
    /// \param angle
    /// \return an equivalent angle in [0,2*pi)
    ///
    /// relative error about 1e-16
    double wrap_2pi (double angle) noexcept;

    /// \brief wrap_minus_pi_pi maps angle on the range [-pi,pi)
    /// \param angle
    /// \return an equivalent angle in [-pi,pi)
    ///
    /// relative error about 1e-16
    double wrap_minus_pi_pi (double angle) noexcept;

}
#endif //MYUTILITIES_WRAP_HPP
