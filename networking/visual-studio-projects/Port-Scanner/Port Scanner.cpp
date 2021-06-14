#include <stdio.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <Windows.h>
#include <time.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#pragma warning (disable : 4996)
#pragma warning (disable : 6385)
#pragma warning (disable : 6386)
#pragma warning (disable : 6001)
#pragma warning (disable : 4267)

void ErrChk(int code, const char* func)
{
	if (code == SOCKET_ERROR)
	{
		printf("Error %x in function %s\n", WSAGetLastError(), func);
		exit(-1);
	}
}

struct Data
{
	FILE* outf;
	size_t port_min;
	size_t port_max;
	char* address;
	size_t id;
};

static int scanned_ports = 0, closed_threads = 0;
static bool Ports[65536] = { 0 }, run = false;
static bool threads_done[65536];

DWORD WINAPI ChkThread(LPVOID lParam)
{
	char port[6] = { 0 };
	Data* d = (Data*)lParam;
	FILE* outf = d->outf;
	SOCKET sock = INVALID_SOCKET;
	addrinfo addr = { 0 }, * result = NULL;
	addr.ai_family = AF_UNSPEC;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_protocol = IPPROTO_TCP;
	
	while (!run)
	{
		//we sleep to use less CPU time
		Sleep(10);
	}

	for (int i = d->port_min; i < d->port_max; i++, scanned_ports++)
	{
		//get the port in text
		_itoa(i, port, 10);
		//connect to 'address'
		INT res = getaddrinfo(d->address, port, &addr, &result);
		if (res)
		{
			puts("\nFailed to configure the address and\\or the port.");
			exit(-1);
		}
		for (addrinfo* ptr = result; ptr != NULL; ptr = ptr->ai_next)
		{
			sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (sock == INVALID_SOCKET)
			{
				puts("Error in creating socket.");
				exit(-1);
			}
			if (connect(sock, ptr->ai_addr, ptr->ai_addrlen) == SOCKET_ERROR)
			{
				//the connection failed. try another addrinfo
				closesocket(sock);
				sock = INVALID_SOCKET;
				continue;
			}
			break;
		}
		if (sock == INVALID_SOCKET)continue;
		//mark this port as 'open'
		Ports[i] = true;
		closesocket(sock);
		sock = INVALID_SOCKET;
	}
	
	threads_done[d->id] = true;
	closed_threads++;
	return 0;
}

struct ProgStruct
{
	FILE* outf;
	size_t threads;
};
DWORD WINAPI ProgressThread(LPVOID lParam)
{
	ProgStruct* ps = (ProgStruct*)lParam;
	time_t start = time(0);
	while (!run)
	{
		//we sleep to use less CPU time
		Sleep(10);
	}
	puts("Scanning...");
	bool stop = false;
	while (!stop && closed_threads < ps->threads && scanned_ports < 65536)
	{
		stop = true;
		printf("\rScanned ports: %d", scanned_ports);
		for (int i = 0; i < ps->threads; i++)
			stop = stop && threads_done[i];
		//we add this delay to use less CPU time
		Sleep(10);
	}
	printf("\rScanned ports: %d", scanned_ports);
	printf("\nThe scan has been finished.\nIt took %llu seconds.\n", time(0) - start);
	//write the results to the file
	for (int i = 0; i < 65536; i++)
		if (Ports[i])
			fprintf(ps->outf, "%d\n", i);
	fflush(ps->outf);
	ExitThread(0);
}

int main(int argc,char**argv)
{
	char port[6] = { 0 };
	SOCKET sock = INVALID_SOCKET;
	addrinfo addr = { 0 }, * result = NULL;
	addr.ai_family = AF_UNSPEC;
	addr.ai_socktype = SOCK_STREAM;
	addr.ai_protocol = IPPROTO_TCP;
	WSADATA wsa;

	Data* ThreadsData = NULL;
	HANDLE* threads = NULL;
	size_t threads_count = 0;

	if (argc != 4)
	{
		puts("For usage, see https://github.com/SKC-Developer/Port-Scanner.git or README.md in the source of your version.");
		return 0;
	}

	//set the WSA
	ErrChk(WSAStartup(MAKEWORD(2, 2), &wsa), "WSAStartup");

	//parse all the arguments
	FILE* outf;
	fopen_s(&outf, argv[2], "w");
	if (!outf)
	{
		printf("Failed to create \'%s\'.\n", argv[2]);
		return -1;
	}

	threads_count = _atoi64(argv[3]);
	if (threads_count > 65536 || threads_count == 0)
	{
		puts("Invalid number of threads. The number of threads should be more than 0 and less than 65537 (1-65536).");
		return -1;
	}
	ThreadsData = (Data*)malloc(sizeof(Data) * threads_count);
	threads = (HANDLE*)malloc(sizeof(HANDLE) * (threads_count + 1));
	if (ThreadsData == NULL || threads == NULL)
	{
		puts("Error in memory allocation.");
		return -1;
	}

	fprintf(outf, "Scan results of \'%s\'.\n", argv[1]);
	printf("Scanning open ports of \'%s\'.\n", argv[1]);

	//begin the scan
	ProgStruct ps = { outf, threads_count };
	threads[threads_count] = CreateThread(NULL, 0, ProgressThread, &ps, 0, NULL);
	if (!threads[threads_count])
	{
		puts("Error in creating threads...");
		return -1;
	}

	for (size_t l = 0; l < threads_count; l++)
	{
		ThreadsData[l] = { outf, l * (65536 / threads_count), (65536 / threads_count + l * (65536 / threads_count) < 65536 && l + 1 == threads_count) ? 65536 : (65536 / threads_count + l * (65536 / threads_count)), argv[1], l };
		threads[l] = CreateThread(NULL, 0, ChkThread, ThreadsData + l, 0, NULL);
		printf("\r%llu threads have been created.", l + 1);
		if (!threads[l])
		{
			puts("\nError in creating threads...");
			return -1;
		}
	}
	putchar('\n');
	run = true;

	//wait for the progress thread. it knows when the scan is done.
	DWORD ExitCode = STILL_ACTIVE;
	while (GetExitCodeThread(threads[threads_count], &ExitCode))
		if (ExitCode != STILL_ACTIVE)break;

	//clean & close
	puts("Cleaning up...");
	for (size_t l = 0; l < threads_count + 1; l++)
		CloseHandle(threads[l]);
	if (sock != INVALID_SOCKET)
		closesocket(sock);
	WSACleanup();
	free(threads);
	free(ThreadsData);
	fclose(outf);
	puts("Done!");
	return 0;
}