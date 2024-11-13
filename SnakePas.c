
/* Output from p2c 2.00.Oct.15, the Pascal-to-C translator */
/* From input file "snake.pas" */

/* revived 6/9/17 - tct */
/* added pause (P) toggle */

#define DELAYSECONDS 0.2

//from p2c.h
#define boolean char
#define true 1
#define false 0
#include <ctype.h>

// kbhit
// AWW: support kbhit() on APPLE
// from  https://cboard.cprogramming.com/c-programming/178177-very-simple-program-impossible-create-mac.html
#if defined(__APPLE__) || defined(__linux__) // https://stackoverflow.com/questions/6802903/c-ifdef-mac-os-x-question

#ifndef GETCH_H_INCLUDED
#define GETCH_H_INCLUDED

#include <stdio.h>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h> //for new version of kbhit
#include <sys/ioctl.h>

#include <stdlib.h>
#include <termios.h>

// call stty_clflag(0,0,&old_clflag) to revert to old flags
int stty_clflag(int setbits, int clearbits, int* old_clflag)
{
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    if (setbits | clearbits)
    {
        if (old_clflag)
        {
            *old_clflag = term.c_lflag;
        }
        term.c_lflag |= setbits;
        term.c_lflag &= ~(clearbits);
    }
    else
    {
        if (old_clflag)
        {
            term.c_lflag = *old_clflag;
        }
    }
    return tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

/// reads from keypress, doesn't echo
int getch()
{
    struct termios t, told;
    int ch;
    tcgetattr(STDIN_FILENO, &t);
    told = t;
    t.c_lflag &= ~(ECHO | ICANON | ISIG |
        ECHOE | ECHOK | ECHONL);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
    ch = fgetc(stdin); // ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &told);
    return ch;
}

// braucht keine Bestätigung mit Enter-Taste
int kbhit(void)
{
    struct termios t;
    tcflag_t old_c_lflag;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &t);

    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    old_c_lflag = t.c_lflag;
    t.c_lflag &= ~(ECHO | ICANON | ISIG |
        ECHOE | ECHOK | ECHONL);
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    ch = fgetc(stdin);

    fcntl(STDIN_FILENO, F_SETFL, oldf);

    t.c_lflag = old_c_lflag;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}
#endif // GETCH_H_INCLUDED

#elif defined _WIN32 || defined _WIN64
// this works under Windows
#undef boolean
#include <windows.h>
#define ECHO 0

#include <conio.h>
#include <stdio.h>
#include <stdlib.h>

void usleep(long uSec) {
    Sleep(uSec / 1000);
}

//int getch() { return _getch(); } // compiler error does not go away
#define getch _getch
#define kbhit _kbhit

int stty_clflag(int _setbits, int _clearbits, int _dummy)
{
    return 0;
}
#else
#error unknown architecture
#endif
// /kbhit

//#include <p2c/p2c.h>
#include <time.h>

#define playerchar 'I'
#define snakechar 'S'
#define moneychar '$'
#define doorchar '#'

#define upcommand    'W' // 'U'
#define downcommand  'S' // 'N'
#define leftcommand  'A' // 'H'
#define rightcommand 'D' // 'J'
#define quitcommand  'Q' // 'Q'
#define pausecommand 'P' // 'P'

#define snakelength 5
#define height 23
#define width 79
#define moneyworth 25

#ifdef __GNUC__
#define INLINE inline __attribute__((always_inline))
#else
#define INLINE inline
#endif
INLINE void putstr(char* input)
{
    fputs(input, stdout);
}
void home()
{
    putstr((char*)"\x1b[0H");
}
void cls()
{
    putstr((char *)"\x1b[2J");
    home();
}

typedef struct coordinate
{
    long x, y;
} coordinate;

typedef coordinate snaketype[snakelength];
typedef enum
{
    playerthing,
    snakething,
    moneything,
    doorthing,
    emptything,
    scorething
} thing;

