#pragma once
#include <string>

class Compressor_station
{
private:
    int id;
    int comp_workshops = 0;
    int comp_workshops_working = 0;
    int comp_station_class = 0;
    std::string comp_name;

public:
    Compressor_station(int new_id, int workshops,
        int working_workshops, int station_class,
        const std::string& name);

    int Get_id() const;
    int Get_workshops() const;
    int Get_workshops_working() const;
    int Get_station_class() const;
    std::string Get_name() const;

    void Set_workshops(int working_workshops);
};