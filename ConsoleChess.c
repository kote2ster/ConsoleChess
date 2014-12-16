/**
 * @file ConsoleChess.c
 * @brief Simple Console Chess
 */
#include "move.h"

/** [TOC]
 * @mainpage Simple Console Chess
 * @section intro_sec Introduction
 *  @author    Ákos Köte
 *  @version   1.0
 *  @date      Last Modification: 2014.12.16.
 *
 * [GitHub Project README](https://github.com/kote2ster/ConsoleChess "GitHub Project")
 *
 * @section board_sec BOARD:
 *
 <PRE>
 * 00 10 20 30 40 50 60 70     a1 b1 c1 d1 e1 f1 g1 h1
 * 01 11 21 31 41 51 61 71     a2 b2 c2 d2 e2 f2 g2 h2
 * 02 12 22 32 42 52 62 72     a3 b3 c3 d3 e3 f3 g3 h3
 * 03 13 23 33 43 53 63 73 ->  a4 b4 c4 d4 e4 f4 g4 h4
 * 04 14 24 34 44 54 64 74     a5 b5 c5 d5 e5 f5 g5 h5
 * 05 15 25 35 45 55 65 75     a6 b6 c6 d6 e6 f6 g6 h6
 * 06 16 26 36 46 56 66 76     a7 b7 c7 d7 e7 f7 g7 h7
 * 07 17 27 37 47 57 67 77     a8 b8 c8 d8 e8 f8 g8 h8
 </PRE>
 */
int main(void)
{
    GAME *step;
    /*    int i=0; */
    /*    int j=0; */
    int end=0;
    step = (GAME*)malloc(sizeof(GAME));
    step->lap = WHITE; /* First round white */
    step->check = 0;   /* not in check */
    TableINI(step);
    do
    {
        WriteOut(step);
        GetStep(step);
        Move(step);
        if(!step->check && CheckForKingCheck(step)) step->check = 1;
        system("cls"); /* danger!! */
    }
    while(!end);
    return 0;
}
