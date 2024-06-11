#include <iostream>
#include <vector>
#include <string>

using namespace std;

/*
 * The 'extraLongFactorials' function appears below.
 * The function accepts INTEGER n as parameter.
 */

void extraLongFactorials(int n) {

    string result = to_string(n);
    for (int currNum = n - 1; currNum > 0; currNum--) {
        // Gather numbers
        string num1 = result;
        string num2 = to_string(currNum);
        vector<vector<int>> products(num2.size(), vector<int>(num1.size(), 0));

        // Pass 1: Generate products, ignoring carries
        for (int i = 0; i < num2.size(); i++) {
            for (int j = 0; j < num1.size(); j++) {
                products[i][j] += (num1[j] - '0') * (num2[i] - '0');
            }
        }

        // Pass 2: Generate products accounting for carries
        // We do "num1.size() + 1" to account for the potential carry place
        vector<vector<int>> carriedProducts(num2.size(), vector<int>(num1.size() + 1, 0));
        for (int i = products.size() - 1; i >= 0; i--) {

            // Init carry to zero
            char addend = '0';
            for (int j = products[i].size() - 1; j >= 0; j--) {
                string product = to_string(products[i][j]);

                // Handle potential carry
                int carrySum = (addend - '0') + stoi(product);
                string carrySumString = to_string(carrySum);
                if (carrySum > 9) {
                    carriedProducts[i][j + 1] += carrySum % 10;
                } else {
                    // Store non-carry digit(s)
                    carriedProducts[i][j + 1] += carrySum;
                }

                // Account for final carry
                if (j == 0 && (carrySumString.size() > 1)) {
                    carriedProducts[i][j] += (carrySumString[0] - '0');
                }

                // Store the potential carry
                if (carrySumString.size() > 1) {
                    addend = carrySumString[0];
                } else {
                    addend = '0';
                }
            }
        }

        // Pass 3: Shift numbers to prepare for final addition
        // We do "num1.size() + num2.size()" to account for the shifting places (added zeros) in tabular multiplication
        vector<vector<int>> shiftedCarriedProducts(num2.size(), vector<int>(num1.size() + num2.size(), 0));
        for (int i = 0; i < carriedProducts.size(); i++) {

            // Add zeros to left
            int startPos = 0;
            for (int beginZeros = i; beginZeros > 0; beginZeros--) {
                startPos++;
            }

            // Add product's numbers
            for (int j = 0; j < carriedProducts[i].size(); j++) {
                shiftedCarriedProducts[i][j + startPos] = carriedProducts[i][j];
            }
        }

        // Pass 4: Add products, ignoring carries
        vector<int> addedCarriedProducts(num1.size() + num2.size(), 0);
        for (int i = 0; i < addedCarriedProducts.size(); i++) {

            int sum = 0;
            for (int j = 0; j < shiftedCarriedProducts.size(); j++) {
                sum += shiftedCarriedProducts[j][i];
            }
            addedCarriedProducts[i] = sum;
        }

        // Pass 5: Add products, accounting for carries
        vector<int> finalProduct(num1.size() + num2.size(), 0);
        char addend = '0';
        for (int i = addedCarriedProducts.size() - 1; i >= 0; i--) {
            string sum = to_string(addedCarriedProducts[i]);

            // Handle potential carry
            int carrySum = (addend - '0') + stoi(sum);
            string carrySumString = to_string(carrySum);
            if (carrySum > 9) {
                finalProduct[i] += carrySum % 10;
            } else {
                // Store non-carry digit(s)
                finalProduct[i] += carrySum;
            }

            // Store the potential carry
            if (carrySumString.size() > 1) {
                addend = carrySumString[0];
            } else {
                addend = '0';
            }
        }

        // Update result, removing leading zeros
        result.clear();
        bool isLeadingZero = true;
        for (int i = 0; i < finalProduct.size(); i++) {
            char num = to_string(finalProduct[i])[0];
            if (num != '0' && isLeadingZero) {
                isLeadingZero = false;
            }
            if (!isLeadingZero) {
                result.push_back(num);
            }
        }
    }

    // Print result to terminal
    std::cout << n << "! = " << result << endl;
}

int main() {
    string num;

    cout << "Input a number: ";
    cin >> num;
    
    // Validate number
    for (int i = 0; i < num.size(); i++) {
        if (!isdigit(num[i])) {
            cout << endl << "Input a number: ";
            cin >> num;
            i = -1;
        } 
    }
    
    int n = stoi(num);
    extraLongFactorials(n);

    return 0;
}
