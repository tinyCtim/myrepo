
/* last changed on 4/9/2015, 5/13/24 - lrb */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAMESIZE 132

void cls() {
#if defined(__linux__)
	/* Linux. --------------------------------------------------- */
	system("clear");
#elif defined(_WIN64)
	/* Microsoft Windows (64-bit). ------------------------------ */
	system("cls");
#elif defined(_WIN32)
	/* Microsoft Windows (32-bit). ------------------------------ */
	system("cls");
#endif
}

typedef struct
{
  int hitPoints,maxHitPoints,strength,maxStrength,potions,gold;
  char name[NAMESIZE];
} actor;

#define MAXSCENE 6

char buffer[132];
actor hero;      /* The hero object    -- constantly updated by the game */
actor monster;   /* The monster object -- constantly updated by the game */

void intro()
{
  printf("You approach a ruined dwarven mine, ");
  printf("rumored to be filled with lost treasure, \n");
  printf("but guarded by ");
  printf("monsters dangerous and most foul.\n\n");
  printf("None but the brave dare enter.\n\n");
  printf("Do you wish to continue? (y or n) ");
  fgets( buffer, 30, stdin);
  if ( buffer[0] != 'y' && buffer[0] != 'Y' )
  {
    printf("You turn tail and run. ");
    printf("From the trees around you, wood nymphs giggle derisively.\n\n");
    printf("In your panic, you step on a bear trap and die.\n");
    hero.hitPoints = 0;
  }
  else
  {
    printf("Spoken like a true Hero!\n");
    printf("Enter your name, Hero: ");
    fgets( buffer, 30, stdin);
    while ( strlen( buffer ) < 4 )
    {
      printf("You call *that* a name for a Hero? Try again: ");
      fgets( buffer, 30, stdin);
    }
    printf("\nNow *that's* a Heroic name\n");
    strcpy( hero.name, buffer );
  }
}

/* Generate a random integer  min <= r <= max
|
|  max-min+1 should be no larger than 65535
|
*/

int randInt( int min, int max )
{
  int num;
  num = rand()%(max-min+1) + min;
  return num;
}

void makeActor(actor *act, char* nm, int hp, int st, int gld)
{
  strcpy( act->name, nm );
  act->hitPoints = hp; act->maxHitPoints = hp;
  act->strength  = st; act->maxStrength  =st;
  act->gold = gld;
}

void heroSummary()
{
  printf("Hero   : Hit Points/Max Hit Points %1d/%1d Strength/Max Strength %1d/%1d Gold %1d \n",
    hero.hitPoints, hero.maxHitPoints,                                               
    hero.strength,  hero.maxStrength, hero.gold );
}

void monsterSummary()
{
  printf("Monster: Hit Points/Max Hit Points %1d/%1d Strength/Max Strength %1d/%1d \n",
    monster.hitPoints,  monster.maxHitPoints,
    monster.strength,   monster.maxStrength);
}

void summary()
{
  heroSummary();
  monsterSummary();
}

/* Magic Potion Scene
|
|
*/

static int potions[] = {0, 1, 2, 3}; /* increase, restore, neutral, poison */
static int potionInit = 0;

void potionScene()
{
   int toss, tossA, tossB, temp, j;

  /* Determine lucky potions for this game (done just once) */
  if ( !potionInit )
  {
    potionInit = 1;
    for ( j=0; j<3; j++ )
    {
      tossA = randInt(0,3);
      tossB = randInt(0,3);
      temp = potions[ tossA ];
      potions[ tossA ] = potions[ tossB ];
      potions[ tossB ] = temp;
    }
  }

  /* What does the Hero see? */
    toss = randInt(0,3);
    printf("You find a ");
    if ( toss == 0 ) printf("puce ");
    if ( toss == 1 ) printf("green ");
    if ( toss == 2 ) printf("red ");
    if ( toss == 3 ) printf("yellow ");
    printf("potion.  Do you wish to drink it? (y/n)");
    fgets( buffer, 30, stdin);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
  {
    if ( toss == potions[0] )
    {
      printf("This tastes great!\n");
      printf("Your max hitpoints increase!\n");
      hero.maxHitPoints += randInt(1,3);
    }
    else if ( toss == potions[1] )
    {
      printf("It tastes like maple syrup.\n");
      printf("You feel warm all over.\n");
      printf("Your hitpoints are restored!\n");
      hero.hitPoints  = hero.maxHitPoints;
    }
    else if ( toss == potions[2] )
    {
      printf("It tastes like warm apple juice.\n");
      printf("Nothing happens.\n");
    }
    else
    {
      printf("It tastes like yellow snow.\n");
      printf("This is not good.\n");
      hero.hitPoints--;
      hero.maxHitPoints--;
    }
  }
}

