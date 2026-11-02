#include "Utils.h"

#include <iostream>
#include <string>
#include <limits>
#include <unordered_set>
#include <unordered_map>
#include <iomanip>
#include <type_traits>

using namespace std;

template <typename T>
void Get_positive(T& value)
{
    while (true)
    {
        if (!(cin >> value))
        {
            cout << "Invalid input. Try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        string rest;
        getline(cin, rest);

        if (rest.find_first_not_of(" \t\r") != string::npos)
        {
            cout << "Invalid input. Try again: ";
            continue;
        }

        if (value < 0)
        {
            cout << "Negative number. Try again: ";
            continue;
        }

        if constexpr (is_floating_point_v<T>)
        {
            cerr << setprecision(numeric_limits<T>::max_digits10)
                << value << endl;
        }
        else
        {
            cerr << value << endl;
        }

        break;
    }
}

void Get_positive_int(int& value)
{
    Get_positive(value);
}

void Get_positive_double(double& value)
{
    Get_positive(value);
}

int Get_search_choice()
{
    int choice;

    cout << "1 - by name, 2 - by characteristic: ";
    Get_positive_int(choice);

    while (choice != 1 && choice != 2)
    {
        cout << "Enter only 1 or 2: ";
        Get_positive_int(choice);
    }

    return choice;
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

unordered_set<int> findPipes(const unordered_map<int, Pipeline>& pipes)
{
    int choice = Get_search_choice();

    if (choice == 1)
    {
        string query;
        cout << "Enter pipe name: ";
        INPUT_LINE(cin, query);

        return Search(pipes, query, FilterName<Pipeline>);
    }
    else
    {
        int state;
        cout << "Search pipes under repair? (1 - Yes, 0 - No): ";
        Get_positive_int(state);

        while (state != 0 && state != 1)
        {
            cout << "Enter only 0 or 1: ";
            Get_positive_int(state);
        }

        bool repair = (state == 1);
        return Search(pipes, repair, FilterPipeRepair);
    }
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

        return Search(compressors, query, FilterName<Compressor_station>);
    }
    else
    {
        double min_inactive_percent;
        cout << "Enter minimum percent of inactive workshops: ";
        Get_positive_double(min_inactive_percent);

        while (min_inactive_percent > 100)
        {
            cout << "Enter a percent from 0 to 100: ";
            Get_positive_double(min_inactive_percent);
        }

        return Search(
            compressors, min_inactive_percent, FilterCompressorInactive);
    }
}
