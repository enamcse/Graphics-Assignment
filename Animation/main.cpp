/**
 * Exhibition of some moving objects.
 *
 * Written by Enamul Hassan July 2015
 *
 * This program draws some moving objects and their
 * speed and shape can be changed by keystroke.
 */
#include "headers.h"

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    /**
     * void glViewport(GLint x, GLint y, GLsizei width, GLsizei height) - set the viewport
     *
     */
    glViewport(0, 0, width, height);

    /**
     * void glMatrixMode(GLenum mode) - specify which matrix is the current matrix
     *
     *                  mode - Specifies which matrix stack is the target for subsequent
     *                  matrix operations. Three values are accepted: GL_MODELVIEW,
     *                  GL_PROJECTION, and GL_TEXTURE. The initial value is GL_MODELVIEW.
     *                  Additionally, if the ARB_imaging extension is supported, GL_COLOR
     *                  is also accepted.
     *
     *                  GL_MODELVIEW - Applies subsequent matrix operations to the
     *                  modelview matrix stack
     *
     *                  GL_PROJECTION - Applies subsequent matrix operations to the
     *                  projection matrix stack
     */
    glMatrixMode(GL_PROJECTION);

    /**
     * void glLoadIdentity(void) - replace the current matrix with the identity matrix
     */
    glLoadIdentity();

    /**
     * void glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top,
     *                GLdouble nearVal, GLdouble farVal) - multiply the current matrix
     *                by a perspective matrix
     *
     *                left, right - Specify the coordinates for the left and right
     *                              vertical clipping planes.
     *
     *                bottom, top - Specify the coordinates for the bottom and top
     *                              horizontal clipping planes.
     *
     *                nearVal, farVal - Specify the distances to the near and far depth
     *                                  clipping planes. Both distances must be positive
     */
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    /**
     * int glutGet(GLenum state) - retrieves simple GLUT state represented by integers
     *                        GLUT_ELAPSED_TIME - Number of milliseconds since glutInit
     *                        called (or first call to glutGet(GLUT_ELAPSED_TIME))
     */
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0;


    /**
     * void glClear(GLbitfield mask) - clear buffers to preset values
     *
     *              GL_COLOR_BUFFER_BIT - Indicates the buffers currently enabled for
     *                                    color writing
     *
     *              GL_DEPTH_BUFFER_BIT - Indicates the depth buffer
     */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3d(1,0,0);

    /**
     * void glPushMatrix(void) - push the current matrix stack
     */
    glPushMatrix();

    glTranslated(-2.4,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);
    glutSolidSphere(1,slices,stacks);

    /**
     * void glPopMatrix(void); - pop the current matrix stack
     */
    glPopMatrix();

    glPushMatrix();

    /**
     * void glTranslated(GLdouble x,GLdouble y,GLdouble z) -  multiply the current
     *                                              matrix by a translation matrix
     */
    glTranslated(0,1.2,-6);

    /**
     * void glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z) - multiply
     *                                       the current matrix by a rotation matrix
     */
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);

     /**
     * void glutSolidCone(GLdouble base,GLdouble height,GLint slices,GLint stacks) -
     *                                                          render a solid cone
     */
    glutSolidCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4,1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);

    /**
     * void glutSolidTorus(GLdouble innerRadius,GLdouble outerRadius,GLint nsides,GLint rings) -
     *                                                          render a solid torus (doughnut)
     */
    glutSolidTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);

    /**
     * void glutWireSphere(GLdouble radius,GLint slices,GLint stacks) - render a
     *                                                          wireframe sphere
     */
    glutWireSphere(1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);

     /**
     * void glutWireCone(GLdouble base,GLdouble height,GLint slices,GLint stacks) -
     *                                                        render wireframe cone
     */
    glutWireCone(1,1,slices,stacks);
    glPopMatrix();

    glPushMatrix();
    glTranslated(2.4,-1.2,-6);
    glRotated(60,1,0,0);
    glRotated(a,0,0,1);

    /**
     * void glutWireTorus(GLdouble innerRadius,GLdouble outerRadius,GLint nsides,GLint rings) -
     *                                                      render a wireframe torus (doughnut)
     */
    glutWireTorus(0.2,0.8,slices,stacks);
    glPopMatrix();

    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case '+':
        slices++;
        stacks++;
        break;

    case '-':
        if (slices>2 && stacks>2)
        {
            slices--;
            stacks--;
        }
        break;
    }

    glutPostRedisplay();
}

