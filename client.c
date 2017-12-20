#include "pipe_networking.h"
#include <string.h>

int main() {

  int to_server;
  int from_server;
  char buffer[BUFFER_SIZE];

  from_server = client_handshake( &to_server );

  while (1) {
    printf("enter data: ");
    fgets(buffer, sizeof(buffer), stdin);
    *strchr(&buffer, '\n') = 0;
    int w = write(to_server, buffer, strlen(buffer));
		printf("wrote %d bytes from string %s, which is %d long\n", w, buffer, sizeof(buffer));
    read(from_server, buffer, sizeof(buffer));
    printf("received: [%s]\n", buffer);
  }
}
