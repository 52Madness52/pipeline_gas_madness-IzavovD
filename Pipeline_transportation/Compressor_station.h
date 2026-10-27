#pragma once
#include <string>
#include <iosfwd>

class Compressor_station
{
private:
    int id;
    std::string comp_name;
    int comp_workshops = 0;
    int comp_workshops_working = 0;
    int comp_station_class = 0;
    static int next_id;

public:
    friend std::ostream& operator<<(std::ostream& out, const Compressor_station& comp);
    friend std::istream& operator>>(std::istream& in, Compressor_station& comp);

    Compressor_station();
    Compressor_station(int workshops,int working_workshops, int station_class, const std::string& name);

    int Get_id() const;
    int Get_workshops() const;
    int Get_workshops_working() const;
    int Get_station_class() const;
    std::string Get_name() const;

    void Set_workings(int working_workshops);//!!!

    void print() const;
    void input();
    void edit();

};