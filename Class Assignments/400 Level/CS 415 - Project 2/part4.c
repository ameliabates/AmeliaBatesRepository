#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <errno.h>

void paresing(char *line, char **args)
{
        int i = 0;
        char *command = strtok(line, " \n");
        while (command!= NULL)
        {
                args[i++] = command;
                command = strtok(NULL, " \n");
        }
        args[i] = NULL;
}
void display (pid_t fork)
{
        char path[40], line[100];
        FILE *file;

        snprintf(path, sizeof(path), "/proc/%d/stat", fork);

        file = fopen(path, "r");

        if (file)
        {
                //found online
		//didn't directly copy
		long unsigned utime, stime;
		int rss;
		 fscanf(file, "%*d %*s %*c %*d %*d %*d %*d %*d %*u %*u %*u %*u %*u %lu %lu %*d %*d %*d %*d %*d %d", &utime, &stime, &rss);
        printf("PID %d: CPU Time (user+system): %lu, RSS: %d\n", fork, utime + stime, rss);
        fclose(file);
    } else {
        printf("Could not open /proc/%d/stat\n", fork);
    }

    snprintf(path, sizeof(path), "/proc/%d/status", fork);
    file = fopen(path, "r");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "VmSize:", 7) == 0 || strncmp(line, "VmRSS:", 6) == 0) {
                printf("PID %d: %s", fork, line);
            }
        }
        fclose(file);
    }

    snprintf(path, sizeof(path), "/proc/%d/io", fork);
    file = fopen(path, "r");
    if (file) {
        while (fgets(line, sizeof(line), file)) {
            if (strncmp(line, "read_bytes:", 11) == 0 || strncmp(line, "write_bytes:", 12) == 0) {
                printf("PID %d: %s", fork, line);
            }
        }
        fclose(file);
    }
}

pid_t child[10];
int int_child = 0;
int proc_index;

void alarm_handler(int sig)
{
        printf("Alarm halthing %d\n", child[proc_index]);
        if (kill(child[proc_index], SIGSTOP))
        {
                perror("Signal says stop");
        }

        int next_index = (proc_index + 1) % int_child;
        for (int i = 0; i < int_child; i++)
        {
                int status;
                pid_t list = waitpid(child[i], &status, WNOHANG);
                if (list == -1)
                {
                        perror("waitpid error");
                }
                else if (list > 0)
                {
                        for (int n = i; n < int_child - 1; n ++)
                        {
                                child[n] = child[n+1];
                        }
			int_child--;
                        if (proc_index >= int_child)
                        {
                                proc_index = 0;
                        }
                        i--;
                }
        }
	for (int i = 0; i < int_child; i++)
	{
		display(child[i]);
	} 
        if (int_child > 0)
        {
                printf("Starting process %d\n", child[next_index]);
                kill(child[next_index], SIGCONT);
                proc_index = next_index;
                alarm(1);
        }
}

int main (int argc, char *argv[])
{
        if (argc != 2)
        {

perror("Error");
                exit(-1);
        }

        FILE *file = fopen(argv[1], "r");
        if (file == NULL)
        {
                perror("Can't open file");
                exit(-1);
        }

        signal(SIGALRM, alarm_handler);

        int signal;
        sigset_t sigset;
        sigemptyset(&sigset);
        sigaddset(&sigset, SIGCONT);
        sigprocmask(SIG_BLOCK, &sigset, NULL);

        char line[256];

        while (fgets(line, sizeof(line), file) != NULL)
        {
char *args[10];
                paresing(line, args);

                pid_t forking = fork();
                if (forking < 0)
                {
                        perror("fork faulure");
                        exit(0);
                }
                else if (forking == 0)
                {
                //printf("CHILD %d WAITING IN SIGUSR1 SIGNAL...\n", getpid());
                sigwait(&sigset, &signal);
                //printf("Child process %d recieved signal %s\n", getpid(), strsignal(sig));
                if (execvp(args[0], args) == -1)
                {
                        perror("error");
                        exit(0);
                }
                }
                else
                {
         child[int_child++] = forking;
                }
          }
        fclose(file);
        if(int_child > 0)
        {
                alarm(1);
                kill(child[proc_index], SIGCONT);
        }
        while(int_child > 0)
        {
                pause();
        }
        return 0;
}