#pragma once
#include <iosfwd>
#include <string>
#include <unordered_map>
#include "Pipeline.h"
#include "Compressor_station.h"

class FileManager
{
private:
    static void Save_Compressor(std::ostream& file, const Compressor_station& comp);
    static void Save_Pipeline(std::ostream& file, const Pipeline& pipe);
    static void Upload_Compressor(std::istream& file, Compressor_station& comp);
    static void Upload_Pipeline(std::istream& file, Pipeline& pipe);

public:
    static bool Save(
        const std::string& filename,
        const std::unordered_map<int, Pipeline>& pipes,
        const std::unordered_map<int, Compressor_station>& compressors);

    static bool Load(
        const std::string& filename,
        std::unordered_map<int, Pipeline>& pipes,
        std::unordered_map<int, Compressor_station>& compressors);
};