#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOB_COUNT 100

struct Job
{
  unsigned int arrivalTime;
  unsigned int duration;
};

void swap(struct Job* jobs[], int index1, int index2)
{
  struct Job* tempJob = jobs[index1];
  jobs[index1] = jobs[index2];
  jobs[index2] = tempJob;
}

void sortJobs(struct Job* jobs[], int jobsLength)
{
  int i, j;
  for (i = 0; i < jobsLength-1; ++i)
  {
    for (j = i+1; j < jobsLength; ++j)
    {
      if (jobs[i]->arrivalTime > jobs[j]->arrivalTime)
      {
        swap(jobs, i, j);
      }
    }
  }
}

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

  struct Job* jobs[MAX_JOB_COUNT];
  char line[11];
  int i = 0;
  unsigned int arrivalTime;
  unsigned int duration;
  int jobsLength = 0;
  fgets(line, 11, input);
  while (!feof(input))
  {
    fgets(line, 11, input);
    if (line[0] != '\n')
    {
      sscanf(line, "%u", &arrivalTime);
      fgets(line, 11, input);
      sscanf(line, "%u", &duration);
      struct Job* job = (struct Job*) malloc(sizeof(struct Job*));
      job->arrivalTime = arrivalTime;
      job->duration = duration;
      jobs[i] = job;
      printf("Arrival: %u", job->arrivalTime);
      printf("Duration: %u", job->arrivalTime);
      jobsLength++;
    }
  }

  printf("jobsLength = %d\n", jobsLength);
  sortJobs(jobs, jobsLength);

  // START FCFS-pertinent stuff

  for (i = 0; i < jobsLength; ++i)
  {
    printf("Arrival time for job %d: %u\n", i, jobs[i]->arrivalTime);
  }

  fclose(input);

  return 0;
}
