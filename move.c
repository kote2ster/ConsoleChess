/**
 * @file move.c
 * @brief Implementations of moving functions
 */
#include "move.h"

/*-----------INITIALISING TABLE------------*/
/**
 * @brief Table initialiser, sets table to default starting position
 * @param [out] step GAME type, sets the default starting table
 */
void TableINI(GAME *step)
{
    int i,j;
    enum pieces a[8][8]=
    {
        {rook  ,knight,bishop,queen ,king  ,bishop,knight,rook},
        {pawn  ,pawn  ,pawn  ,pawn  ,pawn  ,pawn  ,pawn  ,pawn},
        {EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY},
        {EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY},
        {EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY},
        {EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY  ,EPTY},
        {PAWN  ,PAWN  ,PAWN  ,PAWN  ,PAWN  ,PAWN  ,PAWN  ,PAWN},
        {ROOK  ,KNIGHT,BISHOP,QUEEN ,KING  ,BISHOP,KNIGHT,ROOK}
    }; /*Temporary TABLE*/

    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            step->t[j][i].piece=a[i][j]; /*Basic position*/
        }
    }
    for(i=0; i<2; i++)
    {
        for(j=0; j<8; j++)
        {
            step->t[j][i].color=BLACK; /*BLACK top*/
        }
    }
    for(i=2; i<6; i++)
    {
        for(j=0; j<8; j++)
        {
            step->t[j][i].color=EMPTY; /*EMPTY*/
        }
    }
    for(i=6; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            step->t[j][i].color=WHITE; /*WHITE bottom*/
        }
    }
}
/*-----------------------------------------*/
/*-----------WRITING OUT------------*/
/**
 * @brief Writes out informations to Console Screen
 * @param [in] game GAME type, gets the current table
 */
void WriteOut(GAME *game)
{
    int i,j,nl;
    GAME *step=game;
    i=j=nl=0;
    while(step->next->next!=NULL)
    {
        if(i%2==0) mvchgat(2+j,41+12,10, A_NORMAL, 0, NULL);
        else       mvchgat(2+j,41   ,10, A_NORMAL, 0, NULL);
        if(i%34==0) {j=0; clear();}
        if(i%2==0) {j++; move(2+j,41);}
        else move(2+j,41+12);
        step=step->next;
        WriteOutTable(step->from.type);
        printw("%c%d->%c%d ",step->from.col+'A',step->from.row+1,step->where.col+'A',step->where.row+1);
        if(i%2==0) mvchgat(2+j,41   ,10, A_BLINK, 0, NULL);
        else       mvchgat(2+j,41+12,10, A_BLINK, 0, NULL);
        i++;
    }
    move(++nl,0);
    for(i=0; i<8; i++)
    {
        if(i==0)
        {
            printw("  |-A-|-B-|-C-|-D-|-E-|-F-|-G-|-H-|      Moves List"); /*Header*/
            move(++nl,0);
            printw("--+---+---+---+---+---+---+---+---+--");
            move(++nl,0);
        }
        for(j=0; j<8; j++)
        {
            if(j==0)
            {
                printw("%d |",i+1); /*Side*/
            }
            WriteOutTable(step->t[j][i].piece);
            if(j==7)
            {
                printw(" %d",i+1); /*Side*/
            }
        }
        move(++nl,0);
        printw("--+---+---+---+---+---+---+---+---+--");
        move(++nl,0);
        if(i==7)
        {
            printw("  |-A-|-B-|-C-|-D-|-E-|-F-|-G-|-H-|"); /*Footer*/
            move(++nl,0);
            move(++nl,0);
        }
    }
    if(step->lap == WHITE) printw("Current color: WHITE\n");
    if(step->lap == BLACK) printw("Current color: BLACK\n");
    if(step->check) printw("CHECK!");
    move(++nl,0);
    refresh();
}
/**
 * @brief Writes out pieces @see WriteOut()
 * @param [in] piece
 */
void WriteOutTable(enum pieces piece)
{
    switch(piece)
    {
    case PAWN:
            printw("#WP");
        break;
    case ROOK:
        printw("#WR");
        break;
    case KNIGHT:
        printw("#WK");
        break;
    case BISHOP:
        printw("#WB");
        break;
    case QUEEN:
        printw("#WQ");
        break;
    case KING:
        printw("#WK");
        break;
    case pawn:
        printw("#Bp");
        break;
    case rook:
        printw("#Br");
        break;
    case knight:
        printw("#Bk");
        break;
    case bishop:
        printw("#Bb");
        break;
    case queen:
        printw("#Bq");
        break;
    case king:
        printw("#Bk");
        break;
    case EPTY:
        printw("___");
        break;
    }
    printw("|");
}
/*----------------------------------*/
/**
 * @brief Handles input coordinates
 * @param [out] step GAME type, sets FROM-TO coordinates
 * @return if player entered r then regen, if q quit
 */
