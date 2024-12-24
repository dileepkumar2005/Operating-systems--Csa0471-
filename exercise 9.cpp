#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int main() {
    // Create shared memory object
    int shm_fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(1);
    }

    // Configure the size of the shared memory object
    ftruncate(shm_fd, SHM_SIZE);

    // Map the shared memory object to the process's address space
    char *ptr = mmap(0, SHM_SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Write a message to the shared memory
    const char *message = "Hello from the writer process!";
    sprintf(ptr, "%s", message);

    printf("Writer: Wrote to shared memory: %s\n", message);

    // Clean up
    munmap(ptr, SHM_SIZE);
    close(shm_fd);
    return 0;
}
