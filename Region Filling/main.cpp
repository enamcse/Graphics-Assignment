/**
 * Implementation of Scanline Algorithm
 *
 * Written by Enamul Hassan July 2015
 *
 * This program draws a polygon having several points
 * using Scanline Region Filling Algorithm.
 */
#include "headers.h"

vector< pair<int,int> > vertex;

struct edge
{
    int xmin, ymin, ymax;
    int pixelcount;
    double  one_by_m;
    edge( int xmin_, int ymin_, int ymax_, double one_by_m_)
    {
        ymin = ymin_;
        xmin = xmin_;
        ymax = ymax_;
        one_by_m = one_by_m_;
        pixelcount=1;
    }
};

bool comp(edge &a,edge &b)
{
    return a.xmin<b.xmin;
}

vector<edge>edges;
int miny, maxy;


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

void ListEdges(void)
{
    edges.clear();

    for(int i=0,j=1; i<vertex.size(); i++,j++)
    {
        j%=vertex.size();
        if(vertex[i].second!=vertex[j].second)
            edges.pb(edge((vertex[i].second<vertex[j].second? vertex[i].first:vertex[j].first),
            min(vertex[i].second,vertex[j].second), max(vertex[i].second,vertex[j].second),
            (vertex[j].first - vertex[i].first) / (vertex[j].second*1.0-vertex[i].second)));

    }

    set<int>todecrease;

    for(int i=0; i<edges.size(); i++)
    {
        for (int j = 0; j<edges.size(); j++)
        if(edges[j].ymin==edges[i].ymax) todecrease.insert(i);
    }

    for(auto now:todecrease) edges[now].ymax--;


    return;
}

void scanline_algo()
{
    /**
     * glClear(GLbitfield mask) — clear buffers to preset values
     * GL_COLOR_BUFFER_BIT - Indicates the buffers currently
     *                       enabled for color writing
     */
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1,0,0); // cyan color


    DrawLine(-350,0,350,0);
    DrawLine(0,-350,0,350);

    ListEdges();

    cout<<"Edges = "<< edges.size()<<" ymn = "<<miny<<" ymx "<<maxy<<endl;
    cout<<"Vertices = "<< vertex.size()<<endl;

    for ( auto now : edges )
        cout<<"ymin = "<< now.ymin<<" ymax = "<<now.ymax<<" x = "<< now.xmin <<" 1/m = "<< now.one_by_m <<" count = "<< now.pixelcount <<endl;

    /**
    * void glColor3f(GLfloat red, GLfloat green, GLfloat blue) -
    *          set RGB color.
    */
    glColor3f(1, 1, 0);

    for (int i = miny; i<=maxy; i++)
    {
        vector<double>xs;
        for (int j = 0; j<edges.size(); j++)
        {
            if(edges[j].ymin<=i && i<=edges[j].ymax)
            {
                xs.pb(edges[j].xmin+edges[j].one_by_m*edges[j].pixelcount);
                edges[j].pixelcount++;
            }
        }

        sort(all(xs));

        for (int j = 0; j<xs.size(); j+=2)
            DrawLine(xs[j],i,xs[j+1],i);

        for(auto it = edges.begin(); it!=edges.end(); it++)
        {
            if((*it).ymax==i)
            {
                edges.erase(it);
                it--;
            }
        }

    }

    glutSwapBuffers();
    return;
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
    glutCreateWindow("Scanline Algorithm for Region Filling");

    /**
    * gluOrtho2D(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top) -
    *                              define a 2D orthographic projection matrix
    */
    gluOrtho2D(-350,350,-350,350);

    int n,x,y;

    printf("How many points? (at least 3): ");
    scanf("%d", &n);
    printf("Give %d points as input as: \"x y\":\n", n);
    for (int i = 0; i<n; i++)
    {
        scanf("%d %d", &x, &y);
        vertex.pb(mp(x,y));
    }

    miny = vertex[0].second;
    maxy = vertex[0].second;

    for (int i = 1; i<n; i++)
    {
        miny = miny = min(miny, vertex[i].second);
        maxy = maxy = max(maxy, vertex[i].second);
    }



    /**
     * void glutDisplayFunc(void (*func)(void))  - this function takes a function pointer
     *                                             in which all works done.
     */
    glutDisplayFunc(scanline_algo);

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
3
0 0
300 0
0 300

11
0 -200
100 -100
200 -200
200 300
100 0
100 200
0 200
0 100
-200 100
-200 -100
-100 0
*/
