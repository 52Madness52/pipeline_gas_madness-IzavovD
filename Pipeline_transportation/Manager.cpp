#include "Manager.h"
#include "Utils.h"

#include <iostream>
#include <vector>
#include <unordered_set>

using namespace std;

bool SelectIds(const unordered_set<int>& foundIds, vector<int>& selectedIds)
{
    int selection;

    do
    {
        cout << "\nSelect objects:" << endl;
        cout << "1. All found objects" << endl;
        cout << "2. Selected objects" << endl;
        cout << "0. Cancel" << endl;
        cout << "Enter: ";

        Get_positive_int(selection);

        if (selection > 2)
        {
            cout << "Invalid option. Try again." << endl;
        }
    } while (selection > 2);

    if (selection == 0)
    {
        return false;
    }

    selectedIds.clear();

    if (selection == 1)
    {
        selectedIds.assign(foundIds.begin(), foundIds.end());
        return true;
    }

    unordered_set<int> selectedSet;
    int count;

    while (true)
    {
        cout << "How many objects do you want to select?"
            << " (0 - Cancel): ";
        Get_positive_int(count);

        if (count == 0)
        {
            return false;
        }

        if (static_cast<size_t>(count) <= foundIds.size())
        {
            break;
        }

        cout << "Too many objects. Found: " << foundIds.size() << endl;
    }

    while (selectedIds.size() < static_cast<size_t>(count))
    {
        int id;
        cout << "Enter object ID: ";
        Get_positive_int(id);

        if (foundIds.find(id) == foundIds.end())
        {
            cout << "ID is not in the search results." << endl;
            continue;
        }

        if (!selectedSet.insert(id).second)
        {
            cout << "This ID has already been selected." << endl;
            continue;
        }

        selectedIds.push_back(id);
    }

    return true;
}

bool ConfirmDeletion()
{
    int confirmation;

    do
    {
        cout << "Confirm deletion? (1 - Yes, 0 - No): ";
        Get_positive_int(confirmation);

        if (confirmation > 1)
        {
            cout << "Enter only 0 or 1." << endl;
        }
    } while (confirmation > 1);

    return confirmation == 1;
}

void managePipes(unordered_map<int, Pipeline>& pipes)
{
    if (pipes.empty())
    {
        cout << "No pipes available" << endl;
        return;
    }

    unordered_set<int> foundIds = findPipes(pipes);

    if (foundIds.empty())
    {
        cout << "No pipes found" << endl;
        return;
    }

    cout << "\nFound pipes: " << foundIds.size() << endl;

    for (int id : foundIds)
    {
        pipes.at(id).print();
    }

    int action;

    do
    {
        cout << "\nPipe management:" << endl;
        cout << "1. Set under repair" << endl;
        cout << "2. Remove from repair" << endl;
        cout << "3. Delete pipes" << endl;
        cout << "0. Back" << endl;
        cout << "Enter: ";
        Get_positive_int(action);

        if (action > 3)
        {
            cout << "Invalid menu option. Try again." << endl;
        }
    } while (action > 3);

    if (action == 0)
    {
        return;
    }

    vector<int> selectedIds;

    if (!SelectIds(foundIds, selectedIds))
    {
        cout << "Operation canceled." << endl;
        return;
    }

    if (action == 3 && !ConfirmDeletion())
    {
        cout << "Deletion canceled." << endl;
        return;
    }

    int count = 0;

    for (int id : selectedIds)
    {
        if (action == 1)
        {
            pipes.at(id).Set_condition(true);
            count++;
        }
        else if (action == 2)
        {
            pipes.at(id).Set_condition(false);
            count++;
        }
        else if (action == 3)
        {
            pipes.erase(id);
            count++;
        }
    }

    cout << "Processed pipes: " << count << endl;
}

void manageCompressors(unordered_map<int, Compressor_station>& compressors)
{
    if (compressors.empty())
    {
        cout << "No compressor stations available" << endl;
        return;
    }

    unordered_set<int> foundIds = findCompressors(compressors);

    if (foundIds.empty())
    {
        cout << "No compressor stations found" << endl;
        return;
    }

    cout << "\nFound compressor stations: " << foundIds.size() << endl;

    for (int id : foundIds)
    {
        compressors.at(id).print();
    }

    int action;

    do
    {
        cout << "\nCompressor station management:" << endl;
        cout << "1. Start a workshop" << endl;
        cout << "2. Stop a workshop" << endl;
        cout << "3. Delete compressor stations" << endl;
        cout << "0. Back" << endl;
        cout << "Enter: ";
        Get_positive_int(action);

        if (action > 3)
        {
            cout << "Invalid menu option. Try again." << endl;
        }
    } while (action > 3);

    if (action == 0)
    {
        return;
    }

    vector<int> selectedIds;

    if (!SelectIds(foundIds, selectedIds))
    {
        cout << "Operation canceled." << endl;
        return;
    }

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

        Compressor_station& comp = compressors.at(id);

        if (action == 1)
        {
            if (comp.Get_workshops_working() < comp.Get_workshops())
            {
                if (comp.Set_workings_workshops(
                    comp.Get_workshops_working() + 1))
                {
                    count++;
                }
            }
            else
            {
                cout << "Station ID " << id
                    << ": all workshops are already working." << endl;
            }
        }
        else if (action == 2)
        {
            if (comp.Get_workshops_working() > 0)
            {
                if (comp.Set_workings_workshops(
                    comp.Get_workshops_working() - 1))
                {
                    count++;
                }
            }
            else
            {
                cout << "Station ID " << id
                    << ": no working workshops." << endl;
            }
        }
    }

    cout << "Processed compressor stations: " << count << endl;
}
