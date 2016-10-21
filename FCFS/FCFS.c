#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
  for (i = 1; i < jobsLength; ++i)
  {
    j = i;
    while (j > 0 && jobs[j-1]->arrivalTime > jobs[j]->arrivalTime)
    {
      swap(jobs, j, j-1);
      j--;
    }
  }
}

void getNextUnsignedInt(FILE *fp, char *line)
{
  char c = fgetc(fp);
  while (isspace(c) != 0)
  {
    c = fgetc(fp);
  }

  int i = 0;
  while (isspace(c) == 0)
  {
    line[i] = c;
    i++;
    c = fgetc(fp);
  }
  line[i] = '\n';
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
  char line[4];
  unsigned int arrivalTime, duration;
  int jobsLength;
  int i = 0, arrivalTimeRead = 0;
  getNextUnsignedInt(input, line);
  sscanf(line, "%d", &jobsLength);
  if (jobsLength == 0)
  {
    printf("0.00000\n0.00000\n");
    return 0;
  }

  while (i < jobsLength)
  {
    getNextUnsignedInt(input, line);
    sscanf(line, "%u", &arrivalTime);
    getNextUnsignedInt(input, line);
    sscanf(line, "%u", &duration);
    struct Job* job = (struct Job*) malloc(sizeof(struct Job*));
    job->arrivalTime = arrivalTime;
    job->duration = duration;
    jobs[i] = job;
    i++;
  }
  fclose(input);

  sortJobs(jobs, jobsLength);

  unsigned int t = 0;
  double turnaround = 0, response = 0;
  for (i = 0; i < jobsLength; ++i)
  {
    if (jobs[i]->arrivalTime > t)
    {
      t = jobs[i]->arrivalTime;
    }
    response += t - jobs[i]->arrivalTime;
    t += jobs[i]->duration;
    turnaround += t - jobs[i]->arrivalTime;
  }

  printf("%.5lf\n", turnaround/jobsLength);
  printf("%.5lf\n", response/jobsLength);

  return 0;
}
