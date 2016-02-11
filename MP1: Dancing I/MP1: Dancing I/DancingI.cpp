//
//  DancingI.cpp
//  MP1: Dancing I
//
//  Created by Shaun Chung on 1/30/15.
//  Copyright (c) 2015 Shaun Chung. All rights reserved.
//
#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <ctime>

#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#endif

void display();
void timer(int v);
void keyBoard(unsigned char key);

static int win;                /* Window identifier */
static float currTime;         /* Timer*/
static float stop = 0;         /* pause or no pause*/
static int wire_display = 0;   /* display wireframe default no */
float dance = 0.0;

/* FPS things */
int FPS = 32;
clock_t startClock = 0, curClock;
long long int prevF = 0, curF = 0;


void CreateGlutWindow()
{
    /* Creation of Glut Window */
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition (10, 10);
    glutInitWindowSize (800, 600);
    win = glutCreateWindow ("Chung, Shaun");
}

void InitOpenGL()
{
    /* Set Color and Line width, General initialization of I */
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-3.0, 3.0, 3.0, 3.0, -3.0, 3.0);
    glMatrixMode(GL_MODELVIEW);
    glLineWidth(3.0);
}

void ExitGlut()
{
    /* Exit Program */
    glutDestroyWindow(win);
    exit(0);
}

void drawScene()
{
    /* Use sine curve to mess with coordinates of vertexes */
    float rand_a = 0.1 * sin(currTime - 0.5);
    float rand_b = 0.1 * sin(currTime - 0.3);
    
    /* Top block of I */
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-0.3f, 0.5+rand_b, 0.0f);       //v1
        glVertex3f(-0.3f, 0.3+rand_b, 0.0f);       //v2
        glVertex3f(-0.1f, 0.3+rand_a, 0.0f);       //v3
        glVertex3f(0.1f, 0.3+rand_a, 0.0f);        //v10
        glVertex3f(0.3f, 0.3+rand_b, 0.0f);        //v11
        glVertex3f(0.3f, 0.5+rand_a, 0.0f);        //v12
    glEnd();
    
    /* Bottom block of I*/
    glBegin(GL_TRIANGLE_FAN);
        glVertex3f(-0.3f, -0.5+rand_b, 0.0f);      //v6
        glVertex3f(-0.3f, -0.3+rand_b, 0.0f);      //v5
        glVertex3f(-0.1f, -0.3+rand_a, 0.0f);      //v4
        glVertex3f(0.1f, -0.3+rand_a, 0.0f);       //v9
        glVertex3f(0.3f, -0.3+rand_b, 0.0f);       //v8
        glVertex3f(0.3f, -0.5+rand_a, 0.0f);       //v7
    glEnd();
    
    /* Center Block of I*/
    glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(-0.1f, 0.3+rand_a, 0.0f);       //v3
        glVertex3f(-0.1f, -0.3+rand_a, 0.0f);      //v4
        glVertex3f(0.1f, 0.3+rand_a, 0.0f);        //v10
        glVertex3f(0.1f, -0.3+rand_a, 0.0f);       //v9
    glEnd();
    
   }

void display(){
    /* Clear */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    /* If we wish to display Wire display */
    if(wire_display == 1)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glColor3f(1.0f,0.5f, 0.0f);
        drawScene();
    }
    /* Otherwise, fill the polygon with color */
    else
    {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
        glColor3f(1.0f,0.5f, 0.0f);
        drawScene();
    }
    /* Refresh */
    glutSwapBuffers();
    
    /* FPS Counter from example*/
    curClock = clock();
    float elapsed = (curClock-startClock)/(float)CLOCKS_PER_SEC;
    if(elapsed > 1.0f)
    {
        float nFps = (float)(curF - prevF)/elapsed;
        printf("fps: %f\n", nFps);
        prevF = curF;
        startClock = curClock;
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, nFps);
    }
    
}

void CreateGlutCallbacks()
{
    glutDisplayFunc(display);
}

void timer(int v)
{
    /* Increment Time if not paused */
    if(!stop){
        currTime += 0.2;
    }
    glutPostRedisplay();
    glutTimerFunc(FPS, timer, v);
}

void keyBoard(unsigned char key, int filler, int whyWontYouWorkWithoutThese)
{
    /* Kill Program */
    if(key == 'x')
    {
        ExitGlut();
    }
    /* Toggle Wire Display */
    else if(key == 'w')
    {
        wire_display = !wire_display;
    }
    /* Toggle Movement */
    else if(key == 's')
    {
        stop = !stop;
    }
}

int main (int argc, char **argv)
{
    /*General Initialization of Window*/
    glutInit(&argc, argv);
    CreateGlutWindow();
    InitOpenGL();
    CreateGlutCallbacks();
    
    /* Enable Keyboard input */
    glutKeyboardFunc(keyBoard);
    
    /* Tick every 10 milliseconds */
    glutTimerFunc(10,timer,FPS);
    curClock = clock();
    
    /* Main loop of Animation */
    glutMainLoop();
}