static snaketype snake;
static coordinate player, money, door;
static long score;
static boolean left, eaten;

static thing screen[width + 1][height + 1];

static char lookslike[6];

static void CursorOff()
{
    printf("\033[?25l"); /* ANSI */
}

static void CursorOn()
{
    printf("\033[?25h"); /* ANSI */
}

void gotoxy(int x, int y)
{
    printf("\033[%d;%dH", y, x);
}

/* returns a random integer between min and max */

static long randint(long min, long max)
{
    return (min + rand() % (max - min + 1));
}

static void instructions()
{
    char answer;

    printf("SNAKE.PAS 6/9/17 7/3/23\n");
    printf("Do you want instructions? ");
    answer = getch();
    if (answer == '\n')
        answer = ' ';
    putchar('\n');
    while (toupper(answer) != 'N' && toupper(answer) != 'Y')
    {
        printf("Please enter Yes or No.\n");
        answer = getch();
        if (answer == '\n')
            answer = ' ';
        putchar('\n');
    }
    if (toupper(answer) != 'Y')
        return;
    printf("\nThe object of SNAKE is to get as much money ($) to the door (#) as possible.\n");
    printf("The snake tries to prevent you (I). As you get more money, he tries\n");
    printf("more and more successfully. You move up, down, left, and right\n");
    printf("by typing W, S, A and D respectively. You cannot move diagonally\n");
    printf("though the snake can. You may quit with Q. You may pause with P (and resume with another P).\n\n");
    printf("Type any key to continue ");
    answer = getch();
    if (answer == '\n')
        answer = ' ';
}

static void initialize()
{
    long x, y;

    instructions();
    CursorOff();
    for (x = 0; x <= width; x++)
    {
        for (y = 0; y <= height; y++)
            screen[x][y] = emptything;
    }
    srand(time(0));
    lookslike[(long)snakething] = snakechar;
    lookslike[(long)playerthing] = playerchar;
    lookslike[(long)moneything] = moneychar;
    lookslike[(long)emptything] = ' ';
    lookslike[(long)doorthing] = doorchar;
    left = false;
    eaten = false;
    score = 0;
    for (x = 0; x <= 10; x++)
        screen[x][0] = scorething;
    cls();
}

/* returns true if the position is valid and empty */

static boolean freespot(coordinate pos)
{
    if ((unsigned long)pos.x <= width && (unsigned long)pos.y < 32 &&
        ((1L << pos.y) & ((1L << (height + 1)) - (1L << 0))) != 0)
        return (screen[pos.x][pos.y] == emptything);
    else
        return false;
}

/* assigns the coordinates of a position on the screen that is not being used */

static void makespace(coordinate* newpos, thing forwhat)
{
    do
    {
        newpos->x = randint(0L, width - 1L);
        newpos->y = randint(0L, height - 1L);
    } while (!freespot(*newpos));
    gotoxy((int)newpos->x, (int)newpos->y);
    putchar(lookslike[(long)forwhat]);
    screen[newpos->x][newpos->y] = forwhat;
}

/*
finds a free coordinate adjacent to the argument coordinate
and places the thing there
*/

static void placenearby(coordinate* near_, coordinate* coord)
{
    long deltax, deltay;

    do
    {
        do
        {
            deltax = randint(-1L, 1L);
            deltay = randint(-1L, 1L);
        } while (deltax == 0 && deltay == 0);
        near_->x = coord->x + deltax;
        near_->y = coord->y + deltay;
    } while (!(freespot(*near_) || near_->x == player.x && near_->y == player.y));
    gotoxy((int)near_->x, (int)near_->y);
    screen[near_->x][near_->y] = snakething;
    putchar(lookslike[(long)snakething]);
}

/*
removes whatever is at the coordinates from the terminal screen
and the array screen
*/

