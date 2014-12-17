/**
 * @file move.h
 * @brief Header of moving functions
 */
#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <curses.h> /* For Windows ONLY */

/** @brief Enumeration for the pieces, black==lowercase, white==uppercase */
typedef enum pieces {PAWN,ROOK,KNIGHT,BISHOP,QUEEN,KING,pawn,rook,knight,bishop,queen,king,EPTY} PIECES;
/** @brief Color enum */
typedef enum color {WHITE,BLACK,EMPTY} COLOR;
/** @brief White/Black KING in check */
typedef enum chk {NOTINCHECK,WHITEKINGCHK,BLACKKINGCHK,BOTHKINGCHK,INVALIDMOVE} CHK;
/** @brief Menu controll */
typedef enum menucntr {REGEN,DONTEXIT,QUIT,CHECKMATE,UNDO} MENUCNTR;
/** @brief TABLE type */
typedef struct _TABLE
{
    PIECES piece; /**< piece enum */
    COLOR color;  /**< color enum */
} TABLE;
/** @brief PIECE type */
typedef struct _PIECE
{
    PIECES type;
    int col; /**< TABLE column */
    int row; /**< TABLE row */
} PIECE;
/** @brief GAME type list */
typedef struct _GAME
{
    COLOR lap; /**< Chess game round */
    PIECE from;     /**< Moved from */
    PIECE where;    /**< Moved to */
    TABLE t[8][8];  /**< Current table */
    int check;      /**< Checked? 1:yes */
    struct _GAME *next; /**< C list */
} GAME;
/** @brief Function pointer type */
typedef int (*UnaryFunc)(int);

void TableINI(GAME *step);

void WriteOut(GAME *game);
void WriteOutTable(enum pieces piece);

MENUCNTR GetStep(GAME *step);

CHK Move(GAME *step);
int ValidMove(GAME *step);
int CalculateMaxMove(GAME *step,enum pieces piece);
void GetMaxDirections(UnaryFunc FuncCol,UnaryFunc FuncRow,GAME *step,int *legitmove);
CHK CheckForKingCheck(GAME *step);
MENUCNTR CheckForCheckmate(GAME *step);

GAME *CreateList();
void InsertAtEnd(GAME *game,GAME *step);
void RemoveAtEnd(GAME *game,GAME *step);
void DeleteList(GAME *game);
int Increment(int a);
int Decrement(int a);
int DontChange(int a);

#endif // MOVE_H_INCLUDED
