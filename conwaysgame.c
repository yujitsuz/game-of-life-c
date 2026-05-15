#include <stdio.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define SLEEP(ms) Sleep(ms)
    #define CLEAR() system("cls")
#else
    #include <unistd.h>
    #define SLEEP(ms) usleep((ms) * 1000)
    #define CLEAR() printf("\033[H")
#endif

short unsigned int frameRateIO();
short int loopIO();
void matrixTypeIO(int inMatrix[][10]);
void gameOfLifeFunction(int initial[][10], int next[][10], int size);



int main() {
    // Initial Matrix and next Gen Matrix
    int initial[10][10] = {0};
    int next[10][10] = {0};

    // Size of general 10x10 Matrix
    int size = (sizeof(initial) / sizeof(initial[0]));

    short int loopsIn;
    unsigned short int frames;
    unsigned int frameTime;

    // Get the Frame Values and then set the amount of time 
    frames = frameRateIO();
    frameTime = 1000 / frames;

    // Get the Loop amount
    loopsIn = loopIO();

    // Choose the Matrix Type
    matrixTypeIO(initial);

    printf("\033[?25l"); // Hides Cursor
    
    if (loopsIn == -1) {
        while(1) {
            printf("\033[H"); // goes back to terminal top
            gameOfLifeFunction(initial, next, size);
            printf("\033[12;0H"); // Vai até a linha 12 coluna 0 do terminal
            printf("Press CTRL + C to exit...");
            SLEEP(frameTime);
        }
    }else {
        // Sets the total amount of loops
        int loopsTotal = frames * loopsIn;
        for (int i = 0; i < loopsTotal; i++) {
            printf("\033[H"); // goes back to terminal top
            printf("Frame: %d\n", i + 1);
            gameOfLifeFunction(initial, next, size);
            SLEEP(frameTime);
        }
    }

    printf("Finished. Press ENTER to exit...");
    printf("\033[?25h"); // restores the cursor
    setbuf(stdin, NULL);
    getchar();

    return 0;
}

// Function that gets the total framerates
short unsigned int frameRateIO() {
    short unsigned int frames;
    printf("What framerate do you want the program to work (1-60FPS)\nFPS: ");
    do {
        if (scanf("%hu", &frames) != 1 || frames > 60) {
            printf("Please insert a valid Number.\nFPS: ");
            setbuf(stdin, NULL);
        }
    }while (frames > 60);

    CLEAR();

    return frames;
}

// Function that gets the total loops values
short int loopIO() {
    short int loopsIn;
    printf("How many loops you want? (1 - 50)");
    printf("(ex: in 2 loops in a 30 fps scenario, will run it 60 times)\n");
    printf("(Type -1 for infinite, but you will need to close the program Manually byt CTRL + C or closing the tab)\nLoops: ");
    do {
        if (scanf("%hd", &loopsIn) != 1) {
            setbuf(stdin, NULL);
        }
        if ((loopsIn <= 0 || loopsIn > 50) && loopsIn != -1) {
            printf("Please insert a valid Number.\nLoops: ");
        }
    }while ((loopsIn <= 0 || loopsIn > 50) && loopsIn != -1);

    CLEAR();

    return loopsIn;
}

// Function that selects the type of the current matrix
void matrixTypeIO(int inMatrix[][10]) {
    int optionMatrix = 0;

    printf("Select the Initial Matrix Type\n");
    printf("1 - Glider\n2 - BLinker + Blocker\n\nOption: ");
    do {
        if (scanf("%d", &optionMatrix) != 1) {
            setbuf(stdin, NULL);
        }
        if (optionMatrix != 1 && optionMatrix != 2) {
            printf("Please insert a valid Number.\nOption: ");
        }
    }while (optionMatrix != 1 && optionMatrix != 2);
    
    switch (optionMatrix) {
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
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            };
            for (int i = 0; i < 10; i++) {
                memcpy(inMatrix[i], tempMatrix[i], 10 * sizeof(int));
            }
            break;
        }
        case 2: {
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
                {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
            };
            for (int i = 0; i < 10; i++) {
                memcpy(inMatrix[i], tempMatrix[i], 10 * sizeof(int));
            }
            break;
        }
    }
    CLEAR();
}

// Function that calculates everything in the game of life
void gameOfLifeFunction(int initial[][10], int next[][10], int size) {
    // Gets the Adjacents/Neighbours Values
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Declares Sum of Adjacent values
            int sum = 0; 
            for (int r = i - 1; r <= i + 1; r++) {
                for (int s = j - 1; s <= j + 1; s++) {
                // This one if for when we want the cell to die
                    /*if (r >= 0 && r < size && s >= 0 && s < size && !(r == i && s == j)) {
                        sum += initial[r][s]; 
                    }*/
                // This one is for general cases, makiing the borders "safe"
                    int wr = (r + size) % size; // -1 -> 9, 0 -> 1
                    int ws = (s + size) % size;
                    if (!(wr == i && ws == j)) {
                        sum += initial[wr][ws]; 
                    }
                }        
            }
            // Checks the value for the next Gen
            switch (initial[i][j]) {
                case 0:
                    next[i][j] = (sum == 3) ? 1:0;
                    break;
                case 1:
                    next[i][j] = (sum == 2 || sum == 3) ? 1:0;
                    break;
            } 
        }
    }
    
    // Prints out the visual aspect of the Matrix
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (next[i][j] == 0) {
                printf(". ");
            } else {
                printf("# ");
            }
        }
        printf("\n");
    }

    // Saves the current value to the initial one of the next gen
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            initial[i][j] = next[i][j];
        }
    }
}