/**
 * @file   stdafx.h
 * @brief  implement Precompiled technology
 * @author Arthur Mytsko
 */
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN     

#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>

typedef unsigned char UC;
typedef unsigned int UI;
 /**
   * @brief           Implement Tic-Tca-Toe game
   * @return	      void
   */
extern "C" __declspec(dllexport) void TicTacToe();

 /**
   * @brief           Implement player's move
   * @param	[in]      iBoard - pointer to game board
   * @return	      bool - true if everything good
   */
bool MakePlayerMove(UI *iBoard);

 /**
   * @brief           Implement computer's move
   * @param	[in]      iBoard - pointer to game board
   * @param	[in, out] bIsPcWin - pointer variable wich mean "Computer win"
   * @return	      bool - true if everything good
   */
bool MakePCMove(UI *iBoard, bool *bIsPcWin);

 /**
   * @brief           Print game board
   * @param	[in]      iBoard - link to game board
   * @return	      void
   */
void ShowBoard(UI &iBoard);

 /**
   * @brief           Implement findind sequence of two things('0' or 'X')
   * @param	[in]      iBoard - link to game board
   * @param	[in]      bIsFindToWin - true, when you need to find '0'
   * @return	      number wich means position in board, or 10 if there are no such position
   */
UC Find2X(UI &iBoard, bool bIsFindToWin);

 /**
   * @brief           Check all combination for one position to find 2 'X' or '0'
   * @param	[in]      iBoard - link to game board
   * @param	[in]      pos - position in board
   * @return	      true if poition is satisfies conditions
   */
bool Is2x(UI iBoard, UC pos);
