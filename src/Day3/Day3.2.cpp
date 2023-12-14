#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int ExtractNumber(const string str, int pos) {
    int begin = pos, end = pos;
    while (begin >= 0 && isdigit(str[begin])) {
        --begin;
    }
    ++begin;

    while (end < str.size() && isdigit(str[end])) {
        ++end;
    }
    --end;

    return stoi(str.substr(begin, end-begin+1));
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
    vector<string> input;
    string line;
    vector<int> pos_numbers;
    int sum = 0;

    while (getline(file, line)) {
        input.push_back(line);
    }

    // Rows
    for (int i=0; (unsigned int)i<input.size(); ++i) {
        // Columns
        int j = input[i].find('*');
        while (j != string::npos) {
            pos_numbers.clear();

            // Store all the numbers around the character '*'
            char last_char = '.';
            for (int k=i-1; k<=i+1; ++k) {
                for (int l=j-1; l<=j+1; ++l) {
                    if (k>=0 && k<input.size() && l>=0 && l<=input.size()) {
                        if (((last_char=='.' || last_char=='*') && isdigit(input[k][l])) ||
                            (isdigit(last_char) && l==j-1 && isdigit(input[k][l]))) {
                                pos_numbers.push_back(ExtractNumber(input[k], l));
                        }
                    }
                    last_char = input[k][l];
                }
            }

            if (pos_numbers.size() == 2) {
                sum += pos_numbers[0] * pos_numbers[1];
            }

            j = input[i].find('*', j+1);
        }
    }

    cout << sum << endl;

    return 0;
}