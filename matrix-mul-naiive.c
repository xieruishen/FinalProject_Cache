// Experiement worth trying:
// matrix of size 1022,1023,1024,1025,1026

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

void multiply(int a[], int b[], int c[], int dimension){
  for (int i = 0; i < dimension; i++)
      for (int j = 0; j < dimension; j++)
          for (int k = 0; k < dimension; k++)
              c[dimension*i+j] += a[dimension*i+k] * b[dimension*k+j];
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
  if(argc < 2) {
    fprintf(stderr, "Usage: %s <list size>\n", argv[0]);
    return 1;
  }

  // dimension of square matrix
  int dim = atoi(argv[1]);

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
  multiply(A, B, C, dim);
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
