
#include <iostream>
#include <omp.h>
#include <vector>
#include <cstdlib>//for random numbers
#include <chrono>

using namespace std;

//Matrix size
// int N = 1024;  

//Function for normal (naive) matrix multiplication (single-core, no OpenMP)
void matrixMultiplyNaive(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int N){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            int sum1 = 0;
            for (int k = 0; k < N; k++){
                sum1 += A[i][k] * B[k][j];
            }
            C[i][j] = sum1;
        }
    }
}

//Function for blocked matrix multiplication (multi-core using OpenMP)
void matrixMultiplyBlocked(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C, int num_threads, int N){
    
    //Calculate block size based on number of threads
    int blockSize = N / num_threads;
    //Ensure block size is at least 1  
    blockSize = (blockSize < 1) ? 1 : blockSize; 

    #pragma omp parallel num_threads(num_threads)
    {
        int thread_id = omp_get_thread_num();
        //Parallelizing the i and j loops
        #pragma omp for collapse(2)  
        for (int i = 0; i < N; i += blockSize){
            for (int j = 0; j < N; j += blockSize){
                for (int k = 0; k < N; k += blockSize){
                    for (int row = i; row < min(i + blockSize, N); row++){
                        for (int col = j; col < min(j + blockSize, N); col++){
                            int sum1 = 0;
                            for (int k1 = k; k1 < min(k + blockSize, N); k1++){
                                sum1 += A[row][k1] * B[k1][col];
                            }
                            C[row][col] += sum1;
                        }
                    }
                }
                // Print the thread ID handling this block (i, j)
                // #pragma omp critical
                // {
                //     cout << "Thread " << thread_id << " is working on block (" << i << ", " << j << ")" << endl;
                // }
            }
        }
    }
}

//Function to print a matrix (for debugging or visualization)
void printMatrix(const vector<vector<int>> &matrix, const string &name, int N){
    cout << "Matrix: " << name << endl;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int main() {
    

    

    //Measure time for blocked matrix multiplication (multi-core using OpenMP)
    for(int N : {10, 50, 100, 500}){

        //Initialize matrices A, B, and C
        vector<vector<int>> A(N, vector<int>(N));
        vector<vector<int>> B(N, vector<int>(N));
        vector<vector<int>> C_naive(N, vector<int>(N, 0));
        vector<vector<int>> C_blocked(N, vector<int>(N, 0));

        

        //Fill matrices A and B with random integers
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                A[i][j] = rand() % 10; 
                B[i][j] = rand() % 10;
            }
        }

        cout << "For " << N << "x" << N << " matrix:" << endl;

        //Measure time for naive matrix multiplication (single-core)
        auto start_naive = chrono::high_resolution_clock::now();
        matrixMultiplyNaive(A, B, C_naive, N);
        auto end_naive = chrono::high_resolution_clock::now();
        chrono::duration<double> duration_naive = end_naive - start_naive;
        cout << "Time taken for sequential matrix multiplication: " << duration_naive.count() << " seconds" << endl;


        for (int num_threads : {1, 2, 4, 8}) {
            auto start_blocked = chrono::high_resolution_clock::now();
            matrixMultiplyBlocked(A, B, C_blocked, num_threads, N);
            auto end_blocked = chrono::high_resolution_clock::now();
            chrono::duration<double> duration_blocked = end_blocked - start_blocked;
            cout << "Time taken for matrix multiplication: " << duration_blocked.count() << " seconds using " << num_threads << " core(s)" << endl;

        }
        cout << endl;

        // Print matrices
        //printMatrix(A, "A", N);
        //printMatrix(B, "B", N);
        //printMatrix(C_naive, "Result (Naive, Single-Core)", N);
        //printMatrix(C_blocked, "Result (Blocked, Multi-Core)", N);
    }
    

    return 0;
}

