#include "Pipeline.h"
#include "Compressor_station.h"
#include "Utils.h"
#include "Manager.h"
#include "FileManager.h"

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

void Menu_print()
{
    cout << "\n===== MAIN MENU =====" << endl;
    cout << "1. Add pipe" << endl;
    cout << "2. Add compressor station" << endl;
    cout << "3. View all items" << endl;
    cout << "4. Search and manage objects" << endl;
    cout << "5. Save to file" << endl;
    cout << "6. Load from file" << endl;
    cout << "0. Exit" << endl << endl;
}

int main()
{
    unordered_map<int, Pipeline> pipes;
    unordered_map<int, Compressor_station> compressors;

    std::ofstream logfile("log.txt", std::ios::app);

    redirect_output_wrapper redirect(std::cerr);

    if (logfile.is_open())
    {
        redirect.redirect(logfile);
    }
    else
    {
        std::cout << "Warning: log file cannot be opened." << std::endl;
    }

    std::cerr << "PROGRAM START" << std::endl;

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
            Pipeline pipe;
            pipe.input();

            pipes.emplace(pipe.Get_id(), pipe);

            cout << "Pipe added. ID: " << pipe.Get_id() << endl;
            cerr << "Added pipe ID: " << pipe.Get_id() << endl;

            break;
        }

        case 2:
        {
            Compressor_station comp;
            comp.input();

            compressors.emplace(comp.Get_id(), comp);

            cout << "Compressor added. ID: " << comp.Get_id() << endl;
            cerr << "Added compressor ID: " << comp.Get_id() << endl;

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
            int type;

            do
            {
                cout << "1. Manage pipes" << endl;
                cout << "2. Manage compressors" << endl;
                cout << "0. Back" << endl;
                cout << "Enter: ";

                Get_positive_int(type);

            } while (type > 2);

            if (type == 1)
            {
                managePipes(pipes);
            }
            else if (type == 2)
            {
                manageCompressors(compressors);
            }

            break;
        }
        case 5:
        {
            string filename;

            cout << "Enter filename to save: ";
            INPUT_LINE(cin, filename);

            FileManager::Save(filename, pipes, compressors);

            break;
        }
        case 6:
        {
            string filename;

            cout << "Enter filename to load: ";
            INPUT_LINE(cin, filename);

            FileManager::Load(filename, pipes, compressors);

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
