#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

int main() {
    string ciphertext;
    const double ENGLISH_IC = 0.0667;

    // Read input from the user and remove spaces
    cout << "Enter the ciphertext: ";
    getline(cin, ciphertext);
    ciphertext.erase(remove_if(ciphertext.begin(), ciphertext.end(), ::isspace), ciphertext.end());

    // Convert all characters to uppercase
    transform(ciphertext.begin(), ciphertext.end(), ciphertext.begin(), ::toupper);

    // Calculate the index of coincidence
    double ciphertext_length = ciphertext.length();
    unordered_map<char, double> observed_frequency;
    for (char c : ciphertext) {
        if (observed_frequency.count(c) == 0) {
            observed_frequency[c] = 1.0;
        }
        else {
            observed_frequency[c]++;
        }
    }
    double ic = 0;
    for (auto it = observed_frequency.begin(); it != observed_frequency.end(); ++it) {
        double frequency = it->second / ciphertext_length;
        ic += frequency * (frequency - 1);
    }
    cout << "The index of coincidence is: " << ic << endl;

    // Calculate the key period
    vector<double> ics;
    for (int period = 1; period <= 20; period++) {
        vector<unordered_map<char, double>> frequency_tables(period);
        for (int i = 0; i < ciphertext_length; i++) {
            char c = ciphertext[i];
            int table_index = i % period;
            if (frequency_tables[table_index].count(c) == 0) {
                frequency_tables[table_index][c] = 1.0;
            }
            else {
                frequency_tables[table_index][c]++;
            }
        }
        double average_ic = 0;
        for (auto table : frequency_tables) {
            double table_length = 0;
            double table_ic = 0;
            for (auto it = table.begin(); it != table.end(); ++it) {
                double frequency = it->second;
                table_length += frequency;
                table_ic += frequency * (frequency - 1);
            }
            table_ic /= (table_length * (table_length - 1));
            average_ic += table_ic;
        }
        average_ic /= period;
        ics.push_back(average_ic);
    }
    auto max_ic_it = max_element(ics.begin(), ics.end());
    int max_ic_period = distance(ics.begin(), max_ic_it) + 1;
    cout << "The key period is most likely " << max_ic_period << "." << endl;

    return 0;
}