void rip()
{
  printf("\n");
  printf("        *           *                       \n");
  printf("                          *                \n");
  printf("           ______________        *                       \n");
  printf("          /___________  /\\                  \n");
  printf("         /              \\ \\                  \n");
  printf("        /                \\ \\        *        \n");
  printf("       |                  ||                \n");
  printf("       |    R. I. P.      ||               \n");
  printf("       |                  ||                 \n");
  printf("  *    |   %10s     ||                     \n", hero.name);
  printf("       |                  ||                 \n");
  printf("       |                  ||    *            \n");
  printf("       |                  ||                 \n");
  printf("       |                  ||                 \n");
  printf("  @    |       @       @  ||    @           \n");
  printf("  |    |       |       |  |/    |         \n");
  printf("//////\\\\\\\\\\///\\\\////\\\\\\/\\/\\////\\\\/////\n");
  printf("\n");
}

/* A fight between the hero and a monster
|
|  The fight continues until one contestant is dead or
|  the hero runs away.
|
*/

void sortie()
{
  int monsterThrow, heroThrow;
  int bothAlive = 1;
  int runAway   = 0;

  while ( bothAlive && !runAway )
  {
    printf("\nWhat do you wish to do? (f fight, r run away, d duck) ");
    fgets( buffer, 30, stdin);
    cls;

    /* Hero Fights the Monster */
    if ( buffer[0] == 'f' || buffer[0] == 'F' )
    {
      printf("You attack the %s\n\n", monster.name );
      monsterThrow = randInt( 1, monster.strength );
      heroThrow    = randInt( 1, hero   .strength );

      if ( heroThrow == monsterThrow )
      {
        printf("You swing and miss.\n");
        printf("The %s swings and misses.\n\n", monster.name );
      }
      else if ( heroThrow > monsterThrow )
      {
        printf("BAM!! You swing and hit.\n");
        printf("The %s loses a hit point.\n\n", monster.name );
        monster.hitPoints--;
      }
      else
      {
        printf("OOF!! The %s hits you.\n", monster.name);
        printf("You lose a hit point.\n\n");
        hero.hitPoints--;
      }
    }

    /* Hero Runs Away */
    else if ( buffer[0] == 'r' || buffer[0] == 'R' )
    {
      printf("You run away from the %s.\n", monster.name);
      printf("The %s throws a shurikin at your back!!\n", monster.name);
      monsterThrow = randInt( 1, 4 );
      if ( monsterThrow > 3 )
      {
        printf("It hits! You lose a hit point\n");
        hero.hitPoints--;
      }
      else
        printf("It misses.\n");
      runAway = 1;
    }

    /* Hero Ducks the Monster's Blow */
    else
    {
      printf("You duck from the monster's blow.\n");
      monsterThrow = randInt( 1, monster.strength );
      heroThrow    = randInt( 1, hero   .strength );

      if ( hero.hitPoints < hero.maxHitPoints && heroThrow > 3*monsterThrow/4 )
      {
        printf("The %s misses.\n\n", monster.name );
        printf("Your tricky move gains you a hit point!!!\n");
        hero.hitPoints++;
      }
      else if ( heroThrow > monsterThrow/2 )
      {
        printf("The %s misses.\n\n", monster.name );
      }
      else
      {
        printf("The %s hits you anyway.\n", monster.name);
        printf("You lose a hit point!\n\n");
        hero.hitPoints--;
      }
    }

    /* Determine the outcome of this exchange of blows */
    if ( hero.hitPoints <= 0 )
    {
      printf("You moan... and die...\n");
      bothAlive = 0;
    }
    else if ( monster.hitPoints <= 0 )
    {
      printf("The %s drops dead.\n", monster.name );
      bothAlive = 0;
    }
    summary();

  } /* end while */

  /* Final Result of the Sortie */
  if ( !runAway && hero.hitPoints > 0 )
  {
    printf("You gain strength from your experience\n");
    hero.strength++;
    hero.maxStrength++;
    heroSummary();
    printf("\n");
  }
}

