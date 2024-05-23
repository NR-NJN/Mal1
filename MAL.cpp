#include <stdio.h>
#include <windows.h>


const char* OK = "[+]";
const char* INFO = "[*]";
const char* ERR = "[-]";

DWORD PID = NULL;
HANDLE hProcess;

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

	if (hProcess == NULL)
	{
		printf("%s couldnt get a handle to the process (%ld) error : %ld", ERR, PID, GetLastError());
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}