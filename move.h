/**
 * @file move.h
 * @brief Header of moving functions
 */
#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/** @brief Enumeration for the pieces, black==lowercase, white==uppercase */
typedef enum pieces {PAWN,ROOK,KNIGHT,BISHOP,QUEEN,KING,pawn,rook,knight,bishop,queen,king,EPTY} PIECES;
/** @brief Color enum */
typedef enum color {WHITE,BLACK,EMPTY} COLOR;
/** @brief White/Black KING in check */
typedef enum chk {WHITEKINGCHK=1,BLACKKINGCHK} CHK;
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
/** @brief DIRECTION type */
typedef struct _DIRECTION
{
    PIECE upleft;
    PIECE up;
    PIECE upright;
    PIECE right;
    PIECE downright;
    PIECE down;
    PIECE downleft;
    PIECE left;
} DIRECTION;
/** @brief Function pointer type */
typedef int (*UnaryFunc)(int);

void TableINI(GAME *step);

void WriteOut(GAME *step);
void WriteOutTable(enum pieces piece);

char GetStep(GAME *step);

void Move(GAME *step);
int ValidMove(GAME *step);
int CalculateMaxMove(GAME *step,enum pieces piece);
void GetMaxDirections(UnaryFunc FuncCol,UnaryFunc FuncRow,GAME *step,int *legitmove);
int CheckForKingCheck(GAME *step);
void CheckForCheckMate(GAME *step,char *over);

int Increment(int a);
int Decrement(int a);
int DontChange(int a);

#endif // MOVE_H_INCLUDED
