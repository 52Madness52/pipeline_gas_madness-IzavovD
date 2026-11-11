#include "Utils.h"

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int Get_search_choice()
{
    cout << "1 - by name, 2 - by characteristic: ";
    return GetCorrectNumber(1, 2);
}

template <typename TObj, typename T>
using Filter = bool (*)(const TObj&, const T&);

template <typename TObj>
bool FilterName(const TObj& object, const string& query)
{
    return object.Get_name().find(query) != string::npos;
}

bool FilterPipeRepair(const Pipeline& pipe, const bool& repair)
{
    return pipe.Get_condition() == repair;
}

bool FilterCompressorInactive(
    const Compressor_station& comp, const double& min_percent)
{
    return comp.Get_workshops() > 0 &&
        comp.Get_inactive_percent() >= min_percent;
}

template <typename TObj, typename T>
unordered_set<int> Search(
    const unordered_map<int, TObj>& objects,
    const T& value,
    Filter<TObj, T> condition)
{
    unordered_set<int> foundIds;

    for (const auto& [id, object] : objects)
    {
        if (condition(object, value))
        {
            foundIds.insert(id);
        }
    }

    return foundIds;
}

unordered_set<int> findPipes(
    const unordered_map<int, Pipeline>& pipes)
{
    int choice = Get_search_choice();

    if (choice == 1)
    {
        string query;

        cout << "Enter pipe name: ";
        INPUT_LINE(cin, query);

        return Search(pipes, query, FilterName<Pipeline>);
    }

    cout << "Search pipes under repair? (1 - Yes, 0 - No): ";

    bool repair = GetCorrectNumber(0, 1) == 1;

    return Search(pipes, repair, FilterPipeRepair);
}

unordered_set<int> findCompressors(
    const unordered_map<int, Compressor_station>& compressors)
{
    int choice = Get_search_choice();

    if (choice == 1)
    {
        string query;

        cout << "Enter compressor name: ";
        INPUT_LINE(cin, query);

        return Search(
            compressors, query, FilterName<Compressor_station>);
    }

    cout << "Enter minimum percent of inactive workshops: ";

    double min_percent = GetCorrectNumber(0.0, 100.0);

    return Search(
        compressors, min_percent, FilterCompressorInactive);
}

//Pipeline_transportation.exe < log_03_11_2026_15_30_00.txt