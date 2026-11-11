#include "Manager.h"
#include "Utils.h"

#include <iostream>
#include <unordered_set>

using namespace std;

unordered_set<int> SelectIds(const unordered_set<int>& foundIds)
{
    cout << "\nSelect objects:\n1. All found objects\n"
        << "2. Selected objects\n0. Cancel\nEnter: ";

    int selection = GetCorrectNumber(0, 2);

    if (selection == 0) return {};
    if (selection == 1) return foundIds;

    unordered_set<int> selectedIds;

    while (true)
    {
        cout << "Enter object ID (0 - exit): ";
        int id = GetCorrectNumber(0);

        if (id == 0) break;

        if (!foundIds.contains(id))
            cout << "ID is not in the search results." << endl;
        else if (!selectedIds.insert(id).second)
            cout << "This ID has already been selected." << endl;
    }

    return selectedIds;
}

bool ConfirmDeletion()
{
    cout << "Confirm deletion? (1 - Yes, 0 - No): ";
    return GetCorrectNumber(0, 1) == 1;
}

void managePipes(unordered_map<int, Pipeline>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes available" << endl;
        return;
    }

    auto foundIds = findPipes(pipes);
    if (foundIds.empty())
    {
        cout << "No pipes found" << endl;
        return;
    }

    cout << "\nFound pipes: " << foundIds.size() << endl;
    for (int id : foundIds) pipes.at(id).print();

    cout << "\nPipe management:\n1. Set under repair\n"
        << "2. Remove from repair\n3. Delete pipes\n0. Back\nEnter: ";

    int action = GetCorrectNumber(0, 3);
    if (action == 0) return;

    auto selectedIds = SelectIds(foundIds);
    if (selectedIds.empty()) return;

    if (action == 3 && !ConfirmDeletion())
    {
        cout << "Deletion canceled." << endl;
        return;
    }

    for (int id : selectedIds)
    {
        if (action == 3) pipes.erase(id);
        else pipes.at(id).Set_condition(action == 1);
    }

    cout << "Processed pipes: " << selectedIds.size() << endl;
}

void manageCompressors(unordered_map<int, Compressor_station>& compressors)
{
    if (compressors.empty())
    {
        cout << "No compressor stations available" << endl;
        return;
    }

    auto foundIds = findCompressors(compressors);
    if (foundIds.empty())
    {
        cout << "No compressor stations found" << endl;
        return;
    }

    cout << "\nFound compressor stations: " << foundIds.size() << endl;
    for (int id : foundIds) compressors.at(id).print();

    cout << "\nCompressor station management:\n1. Start a workshop\n"
        << "2. Stop a workshop\n3. Delete compressor stations\n"
        << "0. Back\nEnter: ";

    int action = GetCorrectNumber(0, 3);
    if (action == 0) return;

    auto selectedIds = SelectIds(foundIds);
    if (selectedIds.empty()) return;

    if (action == 3 && !ConfirmDeletion())
    {
        cout << "Deletion canceled." << endl;
        return;
    }

    int count = 0;

    for (int id : selectedIds)
    {
        if (action == 3)
        {
            compressors.erase(id);
            count++;
            continue;
        }

        auto& comp = compressors.at(id);

        if (comp.Set_workings_workshops(
            comp.Get_workshops_working() + (action == 1 ? 1 : -1)))
            count++;
        else
            cout << "Station ID " << id
            << ": cannot change working workshops." << endl;
    }
    cout << "Processed compressor stations: " << count << endl;
}
