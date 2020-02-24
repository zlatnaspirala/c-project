
////FTP SERVER WITH TCP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/stat.h>

#if __APPLE__
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <sys/uio.h>
#elif
    #include <sys/sendfile.h>
#endif

#include <fcntl.h>

/*
OSX:
  int sendfile(int fd, int s, off_t offset, off_t *len, struct sf_hdtr *hdtr, int flags);
Linux:
  ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);
*/

int main()
{
  int sock_desc, sock_desc2;
  socklen_t len;
  struct stat obj;
  char length[10];
  int filehandle;
  char choice[100];
  int k, i;
  char buf[100];
  char target[100];
  struct sockaddr_in client, server;
  memset(&client, 0, sizeof(client));
  memset(&server, 0, sizeof(server));
  sock_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (sock_desc == -1)
  {
    puts("Error in socket 1");
    exit(1);
  }
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 8045;

  k = bind(sock_desc, (struct sockaddr *)&server, sizeof(server));
  if (k == -1)
  {
    puts("Error in binding");
    exit(1);
  }
  k = listen(sock_desc, 5);
  if (k == -1)
  {
    puts("Error in listening");
    exit(1);
  }
  len = sizeof(client);
  sock_desc2 = accept(sock_desc, (struct sockaddr *)&client, &len);
  if (sock_desc2 == -1)
  {
    puts("Error in socket2");
    exit(1);
  }
  while (1)
  {
    k = recv(sock_desc2, buf, 100, 0);
    if (k == -1)
    {
      puts("Error in receive");
      exit(1);
    }
    for (i = 0; i < 4; i++)
    {
      choice[i] = buf[i];
    }
    choice[i] = '\0';
    puts("");
    puts(choice);
    puts("");
    if (strcmp(choice, "LIST") == 0)
    {
      system("ls -al>list.txt");
      filehandle = open("list.txt", O_RDONLY); //
      stat("list.txt", &obj);                  //
      sprintf(length, "%d", (int)obj.st_size);
      puts("sending size of file");
      k = send(sock_desc2, length, strlen(length), 0);
      if (k == -1)
      {
        printf("send failed");
        exit(1);
      }
      puts("send entire file");
      k = sendfile(sock_desc2, filehandle, NULL, obj.st_size);
      if (k == -1)
      {
        printf("file sendingfailed");
        exit(1);
      }
    }
    else if (strcmp(choice, "LOAD") == 0)
    {
      puts("inside load");
      strcpy(target, buf + 5);
      printf("target file is*%s*\n", target);
      memset(&obj, 0, sizeof(obj));
      stat(target, &obj);
      filehandle = open(target, O_RDONLY);
      if (filehandle == -1)
      {
        puts("Error in opening file for read");
        exit(1);
      }
      sprintf(length, "%d", (int)obj.st_size);
      k = send(sock_desc2, length, strlen(length), 0);
      if (k == -1)
      {
        puts("Error in sending");
        exit(1);
      }
      k = sendfile(sock_desc2, filehandle, NULL, obj.st_size);
      if (k == -1)
      {
        puts("Error in sending file");
        exit(1);
      }
    }
  }
}