static void removeCurrent(coordinate pos)
{
    gotoxy((int)pos.x, (int)pos.y);
    putchar(' ');
    screen[pos.x][pos.y] = emptything;
}

static void takegold()
{
    score += moneyworth;
    gotoxy(0, 0);
    printf("$%12ld", score);
    screen[money.x][money.y] = emptything;
    makespace(&money, moneything);
}

/* position all items in game making sure none overlap */

static void placeobjects()
{
    long snakebody;

    makespace(snake, snakething);
    for (snakebody = 2; snakebody <= snakelength; snakebody++)
        placenearby(&snake[snakebody - 1], &snake[snakebody - 2]);
    makespace(&player, playerthing);
    makespace(&money, moneything);
    makespace(&door, doorthing);
}

/*
read player's move from the keyboard, not input so letter
is not echoed and mess up the display
*/

static void playermove()
{
    char command;
    coordinate oldpos;

    command = ' ';
    usleep((int)(DELAYSECONDS * 1e6));
    while (kbhit()) {
        oldpos = player;
        command = getch();
        if (command == '\n')
            command = ' ';
        command = toupper(command);
        switch (command)
        {

        case upcommand:
            if (player.y > 0)
                player.y--;
            break;

        case downcommand:
            if (player.y < height)
                player.y++;
            break;

        case leftcommand:
            if (player.x > 0)
                player.x--;
            break;

        case rightcommand:
            if (player.x < width)
                player.x++;
            break;

        case quitcommand:
            left = true;
            break;

        case pausecommand:
            command = ' ';
            do
                command = getch();
            while (command != 'P' && command != 'p');
        }

        if (screen[player.x][player.y] == scorething)
        {
            player = oldpos;
            return;
        }
        removeCurrent(oldpos);
        if (player.x == money.x && player.y == money.y)
            takegold();
        else if (player.x == door.x && player.y == door.y)
            left = true;
        gotoxy((int)player.x, (int)player.y);
        putchar(playerchar);
        screen[player.x][player.y] = playerthing;
    }
}

/*
used by snakemove to figure out which way is the direction
toward the player
*/

static long sign(long x)
{
    if (x == 0)
        return 0;
    else if (x > 0)
        return 1;
    else
        return -1;
}

/* snake moves randomly at first then more directly toward player */
static void snakemove()
{
    coordinate newpos;
    long bodypart;

    if (randint(0L, score) < 100)
        placenearby(&newpos, snake);
    else
    {
        newpos.x = snake[0].x + sign(player.x - snake[0].x);
        newpos.y = snake[0].y + sign(player.y - snake[0].y);
        if (screen[newpos.x][newpos.y] == emptything ||
            newpos.x == player.x && newpos.y == player.y)
        {
            gotoxy((int)newpos.x, (int)newpos.y);
            putchar(snakechar);
            screen[newpos.x][newpos.y] = snakething;
        }
        else
            placenearby(&newpos, snake);
    }
    removeCurrent(snake[snakelength - 1]);
    if (newpos.x == player.x && newpos.y == player.y)
        eaten = true;
    for (bodypart = snakelength; bodypart >= 2; bodypart--)
    {
        snake[bodypart - 1] = snake[bodypart - 2];
        if (snake[bodypart - 1].x == player.x && snake[bodypart - 1].y == player.y)
            eaten = true;
    }
    snake[0] = newpos;
}

int main(int argc,char* argv[])
{
    initialize();
    placeobjects();
    stty_clflag(0, ECHO, NULL); // system("stty -echo");
    do
    {
        playermove();
        if (!left)
            snakemove();
    } while (!(left || eaten));
    gotoxy(0, height);
    putchar('\n');
    if (left)
        printf("You have escaped with $%12ld\n", score);
    else
        printf("The snake has eaten you.\n");
    stty_clflag(ECHO, 0, NULL); // system("stty echo");
    CursorOn();
    exit(EXIT_SUCCESS);
}
