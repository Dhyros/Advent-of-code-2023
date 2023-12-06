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

    map<string, int> max_cubes = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}
    };
    string line, aux;
    int game_index, cube_value, sum = 0;
    bool possible_game;

    while (getline(file, line)) {
        possible_game = true;

        // Introduction of the line in a stringstream
        stringstream ss;
        ss.str(line);

        // Game
        ss >> aux;

        // Game index
        ss >> game_index;
        ss.get();

        while (possible_game && ss >> cube_value) { // Cube value
            ss.get();

            // Cube color
            ss >> aux;

            // Remove the comma or semicolon
            if (aux.at(aux.size() - 1) == ',' || aux.at(aux.size() - 1) == ';') {
                aux = aux.substr(0, aux.size() - 1);
            }

            // Check if the cube value is greater than the maximum allowed
            if (cube_value > max_cubes[aux]) {
                possible_game = false;
            }
        }

        if (possible_game) {
            sum += game_index;
        }
    }

    cout << sum << endl;

    return 0;
}