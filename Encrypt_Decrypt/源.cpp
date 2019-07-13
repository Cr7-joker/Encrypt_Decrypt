#pragma comment(lib, "crypt32.lib")
#include <iostream>
#include <windows.h>

int main()
{
	DATA_BLOB DataIn;
	DATA_BLOB DataOut;
	DATA_BLOB DataVerify;
	BYTE* pbDataInput = (BYTE*)"Hello world of data protection.";
	DWORD cbDataInput = strlen((char*)pbDataInput) + 1;
	DataIn.pbData = pbDataInput;
	DataIn.cbData = cbDataInput;
	LPWSTR pDescrOut = NULL;
	//-------------------------------------------------------------------
	//  Begin processing.
	printf("The data to be encrypted is: %s\n", pbDataInput);
	//-------------------------------------------------------------------
	//  Begin protect phase.
	if (CryptProtectData(
		&DataIn,
		L"This is the description string.", // A description string. 
		NULL,                               // Optional entropy
		NULL,                               // Reserved.
		NULL,                      // Pass a PromptStruct.
		0,
		&DataOut))
	{
		printf("The encryption phase worked. \n");
	}
	else
	{
		printf("Encryption error!");
	}
	//-------------------------------------------------------------------
	//   Begin unprotect phase.
	if (CryptUnprotectData(
		&DataOut,
		&pDescrOut,
		NULL,                 // Optional entropy
		NULL,                 // Reserved
		NULL,        // Optional PromptStruct
		0,
		&DataVerify))
	{
		printf("The decrypted data is: %s\n", DataVerify.pbData);
		printf("The description of the data was: %S\n", pDescrOut);
	}
	else
	{
		printf("Decryption error!");
	}
	//-------------------------------------------------------------------
	//  Clean up.
	LocalFree(pDescrOut);
	LocalFree(DataOut.pbData);
	LocalFree(DataVerify.pbData);
} // End of main