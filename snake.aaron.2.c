///////////////////////////////////////////////////
// https://www.geeksforgeeks.org/snake-game-in-c //
///////////////////////////////////////////////////

//based on https://groups.google.com/a/isocpp.org/g/std-proposals/c/GrDSO7lVu18/m/_uUmcWpBAgAJ
#ifdef __GNUC__
#define INLINE inline __attribute__((always_inline))
#else
#define INLINE inline
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELAYSECONDS 3
#define MAXX (width - 1)
#define MAXY (height - 1)

//#define putstr(input) fputs(input, stdout)

INLINE void putstr(char *input) {
    fputs(input, stdout);
}

void home()
{
    putstr("\x1b[0H");
}
void cls()
{
    putstr("\x1b[2J");
    home();
}

// kbhit
// AWW: support kbhit() on APPLE 
// from  https://cboard.cprogramming.com/c-programming/178177-very-simple-program-impossible-create-mac.html
#if defined(__APPLE__) || defined(__linux__) // https://stackoverflow.com/questions/6802903/c-ifdef-mac-os-x-question

#ifndef GETCH_H_INCLUDED
#define GETCH_H_INCLUDED

#include <termios.h>
#include <unistd.h>
#include <fcntl.h> //for new version of kbhit
// #include <sys/time.h> old version

/// reads from keypress, doesn't echo
int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void clpuf(void)
{
    while (getc(stdin) != '\n')
        ;
}

/// reads from keypress, echoes
int getche(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~(ICANON);
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
    return ch;
}
/*old:
// braucht Bestätigung mit Enter-Taste
long kbhit(void)
{
struct timeval tv;
fd_set read_fd;
tv.tv_sec=0;
tv.tv_usec=0;
FD_ZERO(&read_fd);
FD_SET(0,&read_fd);
if(select(1, &read_fd, NULL, NULL, &tv) == -1)
return 0;
if(FD_ISSET(0,&read_fd))
 return 1;
return 0;
}
*/

// braucht keine Bestätigung mit Enter-Taste
int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

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
#include <conio.h>
#else
#error unknown architecture
#endif
// /kbhit

///////////////////////////////////////////////////
// https://www.geeksforgeeks.org/snake-game-in-c //
///////////////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// unfortunately, keymap and Direction have to be in the same order 
static char* keymap = "  AwBsCdDaxXqQ\003"; // first 10 characters are directions; rest are quit
#define FIRSTQUITCHAR (keymap + 10) //keep in sync with keymap
enum Direction {
    DirNone,
    DirUp,
    DirDown,
    DirRight,
    DirLeft
};
const int height = 20, width = 20;
int score;
int x, y, fruitx, fruity;
enum Direction direction = DirNone;
int gameover = 0;

// Function to generate the fruit within the boundary
void randfruit() {
    fruitx = rand() % (width-2) + 1;
    fruity = rand() % (height-2) + 1;
} 

void setup()
{
    gameover = 0;
    // Stores height and width
    y = height / 2;
    x = width / 2;
    randfruit();
    score = 0;
}

// Function to draw the boundaries, snake head, and fruit
void draw()
{
    system("cls");
//    home();
    for (int r = 0; r < height; r++)
    {
        for (int c = 0; c < width; c++)
        {
            if (r == 0 || r == MAXY || c == 0 || c == MAXX)
            {
                putchar('#');
            }
            else
            {
                if (r == y && c == x)
                    putchar('0');
                else if (r == fruity && c == fruitx)
                    putchar('*');
                else
                    putchar(' ');
            }
        }
        putchar('\n');
    }

    // Print the score after each pass
    printf("\nscore = %d\nKeys=(space)|w|a|s|d|qQxX\n", score);
}

// Function to take the input
void input()
{
    while (kbhit()) // throw away Escape-LeftBracket prefix to arrow key sequences
    {
        int c = getch();
        char *p = strchr(keymap, c);
        if (p >= FIRSTQUITCHAR) {
            gameover = 1;
            break;
        }
        if (p) {
            direction = (p-keymap)/2;
        }
    }
}

// Function for the logic behind each movement
void logic()
{
//    usleep((int)(DELAYSECONDS*1e6)); // aww // lrb sleep(1)
    sleep(DELAYSECONDS); // aww // lrb sleep(1)
    switch (direction)
    {
    case DirUp:
        y--;
        break;
    case DirDown:
        y++;
        break;
    case DirRight: // right
        x++;
        break;
    case DirLeft:
        x--;
        break;
    default:
        break;
    }

    // If the game is over
    if (x <= 0 || x >= MAXX || y <= 0 || y >= MAXY)
        gameover = 1;

    // If the snake reaches the fruit then update the score
    if (x == fruitx && y == fruity) {
        // After eating the above fruit generate new fruit
        score += 10;
        randfruit();
    }
}

int main()
{
    system("cls");
//    cls();
    setup();
#if defined(__APPLE__) || defined(__linux__)
    system("stty -echo");
#endif
    while (!gameover)
    {
        draw();
        input();
        logic();
    }
#if defined(__APPLE__) || defined(__linux__)
    system("stty echo");
#endif
}

