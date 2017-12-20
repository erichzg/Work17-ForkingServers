#include "pipe_networking.h"
#include <signal.h>
#include <ctype.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove("luigi");
    exit(0);
  }
}

int main() {
  signal(SIGINT, sighandler);
  
  int from_client;
  int f;
  
  while (1) {
    from_client = server_setup();
    f = fork();
    if (!f) {
      subserver(from_client);
    }
  }
    
  
}

void subserver(int from_client) {
  int to_client = server_connect(from_client);
  char input_string[256];
  
  while (1) {
    read(from_client, input_string, 256);
    printf("[subserver %d] Recieved: %s\n", getpid(), input_string);
    //printf("length of string: %d\n", strlen(input_string));
    process(input_string);
    write(to_client, input_string, strlen(input_string));
  }
}

void process(char * s) {
  int index = 0;
  printf("process length of string: %d\n", strlen(s));
  while (index < strlen(s)) {
    s[index] = toupper(s[index]);
    index++;
  }
}
