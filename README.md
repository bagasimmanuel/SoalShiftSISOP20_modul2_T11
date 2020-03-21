# Shift 2 SISOP T11

Penjelasan Soal Shift 2 Kelompok T11

Anggota :
- Fachrizal Rahmat
- Bagas Immanuel Lodianto 05311840000026

Table of Contents
=================

  * soal1
  * soal2
  * soal3

  ## Soal1

  Soal :
  Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut:

  * Program menerima 4 argumen berupa:
    * Detik: 0-59 atau * (any value)
    * Menit: 0-59 atau * (any value)
    * Jam: 0-23 atau * (any value)
    * Path file .sh

  * Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai
  * Program hanya menerima 1 config cron
  * Program berjalan di background (daemon)
  * Tidak boleh menggunakan fungsi system()

  Contoh: `./program \* 34 7 /home/somi/test.sh`

  ### Penjelasan

  ```
  #include <sys/types.h>
  #include <sys/stat.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <errno.h>
  #include <unistd.h>
  #include <syslog.h>
  #include <string.h>
  #include <ctype.h>
  #include <time.h>
  ```

  Beberapa Library yang digunakan untuk menjalankan Program

  ```
  int main(int argc, char *argv[]) {

      pid_t pid, sid;       
      int sec,min,hour;

  ```

  Agar int main dapat menerima argumen, diberikan parameter seperti berikut.

  ```
    pid = fork();   

    if (pid < 0) {
      exit(EXIT_FAILURE);
    }

    if (pid > 0) {
      exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
      exit(EXIT_FAILURE);
    }

    if ((chdir("/")) < 0) {
      exit(EXIT_FAILURE);
    }

  ```
  Untuk merubah agar proses berubah menjadi process daemon

  ```
  if(argc != 5){

    printf("Argumen harus 5");

    return 0;
  }

  ```
  Akan mengeluarkan Error apabila argumen tidak sama dengan 5

  ```
  sec = 0;
  min = 0;
  hour = 0;

  //Argument Detik
  if(argv[1][0] == '*'){

    sec = 0;

  }else if(isalpha(argv[1][0])){

    printf("Harus angka");

  }else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 59){

    printf("Range 0 - 59");

  }else{

    sec = atoi(argv[1]);

  }

  ```
  Melakukan Pengecheckan apakh Argumen vaild, dilakukan untuk tiap argumen detik,menit dan Jam (Untuk melihat Pengecheckan Argumen menit dan Jam dapat melihat Source Code)

  ```

  while(1) {

    time_t t = time(NULL);

    struct tm tm = *localtime(&t);

    if((hour == tm.tm_hour || hour == 0) && (min == tm.tm_min || min == 0) && (sec == tm.tm_sec || sec == 0)){

      if(fork()==0){
        char *argx[] = {"bash",argv[4], NULL};
        execv("/bin/bash", argx);
      }
    }
    sleep(1);
  }

  ```

  Apabila semua argumen valid, maka Daemon akan melakukan loop tiap detik untuk mengecheck apakah jam saat ini sesuai dengan jam yang diinputkan, bila iya, maka lakukan fork sehingga child process akan menjalankan program `.sh` kemudian mati, sedangkan parent akan terus melakukan loop.

  Screenshot ketika bahwa daemon tengah berjalan :
  ![Screenshot Nomor 1](/images/screenshot_nomor_1.png)

  Source Code : [soal1.c](/Soal1/shiftsoal11.c)

  ## Soal 2

  Bingung Bagaimana cara mengerjakannya

  Source Code : [soal2.c](/Soal2/shiftsoal2.c)

  ## Soal 3
```
#include <dirent.h>					
#include <string.h> 
#include <sys/stat.h>
#include <unistd.h> 
#include <wait.h>
#include <stdio.h> 
#include <stdlib.h> 
```
Library yang digunakan dalam program ini

```
int findStat(const char *path)
{
  struct stat pathDir; 
  stat(path, &pathDir);
  return S_ISDIR(pathDir.st_mode); 
} 
```
membuat fungsi findStat untuk mengetahui apakah direktori atau bukan

```
	pid_t c_satu = fork(); 
	int status;  	
	int c_dua = fork();   
	int c_tiga = fork();
```
mendeklarasikan int dari child

```
else if (c_dua > 0 && c_tiga == 0)
	{ 
    char* argv[] = {"unzip", "-oq","/home/umum/Desktop/jpg.zip", NULL};
    execv("/usr/bin/unzip", argv);
	}
```
merupakan parent dari para childnya

```
else if (c_dua == 0 && c_tiga > 0)
	{ 
    while ((wait(&status)) > 0);
    if (c_satu == 0)
    {
      char *argv[] = {"mkdir", "-p","/home/umum/Desktop/indomie", NULL};
      execv("/bin/mkdir", argv); 
    }
```
code ini membuat direktori indomie dan berjalan bersamaan dengan parent nya

```
 else
{
      while ((wait(&status)) > 0); 
      sleep(5); 
      char *argv[] = {"mkdir", "-p","/home/umum/Desktop/sedaap", NULL}; 
      execv("/bin/mkdir", argv); 
    }
  } 
```
code ini digunakan untuk membuat direktori sedaap dengan menunggu 5 detik

```
if (c_dua > 0 && c_tiga > 0)
	{  
		while ((wait(&status)) > 0); 
		DIR *dir;  
		struct dirent *directory; 
		chdir("/home/umum/Desktop/jpg/");  
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
		        sprintf(file,"/home/umum/Desktop/jpg/%s",directory->d_name);
		        char* argv[] = {"mv", file,"/home/umum/Desktop/indomie/", NULL};
		        execv("/bin/mv", argv);
          		} 
```
jika file itu direktori maka dipindahkan ke direktori indomie

```
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
```
pada setiap folder direktori di yang ada di indomie akan diisi coba1.txt dan 3 detik berikutnya akan diisi coba2.txt

```
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
```
selain file sisanya di jpg dipindah ke sedaap 
