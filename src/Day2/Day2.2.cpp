#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

int main(int argc, char **argv) {

    // Check the amount of arguments
    if (argc != 2) {
        cerr <<"Error: Invalid amount of arguments." << endl;
        cerr << "Use: " << argv[0] << " <input>" << endl;
        exit(-1);
    }

    // Check if the input file can be opened
    ifstream file(argv[1]);
    if (!file) {
        cerr << "Error opening file \"" << argv[1] << "\"." << endl;
        exit(-1);
    }

    string line, aux;
    int game_index, cube_value, sum = 0;

    while (getline(file, line)) {
        map<string, int> cubes = {
            {"red", 0},
            {"green", 0},
            {"blue", 0}
        };

        // Introduction of the line in a stringstream
        stringstream ss;
        ss.str(line);

        // Game
        ss >> aux;

        // Game index
        ss >> game_index;
        ss.get();

        while (ss >> cube_value) { // Cube value
            ss.get();

            // Cube color
            ss >> aux;

            // Remove the comma or semicolon
            if (aux.at(aux.size() - 1) == ',' || aux.at(aux.size() - 1) == ';') {
                aux = aux.substr(0, aux.size() - 1);
            }

            if (cube_value > cubes[aux]) {
                cubes[aux] = cube_value;
            }
        }

        int cube_power = 1;
        for (auto i : cubes) {
            cube_power *= i.second;
        }

        sum += cube_power;
    }

    cout << sum << endl;

    return 0;
}