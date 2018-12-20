void be_cat(int togrep[2],int tosort[2],int fromsort[2])
{
    char buff[BUFSIZ],file[100],food[100],chosen[100];
	 int num;
    FILE *fpout,*fpin;

    close(tosort[0]);
    close(tosort[1]);
    close(fromsort[1]);
    close(togrep[0]);

    fpout = fdopen(togrep[1],"w");
    fpin = fdopen(fromsort[0],"r");

   
    fprintf(fpout,"%s",grep_argument);
    fflush(fpout);
    
	 wait(NULL);

	 printf("choose one food recipe\n");

	 for(int i=0;i<3;i++)
	 {
		 fgets(buff,BUFSIZ,fpin);
		 sscanf(buff,"%s:%d",file,&num);
		 sscanf(file,"%s.txt",food);
		 printf("%s\n",food);
	 }
	scanf("%s",chosen);
	execlp("cat","cat",chosen);
}
