#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void printSpaces(const int maxSpaceSize, const int num) {
    int numSize = (num == 0) ? 1 : floor(log10(abs(num))) + 1;
    int numSpaces = maxSpaceSize - numSize;
    for (int k = 0; k < numSpaces; k++) {
        printf(" ");
    }
}

int main() {

    int n = NULL;
    if (!isdigit(n)) {
        printf("Enter a digit: ");
        scanf("%d", &n);
    }

    // Find the size of the largest digit + the necessaary space following it (for printing)
    const int maxSpaceSize = ((n == 0) ? 1 : floor(log10(abs(n))) + 1) + 1;

    // Store the first half in an array
    const int width = (n * 2) - 1;
    const int height = n - 1;
    int numArray[height][width];

    // We don't need to work on the entire array; just mirror the top of it in printing
    for (int i = 0; i < height; i++) {

        // Constant outside edges
        numArray[i][0] = n;
        numArray[i][width - 1] = n;

        // Iterate down to middle of line
        int currNum = n;
        int currPos = 1;
        for (currPos; currPos <= i; currPos++) {
            currNum = n - currPos;
            numArray[i][currPos] = currNum;
            numArray[i][width - 1 - currPos] = currNum;
        }

        // Fill middle with the repeating number
        int middleSize = width - ((i + 1) * 2);
        for (int j = 0; j < middleSize; j++) {
            numArray[i][currPos++] = currNum;
        }
    }

    // Print the upper array
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int num = numArray[i][j];
            printf("%d", num);
            printSpaces(maxSpaceSize, num);
        }
        printf("\n");
    }

    // Print the middle line
    for (int i = n; i > 1; i--) {
        printf("%d", i);
        printSpaces(maxSpaceSize, i);
    }
    for (int i = 1; i <= n; i++) {
        printf("%d", i);
        printSpaces(maxSpaceSize, i);
    }
    printf("\n");

    // Print the lowwer array mirroring the upper array
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            int num = numArray[i][j];
            printf("%d", num);
            printSpaces(maxSpaceSize, num);
        }
        printf("\n");
    }

    system("pause");
    return 0;
}