/* Easy first scene */

void scene00( int monsterHit, int monsterStr )
{
  printf("You enter the mine and walk a few feet.\n");
  printf("You find a piece of gold and pick it up.\n");
  hero.gold++;
  printf("It makes a pleasant clink in your bag.\n");
  printf("\n");
  printf("You continue walking into the mine.\n");
}

/* First fight scene */

void scene01part2()
{
  printf("The dead bat lies at your feet.\n");
  printf("Is that some gold in its teeth?\n");
  printf("Do you wish to pry the gold from the bat's teeth? (y or n): ");
  fgets( buffer, 30, stdin);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
  {
    int toss = randInt( 1, 12 );
    if ( toss < 5 )
    {
      printf("The bat is not quite dead!\n It bites! You die of rabies.\n");
      hero.hitPoints = 0;
    }
    else
    {
      printf("Where did the bat ever get %2d pieces of gold?\n", toss );
      printf("You pocket the gold and move on.\n\n");
      hero.gold += toss;
    }
  }
}

void scene01(int monsterHit, int monsterStr )
{
  printf("What is that fluttering sound?\n");
  printf("OH NO! It's a saber-tooth bat!\n");
  makeActor( &monster, "Bat", monsterHit, monsterStr, 0);
  monsterSummary();
  printf("\n");
  sortie();
  if ( monster.hitPoints<=0 && hero.hitPoints>0 )
    scene01part2();
}

/* Scene 02 */

void scene02( int monsterHit, int monsterStr )
{
  printf("You go deeper into the mine.\n\n");
  printf("You find a small chest. ");
  printf("On the chest is an inscription in a mystical language:\n");
  printf("Do you wish to open the box? (y or n): ");
  fgets( buffer, 30, stdin);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
  {
    int toss = rand()%6;

    if ( toss == 0 )
    {
      printf("You open the box. A burst of poison gas hits you. You die.\n");
      hero.hitPoints = 0;
    }
    else if ( toss == 1 )
    {
      printf("You open the box and find it empty.\n");
      printf("You hear a snicker in the distance.\n");
    }
    else if ( toss == 2 )
    {
      printf("You find a Purple magic potion.\n" );
      printf("Do you drink the potion? (y or n): ");
      fgets( buffer, 30, stdin);
      if ( buffer[0] == 'y' || buffer[0] == 'Y' )
      {
        printf("Your hit points are restored.\n");
        hero.hitPoints = hero.maxHitPoints;
      }
    }
    else if ( toss == 3 )
    {
      printf("You find a Red magic potion.\n" );
      printf("Do you drink the potion? (y or n): ");
      fgets( buffer, 30, stdin);
      if ( buffer[0] == 'y' || buffer[0] == 'Y' )
      {
        printf("Your strength is increased.\n");
        hero.maxStrength++;
      }
    }
    else if ( toss == 4 )
    {
      printf("You find a Yucky Green magic potion.\n" );
      printf("Do you drink the potion? (y or n): ");
      fgets( buffer, 30, stdin);
      if ( buffer[0] == 'y' || buffer[0] == 'Y' )
      {
        printf("You feel ill.\n");
        hero.maxStrength--;
      }
    }
    else
    {
      printf("You find a Orange magic potion.\n" );
      printf("Do you drink the potion? (y or n): ");
      fgets( buffer, 30, stdin);
      if ( buffer[0] == 'y' || buffer[0] == 'Y' )
      {
        printf("Nothing happens\n");
      }
    }
  }
}

