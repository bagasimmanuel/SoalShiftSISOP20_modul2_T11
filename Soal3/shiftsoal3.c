#include <dirent.h>					
#include <string.h> 
#include <sys/stat.h>
#include <unistd.h> 
#include <wait.h>
#include <stdio.h> 
#include <stdlib.h> 

int findStat(const char *path)
{
  struct stat pathDir; 
  stat(path, &pathDir);
  return S_ISDIR(pathDir.st_mode); 
} 

int main()
{
	pid_t c_satu = fork(); 
	int status;  	
	int c_dua = fork();   
	int c_tiga = fork();   
	#1 
	if (c_dua > 0 && c_tiga > 0)
	{  
		while ((wait(&status)) > 0); 
		DIR *dir;  
		struct dirent *directory; 
		chdir("/home/kecoak/Desktop/jpg/");  
		dir = opendir("."); 
		if (dir){  
     		while ((directory = readdir(dir)) != NULL){
	    if(strcmp(directory->d_name, ".") == 0 || strcmp(directory->d_name, "..") == 0)
		      continue;  
		    if(findStat(directory->d_name))
		    {
		      if(fork() == 0)
			{  
		        char file[1000];
		        sprintf(file,"/home/kecoak/Desktop/jpg/%s",directory->d_name);
		        char* argv[] = {"mv", file,"/home/kecoak/Desktop/indomie/", NULL};
		        execv("/bin/mv", argv);
          		} 
          	else
		{
            	while ((wait(&status)) > 0); 
            	if(fork() == 0)
		{

            	    	char coba1[999];
            	    	FILE *file;
		        	    sprintf(coba1,"/home/kecoak/Desktop/indomie/%s/coba1.txt",directory->d_name);
		        	    file = fopen(coba1, "w");
		        	    fclose(file);
				sleep(3);
		            	char coba2[999];
		            	sprintf(coba2,"/home/kecoak/Desktop/indomie/%s/coba2.txt",directory->d_name);
		            	file = fopen(coba2, "w");
		            	fclose(file);
		            	exit(0);
    }
    }
    }
    
        else
	{
          	while ((wait(&status)) > 0);
          	if(fork() == 0)
			{ 
            	while ((wait(&status)) > 0); 
            	char sFile[1000];
            	sprintf(sFile,"/home/kecoak/Desktop/jpg/%s",directory->d_name);
            	char* argv[] = {"mv", sFile,"/home/kecoak/Desktop/sedaap/", NULL};
            	execv("/bin/mv", argv);
          		}
    
    }
                }         
    }
    }

	else if (c_dua == 0 && c_tiga > 0)
	{ 
    while ((wait(&status)) > 0);
    if (c_satu == 0)
    {
      char *argv[] = {"mkdir", "-p","/home/kecoak/Desktop/indomie", NULL};
      execv("/bin/mkdir", argv); 
    }
    else
{
      while ((wait(&status)) > 0); 
      sleep(5); 
      char *argv[] = {"mkdir", "-p","/home/kecoak/Desktop/sedaap", NULL}; 
      execv("/bin/mkdir", argv); 
    }
}
	else if (c_dua > 0 && c_tiga == 0){ 
    char* argv[] = {"unzip", "-oq","/home/kecoak/Desktop/jpg.zip", NULL};
    execv("/usr/bin/unzip", argv);
	}
	return 0; 
} 
