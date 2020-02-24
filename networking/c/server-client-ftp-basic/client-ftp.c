///FTP CLIENT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

#include<sys/stat.h>
#include<sys/sendfile.h>
#include<fcntl.h>

int main()
{
        int k,choice;
        int len1,l;
        int counter;
        int sock_desc,filehandle;
        struct sockaddr_in client;
        char buf[100],length[100],fil[100];
        char temp1[100];
        memset(&client,0,sizeof(client));
        sock_desc=socket(AF_INET,SOCK_STREAM,0);
        if(sock_desc==-1)
        {
                puts("Unable to create socket");
                exit(1);
        }

        client.sin_family=AF_INET;
        client.sin_addr.s_addr=INADDR_ANY;
        client.sin_port=8045;

        k=connect(sock_desc,(struct sockaddr *)&client,sizeof(client));
        if(k==-1)
        {
                puts("Error in connect");
                exit(1);
        }
        while(1)
        {
                puts("1.List");
                puts("2.Load");
                puts("3.Store");
                puts("4.EXIT");
                puts("Enter choice:");
                scanf("%d",&choice);
                switch(choice)
                {
                case 1:
                        filehandle=open("list2.txt",O_RDWR|O_CREAT,0700);
                        strcpy(buf,"LIST");
                        k=send(sock_desc,buf,100,0);
                        if(k==-1)
                        {
                                puts("Unable to send");
                                exit(1);
                        }
                        k=recv(sock_desc,length,100,0);
                        if(k==-1)
                        {
                                puts("Error in receive");
                                exit(1);
                        }
                        len1=atoi(length);
                        printf("length is %d\n",len1);
                        counter=0;
                        while(counter<len1)
                        {
                                l=read(sock_desc,fil,100);
                                l=write(filehandle,fil,100);
                                counter+=l;
                        }
                        system("cat list2.txt");
                        close(filehandle);
                        break;
                case 2:

                        filehandle=open("list4.txt",O_RDWR|O_CREAT,0700);
                        strcpy(buf,"LOAD ");
                        puts("Enter filename:");
                        scanf("%s",temp1);
                        strcat(buf,temp1);
                        k=send(sock_desc,buf,100,0);
                        if(k==-1)
                        {
                                puts("Error in sending");
                                exit(1);
                        }
                        k=recv(sock_desc,length,100,0);
                        if(k==-1)
                        {
                                puts("Error in receiving file");
                                exit(1);
                        }
                        len1=atoi(length);
                        printf("Length received:%d\n",len1);
                        counter=0;
                        strcpy(fil,"");
                        while(counter<len1)
                        {
                                l=read(sock_desc,fil,100);
                                l=write(filehandle,fil,100);
                                counter+=l;
                        }
                        system("cat list4.txt");
                        break;
                case 3:
                case 4:
                        puts("EXITing..");
                        break;
                }
        }
        close(sock_desc);
        exit(1);
}
