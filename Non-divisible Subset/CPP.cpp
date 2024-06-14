#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

/*
 * The 'nonDivisibleSubset' function appears below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER k
 *  2. INTEGER_ARRAY s
 */

int nonDivisibleSubset(int k, vector<int> s) {

    // Find all possible sums within the vector whose %k is 0
    vector<pair<int, int>> hits;
    for (int i = 0; i < s.size(); i++) {
        for (int j = i + 1; j < s.size(); j++) {
            if ((s[i] + s[j]) % k == 0) {
                hits.push_back({ s[i], s[j] });
            }
        }
    }

    // Create a frequency map
    unordered_map<int, int> frequencies;
    for (int i = 0; i < hits.size(); i++) {
        pair<int, int> set = hits[i];
        frequencies[set.first]++;
        frequencies[set.second]++;
    }

    // Sort the frequencies
    vector<pair<int, int>> sortedFreqList;
    for (pair<int, int> item : frequencies) {
        sortedFreqList.push_back({item.second, item.first});
    }
    sort(sortedFreqList.begin(), sortedFreqList.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.first > b. first;
    });

    // We don't need to generate all permutations (too slow); we simply need to adjust for probability
    // Get rid of problematic addends from pairs in descending order of frequency
    vector<int> resultSet;
    for (auto freq : sortedFreqList) {
        for (auto addends : hits) {

            // Check blacklist first. If it's on there, we can't add it without making a bad pair.
            bool isBlacklisted = false;
            for (int badNum : resultSet) {
                if (addends.first == badNum || addends.second == badNum) {
                    isBlacklisted = true;
                    break;
                }
            }
            if (isBlacklisted) {
                continue;
            }
            
            // Push the least-common choice
            if (addends.first == freq.second) {
                resultSet.push_back(addends.second);
            } else if (addends.second == freq.second) {
                resultSet.push_back(addends.first);
            }
        }
    }

    // Account for "safe" nums (no additions which %k == 0)
    for (int num : s) {
        for (int i = 0; i < sortedFreqList.size(); i++) {
            int currCheck = sortedFreqList[i].second;
            if (currCheck == num) {
                break;
            }
            if (i + 1 == sortedFreqList.size()) {
                resultSet.push_back(num);
            }
        }
    }

    return resultSet.size();
}

int main() {

    // Assuming input is correct
    string temp;
    cout << "Input size of number array: ";
    cin >> temp;
    cin.clear();
    int n = stoi(temp);

    cout << endl << "Input k: ";
    cin >> temp;
    cin.clear();
    int k = stoi(temp);

    cout << endl << "Input numbers one at a time..." << endl;
    vector<int> s;
    for (int i = 0; i < n; i++) {
        cout << "Number: ";
        cin >> temp;
        cin.clear();
        s.push_back(stoi(temp));
    }

    int result = nonDivisibleSubset(k, s);
    cout << endl << "Max non-divisible subset size: " << result << endl;
    system("pause");
    
    /*
    int n = 7;
    int k = 4;
    vector<int> s = { 19, 10, 12, 10, 24, 25, 22 };
    */

    return 0;
}