#pragma once
#include <unordered_map>
#include "Pipeline.h"
#include "Compressor_station.h"

void managePipes(std::unordered_map<int, Pipeline>& pipes);

void manageCompressors(
    std::unordered_map<int, Compressor_station>& compressors);


