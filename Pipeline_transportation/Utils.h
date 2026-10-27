#pragma once
#include "Pipeline.h"
#include "Compressor_station.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

#define INPUT_LINE(in, str) getline(in>>std::ws, str); \
						std::cerr << str << std::endl

#define PRINT_PARAM(out, x) out<< #x << "=" << x << std::endl

class redirect_output_wrapper
{
	std::ostream& stream;
	std::streambuf* const old_buf;
public:
	redirect_output_wrapper(std::ostream& src)
		: stream(src), old_buf(src.rdbuf())
	{
	}

	~redirect_output_wrapper() {
		stream.rdbuf(old_buf);
	}
	void redirect(std::ostream& dest)
	{
		stream.rdbuf(dest.rdbuf());
	}
};

std::vector<int> findPipes(const std::unordered_map<int, Pipeline>& pipes);
std::vector<int> findCompressors(const std::unordered_map<int, Compressor_station>& compressors);

void Get_positive_int(int& value);
void Get_positive_double(double& value);

