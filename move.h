/**
 * @file move.h
 * @brief Header of moving functions
 */
#ifndef MOVE_H_INCLUDED
#define MOVE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

/** @brief Enumeration for the pieces, black==lowercase, white==uppercase */
enum pieces {PAWN,ROOK,KNIGHT,BISHOP,QUEEN,KING,pawn,rook,knight,bishop,queen,king,EPTY};
/** @brief Color enum */
enum color {WHITE,BLACK,EMPTY};
/** @brief TABLE type */
typedef struct _TABLE
{
    enum pieces piece; /**< piece enum */
    enum color color;  /**< color enum */
} TABLE;
/** @brief PIECE type */
typedef struct _PIECE
{
    enum pieces type;
    int col; /**< TABLE column */
    int row; /**< TABLE row */
} PIECE;
/** @brief GAME type list */
typedef struct _GAME
{
    enum color lap; /**< Chess game round */
    PIECE from;     /**< Moved from */
    PIECE where;    /**< Moved to */
    TABLE t[8][8];  /**< Current table */
    int check;      /**< Checked? */
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

void GetStep(GAME *step);

void Move(GAME *step);
int ValidMove(GAME *step);
int CalculateMaxMove(GAME *step,enum pieces piece);
void GetMaxDirections(UnaryFunc FuncCol,UnaryFunc FuncRow,GAME *step,int *legitmove);
int CheckForKingCheck(GAME *step);

int Increment(int a);
int Decrement(int a);
int DontChange(int a);

#endif // MOVE_H_INCLUDED
