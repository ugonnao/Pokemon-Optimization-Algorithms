//Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include <algorithm>
#include <cassert>
#include <iostream>
#include <utility>
#include <iomanip>
#include "getopt.h"
#include "MST.h"
#include "FASTTSP.h"
#include "OPTTSP.h"
using namespace std;


class Pokemon{
    private:
        bool isHelp = false;

    public:
        void get_options(int argc, char** argv){
            int option_index = 0; 
            int option = 0; 
            string mode; 
            opterr = false; 

            struct option longOpts[] = {
                {"help", no_argument, nullptr, 'h'},
                {"mode", required_argument, nullptr, 'm'},
                {nullptr, 0, nullptr, '\0'}
            };
            while((option = getopt_long(argc, argv, "hm:", longOpts, &option_index)) != -1){
                switch(option){
                    case 'h':
                        cout << "helpful message\n";
                        isHelp = true; 
                        exit(0);
                    case 'm':
                        mode = optarg;
                        if(mode == "MST"){
                            MST charmander;
                            charmander.read_MST();
                            charmander.MST_Algorithm();
                        }else if(mode == "FASTTSP"){
                            FASTTSP squirtle;
                            squirtle.read_fasttsp();
                            squirtle.arbitraryInsertion();
                        }else if(mode == "OPTTSP"){
                            OPTTSP bulbasaur;
                            bulbasaur.read_input();
                            bulbasaur.TSP_Algorithm();
                        }else{
                            cerr << "Error: Invalid mode\n";
                        }
                        break;
                    default:
                       cerr << "Error: Invalid command line option\n";
                       break; 
                }
            }//while
        }//get_options
};//pokemon

int main(int argc, char** argv){
    std::ios::sync_with_stdio(false);
    cerr << fixed << showpoint << setprecision(2) << boolalpha;
    cout << std::setprecision(2); //Always show 2 decimal places
    cout << std::fixed;

    Pokemon Pikachu;
    Pikachu.get_options(argc, argv);
    return 0; 
}//main
