#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void getMatrixSize(const char *filename, const char *sectionName, int *rows, int *columns) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Khong the mo file %s\n", filename);
        exit(1);
    }

    char line[1024];
    *rows = 0;
    *columns = 0;
    int foundSection = 0; 

    while (fgets(line, sizeof(line), f)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;
        if (strstr(line, sectionName) != NULL) {
            foundSection = 1;
            continue; 
        }
        if (foundSection) {

            if ((line[0] >= '0' && line[0] <= '9') || line[0] == '-' || line[0] == '+') {
                (*rows)++;
                if (*rows == 1) {
                    int count = 1;
                    for (int i = 0; line[i] != '\0'; i++) {
                        if (line[i] == ',') count++;
                    }
                    *columns = count;
                }
            } else {
                break;
            }
        }
    }
    fclose(f);
}

float **readCSV(const char *filename, const char *sectionName, int rows, int columns) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        printf("Khong the mo file %s\n", filename);
        exit(1);
    }

    float **matrix = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++)
        matrix[i] = (float *)malloc(columns * sizeof(float));

    char line[1024];
    int foundSection = 0;
    int r = 0;

    while (fgets(line, sizeof(line), f) && r < rows) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0) continue;

        if (strstr(line, sectionName) != NULL) {
            foundSection = 1;
            continue;
        }

        if (foundSection) {
             if ((line[0] >= '0' && line[0] <= '9') || line[0] == '-' || line[0] == '+') {
                 char *token = strtok(line, ",");
                 int c = 0;
                 while(token != NULL && c < columns) {
                     matrix[r][c] = atof(token);
                     token = strtok(NULL, ",");
                     c++;
                 }
                 r++;
             } else {
                 break;
             }
        }
    }

    fclose(f);
    return matrix;
}

int checkAddPossible(int r1, int c1, int r2, int c2) {
    return (r1 == r2 && c1 == c2);
}

float **sumMatrix(float **A, float **B, int rows, int columns) {
    float **C = (float **)malloc(rows * sizeof(float *));
    for (int i = 0; i < rows; i++)
        C[i] = (float *)malloc(columns * sizeof(float));

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
            C[i][j] = A[i][j] + B[i][j];

    return C;
}

int checkMultiplyPossible(int r1, int c1, int r2, int c2) {
    return (c1 == r2);
}

float **multiplyMatrix(float **A, float **B, int r1, int c1, int r2, int c2) {
    float **C = (float **)malloc(r1 * sizeof(float *));
    for (int i = 0; i < r1; i++)
        C[i] = (float *)malloc(c2 * sizeof(float));

    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            float sum = 0;
            for (int k = 0; k < c1; k++) {
                sum += A[i][k] * B[k][j];
            }
            C[i][j] = sum;
        }
    }
    return C;
}

void printMatrix(float **a, int rows, int columns) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
            printf("%.2f ", a[i][j]);
        printf("\n");
    }
}

void freeMatrix(float **a, int rows) {
    for (int i = 0; i < rows; i++)
        free(a[i]);
    free(a);
}

int main() {
    int r1, c1, r2, c2;
    const char *filename = "Book1.csv"; 

    getMatrixSize(filename, "matran1", &r1, &c1);
    float **A = readCSV(filename, "matran1", r1, c1);
    printf("Ma tran A (%dx%d):\n", r1, c1);
    printMatrix(A, r1, c1);

    getMatrixSize(filename, "matran2", &r2, &c2);
    float **B = readCSV(filename, "matran2", r2, c2);
    printf("Ma tran B (%dx%d):\n", r2, c2);
    printMatrix(B, r2, c2);

    if (checkAddPossible(r1, c1, r2, c2)) {
        printf("Phep cong ton tai. Ket qua A + B:\n");
        float **S = sumMatrix(A, B, r1, c1);
        printMatrix(S, r1, c1);
        freeMatrix(S, r1);
    } else {
        printf("Phep cong khong ton tai (kich thuoc khong khop).\n");
    }

    if (checkMultiplyPossible(r1, c1, r2, c2)) {
        printf("Phep nhan ton tai. Ket qua A * B:\n");
        float **P = multiplyMatrix(A, B, r1, c1, r2, c2);
        printMatrix(P, r1, c2);
        freeMatrix(P, r1);
    } else {
        printf("Phep nhan KHONG ton tai (so cot A khac so dong B).\n");
    }

    freeMatrix(A, r1);
    freeMatrix(B, r2);

    return 0;
}