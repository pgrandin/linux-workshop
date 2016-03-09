#include <stdlib.h>
#include <unistd.h>
#include <err.h>
#include <math.h>
#include <sys/time.h>
#include <stdarg.h>
#include <sys/wait.h>

#define CPUUSAGE 0.999      /* set it to a 0 < float < 1 */
#define PROCESSES 10       /* number of child worker processes */
#define CYCLETIME 50000   /* total cycle interval in microseconds */

#define WORKTIME (CYCLETIME * CPUUSAGE)
#define SLEEPTIME (CYCLETIME - WORKTIME)

/* returns t1-t2 in microseconds */
static inline long timediff(const struct timeval *t1, const struct timeval *t2)
{
  return (t1->tv_sec - t2->tv_sec) * 1000000 + (t1->tv_usec - t2->tv_usec);
}

static inline void gettime (struct timeval *t)
{
  if (gettimeofday(t, NULL) < 0)
  {
    err(1, "failed to acquire time");
  }
}

int hogcpu (void)
{
  struct timeval tWorkStart, tWorkCur, tSleepStart, tSleepStop;
  long usSleep, usWork, usWorkDelay = 0, usSleepDelay = 0;

  do
  {
    usWork = WORKTIME - usWorkDelay;
    gettime (&tWorkStart);
    do
    {
      sqrt (rand ());
      gettime (&tWorkCur);
    }
    while ((usWorkDelay = (timediff (&tWorkCur, &tWorkStart) - usWork)) < 0);

    if (usSleepDelay <= SLEEPTIME)
      usSleep = SLEEPTIME - usSleepDelay;
    else
      usSleep = SLEEPTIME;

    gettime (&tSleepStart);
    usleep (usSleep);
    gettime (&tSleepStop);
    usSleepDelay = timediff (&tSleepStop, &tSleepStart) - usSleep;
  }
  while (1);
  return 0;
}

int main (int argc, char const *argv[])
{
  pid_t pid;
  int i;
  for (i = 0; i < PROCESSES; i++)
  {
    switch (pid = fork ())
    {
    case 0:
      _exit (hogcpu ());
    case -1:
      err (1, "fork failed");
      break;
    default:
      warnx ("worker [%d] forked", pid);
    }
  }
  wait(NULL);
  return 0;
}
