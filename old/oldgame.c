#include <stdio.h>

void reduzaLinhasImediatamente(int matriz[][10], int argX, int argY, unsigned int intervalX, unsigned int intervalY);

int main() {
    int totalLives = 0;
    int totalDeaths = 0;
    unsigned int i = 0;
    unsigned int j = 0;

    int initial[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 3, 4},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 5, 4}
    };

    unsigned int initialSize = sizeof(initial) / sizeof(initial[0]);

    unsigned int borda = initialSize - 1;

        // Top-left
    reduzaLinhasImediatamente(initial, 0, 0, 2, 2);

    // Top-right
    reduzaLinhasImediatamente(initial, 0, borda - 1, 2, initialSize);

    // Bottom-left
    reduzaLinhasImediatamente(initial, borda - 1, 0, initialSize, 2);

    // Bottom-right
    reduzaLinhasImediatamente(initial, borda - 1, borda - 1, initialSize, initialSize);

    printf("\n");

    for(unsigned int i = 0; i < 10; i++) {
        for(unsigned int j = 0; j < 10; j++) {
            if (initial[i][j] == 0) {
                printf(". ");
                totalLives++;
            } else {
                printf("# ");
                totalDeaths++;
            }
        }
        printf("\n");
    }
    return 0;    
}

void reduzaLinhasImediatamente(int matriz[][10], int argX, int argY, unsigned int intervalX, unsigned int intervalY) {
    int sub[2][2];
    int si = 0; // variavel sub inicial x (Divide para não causar problemas)
    for (int x = argX; x < intervalX; x++) {
        int sj = 0;// variavel sub inicial y 
        for (int y = argY; y < intervalY; y++) {
            sub[si][sj] = matriz[x][y];  
            sj++;
        }
        si++;
    }

    // Print Sub
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 2; y++) {
            printf("%4d ", sub[x][y]);
        }
        printf("\n");
    }
}