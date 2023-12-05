#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

vector<int> find_all_occurences(const string & str, const string & substr) {
    vector<int> positions;
    int pos = str.find(substr);

    while (pos != string::npos) {
        positions.push_back(pos);
        pos = str.find(substr, pos+1);
    }

    return positions;
}

string min_value(const map<string, vector<int>> & numbers_pos) {
    string min;
    int min_val = -1;
    for (auto i : numbers_pos) {
        int n = *min_element(i.second.begin(), i.second.end());
        if (min_val == -1 || n < min_val) {
            min_val = n;
            min = i.first;
        }
    }

    return min;
}

string max_value(const map<string, vector<int>> & numbers_pos) {
    string max;
    int max_val = -1;
    for (auto i : numbers_pos) {
        int n = *max_element(i.second.begin(), i.second.end());
        if (max_val == -1 || n > max_val) {
            max_val = n;
            max = i.first;
        }
    }

    return max;
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
    vector<string> numbers = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", 
                              "0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    // map that stores the positions of each number in the line
    map<string, vector<int>> numbers_pos;

    // Calculate the sum of the digits
    while (getline(file, line)) {
        numbers_pos.clear();

        for (unsigned int i=0; i<numbers.size(); i++) {
            vector<int> positions_string = find_all_occurences(line, numbers.at(i));
            if (!positions_string.empty()) {
                numbers_pos[numbers.at(i)] = positions_string;
            }
        }
        int digit1 = (find(numbers.begin(), numbers.end(), min_value(numbers_pos)) - numbers.begin()) % 10;
        int digit2 = (find(numbers.begin(), numbers.end(), max_value(numbers_pos)) - numbers.begin()) % 10;

        sum += digit1*10 + digit2;
    }

    cout << sum << endl;

    return 0;
}