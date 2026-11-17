#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
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

    for (const auto& [id, pipe] : pipes)
        Save_Pipeline(file, pipe);

    file << '\n';

    for (const auto& [id, comp] : compressors)
        Save_Compressor(file, comp);

    file.close();

    if (!file)
    {
        std::cout << "Error: failed to save data." << std::endl;
        return false;
    }

    std::cout << "Data saved successfully." << std::endl;
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

    bool readingPipes = true;
    std::string line;

    while (std::getline(file, line))
    {
        if (line.empty())
        {
            if (!readingPipes)
            {
                std::cout << "Error: invalid file format." << std::endl;
                return false;
            }

            readingPipes = false;
            continue;
        }

        std::string data = line;

        for (int i = 0; i < 4; i++)
        {
            if (!std::getline(file, line) || line.empty())
            {
                std::cout << "Error: incomplete object data." << std::endl;
                return false;
            }

            data += '\n' + line;
        }

        std::istringstream record(data);

        if (readingPipes)
        {
            Pipeline pipe;

            if (!(record >> pipe) ||
                pipe.Get_id() <= 0 ||
                pipe.Get_length() < 0 ||
                pipe.Get_diameter() < 0 ||
                !loadedPipes.emplace(pipe.Get_id(), pipe).second)
            {
                std::cout << "Error: invalid pipe data." << std::endl;
                return false;
            }
        }
        else
        {
            Compressor_station comp;

            if (!(record >> comp) ||
                comp.Get_id() <= 0 ||
                comp.Get_workshops() < 0 ||
                comp.Get_workshops_working() < 0 ||
                comp.Get_workshops_working() > comp.Get_workshops() ||
                comp.Get_station_class() < 0 ||
                !loadedCompressors.emplace(comp.Get_id(), comp).second)
            {
                std::cout << "Error: invalid compressor data." << std::endl;
                return false;
            }
        }

        record >> std::ws;

        if (!record.eof())
        {
            std::cout << "Error: invalid object format." << std::endl;
            return false;
        }
    }

    if (readingPipes || !file.eof())
    {
        std::cout << "Error: invalid file format." << std::endl;
        return false;
    }

    pipes.swap(loadedPipes);
    compressors.swap(loadedCompressors);

    std::cout << "Data loaded successfully." << std::endl;
    return true;
}
