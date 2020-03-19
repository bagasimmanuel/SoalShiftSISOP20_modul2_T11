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

  Source Code : [soal1.c](/Soal1/shiftsoal1.c)
