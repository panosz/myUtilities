//
// Created by Panagiotis Zestanakis on 26/02/19.
//

#include <iostream>
#include <sstream>

#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <boost/range/algorithm/copy.hpp>

#include "data_reading.hpp"

namespace PanosUtilities
{

    namespace
    {
        const auto float_regex =
            boost::regex(R"(((\+|-)?[[:digit:]]+)(\.(([[:digit:]]+)?))?((e|E)((\+|-)?)[[:digit:]]+)?)");

    }

    std::string trimm_comments (const std::string& input, const std::string& comment_characters)
    {

        const auto pos = input.find_first_of(comment_characters);

        return input.substr(0,pos);

    }


    inline double convertToDouble_No_Check(const std::string& s)
    {
        std::istringstream i(s);
        double x;
        i>>x;
        return x;
    }


    std::vector<double> doubles_from_string (const std::string& string)
    {
        std::vector<double> output;

        boost::push_back(output,string
                                | boost::adaptors::tokenized(float_regex)
                                |boost::adaptors::transformed(convertToDouble_No_Check) );
        return output;

    }
}