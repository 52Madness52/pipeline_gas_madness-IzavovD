#include "Compressor_station.h"

Compressor_station::Compressor_station(int new_id, int workshops,
    int working_workshops, int station_class,
    const std::string& name)
{
    id = new_id;
    comp_workshops = workshops;
    comp_workshops_working = working_workshops;
    comp_station_class = station_class;
    comp_name = name;
}

int Compressor_station:: Get_id() const
{
    return id;
}

int Compressor_station::Get_workshops() const
{
    return comp_workshops;
}

int Compressor_station::Get_workshops_working() const
{
    return comp_workshops_working;
}

int Compressor_station::Get_station_class() const
{
    return comp_station_class;
}

std::string Compressor_station::Get_name() const
{
    return comp_name;
}

void Compressor_station::Set_workshops(int working_workshops)
{
    comp_workshops_working = working_workshops;
}