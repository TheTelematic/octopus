#ifndef __UTILS__HPP__
#define __UTILS__HPP__

namespace octopus{

    std::vector<std::string> split(const string& input, const string& regex) {
        // passing -1 as the submatch index parameter performs splitting
        std::regex re(regex);
        std::sregex_token_iterator
            first{input.begin(), input.end(), re, -1},
            last;
        return {first, last};
    }

}

#endif
