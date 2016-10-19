#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_JOB_COUNT 100

struct Job
{
  unsigned int arrivalTime;
  unsigned int duration;
  int done;
  int started;
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

int getNextJobIndex(struct Job* jobs[], unsigned int currentTime, int jobsLength)
{
  int i;
  int minDurationIndex = -1;
  unsigned int updatedTime = currentTime;
  for (i = 0; i < jobsLength; ++i)
  {
    if (jobs[i]->done != 1)
    {
      if (jobs[i]->arrivalTime > updatedTime)
      {
        if (minDurationIndex == -1)
        {
          updatedTime = jobs[i]->arrivalTime;
        }
        else
        {
          break;
        }
      }
      if (minDurationIndex == -1 || (jobs[i]->arrivalTime <= updatedTime && jobs[i]->duration < jobs[minDurationIndex]->duration))
      {
        minDurationIndex = i;
      }
    }
  }

  return minDurationIndex;
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
  unsigned int arrivalTime, duration;
  int jobsLength, i;
  fgets(line, 11, input);
  sscanf(line, "%d", &jobsLength);
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
      job->done = 0;
      job->started = 0;
      jobs[i] = job;
      i++;
    }
  }

  fclose(input);

  if (jobsLength == 0)
  {
    exit(EXIT_FAILURE);
  }

  sortJobs(jobs, jobsLength);

  int jobIndex, jobsCompleted = 0;
  unsigned int t = 0;
  double turnaround = 0, response = 0;
  while (jobsCompleted < jobsLength)
  {
    jobIndex = getNextJobIndex(jobs, t, jobsLength);
    if (jobs[jobIndex]->started != 1)
    {
      jobs[jobIndex]->started = 1;
      if (jobs[jobIndex]->arrivalTime > t)
      {
        t = jobs[jobIndex]->arrivalTime;
      }
      response += t - jobs[jobIndex]->arrivalTime;
    }
    t++;
    jobs[jobIndex]->duration--;
    if (jobs[jobIndex]->duration == 0)
    {
      jobs[jobIndex]->done = 1;
      turnaround += t - jobs[jobIndex]->arrivalTime;
      jobsCompleted++;
    }
  }

  FILE *output;
  output = fopen("STCF_out.txt","w");
  if (output == NULL)
  {
    printf("Error: unable to open file to write\n");
    exit(EXIT_FAILURE);
  }

  fprintf(output, "%.5lf\n", turnaround/jobsLength);
  fprintf(output, "%.5lf\n", response/jobsLength);

  fclose(output);

  return 0;
}
