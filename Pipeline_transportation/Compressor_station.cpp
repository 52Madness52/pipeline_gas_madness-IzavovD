#include "Compressor_station.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int Compressor_station::next_id = 1;

Compressor_station::Compressor_station()
{
    id = next_id++;
}

Compressor_station::Compressor_station(int workshops,int working_workshops, int station_class, const std::string& name)
{
    id = next_id++;
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

void Compressor_station::Set_workings_workshops(int working_workshops)
{
    comp_workshops_working = working_workshops;//!!!!
}

void Compressor_station::print() const
{
    cout << "----Compressor Station----" << endl;
    cout << "ID: " << id << endl;
    cout << "Compressor name: " << comp_name << endl;
    cout << "Number of workshops: " << comp_workshops << endl;
    cout << "Number of working workshops: " << comp_workshops_working << endl;
    cout << "Station class: " << comp_station_class << endl;
}

void Compressor_station::input()
{
    cout << "Enter compressor name: ";
    INPUT_LINE(cin, comp_name);

    cout << "Enter number of workshops: ";
    Get_positive_int(comp_workshops);

    cout << "Enter number of working workshops: ";
    Get_positive_int(comp_workshops_working);

    while (comp_workshops < comp_workshops_working)
    {
        cout << "The total number of workshops is less than the number of working workshops. Try again: ";
        Get_positive_int(comp_workshops_working);
    }

    cout << "Enter station class: ";
    Get_positive_int(comp_station_class);

    cout << endl;

}

void Compressor_station::edit()
{
    int user_inp; //!!!
    cout << "Total workshops:" << comp_workshops << endl;
    cout << "Working workshops:" << comp_workshops_working << endl;

    cout << "What do you want to do ?" << endl;
    cout << "1.Start a workshop" << endl;
    cout << "2.Stop a workshop" << endl;

    cout << "Enter: ";
    Get_positive_int(user_inp);


    if (user_inp == 1 && (comp_workshops_working < comp_workshops))
    {
        Set_workings_workshops(comp_workshops_working + 1);

        cout << "New number of working workshops: "
            << comp_workshops_working << endl;
    }
    else if (user_inp == 2 && comp_workshops_working != 0)
    {
        Set_workings_workshops(comp_workshops_working - 1);

        cout << "New number of working workshops: "
            << comp_workshops_working << endl;
    }
    else
    {
        cout << "ERROR" << endl << endl;
    }
}

std::ostream& operator<<(std::ostream& out, const Compressor_station& comp)
{
    out << comp.id << endl;
    out << std::quoted(comp.comp_name) << endl;
    out << comp.comp_workshops << endl;
    out << comp.comp_workshops_working << endl;
    out << comp.comp_station_class << endl;

    return out;
}

std::istream& operator>>(std::istream& in, Compressor_station& comp)
{
    in >> comp.id;
    in >> std::quoted(comp.comp_name);
    in >> comp.comp_workshops;
    in >> comp.comp_workshops_working;
    in >> comp.comp_station_class;

    if (in)
    {
        if (comp.id >= Compressor_station::next_id && comp.id > 0)
        {
            Compressor_station::next_id = comp.id + 1;
        }
    }

    return in;
}