#pragma once

#include "Pipeline.h"
#include "Compressor_station.h"

#include <unordered_map>

struct Connection
{
    int from;
    int to;
};

using GasNetwork = std::unordered_map<int, Connection>;

void ConnectStations(
    GasNetwork& network,
    std::unordered_map<int, Pipeline>& pipes,
    const std::unordered_map<int, Compressor_station>& compressors);

void CleanupNetwork(
    GasNetwork& network,
    const std::unordered_map<int, Pipeline>& pipes,
    const std::unordered_map<int, Compressor_station>& compressors);

void TopologicalSort(
    const GasNetwork& network,
    const std::unordered_map<int, Compressor_station>& compressors);
