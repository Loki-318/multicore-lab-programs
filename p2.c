// a.	OpenMP
#include <omp.h> 
#include <stdio.h> 
int main() { 
    #pragma omp parallel 
    { 
        int thread_id = omp_get_thread_num(); 
        printf("Hello from thread %d\n", thread_id); 
    } 
    return 0; 
} 

// b.	pThread
#include <pthread.h> 
#include <stdio.h> 
void* print_message(void* thread_id) { 
    int tid = *((int*)thread_id); 
    printf("Hello from thread %d\n", tid); 
    return NULL; 
} 
int main() { 
    pthread_t threads[5]; 
    int thread_ids[5]; 
    for (int i = 0; i < 5; i++) { 
        thread_ids[i] = i; 
        pthread_create(&threads[i], NULL, print_message, (void*)&thread_ids[i]); 
    } 
    for (int i = 0; i < 5; i++) { 
        pthread_join(threads[i], NULL); 
    } 
    return 0; 
} 

// c.	CUDA
#include <stdio.h> 
__global__ void helloFromGPU() { 
    printf("Hello from GPU thread %d\n", threadIdx.x); 
} 
int main() { 
    helloFromGPU<<<1, 5>>>(); 
    cudaDeviceSynchronize(); 
    return 0; 
}

// d.	MPI
#include <mpi.h> 
#include <stdio.h> 
int main(int argc, char** argv) { 
    MPI_Init(&argc, &argv); 
    int world_size; 
    MPI_Comm_size(MPI_COMM_WORLD, &world_size); 
    int world_rank; 
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank); 
    printf("Hello from process %d out of %d processes\n", world_rank, world_size); 
    MPI_Finalize(); 
    return 0; 
}
