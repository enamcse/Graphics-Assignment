/**
 * Implementation of Perspective Projection of a Cube
 *
 * Written by Enamul Hassan July 2015
 *
 * This program draws the perspective projection of a cube
 * in respect to the XY Plane.
 */
#include "headers.h"

double x0,y0,z0,a,b,c,d,d0,d1,n1,n2,n3;

struct matrix
{
    int n, m;
    double mat[10][10];
};

matrix pers, v, result;

void nullify(int n, int m, matrix &mat)
{
    mat.n = n;
    mat.m = m;
    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++)
            mat.mat[i][j] = 0;
}

/**
 * This function draws a line from (x1, y1) to (x2,y2) pixel co-ordinate.
 */
void DrawLine(double x1, double  y1, double x2, double y2)
{
//    cout<<x1<<" "<<y1<<" "<<z1 << " KK"<<endl;
//    cout<<x2<<" "<<y2<<" "<<z2 << " OK"<<endl;
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

void make_perspective_mat(int n, int m)
{
    nullify(n,m , pers);

    pers.mat[0][0] = d+a*n1;
    pers.mat[0][1] = a*n2;
    pers.mat[0][2] = a*n3;
    pers.mat[0][3] = -a*d0;

    pers.mat[1][0] = b*n1;
    pers.mat[1][1] = d+b*n2;
    pers.mat[1][2] = b*n3;
    pers.mat[1][3] = -b*d0;

    pers.mat[2][0] = c*n1;
    pers.mat[2][1] = c*n2;
    pers.mat[2][2] = d+c*n3;
    pers.mat[2][3] = -c*d0;

    pers.mat[3][0] = n1;
    pers.mat[3][1] = n2;
    pers.mat[3][2] = n3;
    pers.mat[3][3] = -d1;
}

matrix matmult(matrix &a, matrix &b)
{
    matrix ret;

    int n = a.n;
    int m = b.m;
    int p = b.n;

    for (int i = 0; i<n; i++)
        for (int j = 0; j<m; j++)
        {
            ret.mat[i][j]=0;
            for (int k = 0; k<p; k++)
                ret.mat[i][j]=ret.mat[i][j]+(a.mat[i][k]*b.mat[k][j]); //we can reduce complexity here
        }
    return ret;
}

void projection(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glutSwapBuffers();
    glColor3f(1,0,0); // cyan color
    DrawLine(result.mat[0][0],result.mat[1][0],result.mat[0][1],result.mat[1][1]);
    DrawLine(result.mat[0][0],result.mat[1][0],result.mat[0][5],result.mat[1][5]);
    DrawLine(result.mat[0][0],result.mat[1][0],result.mat[0][3],result.mat[1][3]);
    DrawLine(result.mat[0][1],result.mat[1][1],result.mat[0][6],result.mat[1][6]);
    DrawLine(result.mat[0][1],result.mat[1][1],result.mat[0][2],result.mat[1][2]);
    DrawLine(result.mat[0][2],result.mat[1][2],result.mat[0][3],result.mat[1][3]);
    DrawLine(result.mat[0][4],result.mat[1][4],result.mat[0][3],result.mat[1][3]);
    DrawLine(result.mat[0][4],result.mat[1][4],result.mat[0][5],result.mat[1][5]);
    DrawLine(result.mat[0][6],result.mat[1][6],result.mat[0][5],result.mat[1][5]);
    DrawLine(result.mat[0][6],result.mat[1][6],result.mat[0][7],result.mat[1][7]);
    DrawLine(result.mat[0][4],result.mat[1][4],result.mat[0][7],result.mat[1][7]);
    DrawLine(result.mat[0][2],result.mat[1][2],result.mat[0][7],result.mat[1][7]);
    glutSwapBuffers();

}

int main(int argc, char *argv[])
{
    int x1, y1, x2, y2, z1, z2;

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
    glutCreateWindow("Perspective Projection of a Cube");

    /**
     * gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) -
     *                              define a 2D orthographic projection matrix
     */
    gluOrtho2D(0,700,0,700);

    printf("A view plane can be described by two things. One is Reference point and another is Normal Vector.\n");
    printf("Give the Reference point co-ordinates as input in the format \"x y z\": ");
    scanf("%lf %lf %lf", &x0, &y0, &z0);

    printf("Give the co-efficients of the Normal Vector as input in the format \"n1 n2 n3\": ");
    scanf("%lf %lf %lf", &n1, &n2, &n3);

    d0 = x0 * n1 + y0 * n2 + z0 * n3;


    printf("Give the co-ordinates of Center of projection as input in the format \"x y z\": ");
    scanf("%lf %lf %lf", &a, &b, &c);

    d1 = a * n1 + b * n2 + c * n3;
    d = d0-d1;

    make_perspective_mat(4,4);

    printf("Give 2 points of the main diagonal of the cube as input in format \"x1 y1 z1 x2 y2 z2\":\n");
    scanf("%d %d %d %d %d %d", &x1, &y1, &z1, &x2, &y2, &z2);

    int xmin = min(x1,x2);
    int xmax = max(x1,x2);
    int ymin = min(y1,y2);
    int ymax = max(y1,y2);
    int zmin = min(z1,z2);
    int zmax = max(z1,z2);

    nullify(4,8,v);

    v.mat[0][0] = v.mat[0][3] = v.mat[0][4] = v.mat[0][5] = xmin;
    v.mat[0][1] = v.mat[0][2] = v.mat[0][6] = v.mat[0][7] = xmax;
    v.mat[1][0] = v.mat[1][1] = v.mat[1][5] = v.mat[1][6] = ymin;
    v.mat[1][2] = v.mat[1][3] = v.mat[1][4] = v.mat[1][7] = ymax;
    v.mat[2][0] = v.mat[2][1] = v.mat[2][2] = v.mat[2][3] = zmin;
    v.mat[2][4] = v.mat[2][5] = v.mat[2][6] = v.mat[2][7] = zmax;
    v.mat[3][0] = v.mat[3][1] = v.mat[3][2] = v.mat[3][3] = 1;
    v.mat[3][4] = v.mat[3][5] = v.mat[3][6] = v.mat[3][7] = 1;

    result = matmult(pers, v);

    for (int i = 0; i<4; i++)
    {
        for (int j = 0; j<8; j++)
            cout<< result.mat[i][j] <<" \n"[j==7];
    }


    /**
     * void glutDisplayFunc(void (*func)(void))  - this function takes a function pointer
     *                                             in which all works done.
     */
    glutDisplayFunc(projection);

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
0 0 5
0 1 1
1 1 0
30 30 30 100 100 100

*/