MENUCNTR GetStep(GAME *step)
{
    int valid,result;
    char temp; /*temp*/
    char from_char; /*temp*/
    int from_number; /*temp*/
    char to_char; /*temp*/
    int to_number; /*temp*/
    do
    {
        move(LINES-3,0);
        clrtobot();
        flushinp();
        printw("From:  ");
        result=scanw("%c%d%c%c%d",&from_char,&from_number,&temp,&to_char,&to_number); /*try to get all at once*/
        if(from_char=='r') return REGEN; /*Regenerate signal*/
        if(from_char=='q') return QUIT; /*Exit signal*/
        if(from_char=='u') return UNDO; /*Undo signal*/
        if(result==2)
        {
            printw("Where: ");
            scanw("%c%d",&to_char,&to_number);
        }
        valid=1;
        if('a'<=from_char && from_char<='h' &&
                'a'<=to_char   && to_char  <='h')
        {
            from_char=from_char-'a'; /*Converting to number*/
            to_char=to_char-'a';
        }
        else
            valid=0; /*error*/
        if(1<=from_number && from_number<=8 &&
                1<=to_number && to_number<=8)
        {
            from_number--;
            to_number--;
        }
        else
            valid=0; /*error*/
        if(!valid || step->t[(int)from_char][from_number].piece==EPTY ||
                step->lap != step->t[(int)from_char][from_number].color || step->lap == step->t[(int)to_char][to_number].color ||
                step->t[(int)to_char][to_number].piece==KING || step->t[(int)to_char][to_number].piece==king)
        {
            valid=0; /*error*/
            move(LINES-1,0);
            printw("Error");
            getch();
        }
        refresh();
    }
    while(!valid);

    step->from.col  = from_char;
    step->from.row  = from_number;
    step->where.col = to_char;
    step->where.row = to_number;
    step->from.type = step->t[(int)from_char][from_number].piece; /*Selected piece*/
    return DONTEXIT; /*do not exit from while*/
}
/*-------------MOVES---------------*/
/**
 * @brief Moves with piece if possible @see ValidMove()
 * @param [out] step GAME type, changes TABLE
 * @return enum chk type, any king in check or invalid move
 */
CHK Move(GAME *step)
{
    TABLE tempFrom;
    TABLE tempWhere;
    enum chk Control;
    if(ValidMove(step))
    {
        /*OK*/
        tempFrom = step->t[step->from.col][step->from.row];
        tempWhere = step->t[step->where.col][step->where.row];
        step->t[step->where.col][step->where.row] = step->t[step->from.col][step->from.row]; /*Copying piece color and type*/
        step->t[step->from.col][step->from.row].piece = EPTY;
        step->t[step->from.col][step->from.row].color = EMPTY;
        /*Check if any king will be in check*/
        Control = CheckForKingCheck(step);
        if (    (step->lap==WHITE&&Control==WHITEKINGCHK) ||
                (step->lap==BLACK&&Control==BLACKKINGCHK) ||
                Control==BOTHKINGCHK)
        {
            step->t[step->from.col][step->from.row]   = tempFrom; /*Undo move*/
            step->t[step->where.col][step->where.row] = tempWhere;
            Control = INVALIDMOVE;
        }
        else
        {
            if(step->check) step->check=0; /*Not in check anymore*/
            if(step->lap == WHITE) step->lap = BLACK; /*Turning lap..*/
            else if(step->lap ==BLACK) step->lap = WHITE;
        }
    }
    else Control = INVALIDMOVE;
    return Control;
}
/**
 * @brief Checks if move was vaild
 * @param [in] step GAME type, informations
 * @return if move was correct 1 (true) else 0 (false)
 */
