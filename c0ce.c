#include <stdio.h>
#include <stdlib.h>

void allocateAndSet(int **ptr, int value) {
     *ptr = malloc(sizeof(int));  // Allocate memory
     **ptr = value;               // Set the value
}

int main() {
    int *myPtr = NULL;
    allocateAndSet(&myPtr, 200);     // Pass address of pointer
    printf("Value: %d\n", *myPtr);  // Output: Value: 200
    free(myPtr);
    return 0;
}

