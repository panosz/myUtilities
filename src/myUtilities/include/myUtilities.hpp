#ifndef MYUTILITIES_LIBRARY_H
#define MYUTILITIES_LIBRARY_H

#include <vector>

namespace PanosUtilities
{
    std::vector<double> linspace (double begin, double end, size_t numOfsamples);

    class Interval {
      double min_{0};
      double max_{0};
     public:
      Interval (double a, double b) noexcept;
      double min () const noexcept;
      double max () const noexcept;
    };

    bool is_inside (double x, const Interval& interval);

    std::vector<double> uniform_samples (const Interval& interval, size_t numOfsamples);

    ///This is equivalent to creating uniform samples of numOfsamples + 1 samples and deleting the first sample
    std::vector<double> uniform_samples_exclude_min (const Interval& interval, size_t numOfsamples);

    ///This is equivalent to creating uniform samples of numOfsamples + 1 samples and deleting the last sample
    std::vector<double> uniform_samples_exclude_max (const Interval& interval, size_t numOfsamples);

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
#endif //MYUTILITIES_LIBRARY_H