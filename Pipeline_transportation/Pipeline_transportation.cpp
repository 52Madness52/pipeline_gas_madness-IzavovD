
#include <iostream>
#include <fstream>
#include <limits>
#include <string>

using namespace std;

struct Pipeline
{
    string pipe_name;
    double pipe_length;
    int pipe_diameter;
    bool pipe_condition;
};

struct Compressor_station
{
    string comp_name;
    int comp_workshops;
    int comp_workshops_working;
    int comp_station_class;
};

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
    cout << "Pipe name: " << pipe.pipe_name << endl;
    cout << "Pipe length: " << pipe.pipe_length << endl;
    cout << "Pipe diameter: " << pipe.pipe_diameter << endl;
    cout << "Pipe condition: " << pipe.pipe_condition << endl << endl;
}

void Compressor_print(const Compressor_station& comp)
{
    cout << "----Compressor Station----" << endl;
    cout << "Compressor name: " << comp.comp_name << endl;
    cout << "Number of workshops: " << comp.comp_workshops << endl;
    cout << "Number of working workshops: " << comp.comp_workshops_working << endl;
    cout << "Station class: " << comp.comp_station_class << endl;
}

void Pipeline_input(Pipeline& pipe)
{
    string condition;
    
    cout << "Enter pipe name: ";
    getline(cin >> ws, pipe.pipe_name);

    cout << "Enter pipe length: ";
    Get_positive_double(pipe.pipe_length);
    
    cout << "Enter pipe diameter: ";
    Get_positive_int(pipe.pipe_diameter);

    while (condition != "No" || condition != "Yes" || condition != "Y" || condition != "N")
    {
        cout << "Enter pipe condition (Yes/No): ";
        cin >> condition;

        if (condition == "Yes" || condition == "Y")
        {
            pipe.pipe_condition = true;
            break;
        }
        else if (condition == "No" || condition == "N")
        {
            pipe.pipe_condition = false;
            break;
        }
        else
        {
            cout << "invalid input for pipe condition" << endl << endl;
        }
    }

    cout << endl;
}

void Compressor_input(Compressor_station& comp)
{
    cout << "Enter compressor name: ";
    getline(cin >> ws, comp.comp_name);
   
    cout << "Enter number of workshops: ";
    Get_positive_int(comp.comp_workshops);
    
    cout << "Enter number of working workshops: ";
    Get_positive_int(comp.comp_workshops_working);

    while (comp.comp_workshops < comp.comp_workshops_working)
    {
        cout << "The total number of workshops is less than the number of working workshops. Try again: ";
        Get_positive_int(comp.comp_workshops_working);
    }
    
    cout << "Enter station class: ";
    Get_positive_int(comp.comp_station_class);

    cout << endl;
}

void Pipe_edit(Pipeline& pipe)
{
    string condition_edit;

    cout << "Current status: " << (pipe.pipe_condition ? "Yes" : "No") << '\n';

    while (condition_edit != "No" || condition_edit != "Yes" || condition_edit != "Y" || condition_edit != "N")
    {
        cout << "Enter the new status condition (Yes/No): ";
        cin >> condition_edit;
        if (condition_edit == "Yes" || condition_edit == "Y")
        {
            pipe.pipe_condition = true;
            break;
        }
        else if (condition_edit == "No" || condition_edit == "N")
        {
            pipe.pipe_condition = false;
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
    cout << "Total workshops:" << comp.comp_workshops << endl;
    cout << "Working workshops:" << comp.comp_workshops_working << endl;

    cout << "What do you want to do ?" << endl;
    cout << "1.Start a workshop" << endl;
    cout << "2.Stop a workshop" << endl;

    cout << "Enter: ";
    Get_positive_int(user_inp);
    

    if (user_inp == 1 && (comp.comp_workshops_working < comp.comp_workshops))
    {
        cout << "New number of working workshops:" << ++comp.comp_workshops_working << endl;
    }
    else if (user_inp == 2 && comp.comp_workshops_working != 0)
    {
        cout << "New number of working workshops:" << --comp.comp_workshops_working << endl;
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
    Pipeline pipe{};
    Compressor_station comp{};
    
    int user_inp = 1;
    bool Pipeline_add = false;
    bool Compressor_add = false;

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
            Pipeline_input(pipe);
            Pipeline_add = true;
            break;

        }
        case 2:
        {
            cout << endl;
            Compressor_input(comp);
            Compressor_add = true;
            break;
        }
        case 3:
        {
            if (Pipeline_add)
            {
                Pipeline_print(pipe);
            }
            else
            {
                cout << "Pipe dont find" << endl << endl;
            }
            if (Compressor_add )
            {
                Compressor_print(comp);
            }
            else
            {
                cout << "Compressor station dont find" << endl;
            }
            cout << endl;
            break;
        }
        case 4:
        {
            if (Pipeline_add == true)
            {
                Pipe_edit(pipe);
            }
            else
            {
                cout << "Pipe dont find. You can't edit pipe." << endl;
            }
            cout << endl;
            break;
        }
        case 5:
        {
            if (Compressor_add == true)
            {
                Compressor_edit(comp);
            }
            else
            {
                cout << "Compressor station dont find. You can't edit Compressor station." << endl;
            }
            cout << endl;
            break;
        }
        case 6:
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
        }
        }
        
    } while (user_inp != 0);    
}
