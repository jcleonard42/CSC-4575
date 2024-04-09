#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    string ciphertext;
    unordered_map<char, double> expected_frequency = {
        {'A', 0.08167}, {'B', 0.01492}, {'C', 0.02782}, {'D', 0.04253}, {'E', 0.12702},
        {'F', 0.02228}, {'G', 0.02015}, {'H', 0.06094}, {'I', 0.06966}, {'J', 0.00153},
        {'K', 0.00772}, {'L', 0.04025}, {'M', 0.02406}, {'N', 0.06749}, {'O', 0.07507},
        {'P', 0.01929}, {'Q', 0.00095}, {'R', 0.05987}, {'S', 0.06327}, {'T', 0.09056},
        {'U', 0.02758}, {'V', 0.00978}, {'W', 0.0236}, {'X', 0.0015}, {'Y', 0.01974},
        {'Z', 0.00074}
    };

    // Read input from the user and remove spaces
    cout << "Enter the ciphertext: ";
    getline(cin, ciphertext);
    ciphertext.erase(remove_if(ciphertext.begin(), ciphertext.end(), ::isspace), ciphertext.end());

    // Convert all characters to uppercase
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);

    // Calculate the frequency of each character in the ciphertext
    unordered_map<char, double> observed_frequency;
    for (char c : ciphertext) {
        if (observed_frequency.count(c) == 0) {
            observed_frequency[c] = 1.0;
        }
        else {
            observed_frequency[c]++;
        }
    }
    for (auto it = observed_frequency.begin(); it != observed_frequency.end(); ++it) {
        it->second /= ciphertext.length();
    }

    // Calculate the correlation of frequency
    double correlation = 0;
    for (auto it = expected_frequency.begin(); it != expected_frequency.end(); ++it) {
        char c = it->first;
        if (observed_frequency.count(c) > 0) {
            double observed_prob = observed_frequency[c];
            double expected_prob = it->second;
            correlation += observed_prob * expected_prob;
        }
    }
    correlation = round(correlation * 10000) / 10000;  // Round to four decimal places

    cout << "The correlation of frequency is: " << correlation << endl;

    return 0;
}
