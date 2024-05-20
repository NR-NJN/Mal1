#include <windows.h>
#include <stdio.h>
int main(void)
{
	STARTUPINFO si = {0};
	PROCESS_INFORMATION pi = {0};


	if (!CreateProcess(
		L"C:\\Windows\\notepad.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		BELOW_NORMAL_PRIORITY_CLASS,
		NULL,
		NULL,
		&si,
		&pi
	   ))
	{
		printf("(-) failed to create process, error: %ld", GetLastError());
		return EXIT_FAILURE;
	}
	printf("(+) process started pid : %ld", pi.dwProcessId);
	return EXIT_SUCCESS;
}