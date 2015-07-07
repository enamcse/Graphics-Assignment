/**
 * Implementation of 2-Dimensional Transformation
 *
 * Written by Enamul Hassan July 2015
 *
 * This program draws several lines having two pixel co-ordinates
 * of each. Then the following operation could do on them:
 *  1. Translation
 *  2. Rotation
 *  2. Scaling
 */
#include "headers.h"

double rotation_factor;
double translation_factor;
double scaling_factor_x;
double scaling_factor_y;
int n;

vector< pair< pair<double, double>, pair<double,double> > >lines;

/**
 * This function draws a line from (x1, y1) to (x2,y2) pixel co-ordinate.
 */
void DrawLine(double x1, double  y1, double x2, double y2)
{
    /**
     * glBegin(GLbitfield mask) - delimit the vertices of a primitive or
     *                            a group of like primitives
     *
     * GL_LINES - Treats each pair of vertices as an independent line segment
     *             Vertices 2*n-1 and 2*n define line n. N lines are drawn.
     */
    glBegin(GL_LINES);

    /**
     * glVertex2f(float,float) - This function takes two floating
     *                           point values of co-ordinate and
     *                           set the point.
     */
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);

    /**
     * glEnd() - end of the environment created by glBegin(int)
     */
    glEnd();

    return;
}

void RedrawLines()
{
    glColor3f(1,0,0); // cyan color
    DrawLine(-350,0,350,0);
    DrawLine(0,-350,0,350);
    glColor3f((100.0+rand()%156)/255.0, (100.0+rand()%156)/255.0, (100.0+rand()%156)/255.0);

    for (int i = 0; i<lines.size(); i++)
        DrawLine(lines[i].first.first, lines[i].first.second, lines[i].second.first, lines[i].second.second);
}


void Translate(double tx, double ty)
{
    for(int i=0;i<lines.size();i++)
    {
        lines[i].first.first+=tx;
        lines[i].first.second+=ty;
        lines[i].second.first+=tx;
        lines[i].second.second+=ty;
    }
}

void Rotate(double angle)
{
    glClear(GL_COLOR_BUFFER_BIT);

//        for(int i=0;i<6;i++)
//    {
//        float ac, as;
//        ac=cos(angle*PI/180);
//        as=sin(angle*PI/180);
//        double x = p[i].x, y = p[i].y;
//        p[i].x =  x*ac - y*as;
//        p[i].y =  x*as + y*ac;
//        cout<<p[i].x<<", "<<p[i].y<<endl;
//
//
//    }


    double x, y;
    double ac, as;
    ac=cos(angle*PI/180);
    as=sin(angle*PI/180);

    for(int i=0;i<lines.size();i++)
    {
        x = lines[i].first.first;
        y = lines[i].first.second;

        lines[i].first.first= x*ac - y*as;
        lines[i].first.second= x*as + y*ac;

        x = lines[i].second.first;
        y = lines[i].second.second;

        lines[i].second.first=x*ac - y*as;
        lines[i].second.second=x*as + y*ac;
    }
}

void Scale(double sx,double sy)
{
    glClear(GL_COLOR_BUFFER_BIT);
    double h, l;
    h=0; /// the x co-ordinate of the reference point
    l=0; /// the y co-ordinate of the reference point
    Translate(-h,-l);

    for(int i=0;i<lines.size();i++)
    {
        lines[i].first.first*=sx;
        lines[i].first.second*=sy;
        lines[i].second.first*=sx;
        lines[i].second.second*=sy;
    }
    Translate(h,l);
}


static void key(unsigned char key, int x, int y)
{
    glClear(GL_COLOR_BUFFER_BIT);
    switch (key)
    {
        case 27 :
        case 'q':
        case 'e':
            exit(0);
            break;
        case 'c':
            glutSwapBuffers();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clean the screen and the depth buffer
            RedrawLines();
            glutSwapBuffers();
            break;
        case 'w':

            Translate(0,translation_factor);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;

        case 's':
            Translate(0,-translation_factor);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;
        case 'a':

            Translate(-translation_factor,0);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;

        case 'd':
            Translate(translation_factor,0);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;
        case '+':

            Scale(scaling_factor_x,scaling_factor_y);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;

        case '-':
            Scale(1/scaling_factor_x,1/scaling_factor_y);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;

        case 'l':
        case '1':

            Rotate(rotation_factor);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;

        case 'r':
        case '2':
            Rotate(-rotation_factor);

            glutSwapBuffers();
            RedrawLines();
            glutSwapBuffers();
            break;
    }

    //glutPostRedisplay();
}


void transformation(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    RedrawLines();
    glutSwapBuffers();
    return;
}

int main(int argc, char *argv[])
{
    int x1, y1, x2, y2;

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
    printf("At first you have to give some constant factors, which mean it would work for how many units in one iteration.\n");

    printf("Translation factor: ");
    scanf("%lf", &translation_factor);

    printf("\nRotation factor: ");
    scanf("%lf", &rotation_factor);

    printf("\nScaling factor for x-axis: ");
    scanf("%lf", &scaling_factor_x);

    printf("\nScaling factor for y-axis: ");
    scanf("%lf", &scaling_factor_y);

    printf("How many lines?: ");
    scanf("%d", &n);
    printf("Give %d lines as input in format \"x1 y1 x2 y2\":\n", n);
    for (int i = 0; i<n; i++)
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        lines.pb(mp(mp(x1,y1),mp(x2,y2)));
    }

    /**
     * void glutDisplayFunc(void (*func)(void))  - this function takes a function pointer
     *                                             in which all works done.
     */
    glutDisplayFunc(transformation);

    /**
     * void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y)) -
     *               this function takes a function pointer which sets keyboard listener
     */
    glutKeyboardFunc(key);

    /**
     * glutMainLoop() - enters the GLUT event processing loop. This routine should be
     *                  called at most once in a GLUT program. Once called, this routine
     *                  will never return. It will call as necessary any callbacks that
     *                  have been registered.
     */
    glutMainLoop();


    return EXIT_SUCCESS;
}

/**
10
10
2
2
3
0 0 100 100
100 100 100 150
100 150 0 0

10
10
2
2
3
100 100 200 100
100 180 200 180
120 160 180 160

10
10
2
2
7
0 0 100 0
0 0 0 80
100 0 100 80
0 80 100 80
0 80 20 60
100 80 80 60
20 60 80 60
*/
