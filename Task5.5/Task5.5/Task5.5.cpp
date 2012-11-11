/**
 * @file   Task5.5.cpp
 * @brief  Implement using DLL of Tic-Tac-Toe game
 * @author Arthur Mytsko
 */

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	// load dll library
	HINSTANCE hMyDll=LoadLibrary(L"Task5.5DLL.dll");

	if(hMyDll==NULL) // if load if fail
	{
		printf("Unable to load library!\n");
		_getch();
		return 0;
	}
	
	Function *FunTicTacToe;

	// get TicTacToe function
	FunTicTacToe = (Function *)GetProcAddress((HMODULE)hMyDll, "TicTacToe");

	if(!(FunTicTacToe) ) // if getting functions is fail
	{
		printf("Unable to get function!\n");
		_getch();
		return 0;
	}

	do
	{
		system("cls");
		FunTicTacToe();
		printf("\nPlay again?('y' - ok):");
	}
	while(_getch() == 'y');

	// free dll library
	FreeLibrary(hMyDll); 

	return 0;
}

