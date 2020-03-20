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

int main(int argc, char *argv[]) {
  pid_t pid, sid;        // Variabel untuk menyimpan PID
  int sec,min,hour;

  pid = fork();     // Menyimpan PID dari Child Process

  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if(argc != 5){
    printf("Argumen harus 5");
    return 0;
  }

  sec = -1;
  min = -1;
  hour = -1;
  //Argument Detik
  if(argv[1][0] == '*'){
    sec = -1;
  }else if(isalpha(argv[1][0])){
    printf("Harus angka");
    return 0;
  }else if(atoi(argv[1]) < 0 || atoi(argv[1]) > 59){
    printf("Range 0 - 59");
    return 0;
  }else{
    sec = atoi(argv[1]);
  }
  //Argument Menit
  if(argv[2][0] == '*'){
    min = -1;
  }else if(isalpha(argv[2][0])){
    printf("Harus angka");
    return 0;
  }else if(atoi(argv[2]) < 0 || atoi(argv[2]) > 59){
    printf("Range 0 - 59");
    return 0;
  }else{
    min = atoi(argv[2]);
  }
  //Argument Jam
  if(argv[3][0] == '*'){
    hour = -1;
  }else if(isalpha(argv[3][0])){
    printf("Harus angka");
    return 0;
  }else if(atoi(argv[3]) < 0 || atoi(argv[3]) > 24){
    printf("Range 0 - 24");
    return 0;
  }else{
    hour = atoi(argv[3]);
  }

  // if(argv[2][0] == '*') min = atoi(argv[2]);
  // if(argv[3][0] == '*') hour = atoi(argv[3]);


  while(1) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if((hour == tm.tm_hour || hour == -1) && (min == tm.tm_min || min == -1) && (sec == tm.tm_sec || sec == -1)){
      if(fork()==0){
        char *argx[] = {"bash",argv[4], NULL};
        execv("/bin/bash", argx);
      }
    }
    sleep(1);
  }
}
