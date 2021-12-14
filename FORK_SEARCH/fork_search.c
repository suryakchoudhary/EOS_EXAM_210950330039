/*3. Open the file /usr/share/dictionary.txt in process P1 which is a parent. Create two child process using fork. 
 * Child 1 searches for a word from the top of the file and child 2 search from bottom of the file. The word is provided by parent Process. 
 * Whichever child finds it prints the message "Found"*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int indexOf(FILE *fptr, const char *word, int *line, int *col);

char word[50];
// Driver code
int main()
{
	int pip_fd[2];
	pipe(pip_fd);

	int fd1, fd2;
	int pid, pid1, pid2;
	pid = fork();

	//Child 1
	if (pid == 0) 
	{
		{	//reading
			close(pip_fd[1]);
			read(pip_fd[0],word , sizeof(word));
			printf("%s  integers are received at child end.\n",word);
			close(pip_fd[0]);

			FILE *fptr;

			fptr = fopen("dictionary.txt", "r");
			if (fptr == NULL)
			{
				printf("Unable to open file.\n");
				printf("Please check you have read/write previleges.\n");

				exit(EXIT_FAILURE);
			}


			if (line != -1)
				printf("'%s' found at line: %d, col: %d\n", word, line + 1, col + 1);
			else
				printf("'%s' does not exists.", word);


			fclose(fptr);

		}

		fd1=open("dictionary.txt", O_RDONLY);

		printf("child[1] --> pid = %d and ppid = %d\n",getpid(), getppid());
	}

	//child 2
	else 
	{
		pid1 = fork();
		if (pid1 == 0) 
		{
			sleep(2);
			printf("child[2] --> pid = %d and ppid = %d\n",getpid(), getppid());
		}


		//Parent
		else 
		{
			//writing
			close(pip_fd[0]);
			printf("Enter word to search in file: ");
			scanf("%s", word);

			write(pip_fd[1],&word,sizeof(word));
			close(pip_fd[1]);

			sleep(3);
			printf("parent --> pid = %d\n", getpid());
		}
	}

	return 0;
}
