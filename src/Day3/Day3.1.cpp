#include <iostream>
#include <fstream>
#include <vector>

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
    vector<string> input;
    string line;
    int sum = 0, current_number;
    bool valid_number = false;

    while (getline(file, line)) {
        input.push_back(line);
    }

    // Rows
    for (int i=0; (unsigned int)i<input.size(); ++i) {
        // Columns
        int j = 0;
        while (j < input[i].size()) {
            valid_number = false;
            current_number = 0;
            // Go to the next number
            while (j<input[i].size() && !isdigit(input[i][j])) {
                ++j;
            }

            // Check if the number is valid
            while (j<input[i].size() && isdigit(input[i][j])) {
                current_number = current_number*10 + (input[i][j] - '0');
                for (int k=i-1; !valid_number && k<=i+1; ++k) {
                    for (int l=j-1; !valid_number && l<=j+1; ++l) {
                        if (!valid_number && k >= 0 && k < input.size() && l >= 0 && l < input[i].size()) {
                            valid_number = !isdigit(input[k][l]) && input[k][l] != '.';
                        }
                    }
                }
                
                ++j;
            }

            if (valid_number) {
                sum += current_number;
            }
        }
    }

    cout << sum << endl;

    return 0;
}