static void idle(void)
{
    /**
     * void glutPostRedisplay(void) - marks the current window as
     *                                needing to be redisplayed
     */
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

/* Program entry point */

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
    glutInitWindowSize(640,480);

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
    glutCreateWindow("GLUT Shapes");

    /**
     * void glutReshapeFunc(void (*func)(int width, int height)) - sets the reshape
     *                                              callback for the current window
     */
    glutReshapeFunc(resize);

    /**
     * void glutDisplayFunc(void (*func)(void))  - this function takes a function pointer
     *                                             in which all works done.
     */
    glutDisplayFunc(display);

    /**
     * void glutKeyboardFunc(void (*func)(unsigned char key, int x, int y)) -
     *             this function takes a function pointer which works as keyboard listener
     */
    glutKeyboardFunc(key);


    /**
     * void glutIdleFunc(void (*func)(void)) - this function takes a function pointer which
     *                                         does work when window system events are not
     *                                         being received.
     */
    glutIdleFunc(idle);


    /**
     * void glClearColor( GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha) -
     *                          red, green, blue are RGB values and alpha is the opacity.
     */
    glClearColor(1,1,1,1);

    /**
     * void glEnable(GLenum cap) - enable or disable server-side GL capabilities
     *                  param cap Specifies a symbolic constant indicating a GL capability
     * GL_CULL_FACE - specify whether front- or back-facing facets can be culled
     * GL_COLOR_MATERIAL - cause a material color to track the current color
     * GL_DEPTH_TEST - do depth comparisons and update the depth buffer
     * GL_LIGHTi -  include light i in the evaluation of the lighting equation
     * GL_LIGHTING - If enabled and no vertex shader is active, use the current lighting
     *               parameters to compute the vertex color or index. Otherwise, simply
     *               associate the current color or index with each vertex
     * GL_NORMALIZE - If enabled and no vertex shader is active, normal vectors are
     *                normalized to unit length after transformation and before lighting
     */
    glEnable(GL_CULL_FACE);

    /**
     * void glCullFace(GLenum  mode) - specify whether front- or back-facing facets can
     *                                 be culled
     * GL_BACK - back-facing facet is selected
     */
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);

    /**
     * void glDepthFunc(GLenum func) - specifies the function used to compare each incoming
     *                   pixel depth value with the depth value present in the depth buffer.
     * GL_LESS - Passes if the incoming depth value is less than the stored depth value.
     */
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);


    /**
     * void glLightfv(GLenum light, GLenum pname, const GLfloat * params) - set light
     *           source parameters.
     *
     *           light - Specifies a light. The number of lights depends on the
     *                   implementation, but at least eight lights are supported. They
     *                   are identified by symbolic names of the form GL_LIGHT i, where
     *                   i ranges from 0 to the value of GL_MAX_LIGHTS - 1
     *
     *           pname - Specifies a light source parameter for light. GL_AMBIENT, GL_DIFFUSE,
     *                   GL_SPECULAR, GL_POSITION, GL_SPOT_CUTOFF, GL_SPOT_DIRECTION,
     *                   GL_SPOT_EXPONENT, GL_CONSTANT_ATTENUATION, GL_LINEAR_ATTENUATION,
     *                   and GL_QUADRATIC_ATTENUATION are accepted.
     *
     *                   GL_AMBIENT - params contains four integer or floating-point values
     *                   that specify the ambient RGBA intensity of the light. Integer values
     *                   are mapped linearly such that the most positive representable value
     *                   maps to 1.0, and the most negative representable value maps to -1.0.
     *                   Floating-point values are mapped directly. Neither integer nor
     *                   floating-point values are clamped. The initial ambient light
     *                   intensity is (0, 0, 0, 1).
     *
     *                   GL_DIFFUSE - params contains four integer or floating-point values
     *                   that specify the diffuse RGBA intensity of the light. Integer values
     *                   are mapped linearly such that the most positive representable value
     *                   maps to 1.0, and the most negative representable value maps to -1.0.
     *                   Floating-point values are mapped directly. Neither integer nor
     *                   floating-point values are clamped. The initial value for GL_LIGHT0
     *                   is (1, 1, 1, 1); for other lights, the initial value is (0, 0, 0, 1)
     *
     *                   GL_SPECULAR - params contains four integer or floating-point values
     *                   that specify the specular RGBA intensity of the light. Integer values
     *                   are mapped linearly such that the most positive representable value
     *                   maps to 1.0, and the most negative representable value maps to -1.0.
     *                   Floating-point values are mapped directly. Neither integer nor
     *                   floating-point values are clamped. The initial value for GL_LIGHT0
     *                   is (1, 1, 1, 1); for other lights, the initial value is (0, 0, 0, 1)
     *
     *                   GL_POSITION - params contains four integer or floating-point values
     *                   that specify the position of the light in homogeneous object
     *                   coordinates. Both integer and floating-point values are mapped directly.
     *                   Neither integer nor floating-point values are clamped.
     *
     *           params - Specifies a pointer to the value or values that parameter pname
     *                    of light source light will be set to
     */
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    /**
     * void glMaterialfv(GLenum face, GLenum pname,const GLfloat * params) - specify material
     *                                                       parameters for the lighting model.
     *
     *                     face - Specifies which face or faces are being updated. Must be one
     *                            of GL_FRONT, GL_BACK, or GL_FRONT_AND_BACK.
     *
     *                     pname - Specifies the material parameter of the face or faces that
     *                             is being updated. Must be one of GL_AMBIENT, GL_DIFFUSE,
     *                             GL_SPECULAR, GL_EMISSION, GL_SHININESS,
     *                             GL_AMBIENT_AND_DIFFUSE, or GL_COLOR_INDEXES.
     *
     *                             GL_SHININESS - params is a single integer or floating-point
     *                             value that specifies the RGBA specular exponent of the
     *                             material. Integer and floating-point values are mapped
     *                             directly. Only values in the range 0 128 are accepted. The
     *                             initial specular exponent for both front- and back-facing
     *                             materials is 0.
     *
     *                     param - Specifies a pointer to the value or values that pname
     *                             will be set to.
     */
    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


    /**
     * glutMainLoop() - enters the GLUT event processing loop. This routine should be
     *                  called at most once in a GLUT program. Once called, this routine
     *                  will never return. It will call as necessary any callbacks that
     *                  have been registered.
     */
    glutMainLoop();

    return EXIT_SUCCESS;
}
