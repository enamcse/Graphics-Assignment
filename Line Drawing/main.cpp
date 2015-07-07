/**
 * Implementation of Bresenham's Algorithm
 *
 * Written by Enamul Hassan July 2015
 *
 * This program draws a line having two pixel co-ordinate
 * using Bresenham's line Algorithm.
 */
#include "headers.h"

double x1, y1, x2, y2;


/**
 * setPixel(int,int) - This function mainly sets the pixel at the
 *                     co-ordinate (x,y) on the OpenGL screen.
 */
void setPixel(int x, int y)
{   /**
     * glBegin(GLbitfield mask) - delimit the vertices of a primitive or
     *                            a group of like primitives
     *
     * GL_POINTS - Treats each vertex as a single point.
     *             Vertex n defines point n. N points are drawn.
     */
    glBegin(GL_POINTS);
    /**
     * glVertex2f(float,float) - This function takes two floating
     *                           point values of co-ordinate and
     *                           set the point.
     */
    glVertex2f(x,y);

    /**
     * Sleep(int) - wait time in milliseconds. It is for distinguish
     *              two operations.
     */
//    Sleep(10);

    /**
     * glEnd() - end of the environment created by glBegin(int)
     */
    glEnd();
}

void bresenham_algo(void)
{
    /**
     * glClear(GLbitfield mask) — clear buffers to preset values
     * GL_COLOR_BUFFER_BIT - Indicates the buffers currently
     *                       enabled for color writing
     * GL_DEPTH_BUFFER_BIT - Indicates the depth buffer
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    /**
     * void glColor3f(GLfloat red, GLfloat green, GLfloat blue) -
     *          set RGB color.
     */
    glColor3f(1,0,0); // cyan color

    for (int i = -350; i<=350; i++)
        setPixel(0,i),setPixel(i,0);

    glColor3f(0,1,1); // cyan color

    ///Main algorithm

    int x1prime = x1+0.5;
    int x2prime = x2+0.5;
    int y1prime = y1+0.5;
    int y2prime = y2+0.5;

    double m = (y2-y1)/(x2-x1);

    if(!(0<=m && m<=1))
    {
        printf("m should be in range of 0 to 1.\n");
        printf("To get the mirrored counter part, swap the co-ordinates accordingly.\n");
        exit(0);
        return;
    }


    int x = x1prime, y = y1prime;
    int dx = x2prime - x1prime, dy = y2prime - y1prime, dT = 2*(dy-dx), dS = 2*dy;
    int d = 2*dy - dx;
    setPixel(x,y);

    while(x<x2prime)
    {
        x++;
        if(d<0) d+=dS;
        else y++,d+=dT;
        setPixel(x,y);
    }

    /**
     * glutSwapBuffers() -  swaps the buffers of the current window
     *                      if double buffered
     */
    glutSwapBuffers();
}


int main(int argc, char *argv[])
{
    /**
     * glutInit(int, char*) - initializes glut environment.
     */
    glutInit(&argc, argv);
    /**
     * glutInitWindowSize(int,int)- initializes new glut window of
     *                              size W * H
     *                              default: 300, 300
     */
    glutInitWindowSize(700,700);
    /**
     * glutInitWindowPosition(int,int) - set the origin of the
     *                                   co-ordinate
     *                                   default: -1, -1
     */
    glutInitWindowPosition(10,10);

    /**
     * glutInitDisplayMode(unsigned int) - set the initial display mode.
     *                      It can take a combinations of some masks
     *                      which are not overlapped in their binary
     *                      representation. So, it takes them having
     *                      bitwise OR.
     * GLUT_RGB - the color input would by set by RGB values.
     * GLUT_DOUBLE - makes it double buffered. It is like using two blackboard.
     *               One blackboard would be shown to the screen and hidden one
     *               would be processed behind. they can be swapped any time.
     * GLUT_DEPTH - It is mainly enables depth concept. Algorithm like z-buffering
     *              could be done by using this.
     */
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    /**
     * glutCreateWindow(char*) - creates a top-level window having the title
     *                           given as parameter.
     */
    glutCreateWindow("Brasenham's Algorithm for Line Drawing");

    /**
     * gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) -
     *                              define a 2D orthographic projection matrix
     */
    gluOrtho2D(-350,350,-350,350);
    printf("Give the input as: \"x1 y1 x2 y2\" - ");

    scanf("%lf %lf %lf %lf", &x1, &y1, &x2, &y2);
    if(x1>x2) swap(x1,x2), swap(y1,y2);

    /**
     * void glutDisplayFunc(void (*func)(void))  - this function takes a function pointer
     *                                             in which all works done.
     */
    glutDisplayFunc(bresenham_algo);

    /**
     * glutMainLoop() - enters the GLUT event processing loop. This routine should be
     *                  called at most once in a GLUT program. Once called, this routine
     *                  will never return. It will call as necessary any callbacks that
     *                  have been registered.
     */
    glutMainLoop();


    return EXIT_SUCCESS;
}