int ValidMove(GAME *step)
{
    if(     step->t[step->where.col][step->where.row].color==BLACK ||
            step->t[step->where.col][step->where.row].piece==EPTY)  /*Moving with white*/
    {
        switch(step->from.type)
        {
        case PAWN:
            /*  -X-  //
            //   @   */
            if (     (step->from.col==step->where.col && step->from.row-1==step->where.row &&
                      step->t[step->where.col][step->where.row].color == EMPTY) ||
                     (step->from.row==6 &&
                      step->from.col==step->where.col && step->from.row-2==step->where.row) ||
                     (step->from.col-1  ==step->where.col && step->from.row-1==step->where.row &&
                      step->t[step->where.col][step->where.row].color == BLACK) ||
                     (step->from.col+1  ==step->where.col && step->from.row-1==step->where.row &&
                      step->t[step->where.col][step->where.row].color == BLACK))
                return 1;
            break;
        case ROOK:
            if(CalculateMaxMove(step,ROOK)) return 1;
            break;
        case KNIGHT:
            /*  X X  //
            // X   X //
            //   @   //
            // X   X //
            //  X X  */
            if (    (step->from.col-2==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row-2==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row-2==step->where.row) ||
                    (step->from.col+2==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col+2==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row+2==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row+2==step->where.row) ||
                    (step->from.col-2==step->where.col && step->from.row+1==step->where.row)) return 1;
            break;
        case BISHOP:
            if(CalculateMaxMove(step,BISHOP)) return 1;
            break;
        case QUEEN:
            if(CalculateMaxMove(step,QUEEN)) return 1;
            break;
        case KING:
            /*  XXX  //
            //  X@X  //
            //  XXX  */
            if (    (step->from.col-1==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col  ==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row  ==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col  ==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row  ==step->where.row)) return 1;
            break;
        default:
            break;
        }
    }
    if (    step->t[step->where.col][step->where.row].color==WHITE ||
            step->t[step->where.col][step->where.row].piece==EPTY)  /*Moving with black*/
    {
        switch(step->from.type)
        {
        case pawn:
            /*   @   //
            //  -X-  */
            if (     (step->from.col==step->where.col && step->from.row+1==step->where.row &&
                      step->t[step->where.col][step->where.row].color == EMPTY) ||
                     (step->from.row==1 &&
                      step->from.col==step->where.col && step->from.row+2==step->where.row) ||
                     (step->from.col+1  ==step->where.col && step->from.row+1==step->where.row &&
                      step->t[step->where.col][step->where.row].color == WHITE) ||
                     (step->from.col-1  ==step->where.col && step->from.row+1==step->where.row &&
                      step->t[step->where.col][step->where.row].color == WHITE))
                return 1;
            break;
        case rook:
            if(CalculateMaxMove(step,rook)) return 1;
            break;
        case knight:
            /*  X X  //
            // X   X //
            //   @   //
            // X   X //
            //  X X  */
            if (    (step->from.col-2==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row-2==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row-2==step->where.row) ||
                    (step->from.col+2==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col+2==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row+2==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row+2==step->where.row) ||
                    (step->from.col-2==step->where.col && step->from.row+1==step->where.row)) return 1;
            break;
        case bishop:
            if(CalculateMaxMove(step,bishop)) return 1;
            break;
        case queen:
            if(CalculateMaxMove(step,queen)) return 1;
            break;
        case king:
            /*  XXX  //
            //  X@X  //
            //  XXX  */
            if (    (step->from.col-1==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col  ==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row-1==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row  ==step->where.row) ||
                    (step->from.col+1==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col  ==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row+1==step->where.row) ||
                    (step->from.col-1==step->where.col && step->from.row  ==step->where.row)) return 1;
            break;
        default:
            break;
        }
    }
    return 0;
}
/**
 * @brief Calculates max possible move for some pieces
 * @param [in] step GAME type, informations
 * @param [in] piece with which piece
 * @return if move was correct 1 (true) else 0 (false)
 */
