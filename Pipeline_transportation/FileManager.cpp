#include "FileManager.h"
#include <fstream>
#include <iostream>

void FileManager::Save_Compressor(std::ostream& file, const Compressor_station& comp)
{
    file << comp;
}

void FileManager::Save_Pipeline(std::ostream& file, const Pipeline& pipe)
{
    file << pipe;
}

void FileManager::Upload_Compressor(std::istream& file, Compressor_station& comp)
{
    file >> comp;
}

void FileManager::Upload_Pipeline(std::istream& file, Pipeline& pipe)
{
    file >> pipe;
}

bool FileManager::Save(
    const std::string& filename,
    const std::unordered_map<int, Pipeline>& pipes,
    const std::unordered_map<int, Compressor_station>& compressors)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Error: cannot open file for writing." << std::endl;
        return false;
    }

    file << pipes.size() << '\n';

    for (const auto& [id, pipe] : pipes)
    {
        Save_Pipeline(file, pipe);
    }

    file << compressors.size() << '\n';

    for (const auto& [id, comp] : compressors)
    {
        Save_Compressor(file, comp);
    }

    file.close();

    if (!file)
    {
        std::cout << "Error: failed to save data." << std::endl;
        return false;
    }

    std::cout << "Data saved successfully." << std::endl;
    std::cerr << "Saved data to " << filename << std::endl;

    return true;
}

bool FileManager::Load(
    const std::string& filename,
    std::unordered_map<int, Pipeline>& pipes,
    std::unordered_map<int, Compressor_station>& compressors)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Error: cannot open file for reading." << std::endl;
        return false;
    }

    std::unordered_map<int, Pipeline> loadedPipes;
    std::unordered_map<int, Compressor_station> loadedCompressors;

    long long pipeCount;

    if (!(file >> pipeCount) || pipeCount < 0)
    {
        std::cout << "Error: invalid pipe count." << std::endl;
        return false;
    }

    for (long long i = 0; i < pipeCount; ++i)
    {
        Pipeline pipe;
        Upload_Pipeline(file, pipe);

        if (!file || pipe.Get_id() <= 0 ||
            pipe.Get_length() < 0 || pipe.Get_diameter() < 0)
        {
            std::cout << "Error: invalid pipe data." << std::endl;
            return false;
        }

        if (!loadedPipes.emplace(pipe.Get_id(), pipe).second)
        {
            std::cout << "Error: duplicate pipe ID." << std::endl;
            return false;
        }
    }

    long long compressorCount;

    if (!(file >> compressorCount) || compressorCount < 0)
    {
        std::cout << "Error: invalid compressor count." << std::endl;
        return false;
    }

    for (long long i = 0; i < compressorCount; ++i)
    {
        Compressor_station comp;
        Upload_Compressor(file, comp);

        if (!file || comp.Get_id() <= 0 ||
            comp.Get_workshops() < 0 ||
            comp.Get_workshops_working() < 0 ||
            comp.Get_workshops_working() > comp.Get_workshops() ||
            comp.Get_station_class() < 0)
        {
            std::cout << "Error: invalid compressor data." << std::endl;
            return false;
        }

        if (!loadedCompressors.emplace(comp.Get_id(), comp).second)
        {
            std::cout << "Error: duplicate compressor ID." << std::endl;
            return false;
        }
    }

    file >> std::ws;

    if (!file.eof())
    {
        std::cout << "Error: unexpected data at end of file." << std::endl;
        return false;
    }

    pipes.swap(loadedPipes);
    compressors.swap(loadedCompressors);

    std::cout << "Data loaded successfully." << std::endl;
    std::cerr << "Loaded data from " << filename << std::endl;

    return true;
}