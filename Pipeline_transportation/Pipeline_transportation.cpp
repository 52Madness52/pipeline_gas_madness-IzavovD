
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <vector>
#include <unordered_map>
#include "Pipeline.h"
#include "Compressor_station.h"
using namespace std;

void Get_positive_int(int& value)
{
    while (true)
    {
        if (!(cin >> value))
        {
            cout << "invalid input try again: ";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        string rest;
        getline(cin, rest);

        if (!rest.empty())
        {
            cout << "invalid input try again: ";
            continue;
        }

        if (value < 0)
        {
            cout << "Numbers negative. Try again: ";
            continue;
        }
    
        break;
    }
}

void Get_positive_double(double& value)
{
    while (true)
    {
        while (!(cin >> value))
        {
            cout << "invalid input try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        string rest1;
        getline(cin, rest1);

        if (!(rest1.empty()))
        {
            cout << "invalid input try again: ";
            continue;
        }
        if (value < 0)
        {
            cout << "Numbers negative. Try again: ";
            continue;
        }

        break;
    }
}

void Menu_print()
{
    cout << "1.Add pipe" << endl;
    cout << "2.Add compressor station" << endl;
    cout << "3.View all items" << endl;
    cout << "4.Edit pipe" << endl;
    cout << "5.Edit compressor station" << endl;
    cout << "6.Save" << endl;
    cout << "7.Upload" << endl;
    cout << "0.Exit" << endl << endl;
}

void Pipeline_print(const Pipeline& pipe)
{
    cout << "----PIPE----" << endl;
    cout << "ID: " << pipe.Get_id() << endl;
    cout << "Pipe name: " << pipe.Get_name() << endl;
    cout << "Pipe length: " << pipe.Get_length() << endl;
    cout << "Pipe diameter: " << pipe.Get_diameter() << endl;
    cout << "Pipe condition: " << pipe.Get_condition() << endl << endl;
}

void Compressor_print(const Compressor_station& comp)
{
    cout << "----Compressor Station----" << endl;
    cout << "ID: " << comp.Get_id() << endl;
    cout << "Compressor name: " << comp.Get_name() << endl;
    cout << "Number of workshops: " << comp.Get_workshops() << endl;
    cout << "Number of working workshops: " << comp.Get_workshops_working() << endl;
    cout << "Station class: " << comp.Get_station_class() << endl;
}

Pipeline Pipeline_input(int id)
{
    string name;
    string condition_input;
    double length;
    int diameter;
    bool condition;
    
    cout << "Enter pipe name: ";
    getline(cin >> ws, name);

    cout << "Enter pipe length: ";
    Get_positive_double(length);
    
    cout << "Enter pipe diameter: ";
    Get_positive_int(diameter);

    while (true)
    {
        cout << "Enter pipe condition (Yes/No): ";
        cin >> condition_input;

        if (condition_input == "Yes" || condition_input == "Y")
        {
            condition = true;
            break;
        }
        else if (condition_input == "No" || condition_input == "N")
        {
            condition = false;
            break;
        }
        else
        {
            cout << "invalid input for pipe condition" << endl << endl;
        }
    }

    cout << endl;

    Pipeline pipe(id, name, length, diameter, condition);

    return pipe;
}

Compressor_station Compressor_input(int id)
{
    string name;
    int workshops;
    int working_workshops;
    int station_class;

    cout << "Enter compressor name: ";
    getline(cin >> ws, name);
   
    cout << "Enter number of workshops: ";
    Get_positive_int(workshops);
    
    cout << "Enter number of working workshops: ";
    Get_positive_int(working_workshops);

    while (workshops < working_workshops)
    {
        cout << "The total number of workshops is less than the number of working workshops. Try again: ";
        Get_positive_int(working_workshops);
    }
    
    cout << "Enter station class: ";
    Get_positive_int(station_class);

    cout << endl;

    Compressor_station comp(id, workshops, working_workshops, station_class, name);

    return comp;
}

void Pipe_edit(Pipeline& pipe)
{
    string condition_edit;

    cout << "Current status: " << (pipe.Get_condition() ? "Yes" : "No") << '\n';

    while (true)
    {
        cout << "Enter the new status condition (Yes/No): ";
        cin >> condition_edit;
        if (condition_edit == "Yes" || condition_edit == "Y")
        {
            pipe.Set_condition(true);
            break;
        }
        else if (condition_edit == "No" || condition_edit == "N")
        {
            pipe.Set_condition(false);
            break;
        }
        else
        {
            cout << "invalid input for pipe condition" << endl;
        }
    }

    cout << endl;
}

void Compressor_edit(Compressor_station& comp)
{
    int user_inp; //!!!
    cout << "Total workshops:" << comp.Get_workshops() << endl;
    cout << "Working workshops:" << comp.Get_workshops_working() << endl;

    cout << "What do you want to do ?" << endl;
    cout << "1.Start a workshop" << endl;
    cout << "2.Stop a workshop" << endl;

    cout << "Enter: ";
    Get_positive_int(user_inp);
    

    if (user_inp == 1 && (comp.Get_workshops_working() < comp.Get_workshops()))
    {
        comp.Set_workshops(comp.Get_workshops_working() + 1);

        cout << "New number of working workshops: "
            << comp.Get_workshops_working() << endl;
    }
    else if (user_inp == 2 && comp.Get_workshops_working() != 0)
    {
        comp.Set_workshops(comp.Get_workshops_working() - 1);

        cout << "New number of working workshops: "
            << comp.Get_workshops_working() << endl;
    }
    else
    {
        cout << "ERROR" << endl << endl;
    }
}

void Save_Pipeline(ofstream& file, Pipeline& pipe)
{
    file << pipe.pipe_name << endl;
    file << pipe.pipe_length << endl;
    file << pipe.pipe_diameter << endl;
    file << pipe.pipe_condition << endl;
}

void Save_Compressor(ofstream& file, Compressor_station& comp)
{
    file << comp.comp_name << endl;
    file << comp.comp_workshops << endl;
    file << comp.comp_workshops_working << endl;
    file << comp.comp_station_class << endl;
}

void Upload_Pipeline(ifstream& file, Pipeline& pipe)
{
    getline(file >> ws, pipe.pipe_name);
    file >> pipe.pipe_length;
    file >> pipe.pipe_diameter;
    file >> pipe.pipe_condition;
}

void Upload_Compressor(ifstream& file, Compressor_station& comp)
{
    getline(file >> ws, comp.comp_name);
    file >> comp.comp_workshops;
    file >> comp.comp_workshops_working;
    file >> comp.comp_station_class;
}

void File_save( Pipeline& pipe, Compressor_station& comp, bool Pipeline_add, bool Compressor_add)
{
    ofstream file("data_pipe_comp.txt");

    if (!file.is_open())
    {
        cout << "Error: cannot open file.";
        return;
    }

    file << Pipeline_add << endl;

    if (Pipeline_add)//!!
        Save_Pipeline(file, pipe);
        

    file << Compressor_add << endl;

    if (Compressor_add)//!!
        Save_Compressor(file, comp);

    file.close();
}

bool File_upload(Pipeline& pipe, Compressor_station& comp, bool& Pipeline_add, bool& Compressor_add)
{
    ifstream file("data_pipe_comp.txt");

    if (!file.is_open())
    {
        cout << "Error: file not found." << endl;
        return false;
    }

    file >> Pipeline_add;

    if (Pipeline_add)//!!
        Upload_Pipeline(file, pipe);
    


    file >> Compressor_add;

    if (Compressor_add)//!!!
        Upload_Compressor(file, comp);
    
    file.close();

    return true;
}


int main()
{
    unordered_map<int, Pipeline > pipes;
    unordered_map<int, Compressor_station > pipes;
    int next_id = 1;
    int user_inp = 1;
    do
    {
        Menu_print();
        cout << "Enter: ";
        Get_positive_int(user_inp);

        switch (user_inp)
        {
        case 0:
        {
            cout << endl;
            cout << "Program terminated." << endl;
            break;
        }
        case 1:
        {
            cout << endl;
            Pipeline new_pipe{};
            Pipeline_input(new_pipe);
            new_pipe.id = next_id++;
            pipes.push_back(new_pipe);
     
            break;

        }
        case 2:
        {
            cout << endl;
            Compressor_station new_compressor{};
            Compressor_input(new_compressor);
            new_compressor.id = next_id++;
            compressors.push_back(new_compressor);
            break;
        }
        case 3:
        {
            if (!pipes.empty())
            {
                for (const Pipeline& pipe : pipes)
                {
                    Pipeline_print(pipe);
                }
            }
            else
            {
                cout << "Pipe dont find" << endl;
            }

            if (!compressors.empty())
            {
                for (const Compressor_station& comp : compressors)
                {
                    Compressor_print(comp);
                }
            }
            else
            {
                cout << "Compressor station dont find" << endl;
            }
            break;
        }
        case 4:
        {
            int required_id;
            bool found_id = false;
            cout << "Enter the ID of the required pipe: ";
            Get_positive_int(required_id);

            if (!pipes.empty())
            {
                for (Pipeline& pipe : pipes)
                {
                    if (pipe.id == required_id)
                    {
                        cout << "Editable Pipe:" << endl;
                        Pipeline_print(pipe);
                        Pipe_edit(pipe);
                        found_id = true;
                        break;

                    }
                }
            }
            else
            {
                cout << "Pipe dont find" << endl;
            }
            
            if (!found_id)
            {
                cout << "Pipe not found" << endl;
            }
            break; 
        }
        case 5:
        {
            int required_id;
            bool found_id = false;

            cout << "Enter the ID of the required compressor: ";
            Get_positive_int(required_id);
            
            if (!compressors.empty())
            {
                for (Compressor_station& comp : compressors)
                {
                    if (comp.id == required_id)
                    {
                        cout << "Editable Compressor Station" << endl;
                        Compressor_print(comp);
                        Compressor_edit(comp);
                        found_id = true;
                        break;
                    }
                }
            }
            else
            {
                cout << "Compressor station dont find" << endl;
            }
            
            
            if (!found_id)
            {
                cout << "Compressor Station not found" << endl;
            }
            break;
        }
        /*case 6:
        {
            if (Pipeline_add || Compressor_add)
            {
                File_save(pipe, comp, Pipeline_add, Compressor_add);
                cout << "Data saved successfully." << endl;
            }
            else
            {
                cout << "Error: no objects have been created yet." << endl;
            }
            cout << endl;
            break;
        }
        case 7:
        {
            if (File_upload(pipe, comp, Pipeline_add, Compressor_add))
            {
                cout << "Data loaded" << endl;
            }
            cout << endl;
            break;
        }
        default:
        {
            cout << "Invalid menu option. Try again" << endl << endl;
            break;
        }*/
        }
        
    } while (user_inp != 0);    
}