int CalculateMaxMove(GAME *step,enum pieces piece)
{
    int legitmove = 0;
    switch(piece) /*Only Rook Bishop Queen*/
    {
    case ROOK:
    case rook:
        if(!legitmove)GetMaxDirections(DontChange,Decrement ,step,&legitmove); /*UP*/
        if(!legitmove)GetMaxDirections(Increment ,DontChange,step,&legitmove); /*RIGHT*/
        if(!legitmove)GetMaxDirections(DontChange,Increment ,step,&legitmove); /*DOWN*/
        if(!legitmove)GetMaxDirections(Decrement ,DontChange,step,&legitmove); /*LEFT*/
        break;
    case BISHOP:
    case bishop:
        if(!legitmove)GetMaxDirections(Decrement ,Decrement ,step,&legitmove); /*UPLEFT*/
        if(!legitmove)GetMaxDirections(Increment ,Decrement ,step,&legitmove); /*UPRIGHT*/
        if(!legitmove)GetMaxDirections(Increment ,Increment ,step,&legitmove); /*DOWNRIGHT*/
        if(!legitmove)GetMaxDirections(Decrement ,Increment ,step,&legitmove); /*DOWNLEFT*/
        break;
    case QUEEN:
    case queen:
        if(!legitmove)GetMaxDirections(Decrement ,Decrement ,step,&legitmove); /*UPLEFT*/
        if(!legitmove)GetMaxDirections(DontChange,Decrement ,step,&legitmove); /*UP*/
        if(!legitmove)GetMaxDirections(Increment ,Decrement ,step,&legitmove); /*UPRIGHT*/
        if(!legitmove)GetMaxDirections(Increment ,DontChange,step,&legitmove); /*RIGHT*/
        if(!legitmove)GetMaxDirections(Increment ,Increment ,step,&legitmove); /*DOWNRIGHT*/
        if(!legitmove)GetMaxDirections(DontChange,Increment ,step,&legitmove); /*DOWN*/
        if(!legitmove)GetMaxDirections(Decrement ,Increment ,step,&legitmove); /*DOWNLEFT*/
        if(!legitmove)GetMaxDirections(Decrement ,DontChange,step,&legitmove); /*LEFT*/
        break;
    default:
        return 0;
        break;
    }
    if(legitmove) return 1;
    return 0;
}
/**
 * @brief Main function in @see CalculateMaxMove()
 * @param [in] FuncCol Function pointer
 * @param [in] FuncRow Function pointer
 * @param [in] step GAME type
 * @param [out] legitmove if move was correct 1 (true) else 0 (false)
 */
void GetMaxDirections(UnaryFunc FuncCol,UnaryFunc FuncRow,GAME *step,int *legitmove)
{
    int col,row,found,precol,prerow;
    precol = col = step->from.col;
    prerow = row = step->from.row;
    found = 0;
    while(row>=0 && col>=0 && row<=7 && col<=7 && !found)
    {
        col = FuncCol(col);
        row = FuncRow(row);
        if(row>=0 && col>=0 && row<=7 && col<=7 && /*Protection from overindexing*/
                step->t[col][row].piece!=EPTY)
        {
            /*We can't hit the piece if it's the same color or it's a king*/
            if(step->lap == step->t[col][row].color)
            {
                col = precol;
                row = prerow;
            }
            found = 1;
        }
        if(step->where.col == col && step->where.row == row) /*Found a legit move*/
        {
            *legitmove = 1;
        }
        precol = FuncCol(precol);
        prerow = FuncRow(prerow);
    }
    if(col == step->from.col && row == step->from.row) /*Nothing changed, error*/
    {
        *legitmove = 0;
    }
}
/**
 * @brief Checks if any king is in check
 * @param [in] step GAME type
 * @return enum chk if any king is in check
 * @details Resimulates game, with moving where: to kings
 */
CHK CheckForKingCheck(GAME *step)
{
    int i,j,check;
    PIECE WhiteKing;
    PIECE BlackKing;
    GAME tempgame = *step;
    WhiteKing.type = KING;
    BlackKing.type = king;
    WhiteKing.col = 0;
    WhiteKing.row = 0;
    BlackKing.col = 0;
    BlackKing.row = 0;
    check = NOTINCHECK;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            if(tempgame.t[j][i].piece==KING)
            {
                WhiteKing.col = j;
                WhiteKing.row = i;
            }
            if(tempgame.t[j][i].piece==king)
            {
                BlackKing.col = j;
                BlackKing.row = i;
            }
        }
    }
    /*First with WHITE KING*/
    tempgame.lap = BLACK;
    tempgame.where.col = WhiteKing.col;
    tempgame.where.row = WhiteKing.row;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            tempgame.from.col = j;
            tempgame.from.row = i;
            if(BLACK == tempgame.t[j][i].color) tempgame.from.type = tempgame.t[j][i].piece;
            if(BLACK == tempgame.t[j][i].color && ValidMove(&tempgame)) check |= WHITEKINGCHK; /*White KING in check*/
        }
    }
    /*Secondly with BLACK KING*/
    tempgame.lap = WHITE;
    tempgame.where.col = BlackKing.col;
    tempgame.where.row = BlackKing.row;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            tempgame.from.col = j;
            tempgame.from.row = i;
            if(WHITE == tempgame.t[j][i].color) tempgame.from.type = tempgame.t[j][i].piece;
            if(WHITE == tempgame.t[j][i].color && ValidMove(&tempgame)) check |= BLACKKINGCHK; /*Black KING in check*/
        }
    }
    return check;
}
/**
 * @brief Checks if the check was a checkmate
 * @param [in] step GAME type
 * @param [out] over sets to 'y' when user wants to play again
 * @details Resimulates game, with moving everywhere and checks if something can prevent check
 */
