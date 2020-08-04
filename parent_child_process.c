#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define Length 8192
#define Finish 0
#define W_Finish 1
#define BUFFER 8192

// new

void cpr(char *, char *);

void cpe(char *, int[]);

void end(char *, char *);

void cpe(char *command, int dp[]) {

	char *t;

	char *argv[10];

	char *cmd;

	int a = 1;

	t = strtok(command, " \r");

	argv[0] = t;

	while (t != NULL) {

		t = strtok(NULL, " \r");

		argv[a] = t;

		a++;
	}
	argv[a] = "\0";

	cmd = argv[0];

	close(STDOUT_FILENO);

	close(dp[Finish]);

	dup2(dp[W_Finish], 1);

	dup2(dp[W_Finish], 2);

	close(dp[W_Finish]);

	execvp(cmd, argv);

	printf("\r");

	exit(1);
}

void cpr(char *filename, char *p) {

	char line[Length];

	FILE *file = fopen(filename, "r");

	if (file == NULL) {

		perror("Error404: File does not exist");
	}
	while (fgets(line, Length, file) != NULL) {

		sprintf(p, "%s", line);

		p += strlen(line);
	}
	fclose(file);

	exit(1);
}

// The main
int main(int argc, char *argv[]) {

	pid_t rp;

	pid_t ep;

	const int S = 6098;

	const char *name = "Systems";

	int sd;

	char *p;

	int dp[2];

	if (pipe(dp) == -1) {

		perror(" Error");

		exit(1);
	}

	sd = shm_open(name, O_CREAT | O_RDWR, 0666);

	ftruncate(sd, S);

	p = (char *) mmap(0, S, PROT_READ | PROT_WRITE, MAP_SHARED, sd, 0);

	rp = fork();

	if (rp < 0) {

		fprintf(stderr, "Does not work");

		return 1;
	}

	if (rp == 0) {

		cpr(argv[1], p);

	} else {

		wait(NULL);

		printf("%s", " It is done\n");

		char *c;

		c = (char *) malloc((sizeof((char *) p)));

		char *t;

		char *s = "\n\r";

		strcpy(c, p);

		shm_unlink(name);

		t = strtok(c, s);

		while (t != NULL) {

			ep = fork();

			if (ep < 0) {

				fprintf(stderr, " Does not work");

				return 1;

			} else if (ep == 0) {

				cpe(t, dp);

			} else {

				wait(NULL);
			}

			char read_msg[BUFFER] = "\0";

			read(dp[Finish], read_msg, BUFFER);

			end(t, read_msg);

			t = strtok(NULL, s);
		}
	}
	return 0;
}

// End
void end(char* command, char* output) {

	printf("The output of: %s : is\n", command);

	printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n%s<<<<<<<<<<<<<<<<<<<<<<<\n",
			output);
}
