#pragma once
#include <string>
#include <iosfwd>

class Pipeline
{
private:
    int id;
    std::string pipe_name;
    double pipe_length = 0;
    int pipe_diameter = 0;
    bool pipe_condition = false;

    static int next_id;
public:
    friend std::ostream& operator<<(std::ostream& out, const Pipeline& pipe);
    friend std::istream& operator>>(std::istream& in,Pipeline& pipe);
    Pipeline();
    Pipeline(const std::string& name, double length,
        int diameter, bool condition);

    std::string Get_name() const;
    double Get_length() const;
    int Get_diameter() const;
    int Get_id() const;
    bool Get_condition() const;

    void Set_condition(bool condition);

    void print() const;//!!
    void input();
    void edit();

};
