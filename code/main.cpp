#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <windows.h>
#include <iostream>
#include <string>

int page = 0, length, input;

// { x, y, direction, color, id }
// int particle_coords[][5] = {{100, 100, 0, 1, 0}, {100, 100, 1, 2, 1}, {100, 100, 2, 3, 2}, {100, 100, 3, 4, 3}, {100, 100, 4, 5, 4}, {100, 100, 5, 6, 5}, {100, 100, 6, 7, 6}, {100, 100, 7, 8, 7}};
int particle_coords[2000][5];
int speed = 10;
int swap_var;

// Used to generate random particles positions.
// Generates 100 random particles.
int randomParticleGenerator();
// Returns direction number for every particle.
// 0 - Right E
// 1 - Left W
// 2 - Down S
// 3 - Up N
// 4 - SE
// 5 - NE
// 6 - NW
// 7 - SW
int returnDirectionNum(int num);
// Returns base number for any number.
int baseReturn(int num);
// Updates particles position.
void particlePositionUpdater();
// Updates particles moment.
void particleMomentUpdater();
// Checks if any collision of particle happens and does some stuff if they collide.
void collisionChecker();

int main()
{
     ShowWindow(FindWindowA("ConsoleWindowClass", NULL), false);
    // Initiating window.
    initwindow(1000, 1000, "Story Of NULL", 50, 50);
    randomParticleGenerator();
    while(1)
    {
        // Clears previous drawn graphics.
        cleardevice();
        particleMomentUpdater();
        particlePositionUpdater();
        collisionChecker();
        setactivepage(page);
        setvisualpage(1-page);
        page = 1 - page;
        delay(speed);// To regulate speed of particles.
    }
    closegraph();
     exit(10);
}

void particlePositionUpdater()
{
    length = sizeof(particle_coords)/sizeof(particle_coords[0]);
    for(int i=0; i<length; i++)
    {
        if(particle_coords[i][0] < 1000 && particle_coords[i][0] >0 && particle_coords[i][1] < 1000 && particle_coords[i][1] > 0)
        {
            if(particle_coords[i][2] == 0)
            {
                particle_coords[i][0] = particle_coords[i][0]+1;
            }
            else if(particle_coords[i][2] == 1)
            {
                particle_coords[i][0] = particle_coords[i][0]-1;
            }
            else if(particle_coords[i][2] == 2)
            {
                particle_coords[i][1] = particle_coords[i][1]+1;
            }
            else if(particle_coords[i][2] == 3)
            {
                particle_coords[i][1] = particle_coords[i][1]-1;
            }
            else if(particle_coords[i][2] == 4)
            {
                particle_coords[i][0] = particle_coords[i][0]+1;
                particle_coords[i][1] = particle_coords[i][1]+1;
            }
            else if(particle_coords[i][2] == 5)
            {
                particle_coords[i][0] = particle_coords[i][0]+1;
                particle_coords[i][1] = particle_coords[i][1]-1;
            }
            else if(particle_coords[i][2] == 6)
            {
                particle_coords[i][0] = particle_coords[i][0]-1;
                particle_coords[i][1] = particle_coords[i][1]-1;
            }
            else if(particle_coords[i][2] == 7)
            {
                particle_coords[i][0] = particle_coords[i][0]-1;
                particle_coords[i][1] = particle_coords[i][1]+1;
            }
        }
        else
        {
            if(particle_coords[i][2] == 0)
            {
                particle_coords[i][2] = 1;
                particle_coords[i][0] = 999;
            }
            else if(particle_coords[i][2] == 1)
            {
                particle_coords[i][2] = 0;
                particle_coords[i][0] = 1;
            }
            else if(particle_coords[i][2] == 2)
            {
                particle_coords[i][2] = 3;
                particle_coords[i][1] = 999;
            }
            else if(particle_coords[i][2] == 3)
            {
                particle_coords[i][2] = 2;
                particle_coords[i][1] = 1;
            }
            else if(particle_coords[i][2] == 4)
            {
                particle_coords[i][2] = 5;
                particle_coords[i][1] = particle_coords[i][1]-1;
                particle_coords[i][0] = particle_coords[i][0]-1;
            }
            else if(particle_coords[i][2] == 5)
            {
                particle_coords[i][2] = 6;
                particle_coords[i][1] = particle_coords[i][1]-1;
                particle_coords[i][0] = particle_coords[i][0]-1;
            }
            else if(particle_coords[i][2] == 6)
            {
                particle_coords[i][2] = 7;
                particle_coords[i][1] = particle_coords[i][1]+1;
                particle_coords[i][0] = particle_coords[i][0]+1;
            }
            else if(particle_coords[i][2] == 7)
            {

                particle_coords[i][2] = 4;
                particle_coords[i][1] = particle_coords[i][1]+1;
                particle_coords[i][0] = particle_coords[i][0]+1;
            }
        }
    }
}

