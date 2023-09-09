#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



#define NOT 0
#define ORIGIN 1
#define DYING 2
#define LIFE 3


#define LENGTH 201
#define WIDTH 51


int **initMatrix();
void addLife(int **matrix);
int generations(int **matrix);
int getNeighborsCount(int **matrix, int y, int x);
void drawMatrix(int **matrix);
void drawLine();
void synchronizeBorders(int **matrix);



int main() {

    int **matrix = initMatrix();



    if (matrix != NULL) {
        addLife(matrix);
        drawMatrix(matrix);

        int count = 1;

        while (count) {
            synchronizeBorders(matrix);
            count = generations(matrix);
            drawMatrix(matrix);

            usleep(100000);
        }
        free(matrix);
    }
    return 0;
}

int **initMatrix() {

    int **matrix = (int **)calloc((WIDTH + 3) * (LENGTH + 2), sizeof(int));
    int *pointer = (int *)(matrix + WIDTH + 2);

    for (int i = 0; i < WIDTH + 2; i++) {
        matrix[i] = pointer + i * (LENGTH + 2);
    }
    return matrix;
}

void addLife(int **matrix) {

    for (int inputCount = 2; inputCount == 2;) {
        int x;
        int y;
        inputCount = scanf("%d%d", &y, &x);
        if (inputCount >= 2 && y >= 1 && y <= WIDTH && x >= 1 && x <= LENGTH) {
            matrix[y][x] = LIFE;
        }
    }
}



int generations(int **matrix) {

    int count = 0;
    for (int y = 1; y <= WIDTH; y++) {
        for (int x = 1; x <= LENGTH; x++) {
            int neighborsCount = getNeighborsCount(matrix, y, x);

            if (matrix[y][x] == NOT && neighborsCount == 3) {
                matrix[y][x] = ORIGIN;
                count++;
            }

            if (matrix[y][x] == LIFE && (neighborsCount < 2 || neighborsCount > 3)) {
                matrix[y][x] = DYING;
                count++;
            }
        }
    }
    return count;
}

int getNeighborsCount(int **matrix, int y, int x) {

    int count = matrix[y][x] == NOT ? 0 : -1;
    for (int i = y - 1; i <= y + 1; i++) {
        for (int j = x - 1; j <= x + 1; j++) {
            if (matrix[i][j] == DYING || matrix[i][j] == LIFE) {
                count++;
            }
        }
    }
    return count;
}



void drawMatrix(int **matrix) {

    int x, y;
    printf("\033[H\033[J");
    drawLine();

    for (y = 1; y <= WIDTH; y++) {
        printf("|");
        for (x = 1; x <= LENGTH; x++) {
            if (matrix[y][x] == ORIGIN) {
                matrix[y][x] = LIFE;
            }


            if (matrix[y][x] == DYING) {
                matrix[y][x] = NOT;
            }

            if (matrix[y][x] == LIFE) {
                printf("O");
            } else {

                printf(" ");

            }
        } 
        printf("|\n");
    }
    drawLine();
}



void drawLine() {

    for (int i = 0; i <= LENGTH + 1; i++) {
        printf("=");
    }
    printf("\n");
}



void synchronizeBorders(int **matrix) {

    for (int y = 1; y <= WIDTH; y++) {
        matrix[y][0] = matrix[y][LENGTH];
        matrix[y][LENGTH + 1] = matrix[y][1];
    }

    for (int x = 1; x <= LENGTH; x++) {
        matrix[0][x] = matrix[WIDTH][x];
        matrix[WIDTH + 1][x] = matrix[1][x];

    }

    matrix[0][0] = matrix[WIDTH][LENGTH];
    matrix[0][LENGTH + 1] = matrix[WIDTH][1];
    matrix[WIDTH + 1][0] = matrix[1][LENGTH];
    matrix[WIDTH + 1][LENGTH + 1] = matrix[1][1];
}