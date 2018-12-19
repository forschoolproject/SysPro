#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#define oops(m,x) {perror(m); exit(x);}

void be_cat(int togrep[2],int tosort[2],int fromsort[2]);
void be_grep(int togrep[2],int tosort[2],int fromsort[2]);
void be_sort(int togrep[2],int tosort[2],int fromsort[2]);

void main()
{
	int pid[2],togrep[2],tosort[2],fromsort[2];

	if(pipe(togrep)==-1)
		oops("pipe to grep failed",1);
	if(pipe(tosort)==-1)
		oops("pipe to sort failed",1);
	if(pipe(fromsort)==-1)
		oops("pipe from sort failed",1);

	if((pid[0] = fork()) == -1 || (pid[1] =fork()) == -1)
		oops("cannot fork",2);
	
	if(pid[0]==0)//grep process
	{
		be_grep(togrep,tosort,fromsort);
	}
	else if(pid[1]==0)//sort process
	{
		be_sort(togrep,tosort,fromsort);
	}
	else//cat process
	{
		be_cat(togrep,tosort,fromsort);
	}
}
void be_cat(int togrep[2],int tosort[2],int fromsort[2])
{
	char grep_argument[BUFSIZ]="\"",buff[BUFSIZ];
	FILE *fpout,*fpin;
	
	close(tosort[0]);
	close(tosort[1]);
	close(fromsort[1]);
	close(togrep[0]);

	fpout = fdopen(togrep[1],"w");
	fpin = fdopen(fromsort[0],"r");

	printf("Input Ingredients you have\n");
   while(1)
   {   
		scanf("%s",buff);
      if(buff[0]=='q' || strcmp(buff,"quit")==0)
		{
			grep_argument[strlen(grep_argument)-1]='\0';
			grep_argument[strlen(grep_argument)-1]='\0';
			grep_argument[strlen(grep_argument)]='\"';
			break;
		}
		strcat(grep_argument,"[");
      strcat(grep_argument,buff);
		strcat(grep_argument,"]");
		strcat(grep_argument,"/|");
		
		
    }
	fprintf(fpout,"%s",grep_argument);
	fflush(fpout);

}
void be_grep(int togrep[2],int tosort[2],int fromsort[2])
{
	char argument_buff[BUFSIZ],*argument;
	FILE *fpout,*fpin;

	close(fromsort[0]);
	close(fromsort[1]);
	close(togrep[1]);
	close(tosort[0]);

	fpout = fdopen(tosort[1],"w");
	fpin = fdopen(togrep[0],"r");

	fgets(argument_buff,BUFSIZ,fpin);
	argument = (char*)malloc(strlen(argument_buff)+1);
	strcpy(argument,argument_buff);

	//execlp("grep","grep","-c",argument,"*",NULL);
}
void be_sort(int togrep[2],int tosort[2],int fromsort[2])
{
	FILE *fpout,*fpin;

	close(togrep[0]);
	close(togrep[1]);
	close(tosort[1]);
	close(fromsort[0]);

	fpout = fdopen(fromsort[1],"w");
	fpin = fdopen(tosort[0],"r");
}

