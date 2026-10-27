#include "Utils.h"
#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;


void Get_positive_int(int& value)
{
    while (true)
    {
        if (!(std::cin >> value))
        {
            std::cout << "invalid input try again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        string rest;
        getline(cin, rest);

        if (!rest.empty())
        {
            cout << "invalid input try again: ";
            continue;
        }

        if (value < 0)
        {
            cout << "Numbers negative. Try again: ";
            continue;
        }

        cerr << value << endl;
        break;
    }
}

void Get_positive_double(double& value)
{
    while (true)
    {
        while (!(cin >> value))
        {
            cout << "invalid input try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        string rest1;
        getline(cin, rest1);

        if (!(rest1.empty()))
        {
            cout << "invalid input try again: ";
            continue;
        }
        if (value < 0)
        {
            cout << "Numbers negative. Try again: ";
            continue;
        }

        cerr << value << endl;
        break;
    }
}

vector<int> findPipes(const unordered_map<int, Pipeline>& pipes)
{
    vector<int> foundIds;

    int choice;

    cout << "Search by name - 1, by repair - 2: ";
    Get_positive_int(choice);

    while (choice != 1 && choice != 2)
    {
        cout << "Enter only 1 or 2: ";
        Get_positive_int(choice);
    }

    if (choice == 1)
    {
        string query;
        cout << "Enter name pipe: ";

        INPUT_LINE(cin, query);

        for (const auto& [id, pipe] : pipes)
        {
            if (pipe.Get_name().rfind(query, 0) == 0)
            {
                foundIds.push_back(id);
            }
        }

    }
    else if (choice == 2)
    {
        int state;

        std::cout << "Search pipes under repair ? (1 - Yes, 0 - No): ";
        Get_positive_int(state);

        while (state != 0 && state != 1)
        {
            cout << "Enter only 0 or 1: ";
            Get_positive_int(state);
        }

        for (const auto& [id, pipe] : pipes)
        {
            if (pipe.Get_condition() == state)
            {
                foundIds.push_back(id);
            }
        }
    }
    return foundIds;
}

vector<int> findCompressors(const unordered_map<int, Compressor_station>& compressors)
{
    vector<int> foundIds;
    int choice;

    cout << "1 - by name, 2 - by min_inactive_percent";
    Get_positive_int(choice);
    while (choice != 1 && choice != 2)
    {
        cout << "Enter only 1 or 2: ";
        Get_positive_int(choice);
    }

    if (choice == 1)
    {
        string query;
        cout << "Enter name compressors: ";

        INPUT_LINE(cin, query);

        for (const auto& [id, comp] : compressors)
        {
            if (comp.Get_name().rfind(query, 0) == 0)
            {
                foundIds.push_back(id);
            }
        }
    }

    else if (choice == 2)
    {
        double min_inactive_percent;
        double inactive_percent;
        cout << "Enter minimum percent of inactive workshops: ";
        Get_positive_double(min_inactive_percent);

        while (min_inactive_percent > 100)
        {
            cout << "Enter a percent from 0 to 100: ";
            Get_positive_double(min_inactive_percent);
        }

        for (const auto& [id, comp] : compressors)
        {
            if (comp.Get_workshops() == 0)
            {
                continue;
            }

            inactive_percent = 100.0 * (comp.Get_workshops() - comp.Get_workshops_working()) / comp.Get_workshops();
            if (inactive_percent >= min_inactive_percent)
            {
                foundIds.push_back(id);
            }
        }
    }

    return foundIds;
}





