/**
 * Implementation of Liang-Barsky Algorithm
 *
 * Written by Enamul Hassan July 2015
 *
 * This program draws several lines having two pixel co-ordinates
 * of each after clipping in respect to a given window.
 */
#include "headers.h"

int xmin, xmax, ymin, ymax;
vector< pair< pair<double, double>, pair<double,double> > >lines, mainlines;

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

void DrawLines()
{
    glColor3f(1,0,0); // cyan color
    DrawLine(-350,0,350,0);
    DrawLine(0,-350,0,350);

    glColor3f(1,1,1); // white color

    DrawLine(xmin,ymin,xmax,ymin);
    DrawLine(xmin,ymin,xmin,ymax);
    DrawLine(xmax,ymin,xmax,ymax);
    DrawLine(xmin,ymax,xmax,ymax);


    glColor3f((100.0+rand()%156)/255.0, (100.0+rand()%156)/255.0, (100.0+rand()%156)/255.0);

    for (int i = 0; i<lines.size(); i++)
        DrawLine(lines[i].first.first, lines[i].first.second, lines[i].second.first, lines[i].second.second);
}


void liang_barsky_algo(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    double p[4], q[4], u1, u2, r, dx, dy;
    lines = mainlines;
    for (int i = 0,j; i<lines.size(); i++)
    {
        u1 = 0; u2 = 1;
        dx = lines[i].second.first - lines[i].first.first;
        dy = lines[i].second.second - lines[i].first.second;
        p[0] = -dx;
        p[1] = dx;
        p[2] = -dy;
        p[3] = dy;
        q[0] = lines[i].first.first -  xmin;
        q[1] = xmax - lines[i].first.first;
        q[2] = lines[i].first.second -  ymin;
        q[3] = ymax - lines[i].first.second;

//        cout<<"Line " <<i<<": "<< lines[i].first.first<<" " <<lines[i].first.second<<" : " <<
//               lines[i].second.first<<" "<< lines[i].second.second<<endl;
//        cout<<"dx = "<<dx<<" dy = "<<dy<<endl;
        for (j = 0; j<4; j++)
        {
//            cout<<"p = "<<p[j]<<",q = "<<q[j];
            if(p[j] == 0)
            {
                if(q[j] < 0) break;
                continue;
            }


            r = q[j]/p[j];

            if(p[j]<0) u1 = max(r,u1);
            else u2 = min(r,u2);
//            cout<<": r = "<<r<<endl;
        }

//        cout<<u1<<" uuuuuu "<<u2<<endl;

        if(j<4 || u1>u2)
        {
            lines.erase(lines.begin()+i);
            i--;
            continue;
        }


        int xpart = lines[i].first.first;
        int ypart = lines[i].first.second;


        lines[i].first.first+=(dx*u1);
        lines[i].first.second+=(dy*u1);

        lines[i].second.first=xpart+(dx*u2);
        lines[i].second.second= ypart+(dy*u2);

//        cout<<"Line " <<i<<"--> "<< lines[i].first.first<<" " <<lines[i].first.second<<" : " <<
//               lines[i].second.first<<" "<< lines[i].second.second<<endl;
    }


    glutSwapBuffers();
    DrawLines();
    glutSwapBuffers();
    return;
}

int main(int argc, char *argv[])
{
    int x1, y1, x2, y2,n;

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
    glutCreateWindow("Liang-Barsky Algorithm for Line Clipping");

    /**
     * gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) -
     *                              define a 2D orthographic projection matrix
     */
    gluOrtho2D(-350,350,-350,350);

    printf("Give the points of diagonal of the clipping window as input in format \"x1 y1 x2 y2\":\n");
    scanf("%d %d %d %d", &x1, &y1, &x2, &y2);

    xmin = min(x1,x2);
    xmax = max(x1,x2);
    ymin = min(y1,y2);
    ymax = max(y1,y2);

    printf("How many lines?: ");
    scanf("%d", &n);
    printf("Give %d lines as input in format \"x1 y1 x2 y2\":\n", n);
    for (int i = 0; i<n; i++)
    {
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        mainlines.pb(mp(mp(x1,y1),mp(x2,y2)));
    }

    /**
     * void glutDisplayFunc(void (*func)(void))  - this function takes a function pointer
     *                                             in which all works done.
     */
    glutDisplayFunc(liang_barsky_algo);

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
10 20 90 80
5
110 60 110 100
30 70 30 100
20 30 80 40
60 60 80 90
-10 70 110 10
*/
