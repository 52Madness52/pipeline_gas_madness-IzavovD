#include "Pipeline.h"

Pipeline::Pipeline(int new_id, const std::string& name,
    double length, int diameter, bool condition)
{
    id = new_id;
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