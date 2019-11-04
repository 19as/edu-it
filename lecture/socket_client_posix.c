// socket_client_posix.c
// Created: 22 December, 2016

#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void check(int nResult, const char *pcszErrMsg)
{
  if (nResult == -1)
  {
    perror(pcszErrMsg);
    exit(EXIT_FAILURE);
  }
}

const char g_cszSocketPath[] = "/tmp/my_socket";

int main(int nArgC, char *apszArgV[])
{
  int nFD = socket(AF_UNIX, SOCK_STREAM, 0);
  check(nFD, "client socket");
  //
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof (addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, g_cszSocketPath, sizeof (addr.sun_path) - 1);
  //
  int nRet = connect(nFD, (struct sockaddr *) &addr, sizeof (addr));
  check(nRet, "client connect");
  //
  char szBuffer1[] = "Some long data from a client to send";
  char szBuffer2[] = "\0";
  const char *pcszBuffer = (nArgC > 1) ? szBuffer2 : szBuffer1;
  const size_t cuLength =
    (nArgC > 1) ? sizeof (szBuffer2) - 1 : sizeof (szBuffer1) - 1;
  ssize_t nSize = send(nFD, pcszBuffer, cuLength, 0);
  check(nSize, "client send");
  if (nSize < cuLength)
     printf("Partially written\n");
  //
  close(nFD);
  putchar('\n');
}

// End of File