/* Scene 03 */

void scene03part2()
{
  printf("The dead mouse lies at your feet.\n");
  printf("You feel like kicking it into the darkness.\n");
  printf("Do you kick the dead mouse? (y or n):");
  fgets( buffer, 30, stdin);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
  {
    int toss = randInt( 1, 12 );

    if ( toss < 3 )
    {
      printf("You actions show disrespect for the fallen.\n");
      printf("You lose a hit point.\n");
      hero.hitPoints--;
    }

    if ( toss >= 3 && toss <= 10 )
    {
      printf("The mouse vanishes into the darkness.\n");
    }
    else
    {
      printf("The corpse bursts open, spilling %3d gold coins!\n", toss );
      printf("You pocket the gold and move on.\n\n");
      hero.gold += toss;
    }
  }
}

void scene03( int monsterHit, int monsterStr )
{
  printf("You continue deeper into the mine\n");
  printf("What is THAT??  A mouse! \n");
  makeActor( &monster, "Mouse", monsterHit, monsterStr, 0);
  monsterSummary();
  printf("\n");
  sortie();
  if ( hero.hitPoints > 0 && monster.hitPoints <= 0 )
    scene03part2();
}

void leftChoice( int monsterHit,  int monsterStr )
{
  printf("You see a sign in front of an orange bag:\n");
  printf("\tTrick or Treat!!\n\n");
  printf("Do you put a piece of gold in the bag? (y or n)");
  fgets( buffer, 30, stdin);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
  {
    hero.gold--;
    printf("Wise choice.  You continue down the tunnel.\n");
  }
  else
  {
    printf("Oh No!! You have angered the Great Pumpkin!!\n");
    makeActor( &monster, "Great Pumpkin", monsterHit, monsterStr, 0);
    printf("\n");
    sortie();
  }
}

void rightChoice( int monsterHit,  int monsterStr )
{
  printf("You find 10 gold pieces\n");
  hero.gold += 10;
}

void scene04( int monsterHit, int monsterStr )
{
  printf("You continue deeper into the mine.\n\n");
  printf("The tunnel splits into two passages. Which one do you take? Left or Right? (enter L or R) \n");
  fgets( buffer, 30, stdin);
  if ( buffer[0] == 'L' || buffer[0] == 'l' )
  {
    leftChoice( monsterHit, monsterStr );
  }
  else
  {
    rightChoice( monsterHit, monsterStr );
  }
}

void bottomChoice( int monsterHit,  int monsterStr )
{
  printf("You see a sign in front of a large blue egg:\n");
  printf("\tEaster's only a few days away. It is April 1st!!\n\n");
  printf("Do you put a piece of gold in front of the egg? (y or n)");
  fgets( buffer, 30, stdin);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
  {
    hero.gold--;
    printf("Wise choice.  You continue down the subterranean tunnel.\n");
  }
  else
  {
    printf("!! You have angered the Bad Bunny!!\n");
    makeActor( &monster, "Bad Bunny", monsterHit, monsterStr, 0);
    printf("\n");
    sortie();
  }
}

void topChoice( int monsterHit,  int monsterStr )
{
  printf("You find 31 gold pieces\n");
  hero.gold += 31;
}

void scene05( int monsterHit, int monsterStr )
{
  printf("You continue deeper into the mine.\n\n");
  printf("The tunnel has a hole in the bottom and a hole in the top.\nWhich one do you take? Bottom or Top (enter B or T) \n");
  fgets( buffer, 30, stdin);

  if ( buffer[0] == 'B' || buffer[0] == 'b' )
  {
    bottomChoice( monsterHit, monsterStr );
  }
  else
  {
    topChoice( monsterHit, monsterStr );
  }
}

/* Scene 06 */

