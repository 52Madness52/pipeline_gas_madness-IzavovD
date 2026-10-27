#include "Pipeline.h"
#include "Compressor_station.h"
#include "Utils.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

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
    ofstream file("log.txt", ios::app);

    redirect_output_wrapper redirect1(cerr);
    if (file.is_open())
    {
        redirect1.redirect(file);
    }

    cerr << "Test logging" << endl;



    unordered_map<int, Pipeline> pipes;
    unordered_map<int, Compressor_station> compressors;

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
            Pipeline pipe;
            pipe.input();
            auto result = pipes.emplace(pipe.Get_id(), pipe);

            if (result.second)
            {
                cout << "Pipe added (ID " << pipe.Get_id() << ")" << endl;
                next_id++;
            }
            else
            {
                cout << "Error: Pipe ID already exists" << endl;
            }
            break;
        }
        case 2:
        {

            cout << endl;
            Compressor_station comp(next_id);
            comp.input();
            auto result = compressors.emplace(next_id, comp);
            comp.Set_workshops(1000000000);//!!!!!!!!!!!!
            if (result.second)
            {
                cout << "Compressor station added (ID " << comp.Get_id() << ")" << endl;
                next_id++;
            }
            else
            {
                cout << "Error: Compressor station ID already exists" << endl;
            }

            break;
        }
        case 3:
        {
            /// Pipeline
            if (!pipes.empty())
            {
                for (const auto& [id, pipe] : pipes)
                {
                    pipe.print();
                }
            }
            else
            {
                cout << "No pipes have been added yet." << endl;
            }

            ///Compressor_station
            if (!compressors.empty())
            {
                for (const auto& [id, comp] : compressors)
                {
                    comp.print();
                }
            }
            else
            {
                cout << "No compressor stations have been added yet." << endl;
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
