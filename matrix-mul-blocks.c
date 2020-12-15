// Experiement worth trying:
// matrix of size 1022,1023,1024,1025,1026
// matrix of size 2047, 2048, 2049

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

struct timeval time_stamp;

double timeStamp(){
  double t;
  gettimeofday(&time_stamp, NULL);
  t = time_stamp.tv_sec + (time_stamp.tv_usec/1000000.0);
  return t;
}

void multiply_with_blocks(int a[], int b[], int c[], int block_size, int mat_size){
  for (int block_i = 0; block_i < mat_size; block_i+= block_size){
      for (int block_j = 0; block_j < mat_size; block_j+= block_size){
          for (int block_k = 0; block_k < mat_size; block_k+= block_size){
              for (int i = block_i; i < block_i+block_size && i < mat_size; i++){
                  for (int j = block_j; j < block_j+block_size && j < mat_size; j++){
                      for (int k = block_k; k < block_k+block_size && k < mat_size; k++){
                          c[mat_size*i + j] += a[mat_size*i + k] * b[mat_size*k + j];
                      }
                  }
              }
          }
      }
  }


}

void print_square_matrix(int mat[], int dimension){
  for (int i=0; i < dimension; i++){
      for(int j=0; j<dimension; j++)
      {
        printf("%d     ", mat[dimension*i + j]);
      }
      printf("\n");
  }
}

int main(int argc, char** argv){
  // Check to make sure we received a command line option
  if(argc < 3) {
    fprintf(stderr, "Usage: %s <list size>\n", argv[0]);
    return 1;
  }

  // dimension of square matrix
  int dim = atoi(argv[1]);
  int block_size = atoi(argv[2]);

  int *A, *B, *C;
  double start, end;

  // Allocation memory in the heap for matrices
  A = (int *)malloc(dim*dim*sizeof(int));
  B = (int *)malloc(dim*dim*sizeof(int));
  C = (int *)malloc(dim*dim*sizeof(int));

  // Use current time as seed for random generator
  srand(time(0));
  for (int i = 0; i < dim; i++){
    for (int j = 0; j < dim; j++){
      A[dim*i+j] = rand();
      B[dim*i+j] = rand();
      // A[dim*i+j] = rand() % (10 + 1 - 0) + 0;
      // B[dim*i+j] = rand() % (10 + 1 - 0) + 0;
      C[dim*i+j] = 0;
    }
  }

  // printf("matrix A: \n");
  // print_square_matrix(A, dim);
  // printf("matrix B: \n");
  // print_square_matrix(B, dim);

  start = timeStamp();
  printf("Start matrix multiplication:\n");
  multiply_with_blocks(A, B, C, block_size, dim);
  end = timeStamp();
  printf("Duration (secs):%f\n", end-start);

  // printf("Product matrix: \n");
  // print_square_matrix(C, dim);

  // Free memory
  free(A);
  free(B);
  free(C);

  return 0;
}
