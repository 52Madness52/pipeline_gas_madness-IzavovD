#pragma once

#include "Pipeline.h"
#include "Compressor_station.h"

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <limits>
#include <iomanip>

#define INPUT_LINE(in, str) std::getline(in >> std::ws, str); \
                            std::cerr << str << std::endl

#define PRINT_PARAM(out, x) out << #x << "=" << x << std::endl

class redirect_output_wrapper
{
    std::ostream& stream;
    std::streambuf* const old_buf;

public:
    redirect_output_wrapper(std::ostream& src)
        : stream(src), old_buf(src.rdbuf())
    {
    }

    ~redirect_output_wrapper()
    {
        stream.rdbuf(old_buf);
    }

    void redirect(std::ostream& dest)
    {
        stream.rdbuf(dest.rdbuf());
    }
};


template <typename T>
T GetCorrectNumber(T min, T max = std::numeric_limits<T>::max())
{
    T x;

    while (true)
    {
        if (!(std::cin >> x))
        {
            if (std::cin.eof())
                throw std::runtime_error("End of input");
        }
        else
        {
            int next = std::cin.peek();

            if ((next == '\n' ||
                next == std::char_traits<char>::eof()) &&
                x >= min && x <= max)
            {
                std::cerr << std::setprecision(
                    std::numeric_limits<T>::max_digits10)
                    << x << std::endl;

                return x;
            }
        }

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Type number ("
            << min << "-" << max << "): ";
    }
}


std::unordered_set<int> findPipes(
    const std::unordered_map<int, Pipeline>& pipes);

std::unordered_set<int> findCompressors(
    const std::unordered_map<int, Compressor_station>& compressors);
