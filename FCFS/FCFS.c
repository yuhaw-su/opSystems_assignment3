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
      jobs[jobsLength] = job;
      printf("Job with arrival %u and duration %u added\n", jobs[jobsLength]->arrivalTime, jobs[jobsLength]->duration);
      jobsLength++;
    }
  }

  fclose(input);

  printf("%d jobs added\n", jobsLength);
  if (jobsLength == 0)
  {
    printf("No jobs detected from file\n");
    exit(EXIT_FAILURE);
  }

  sortJobs(jobs, jobsLength);

  int i;
  unsigned int t = jobs[0]->arrivalTime;
  double turnaround = 0, response = 0;
  for (i = 0; i < jobsLength; ++i)
  {
    response += t - jobs[i]->arrivalTime;
    t += jobs[i]->duration;
    turaround += t - jobs[i]->arrivalTime;
  }

  FILE *output;
  output = fopen("FCFS-out.txt","w");

  return 0;
}