MENUCNTR CheckForCheckmate(GAME *step)
{
    int i,j,k,l;
    GAME tempgame = *step;
    TABLE tempFrom;
    TABLE tempWhere;
    for(i=0; i<8; i++)
    {
        for(j=0; j<8; j++)
        {
            tempgame.from.col = j;
            tempgame.from.row = i;
            tempgame.from.type = tempgame.t[tempgame.from.col][tempgame.from.row].piece;
            for(k=0; k<8; k++)
            {
                for(l=0; l<8; l++)
                {
                    tempgame.where.col = l;
                    tempgame.where.row = k;
                    if(tempgame.lap == tempgame.t[tempgame.from.col][tempgame.from.row].color && ValidMove(&tempgame))
                    {
                        /*OK*/
                        tempFrom = tempgame.t[tempgame.from.col][tempgame.from.row];
                        tempWhere = tempgame.t[tempgame.where.col][tempgame.where.row];
                        tempgame.t[tempgame.where.col][tempgame.where.row] = tempgame.t[tempgame.from.col][tempgame.from.row]; /*Copying piece color and type*/
                        tempgame.t[tempgame.from.col][tempgame.from.row].piece = EPTY;
                        tempgame.t[tempgame.from.col][tempgame.from.row].color = EMPTY;
                        /*Moved with king into check or still in check*/
                        if ((tempgame.lap==WHITE&&CheckForKingCheck(&tempgame)==WHITEKINGCHK)||
                                (tempgame.lap==BLACK&&CheckForKingCheck(&tempgame)==BLACKKINGCHK))
                        {
                            tempgame.t[tempgame.from.col][tempgame.from.row]   = tempFrom; /*Undo move*/
                            tempgame.t[tempgame.where.col][tempgame.where.row] = tempWhere;
                        }
                        else return DONTEXIT; /*there is a possible move*/
                    }
                }
            }
        }
    }
    /*There was not a possible move*/
    return CHECKMATE;
}
/**
 * @brief Creates GAME list
 * @return First element in list
 */
GAME *CreateList()
{
    GAME *gamehead,*gametail;
    gamehead = (GAME*)malloc(sizeof(GAME));
    gametail = (GAME*)malloc(sizeof(GAME));
    gamehead->next=gametail;
    gametail->next=NULL;
    gamehead->lap = WHITE; /* First round white */
    gamehead->check = 0;   /* not in check */
    TableINI(gamehead);
    return gamehead;
}
/**
 * @brief Insert element at end
 * @param [in] game main list
 * @param [in] step new element
 * @return First element in list
 */
void InsertAtEnd(GAME *game,GAME *step)
{
    GAME *curr,*temp;
    curr = game;
    while(curr->next->next!=NULL)
    {
        curr = curr->next;
    }
    temp = (GAME*)malloc(sizeof(GAME));
    *temp = *step;
    temp->next = curr->next;
    curr->next = temp;
}
/**
 * @brief Remove element at end (Undo)
 * @param [in] game main list
 * @param [out] step undo step
 * @return First element in list
 */
void RemoveAtEnd(GAME *game,GAME *step)
{
    GAME *curr,*currbefore;
    curr = game;
    currbefore = game;
    while(curr->next->next!=NULL)
    {
        currbefore = curr;
        curr = curr->next;
    }
    currbefore->next = curr->next;
    if(curr != game) free(curr);
    if(currbefore == game)
    {
        game->lap = WHITE; /* First round white */
        game->check = 0;   /* not in check */
        TableINI(game);
        *step = *game;
    }
    else
        *step = *currbefore;
}
/**
 * @brief Delete list
 * @param [in] game main list
 */
void DeleteList(GAME *game)
{
    GAME *curr,*currbefore;
    curr = game;
    currbefore = game;
    while(curr->next!=NULL)
    {
        currbefore = curr;
        curr = curr->next;
        free(currbefore);
    }
}
int Increment(int a)
{
    return ++a;
}
int Decrement(int a)
{
    return --a;
}
int DontChange(int a)
{
    return a;
}
/*---------------------------------*/
