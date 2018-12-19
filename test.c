#include <stdio.h>
#include <string.h>
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
	if(pid[1]==0)//sort process
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
	FILE *fpout,*fpin;

	close(tosort[0]);
	close(tosort[1]);
	close(fromsort[1]);
	close(togrep[0]);

	fpout = fdopen(togrep[1],"w");
	fpin = fdopen(fromsort[0],"r");
}
void be_grep(int togrep[2],int tosort[2],int fromsort[2])
{
	FILE *fpout,*fpin;

	close(fromsort[0]);
	close(fromsort[1]);
	close(togrep[1]);
	close(tosort[0]);

	fpout = fdopen(tosort[1],"w");
	fpin = fdopen(togrep[0],"r");
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