void particleMomentUpdater()
{
    length = sizeof(particle_coords)/sizeof(particle_coords[0]);
    for(int i=0; i<length; i++)
    {
        setcolor(particle_coords[i][3]);
        circle(particle_coords[i][0], particle_coords[i][1], 1);
    }
}

void collisionChecker()
{
    length = sizeof(particle_coords)/sizeof(particle_coords[0]);
    for(int i=0; i<length; i++)
    {
        for(int j=i+1; j<length;j++)
        {
            // If both particles are colliding.
            if(particle_coords[i][0] == particle_coords[j][0] && particle_coords[i][1] == particle_coords[j][1])
            {
                // printf("Collided %d <===> %d\n", particle_coords[i][4], particle_coords[j][4]);

                if(particle_coords[i][2] == particle_coords[j][2])
                {
                    // If both particles are traveling in same direction it's better to make those two particles as single.
//                    for(int k=j; k<length; k++)
//                    {
//                        particle_coords[k][0] = particle_coords[k+1][0];
//                        particle_coords[k][1] = particle_coords[k+1][1];
//                        particle_coords[k][2] = particle_coords[k+1][2];
//                        particle_coords[k][3] = particle_coords[k+1][3];
//                        particle_coords[k][4] = particle_coords[k+1][4];
//                    }
                    particle_coords[i][2] = 0;
                    particle_coords[j][2] = 7;
                }
                else if(particle_coords[i][2] == 1 - particle_coords[j][2])
                {
                    particle_coords[i][2] = particle_coords[j][2];
                    particle_coords[j][2] = 1 - particle_coords[i][2];
                }
                else if(particle_coords[i][2]+1 == particle_coords[j][2] || particle_coords[i][2] == particle_coords[j][2]+1)
                {
                    swap_var = particle_coords[i][2];
                    particle_coords[i][2] = particle_coords[j][2];
                    particle_coords[j][2] = swap_var;
                }
                else
                {
                    // printf("In Else");
                    if(particle_coords[i][2] < 7)
                    {
                        particle_coords[i][2]++;
                    }
                    else
                    {
                        particle_coords[i][2] = 4;
                    }
                    if(particle_coords[j][2] < 7)
                    {
                        particle_coords[j][2]++;
                    }
                    else
                    {
                        particle_coords[j][2] = 4;
                    }
                }
            }
        }
    }
}

int randomParticleGenerator()
{
    // { x, y, direction, color, id }
    int rand_var0, rand_var1;
    for(int i=0; i<2000; i++)
    {
        rand_var0 = rand();
        rand_var1 = rand();
        rand_var0 = baseReturn(rand_var0);
        rand_var1 = baseReturn(rand_var1);
        particle_coords[i][0] = rand_var0 *100;
        particle_coords[i][1] = rand_var1 *100;
        particle_coords[i][2] = returnDirectionNum(rand_var0);
        particle_coords[i][3] = rand_var0;
        particle_coords[i][4] = i;
    }
}

int returnDirectionNum(int num)
{
    if(num <7)
    {
        return num;
    }
    else
    {
        return num-7;
    }
}

int baseReturn(int num)
{
    while(num/10) num = num/10 + num%10;
    return num;
}
