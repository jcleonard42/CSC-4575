#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    string input;
    unordered_map<char, int> frequency;

    // Read input from the user
    cout << "Enter a string: ";
    getline(cin, input);

    // Calculate the frequency of each character in the input string
    for (char c : input) {
        if (frequency.count(c) == 0) {
            frequency[c] = 1;
        }
        else {
            frequency[c]++;
        }
    }

    // Compute the correlation of frequency
    double correlation = 0;
    int n = input.length();
    for (auto it = frequency.begin(); it != frequency.end(); ++it) {
        int count = it->second;
        correlation += (double)count * (count - 1) / (n * (n - 1));
    }

    // Output the result
    cout << "The correlation of frequency is: " << correlation << endl;

    return 0;
}