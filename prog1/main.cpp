/* 
 * Name: Bryan Stamey
 * File: main.cpp
 * Instructor: Douglas and Karki
 * Class and section: cs4103.01
 * LogonID: cs410373
 *
 * Instructions for how to compile & execute this program:
 * 
 * 
 */

#include <cstdlib>
#include <stdio.h>
#include <pthread.h>

using namespace std;

#define M 4
#define N 3
#define NUM_THREADS 12

int P [M][N] = { {1,4,7}, {6,5,2}, {3,7,0}, {8,1,9} };
int Q [N][M] = { {2,4,7,6}, {5,6,3,3}, {4,0,9,8} };
int R [M][M]; /* result array */

struct Matrix {
    int i;
    int j;
};

void *runner(void *param);
void printMatrix();

int main(int argc, char** argv) {
    
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            // Assign row and column to each thread
            Matrix* data = new Matrix;
            data->i = i;
            data->j = j;
            pthread_t tid;
            pthread_attr_t attr;
            pthread_attr_init(&attr);
            pthread_create(&tid,&attr,runner,data);
            pthread_join(tid,NULL);
        }
    }

    printMatrix();
    
    return 0;
}

void *runner(void *param) {
    Matrix* data = (struct Matrix*)param;
    int n, sum = 0;
    
    for (n = 0; n < M; n++)
        sum += P[data->i][n] * Q[n][data->j];
    
    // Assign sum to resulting coordinate
    R[data->i][data->j] = sum;
    
    pthread_exit(0);
}

void printMatrix() {
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            printf("%d ", R[i][j]);
        }
        printf("\n");
    }
}