#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int char_to_int(char c) {
    return c - '0';
}

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
    
    string line;
    int sum = 0;

    while (getline(file, line)) {
        int n = 0;
        bool first_digit = true;
        char digit1, digit2;

        for (unsigned int i=0; i<line.size(); i++) {
            if (first_digit && isdigit(line.at(i))) {
                digit1 = line.at(i);
                digit2 = line.at(i);
                first_digit = false;
            }
            else if (isdigit(line.at(i))) {
                digit2 = line.at(i);
            }
        }

        sum += char_to_int(digit1)*10 + char_to_int(digit2);
    }

    cout << sum << endl;

    file.close();

    return 0;
}