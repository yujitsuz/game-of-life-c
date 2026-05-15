#include <stdio.h>
#include <string.h>

// Defining if the OS is Windows or not
// Calling Functions for clearing the terminal and doing the sleep
#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define CLEAR() system("cls")
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
    #define CLEAR() printf("\033[H")
#endif

// Define Border Types
#define WRAPPER 1
#define KILLER 2

// Functions
short unsigned int frameRateIO();
short int loopIO();
void matrixTypeIO(int inMatrix[][10]);
unsigned short int borderTypeIO();
void gameOfLifeFunction(int initial[][10], int next[][10], int size,
                        unsigned short int type);

int main() {
    // Initial Matrix and next Gen Matrix
    int initial[10][10] = {0};
    int next[10][10] = {0};

    // Size of general 10x10 Matrix
    int size = (sizeof(initial) / sizeof(initial[0]));

    // Variables
    short int loopsIn;
    unsigned short int frames;
    unsigned int frameTime;

    // Get the Frame Values and then set the amount of time
    frames = frameRateIO();
    frameTime = 1000 / frames;

    // Get the Loop amount
    loopsIn = loopIO();

    // Choose the Matrix Initial Type
    matrixTypeIO(initial);

    // Get the Border Type 1 - Wrapper | 2 - Killer
    unsigned short int type = borderTypeIO();

    // Hides Cursor
    printf("\033[?25l");

    // Check if the loop is infinite or not
    if (loopsIn == -1) {
        while (1) {
            printf("\033[H"); // goes back to terminal top
            gameOfLifeFunction(initial, next, size, type);
            printf("\033[12;0H"); // goes beyond the matrix
            printf("Press CTRL + C to exit...");
            SLEEP(frameTime);
        }
    }
    else {
        // Sets the total amount of loops
        int loopsTotal = frames * loopsIn;
        for (int i = 0; i < loopsTotal; i++) {
            printf("\033[H"); // goes back to terminal top
            printf("Frame: %d\n", i + 1);
            gameOfLifeFunction(initial, next, size, type);
            SLEEP(frameTime);
        }
    }

    // Ends the program
    printf("Finished. Press ENTER to exit...");
    printf("\033[?25h"); // restores the cursor
    setbuf(stdin, NULL);
    getchar();

    return 0;
}

// Function that gets the total framerates
short unsigned int frameRateIO() {
    short unsigned int frames;

    // Asks for Input
    printf("What framerate do you want the program to work (1-60FPS)"
           "\nFPS: ");

    // Input
    do {
        if (scanf("%hu", &frames) != 1 || (frames == 0 || frames > 60)) {
            printf("Please insert a valid Number."
                   "\nFPS: ");
            setbuf(stdin, NULL);
        }
    } while (frames == 0 || frames > 60);

    CLEAR();

    return frames;
}

// Function that gets the total loops values
short int loopIO() {
    short int loopsIn;

    // Asks for Input
    printf("How many loops you want? (1 - 50)"
           "\n(ex: in 2 loops in a 30 fps scenario, will run it 60 times)"
           "\n(Type -1 for infinite, but you will need to close the program manually by CTRL + C or closing the tab)"
           "\nLoops: ");

    // Input
    do {
        if (scanf("%hd", &loopsIn) != 1 || (loopsIn < -1 || loopsIn == 0 || loopsIn > 50)) {
            printf("Please insert a valid Number."
                   "\nLoops: ");
            setbuf(stdin, NULL);
        }
    } while (loopsIn < -1 || loopsIn == 0 || loopsIn > 50);

    CLEAR();

    return loopsIn;
}

// Function that selects the type of the current matrix
void matrixTypeIO(int inMatrix[][10]) {
    unsigned short int optionMatrix = 0;

    // Menu
    printf("Select the Initial Matrix Type"
           "\n1 - Glider"
           "\n2 - BLinker + Blocker"
           "\n\nOption: ");

    // Input
    do {
        if (scanf("%hu", &optionMatrix) != 1 ||
            (optionMatrix != 1 && optionMatrix != 2)) {
            printf("Please insert a valid Number."
                   "\nOption: ");
            setbuf(stdin, NULL);
        }
    } while (optionMatrix != 1 && optionMatrix != 2);

    // Switch for Menu
    switch (optionMatrix) {
    // Glider
    case 1: {
        int tempMatrix[10][10] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, 
            {0, 1, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        // Copies the temp matrix to the one that will be used
        for (int i = 0; i < 10; i++) {
            memcpy(inMatrix[i], tempMatrix[i], 10 * sizeof(int));
        }
        break;
    }
    // Blinker
    case 2: {
        // 
        int tempMatrix[10][10] = {
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 1, 1, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        
        // Copies the temp matrix to the one that will be used
        for (int i = 0; i < 10; i++) {
            memcpy(inMatrix[i], tempMatrix[i], 10 * sizeof(int));
        }
        break;
    } // Blinker Case
    } // Closes the switch

    CLEAR();
} // end of function

// Function that gets the border Type to use
unsigned short int borderTypeIO() {
    unsigned short int optionBorder = 0;

    // Asks the user input
    printf("Select the Type of border Matrix Type"
           "\n1 - Wrap Border"
           "\n2 - Kill at Border"
           "\n\nOption: ");

    // Input
    do {
        if (scanf("%hu", &optionBorder) != 1 ||
            (optionBorder != 1 && optionBorder != 2)) {
            printf("Please insert a valid Number."
                   "\nOption: ");
            setbuf(stdin, NULL);
        }
    } while (optionBorder != 1 && optionBorder != 2);

    CLEAR();

    return optionBorder;
}

// Function that calculates everything in the game of life
void gameOfLifeFunction(int initial[][10], int next[][10], int size, unsigned short int type) {
    // Gets the Adjacents/Neighbours Values
    for (int l = 0; l < 10; l++) {
        for (int c = 0; c < 10; c++) {
            // Declares Sum of Adjacent values
            int sum = 0;
            for (int r = l - 1; r <= l + 1; r++) {
                for (int s = c - 1; s <= c + 1; s++) {
                    int wr = (r + size) % size; // -1 -> 9, 0 -> 1
                    int ws = (s + size) % size;
                    switch (type) {
                    case WRAPPER:
                        // This one is for general cases, makiing the borders "safe"
                        if (!(wr == l && ws == c)) {
                            sum += initial[wr][ws];
                        }
                        break;
                    case KILLER:
                        // This one if for when we want the cell to die
                        if (r >= 0 && r < size && s >= 0 && s < size && !(r == l && s == c)) {
                            sum += initial[r][s];
                        }
                        break;
                    }
                }
            }
            // Checks the value for the next Gen
            switch (initial[l][c]) {
                case 0:
                    next[l][c] = (sum == 3) ? 1 : 0;
                    break;
                case 1:
                    next[l][c] = (sum == 2 || sum == 3) ? 1 : 0;
                    break;
            } // end of sum checking and
        } // end of columns
    } // end of lines

    // Prints out the visual aspect of the Matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            printf("%s", next[i][j] ? "# " : ". ");
        }
        printf("\n");
    }

    // Saves the current value to the initial one of the next gen
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            initial[i][j] = next[i][j];
        }
    }
} // end of function