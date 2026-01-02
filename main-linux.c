#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#define PI 3.14159265358
void settankplace1(int x, char grid[22][121])
{
   strcpy(grid[19] + x, "|_______");
   grid[19][x + 8] = '|';
   strcpy(grid[18] + x, " _|__|_/");
   grid[18][x + 8] = '/';
   strcpy(grid[17] + x, "   __   ");
   grid[17][x + 8] = ' ';
}
void settankplace2(int x, char grid[22][121])
{
   strcpy(grid[19] + x, "|_______");
   grid[19][x + 8] = '|';
   strcpy(grid[18] + x, "\\\\_|__|_");
   grid[18][x + 8] = ' ';
   strcpy(grid[17] + x, "    __  ");
   grid[17][x + 8] = ' ';
}
void cleartankplace(int x, char grid[22][121])
{
   strcpy(grid[19] + x, "        ");
   grid[19][x + 8] = ' ';
   strcpy(grid[18] + x, "        ");
   grid[18][x + 8] = ' ';
   strcpy(grid[17] + x, "        ");
   grid[17][x + 8] = ' ';
}
void printmap(char grid[22][121])
{
   printf("|");
   for (int i = 0; i < 120; i++)
      printf("-");
   printf("|\n");
   for (int i = 0; i < 22; i++)
      printf("|%s|\n", grid[i]);
   printf("|");
   for (int i = 0; i < 120; i++)
      printf("-");
   printf("|\n");
}
void printstatus(int h1, int h2)
{
   for (int i = 0; i < 122; i++)
      printf("=");
   printf("\n|                        [P1] TANK ALPHA  | HEALTH: %3d%%   ||   [P2] TANK BETA  | HEALTH: %3d%%                           |\n", h1, h2);
   for (int i = 0; i < 122; i++)
      printf("=");
   printf("\n");
}
void shot(int angle, int power, int xi, int yi, char grid[22][121], int *h1, int *h2, int b)
{
   int x = xi, y = yi;
   double powval = 2 + 7 * (pow(power / 100.0, 1.5)), t = 0;
   double vx = powval * cos((angle / 180.0) * PI), vy = powval * sin((angle / 180.0) * PI);
   while (1)
   {
      grid[y][x] = '*';
      system("clear");
      printstatus(*h1, *h2);
      printmap(grid);
      usleep(100000);
      grid[y][x] = ' ';
      t += 0.1;
      x = round(vx * t + xi);
      y = round(yi - vy * t + 0.2 * t * t);
      if (y > 11 && grid[y][x] == '^')
      {
         printf("Shot Terminated!\n");
         usleep(3000000);
         break;
      }
      if (x > 119 || x < 0 || y > 19 || y < 0)
      {
         printf("Shot Terminated!\n");
         usleep(3000000);
         break;
      }
      if (grid[y][x] != ' ' && grid[y][x] != '#' && grid[y][x] != '^' && x >= 85)
      {
         if (b)
         {
            printf("BOOM!!! Clean Hit On The Enemy\n");
         }
         else
         {
            printf("BOOM!!! Friendly Fire\n");
         }
         *h2 -= 20;
         usleep(3000000);
         break;
      }
      // printf("(%d,%d):%c",y,x,grid[y][x]);
      if (grid[y][x] != ' ' && grid[y][x] != '#' && grid[y][x] != '^' && x < 25)
      {
         if (!b)
         {
            printf("BOOM!!! Clean Hit On The Enemy\n");
         }
         else
         {
            printf("BOOM!!! Friendly Fire\n");
         }
         *h1 -= 20;
         usleep(3000000);
         break;
      }
   }
}
int main()
{
   srand(time(NULL));
   char grid[22][121] = {
       "                  ^                                                                                                     ",
       "                 ^^^                                                                            ^                       ",
       "                ^^^^^                                                                          ^^^                      ",
       "                                                                                              ^^^^^                     ",
       "                                                                                                                        ",
       "                                                                                                                        ",
       "                      ^^                                                                                                ",
       "                     ^^^^                                                                                               ",
       "                    ^^^^^^                                                                                    ^         ",
       "                                                                                                             ^^^        ",
       "                                                                                                                        ",
       "                                                                                                                        ",
       "                                                          ^                                                             ",
       "                                                         ^^^         ^^                                                 ",
       "                                                        ^^^^^       ^^^^                                                ",
       "                                               ^       ^^^^^^^^    ^^^^^^                                               ",
       "                                              ^^^     ^^^^^^^^^^  ^^^^^^^^     ^                                        ",
       "                                   ^^        ^^^^^  ^^^^^^^^^^^^^^^^^^^^^^^^  ^^^                                       ",
       "                                  ^^^^     ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                      ",
       "                                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^                                    ",
       "########################################################################################################################",
       "########################################################################################################################",
   };
   int h1 = 100, h2 = 100, p1 = rand() % 25, p2 = rand() % 27 + 85, b, angle, power,x;
   settankplace1(p1, grid);
   settankplace2(p2, grid);
   char c;
   while (1)
   {
      b = 0;
      printstatus(h1, h2);
      printmap(grid);
      printf("(Player 1) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game: ");
      scanf(" %c", &c);
      if (c == 'Q')
         return 0;
      else if (c == 'R')
      {
         scanf("%d",&x);
         if (p1+x > 24)
         {
            printf("Illegal Move - Your Turn Is Lost!\n");
            usleep(3000000);
            b = 1;
         }
         else
         {
            cleartankplace(p1, grid);
            settankplace1(p1+x, grid);
            system("clear");
            printstatus(h1, h2);
            printmap(grid);
            p1+=x;
         }
      }
      else if (c == 'L')
      {
         scanf("%d",&x);
         if (p1-x < 0)
         {
            printf("Illegal Move - Your Turn Is Lost!\n");
            usleep(3000000);
            b = 1;
         }
         else
         {
            cleartankplace(p1, grid);
            settankplace1(p1-x, grid);
            system("clear");
            printstatus(h1, h2);
            printmap(grid);
            p1-=x;
         }
      }
      else if (c == 'N')
      {
         system("clear");
         cleartankplace(p1, grid);
         cleartankplace(p2, grid);
         h1 = 100, h2 = 100, p1 = rand() % 25, p2 = rand() % 27 + 85;
         settankplace1(p1, grid);
         settankplace2(p2, grid);
         continue;
      }
      else if (c != 'S')
      {
         printf("Invalid Input - Your Turn Is Lost!\n");
         usleep(3000000);
         b = 1;
      }
      if (b == 0)
      {
         printf("(Player 1) Enter Firing Angle [0-180]: ");
         scanf("%d", &angle);
         if (angle > 180 || angle < 0)
         {
            printf("Angle Out Of Range - Your Turn Is Lost!\n");
            usleep(3000000);
            b = 1;
         }
      }
      if (b == 0)
      {
         printf("(Player 1) Enter Shot Power [1-100]: ");
         scanf("%d", &power);
         if (power > 100 || power < 1)
         {
            printf("Power Out Of Range - Your Turn Is Lost!\n");
            usleep(3000000);
            b = 1;
         }
      }
      if (b == 0)
      {
         shot(angle, power, p1 + 8, 17, grid, &h1, &h2, 1);
      }
      if (h2 == 0)
      {
         printf("-------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------");
         return 0;
      }
      if (h1 == 0)
      {
         printf("-------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------");
         return 0;
      }
      b = 0;
      system("clear");
      printstatus(h1, h2);
      printmap(grid);
      printf("(Player 2) Enter Command - L=Left, R=Right, S=Skip, Q=Quit, N=New Game:\n");
      scanf(" %c", &c);
      if (c == 'Q')
         return 0;
      else if (c == 'R')
      {
         scanf("%d",&x);
         if (p2+x >119)
         {
            printf("Illegal Move - Your Turn Is Lost!\n");
            usleep(3000000);
            b = 1;
         }
         else
         {
            cleartankplace(p2, grid);
            settankplace2(p2+x, grid);
            system("clear");
            printstatus(h1, h2);
            printmap(grid);
            p2+=x;
         }
      }
      else if (c == 'L')
      {
         scanf("%d",&x);
         if (p2-x <85)
         {
            printf("Illegal Move - Your Turn Is Lost!\n");
            usleep(3000000);
         }
         else
         {
            cleartankplace(p2, grid);
            settankplace2(p2-x, grid);
            system("clear");
            printstatus(h1, h2);
            printmap(grid);
            p2-=x;
         }
      }
      else if (c == 'N')
      {
         system("clear");
         cleartankplace(p1, grid);
         cleartankplace(p2, grid);
         h1 = 100, h2 = 100, p1 = rand() % 25, p2 = rand() % 27 + 85;
         settankplace1(p1, grid);
         settankplace2(p2, grid);
         continue;
      }
      else if (c != 'S')
      {
         printf("Invalid Input - Your Turn Is Lost!\n");
         usleep(3000000);
         b = 1;
      }
      if (b == 0)
      {
         printf("(Player 2) Enter Firing Angle [0-180]: ");
         scanf("%d", &angle);
         if (angle > 180 || angle < 0)
         {
            printf("Angle Out Of Range - Your Turn Is Lost!\n");
            usleep(3000000);
            b = 1;
         }
      }
      if (b == 0)
      {
         printf("(Player 2) Enter Shot Power [1-100]: ");
         scanf("%d", &power);
         if (power > 100 || power < 1)
         {
            printf("Power Out Of Range - Your Turn Is Lost!\n");
            usleep(3000000);
            b = 1;
         }
      }
      if (b == 0)
      {
         shot(angle, power, p2, 17, grid, &h1, &h2, 0);
      }
      if (h2 == 0)
      {
         printf("-------------------------------------------------------PLAYER 1 WINS-----------------------------------------------------");
         return 0;
      }
      if (h1 == 0)
      {
         printf("-------------------------------------------------------PLAYER 2 WINS-----------------------------------------------------");
         return 0;
      }
      system("clear");
      // while(getchar()!='\n');
   }
}
