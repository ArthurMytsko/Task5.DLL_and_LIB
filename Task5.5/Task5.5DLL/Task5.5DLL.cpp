/**
 * @file   Task5.5DLL.cpp
 * @brief  Implement Tic-Tac-Toe game
 * @author Arthur Mytsko
 */

#include "stdafx.h"

extern "C" __declspec(dllexport) void TicTacToe()
{
	char cKey;
	do
	{
		printf("Who make first move?\n('p' - player, 'c' - computer)\n");
		cKey = _getch();
	}
	while( !(cKey == 'p' || cKey == 'c') );

	UI iBoard = 0;
	bool bPlayersMove = cKey == 'p';
	bool bIsPcWin = false;
	register int i = 0;

	ShowBoard(iBoard);
	while(i < 9)
	{
		ShowBoard(iBoard);
		if(bPlayersMove)
		{
			if(!MakePlayerMove(&iBoard) )
			{
				printf("Error was occured...");
				continue;
			}
			else
			{
				bPlayersMove = false;
			}
		}
		else
		{
			if(!MakePCMove(&iBoard, &bIsPcWin) )
			{
				printf("Error was occured...");
				continue;
			}
			else
			{
				bPlayersMove = true;				
			}
			if(bIsPcWin)
			{
				ShowBoard(iBoard);
				printf("Game over.Computer won:)\n");
				_getch();
				return;
			}
		}
		++i;
	}
	ShowBoard(iBoard);
	printf("\nGame over.Nobody won...");
	_getch();
}

bool MakePlayerMove(UI *iBoard)
{
	if(iBoard == nullptr)
	{
		return false;
	}
	char cKey = 0;
CYCLE:
	while(cKey <= 0x30 || cKey > 0x39)
	{
		printf("\nEnter position('i' - info):");
		cKey = _getch();
		// print info
		if(cKey == 'i')
		{
			printf("\nEach cell response one digit like this:\n");
			printf("1%c2%c3\n%c%c%c%c%c\n", 179, 179, 196, 196, 196, 196, 196);
			printf("4%c5%c6\n%c%c%c%c%c\n", 179, 179, 196, 196, 196, 196, 196);
			printf("7%c8%c9\n", 179, 179, 196, 196, 196, 196, 196);
			continue;
		}
	}
	if( (*iBoard | (*iBoard >> 9) ) & (0x1 << (cKey - 0x31) ) )
	{
		printf("\nError, this cell is not empty...\n");
		cKey = 0;
		goto CYCLE;
	}
	while(cKey <= 0x30 || cKey > 0x39);

	*iBoard |= 0x1 << (cKey -  0x31);

	return true;
}

bool MakePCMove(UI *iBoard, bool *bIsPcWin)
{
	Sleep(500);
	if(iBoard == nullptr)
	{
		return false;
	}

	// if board is empty
	if(*iBoard == 0)
	{
		*iBoard = 0x2000;
		return true;
	}

	//if there is one element in the center
	if(*iBoard == 0x10)
	{
		srand( (unsigned)time(NULL) );
		UC uRandPos = (rand() % 5 - 1);
		if(uRandPos == 2)
		{
			*iBoard |= 0x1 << 11;
		}
		else
		{
			*iBoard |= 0x1 << (9 + uRandPos*2);
		}
		return true;
	}
	// find cell to win
	UC ucPut = Find2X(*iBoard, true);
	if(ucPut == 10) // if there are not position to win
	{
		// find cell to lose
		ucPut = Find2X(*iBoard, false);
		if(ucPut == 10) // if there no position to lose
		{
			// if center is free
			if( !(*iBoard & 0x2010) )
			{
				*iBoard |= 0x2000;
				return true;
			}
			// if there are no '0'
			if( (*iBoard && 0x3FE00) == 0)
			{
				if(*iBoard & 0X1)
				{
					*iBoard |= 0X1;
				}
				else
				{
					*iBoard |= 0x4;
				}
				return true;
			}
			else
			{
				//inversion(all board in first 9 bits)
				UI iTemp = ~( (*iBoard | (*iBoard >> 9) ) & 0x1FF);

				if( (iTemp & 0x145) != 0) // if there are free cells in coners
				{
					iTemp = iTemp & 0x145;
				}

				// first empty bit
				UI iFirstEmpty = (iTemp & (iTemp - 1) ) ^ iTemp;
				*iBoard |= iFirstEmpty << 9;
				return true;
			}
		}
		else
		{
			*iBoard |= 0X1 << (ucPut + 9);
		}
	}
	else
	{
		*iBoard |= 0x1 << (ucPut + 9);
		*bIsPcWin = true;
	}
	return true;
}

void ShowBoard(UI &iBoard)
{
	system("cls");
	UI iMaskX = 0x1;	// for 'X'
	UI iMask0 = 0x200;	// for '0'

	for(register int i = 0; i < 5; ++i)
	{
		if( (i == 1) || (i == 3) )
		{
			printf("%c%c%c%c%c\n", 196, 196, 196, 196, 196); // _____
			continue;
		}
		for(register int j = 0; j < 5; ++j)
		{
			if( (j == 1) || (j == 3))
			{
				printf("%c", 179); // |
				continue;
			}
			printf("%c", ( (iBoard & iMaskX) != 0) * 'x' + ( (iBoard & iMask0) != 0) * '0');
			iMask0 <<= 1;
			iMaskX <<= 1;
		}
		printf("\n");
	}
	printf("\n");
}

UC Find2X(UI &iBoard, bool bIsFindToWin)
{
	register int i = 0;

	UI mask = 0x1;

	
	for(i = 0; i < 9; i++)
	{
		// chek empty positions
		if( ( (iBoard & mask) == 0) && ( ( (iBoard >> 9) & mask ) == 0) )
		{
			if(bIsFindToWin)
			{
				if(Is2x(iBoard >> 9, i) )
				{
					return i;
				}
			}
			else
			{
				if(Is2x(iBoard, i) )
				{
					return i;
				}
			}

		}
		mask <<= 1;
	}
	return 10;
}

bool Is2x(UI iBoard, UC pos)
{
	switch(pos)
	{
	case 0:
		return ( (iBoard & 0x6) == 0x6) || ( (iBoard & 0x48) == 0x48) || ( (iBoard & 0x110) == 0x110);
	case 1:
		return ( (iBoard & 0x5) == 0x5) || ( (iBoard & 0x90) == 0x90);
	case 2:
		return ( (iBoard & 0x3) == 0x3) || ( (iBoard & 0x120) == 0x120) || ( (iBoard & 0x50) == 0x50);
	case 3:
		return ( (iBoard & 0x41) == 0x41) || ( (iBoard & 0x30) == 0x30);
	case 4:
		return ( (iBoard & 0x101) == 0x101) || ( (iBoard & 0x44) == 0x44) ||
			     ( (iBoard & 0x82) == 0x82) || ( (iBoard & 0x28) == 0x28);
	case 5:
		return ( (iBoard & 0x18) == 0x18) || ( (iBoard & 0x104) == 0x104);
	case 6:
		return ( (iBoard & 0x9) == 0x9) || ( (iBoard & 0x180) == 0x180) || ( (iBoard & 0x14) == 0x14);
	case 7:
		return ( (iBoard & 0x140) == 0x140) || ( (iBoard & 0x12) == 0x12);
	case 8:
		return ( (iBoard & 0xC0) == 0xC0) || ( (iBoard & 0x24) == 0x24) || ( (iBoard & 0x11) == 0x11);
	default:
		return iBoard;
	}
}