void scene06part2()
{
  printf("The Pterotyranosaurissimus is motionless.\n");
  printf("You feel like punching it in the family jewels.\n");
  printf("Do you punch the Pterotyranosaurissimus? (y or n):");
  fgets( buffer, 30, stdin);

  if ( buffer[0] == 'y' || buffer[0] == 'Y' )
  {
    int toss = randInt( 1, 12 );
    if ( toss < 3 )
    {
      printf("You actions show a low esteem for the departed.\n");
      printf("You lose a hit point.\n");
      hero.hitPoints--;
    }
     if ( toss >= 3 && toss <= 10 )
    {
      printf("The Pterotyranosaurissimus evaporates into the darkeness.\n");
    }
    else
    {
      printf("The corpse explodes, spilling %3d gold coins!\n", toss );
      printf("You snap up the gold and move on.\n\n");
      hero.gold += toss;
    }
  }
}

void scene06( int monsterHit, int monsterStr )
{
  printf("You continue into the deepest part of the mine\n");
  printf("WTF??  A Pterotyranosaurissimus! \n");
  makeActor( &monster, "Pterotyranosaurissimus", monsterHit, monsterStr, 0);
  monsterSummary();
  printf("\n");
  sortie();
  if ( hero.hitPoints > 0 && monster.hitPoints <= 0 )
    scene06part2();
}

/* Scene Selector
|
|  Additional scenes will be edited in as they are created.
|
*/

void sceneSelect( int scene )
{
  if      ( scene== 0 ) scene00( 0, 0 );  /* monster-hitpoints, monster-strength  */
  else if ( scene== 1 ) scene01( 2, 2 );
  else if ( scene== 2 ) scene02( 0, 0 );
  else if ( scene== 3 ) scene03( 3, 3 );
  else if ( scene== 4 ) scene04( 5, 5 );
  else if ( scene== 5 ) scene05( 5, 5 );
  else if ( scene== 6 ) scene06( 7, 7);
  else
  {
    fprintf( stderr, "No such scene number %d\n", scene );
  }
}

int main(void)
{
  int scene = 0;  /* The current scene number */
 
  /* Splash Screen */
  printf(" ====                          ====\n");
  printf(" ====        Welcome to        ====\n");
  printf(" ====                          ====\n");
  printf(" ====   THE DUNGEONS OF DOOM   ====\n");
  printf(" ====                          ====\n\n");
  printf("            (Hit enter)"); 
  getchar(); cls();

  /* Create the Hero and start the Game */
  srand( time(NULL) );
  makeActor( &hero, "", 4, 4, 0);
  intro();

  /* Explore the dungeon scene by scene */
  while ( hero.hitPoints > 0 && scene <= MAXSCENE )
  {

  printf("(Hit enter)"); getchar();
  cls();
  printf("\n**** scene %d *****\n\n", scene );
  heroSummary();
  sceneSelect( scene );

  if (  hero.hitPoints > 0 && hero.hitPoints < scene/4 + 2  ) potionScene();

  /* Easter Egg */
  if ( strcmp( hero.name, "Sherlock" ) == 0 ) hero.hitPoints = hero.maxHitPoints;
  scene++;

  }

  /* End of Game Summary */
  if ( hero.hitPoints <= 0 )
  {
    printf("\n\nYou Lose.\n");
    rip();
  }
  else
  {
    printf("\n\nYou reach the end of the mine and find 100 pieces of gold\n\n");
    printf("You now have %2d pieces of gold and have WON the game.\n\n", hero.gold+=100 );
    printf("            (Hit enter)"); 
    getchar(); 
    cls();
    printf(" ====                          ====\n");
    printf(" ====           %10s    ====\n", hero.name);
    printf(" ====           WINNER         ====\n");
    printf(" ====                          ====\n");
    printf(" ====          %5d           ====\n", hero.gold);
    printf(" ====            gold          ====\n");
    printf(" ====                          ====\n\n");
    printf("            (Hit enter)"); 
    getchar();
  }

  return 0;
}

