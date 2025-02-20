#include <aio.h>
#include <errno.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define BUFFER_SIZE 8192
#define NUM_WRITES (1000000 / BUFFER_SIZE + 1)

typedef struct {
  const char *filename;
  int start;
  int end;
} ThreadData;

void *writeToFile(void *arg) {
  ThreadData *data = (ThreadData *)arg;
  FILE *file = fopen(data->filename, "w");
  if (file == NULL) {
    perror("Error opening file");
    return NULL;
  }

  struct aiocb *aiocbList[NUM_WRITES];
  char **buffers = malloc(NUM_WRITES * sizeof(char *));

  for (int i = 0; i < NUM_WRITES; i++) {
    buffers[i] = malloc(BUFFER_SIZE);
    aiocbList[i] = malloc(sizeof(struct aiocb));
    memset(aiocbList[i], 0, sizeof(struct aiocb));
    aiocbList[i]->aio_fildes = fileno(file);
    aiocbList[i]->aio_buf = buffers[i];
  }

  int currentNum = data->start;
  long long totalOffset = 0;

  for (int writeIndex = 0; writeIndex < NUM_WRITES && currentNum <= data->end;
       writeIndex++) {
    int position = 0;
    while (position < BUFFER_SIZE - 20 && currentNum <= data->end) {
      int len = sprintf(buffers[writeIndex] + position, "%d\n", currentNum);
      position += len;
      currentNum++;
    }

    aiocbList[writeIndex]->aio_nbytes = position;
    aiocbList[writeIndex]->aio_offset = totalOffset;
    totalOffset += position;

    if (aio_write(aiocbList[writeIndex]) == -1) {
      perror("Error in aio_write");
      break;
    }
  }

  for (int i = 0; i < NUM_WRITES; i++) {
    while (aio_error(aiocbList[i]) == EINPROGRESS)
      ;
    int ret = aio_return(aiocbList[i]);
    if (ret == -1) {
      perror("Error in aio_return");
    }
  }

  for (int i = 0; i < NUM_WRITES; i++) {
    free(buffers[i]);
    free(aiocbList[i]);
  }
  free(buffers);

  fclose(file);
  return NULL;
}

int main() {
  clock_t start, end;
  double cpu_time_used;
  pthread_t thread1, thread2;
  ThreadData data1 = {"fileA.txt", 1, 1000000};
  ThreadData data2 = {"fileB.txt", 1, 1000000};

  start = clock();

  if (pthread_create(&thread1, NULL, writeToFile, &data1) != 0) {
    perror("Error creating thread 1");
    return 1;
  }
  if (pthread_create(&thread2, NULL, writeToFile, &data2) != 0) {
    perror("Error creating thread 2");
    return 1;
  }

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("Finished writing to both files!\n");
  printf("Time taken: %f seconds\n", cpu_time_used);

  return 0;
}
