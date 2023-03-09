#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <sys/wait.h>

void down(int semid) {
        struct sembuf sb = {0, -1, 0};
        semop(semid , &sb , 1); 
}

void up(int semid) {
		struct sembuf sb = {0, 1, 0};
		semop(semid , &sb , 1);
}

int N = 0;
void down_up(int semid) {
	for(int i = 1 ; i <= N ; ++i) {
		down(semid);
		up(semid);
		std::cout << "Process number " << i << std::endl;
	}	
}


 int main(int argc, char** argv) {
    N = atoi(argv[1]);
    int semid = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT) ;
   
    if (semid == -1) { 
        perror("semget failed");
        exit(1); 
    }
    if (semctl(semid, 0, IPC_RMID, 0) == -1) {
        perror("semctl");
        exit(1); 
    }
   
    for(int i = 1; i <= N; ++i) {
      pid_t p = fork();
      if(p == -1) {
        perror("fork");
        exit(1);
      }
      else if(p == 0) {
        down_up(semid);
      }
        break;
    }
    for(int i = 1; i <= N; ++i) {
      wait(NULL);
    }

   
    return 0;

}
