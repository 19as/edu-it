// socket_server_posix.c
// Created: 22 December, 2016

#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

void check(int nResult, const char *pcszErrMsg)
{
  if (nResult == -1)
  {
    perror(pcszErrMsg);
    exit(EXIT_FAILURE);
  }
}

const char g_cszSocketPath[] = "/tmp/my_socket";

void *thread_func(void *pvParam);

volatile int g_vbRun = 1;

struct ThreadArgs
{
  int m_nConnection;
};

int main()
{
  int nFD = socket(AF_UNIX, SOCK_STREAM, 0);
  check(nFD, "server socket");
  //
  int nFlags = fcntl(nFD, F_GETFL, 0);
  check(nFlags, "server fcntl get");
  nFlags = fcntl(nFD, F_SETFL, nFlags | O_NONBLOCK);
  check(nFlags, "server fcntl set");
  //
  struct sockaddr_un addr;
  memset(&addr, 0, sizeof (addr));
  addr.sun_family = AF_UNIX;
  strncpy(addr.sun_path, g_cszSocketPath, sizeof (addr.sun_path) - 1);
  unlink(g_cszSocketPath);
  //
  int nRet = bind(nFD, (struct sockaddr *) &addr, sizeof (addr));
  check(nRet, "server bind");
  //
  nRet = listen(nFD, SOMAXCONN);
  check(nRet, "server listen");
  //
  while (g_vbRun)
  {
    struct sockaddr_un addr_remote;
    socklen_t uSockLen;
    int nConnection = accept(
      nFD, (struct sockaddr *) &addr_remote, &uSockLen);
    if (nConnection < 0)
    {
      if (errno == EAGAIN || errno == EWOULDBLOCK)
        continue;
      //
      perror("server accept");
      continue;
    }
    //
    struct ThreadArgs *pArgs =
      (struct ThreadArgs *) malloc(sizeof (struct ThreadArgs *));
    pArgs->m_nConnection = nConnection;
    //
    pthread_t hThread;
    nRet = pthread_create(&hThread, NULL, &thread_func, pArgs);
    check(nRet, "server pthread_create");
  }
  //
  printf("Server finished\n");
}

void *thread_func(void *pvParam)
{
  struct ThreadArgs *pArgs = (struct ThreadArgs *) pvParam;
  int nConnection = pArgs->m_nConnection;
  free(pArgs);
  //
  char szBuffer[7];
  ssize_t nSize;
  do
  {
    nSize = recv(nConnection, szBuffer, sizeof (szBuffer), MSG_WAITALL);
    check(nSize, "server recv");
    //
    ssize_t i;
    for (i = 0; i < nSize; ++ i)
    {
      if (szBuffer[i] == '\0')
      {
        g_vbRun = 0;
        printf("Found 0\n");
      }
      else
        putchar(szBuffer[i]);
    }
    putchar('|');
  }
  while (nSize > 0);
  close(nConnection);
  putchar('\n');
  //
  return NULL;
}

// End of File
