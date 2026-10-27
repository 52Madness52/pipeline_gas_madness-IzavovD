#include "Pipeline.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

int Pipeline::next_id = 1;

Pipeline::Pipeline()
{
    id = next_id++;
}

Pipeline::Pipeline(const std::string& name, double length,
    int diameter, bool condition)
{
    id = next_id++;
    pipe_name = name;
    pipe_length = length;
    pipe_diameter = diameter;
    pipe_condition = condition;
}

int Pipeline::Get_id() const
{
    return id;
}

std::string Pipeline::Get_name() const
{
    return pipe_name;
}

double Pipeline::Get_length() const
{
    return pipe_length;
}

int Pipeline::Get_diameter() const
{
    return pipe_diameter;
}

bool Pipeline::Get_condition() const
{
    return pipe_condition;
}

void Pipeline::Set_condition(bool condition)
{
    pipe_condition = condition;
}

void Pipeline::print() const
{
    cout << "----PIPE----" << endl;
    cout << "ID: " << id << endl;
    cout << "Pipe name: " << pipe_name << endl;
    cout << "Pipe length: " << pipe_length << endl;
    cout << "Pipe diameter: " << pipe_diameter << endl;
    cout << "Pipe condition: " << pipe_condition << endl << endl;
}

void Pipeline::input()
{
    string condition_input;

    cout << "Enter pipe name: ";
    INPUT_LINE(cin, pipe_name);

    cout << "Enter pipe length: ";
    Get_positive_double(pipe_length);

    cout << "Enter pipe diameter: ";
    Get_positive_int(pipe_diameter);

    while (true)
    {
        cout << "Pipe condition: " << (pipe_condition ? "Yes" : "No") << endl;
        INPUT_LINE(cin, condition_input);

        if (condition_input == "Yes" || condition_input == "Y")
        {
            pipe_condition = true;
            break;
        }
        else if (condition_input == "No" || condition_input == "N")
        {
            pipe_condition = false;
            break;
        }
        else
        {
            cout << "invalid input for pipe condition" << endl << endl;
        }
    }

    cout << endl;
}

void Pipeline::edit()
{
    string condition_edit;

    cout << "Current status: " << (pipe_condition ? "Yes" : "No") << '\n';

    while (true)
    {
        cout << "Enter the new status condition (Yes/No): ";
        INPUT_LINE(cin, condition_edit);

        if (condition_edit == "Yes" || condition_edit == "Y")
        {
            Set_condition(true);
            break;
        }
        else if (condition_edit == "No" || condition_edit == "N")
        {
            Set_condition(false);
            break;
        }
        else
        {
            cout << "invalid input for pipe condition" << endl;
        }
    }

    cout << endl;
}

std::ostream& operator<<(std::ostream& out, const Pipeline& pipe)
{
    out << pipe.id << endl;
    out << std::quoted(pipe.pipe_name) << endl;
    out << pipe.pipe_length << endl;
    out << pipe.pipe_diameter << endl;
    out << pipe.pipe_condition << endl;

    return out;
}

std::istream& operator>>(std::istream& in, Pipeline& pipe)
{
    in >> pipe.id;
    in >> std::quoted(pipe.pipe_name);
    in >> pipe.pipe_length;
    in >> pipe.pipe_diameter;
    in >> pipe.pipe_condition;

    if (in)
    {
        if (pipe.id >= Pipeline::next_id && pipe.id > 0)
        {
            Pipeline::next_id = pipe.id + 1;
        }
    }
    return in;
}
