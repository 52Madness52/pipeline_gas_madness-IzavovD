#include "Network.h"
#include "Utils.h"
#include <iostream>

#include <queue>
#include <vector>
using namespace std;

int GetDiameter()
{
    int d;
    do
    {
        cout << "Diameter (500, 700, 1000, 1400): ";
        d = GetCorrectNumber(500, 1400);
    } while (d != 500 && d != 700 && d != 1000 && d != 1400);

    return d;
}

int FindFreePipe(
    const GasNetwork& network,
    const unordered_map<int, Pipeline>& pipes,
    int diameter)
{
    for (const auto& [id, pipe] : pipes)
        if (pipe.Get_diameter() == diameter && !network.contains(id))
            return id;

    return 0;
}

void ConnectStations(
    GasNetwork& network,
    unordered_map<int, Pipeline>& pipes,
    const unordered_map<int, Compressor_station>& compressors)
{
    cout << "Input station ID: ";
    int from = GetCorrectNumber(1);

    cout << "Output station ID: ";
    int to = GetCorrectNumber(1);

    if (!compressors.contains(from) || !compressors.contains(to) || from == to)
    {
        cout << "Invalid station IDs." << endl;
        return;
    }

    int diameter = GetDiameter();
    int pipeId = FindFreePipe(network, pipes, diameter);

    if (pipeId == 0)
    {
        string name;
        cout << "No free pipe. Enter new pipe name: ";
        INPUT_LINE(cin, name);

        cout << "Enter pipe length: ";
        double length = GetCorrectNumber(0.0);

        Pipeline pipe(name, length, diameter, false);
        pipeId = pipe.Get_id();
        pipes.emplace(pipeId, pipe);
    }

    network.emplace(pipeId, Connection{ from, to });

    cout << "Connected " << from << " -> " << to
        << " using pipe " << pipeId << endl;
}

void CleanupNetwork(
    GasNetwork& network,
    const unordered_map<int, Pipeline>& pipes,
    const unordered_map<int, Compressor_station>& compressors)
{
    for (auto it = network.begin(); it != network.end();)
        if (!pipes.contains(it->first) ||
            !compressors.contains(it->second.from) ||
            !compressors.contains(it->second.to))
            it = network.erase(it);
        else
            ++it;
}


void TopologicalSort(
    const GasNetwork& network,
    const unordered_map<int, Compressor_station>& compressors)
{
    unordered_map<int, int> degree;
    unordered_map<int, vector<int>> outgoing;

    for (const auto& [id, comp] : compressors)
        degree[id] = 0;

    for (const auto& [pipeId, edge] : network)
    {
        outgoing[edge.from].push_back(edge.to);
        ++degree[edge.to];
    }

    queue<int> ready;

    for (const auto& [id, d] : degree)
        if (d == 0)
            ready.push(id);

    vector<int> order;

    while (!ready.empty())
    {
        int id = ready.front();
        ready.pop();
        order.push_back(id);

        for (int to : outgoing[id])
            if (--degree[to] == 0)
                ready.push(to);
    }

    if (order.size() != compressors.size())
    {
        cout << "Cycle detected. Topological sorting is impossible." << endl;
        return;
    }

    cout << "Topological order: ";
    for (int id : order)
        cout << id << " ";
    cout << endl;
}

