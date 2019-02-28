//
// Created by Panagiotis Zestanakis on 26/02/19.
//

#ifndef MYUTILITIES_DATA_READING_HPP
#define MYUTILITIES_DATA_READING_HPP


#include <vector>
#include <string>



namespace PanosUtilities
{




    std::string trimm_comments(const std::string& input, const std::string& comment_characters = "#");


    std::vector<double> doubles_from_string(const std::string& string);

}

#endif //MYUTILITIES_DATA_READING_HPP
