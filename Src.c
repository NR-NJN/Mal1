#include <windows.h>

void main() 
{
	 MessageBox(
		NULL,
		L"Your device will cease all operations immediately",
		L"Error",
		 0x00000030L|0x00000003L
	);
}