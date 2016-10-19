#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOB_COUNT

struct Job
{
  unsigned int arrivalTime;
  unsigned int duration;
};

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Error: wrong number of arguments. Required: './executable inputFile'\n");
    exit(EXIT_FAILURE);
  }

  FILE *input;
  input = fopen(argv[1],"r");
  if (input == NULL)
  {
    printf("Error: unable to locate/read file\n");
    exit(EXIT_FAILURE);
  }

  struct *Job jobs[MAX_JOB_COUNT] = malloc(MAX_JOB_COUNT*size_of(struct *Job));
  char line[11];
  int i = 0;
  unsigned int arrivalTime;
  unsigned int duration;
  fgets(line, 11, input)
  while (fgets(line, 11, input) != NULL)
  {
    sscanf(line, "%u", &arrivalTime);
    fgets(line, 11, input)
    sscanf(line, "%u", &duration);
    struct Job job = malloc(size_of(struct Job));
    job.arrivalTime = arrivalTime;
    job.duration = duration;
    jobs[i] = *job;

    fgets(line, 11, input)
  }

  // FUN SHIT GOES HERE

  fclose(input);

  return 0;
}
