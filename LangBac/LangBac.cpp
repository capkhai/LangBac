//=========================================================//
//=========================================================//
//

//
//=========================================================//
//=========================================================//
// WINDOW ONLY
//#include <windows.h>					// included in all Windows apps
//#include <winuser.h>          // Windows constants
// for windows GL is in small letters
//#include <gl/gl.h>						// OpenGL include
//#include <gl/glu.h>
//#include <GL/openglut.h>
// for linux GL is in capital letters
//=========================================================//
//=========================================================//

// LINUX or UNIX ONLY
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
//=========================================================//
//=========================================================//
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//=========================================================//
//=========================================================//
// person position in the environment
void move_camera(int specialKey, char normalKey);
void update_camera();
static GLuint axes_list;
GLdouble  g_playerPos[] = { 0.0, 1, 10.0 };//{ 0.0, 0.5, 10.0 };
GLdouble  g_lookAt[] = { 0.0, 0.0, 0.0 };
GLfloat   g_viewAngle = -90.0;
GLfloat   g_elevationAngle = 0.0;
GLfloat   change_collor = 1.0;

float rad = 0;
const float DEFAULT_SPEED = 0.4f;
//=========================================================//
//=========================================================//
GLvoid  drawGround();

GLvoid  DrawNormalObjects();

//=========================================================//
//=========================================================//
//=========================================================//
//=========================================================//
// quadric objects
void init_dados(void);
void setup_sceneEffects(void);
GLUquadricObj* g_normalObject = NULL;
GLUquadricObj* g_wireframeObject = NULL;
GLUquadricObj* g_flatshadedObject = NULL;
void cleanUP_data(void);

// windwheel
float rotateBase_degrees = 0;
float wheelRotateFactor = 1.0;
float rotatePointer_degrees = 0;


const int   WORLDSIZE = 250;
//=========================================================//
//=========================================================//
static void text_onScreen(int row, int col, const char* fmt, ...);
//=========================================================//
//=========================================================//
typedef struct
{
    const char* const name;
    void (*solid) (void);
    void (*wire)  (void);
} entry;
//=========================================================//
//=========================================================//

//=========================================================//
//=========================================================//
static void resize(int width, int height)
{
    const float ar = (float)width / (float)height;

    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (ar > .5)
        glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    else
        glFrustum(-1.0, 1.0, -1 / ar, 1 / ar, 2.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
//=========================================================//
//=========================================================//
GLvoid drawGround()
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glNormal3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glColor3ub(63, 63, 70);
    glVertex3f(-1500.0f, -4.0f, -1500.0f);
    glVertex3f(-1500.0f, -4.0f, 1500.0f);
    glVertex3f(1500.0f, -4.0f, 1500.0f);
    glVertex3f(1500.0f, -4.0f, -1500.0f);
    glEnd();

    //draw lines for depth
//	glColor3f(0, 102.7f, 204.0f);
//	glBegin(GL_LINES);
//		for (int x = -WORLD_SIZE; x < WORLD_SIZE; x += 6) 
//		{
//		  glVertex3i(x, 0, -WORLD_SIZE);
//		  glVertex3i(x, 0, WORLD_SIZE);
//		}
//		for (int z = -WORLD_SIZE; z < WORLD_SIZE; z += 6)
//		{
//		  glVertex3i(-WORLD_SIZE, 0, z);
//		  glVertex3i(WORLD_SIZE, 0, z);
//		}
//	glEnd();

    //glDisable(GL_BLEND);
}


GLvoid DrawNormalObjects(GLfloat rotation)
{
    return GLvoid();
}


void drawCube(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1, GLint r, GLint g, GLint b)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(0.3f, 0.5f, 0.5f);
    //glNormal3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glMateriali(GL_FRONT, GL_SHININESS, rand() % 128);
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = y0 + y1)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
    glColor3ub(r,g,b);     //xám
    glVertex3f(x0, y0 + y1, z0);
    glVertex3f(x0 + x1, y0 + y1, z0);
    glVertex3f(x0 + x1, y0 + y1, z0 + z1);
    glVertex3f(x0, y0 + y1, z0 + z1);

    // Bottom face (y = y0)
    glColor3ub(r, g, b);     //xám
    glVertex3f(x0, y0, z0);
    glVertex3f(x0 + x1, y0, z0);
    glVertex3f(x0 + x1, y0, z0 + z1);
    glVertex3f(x0, y0, z0 + z1);

    // Front face  (z = z0 + z1)   
    glColor3ub(r, g, b);     //xám
    glVertex3f(x0, y0, z0 + z1);
    glVertex3f(x0 + x1, y0, z0 + z1);
    glVertex3f(x0 + x1, y0 +y1, z0 + z1);
    glVertex3f(x0, y0 + y1, z0 + z1);

    // Back face (z = z0)
    glColor3ub(r, g, b);     //xám
    glVertex3f(x0, y0, z0);
    glVertex3f(x0 + x1, y0, z0);
    glVertex3f(x0 + x1, y0 + y1, z0);
    glVertex3f(x0, y0 + y1, z0);

    // Left face (x = x0)
    glColor3ub(r, g, b);     //xám
    glVertex3f(x0, y0, z0);
    glVertex3f(x0, y0, z0 + z1);
    glVertex3f(x0, y0 + y1, z0 + z1);
    glVertex3f(x0, y0 + y1, z0);

    // Right face (x = x0 + x1)
    glColor3ub(r, g, b);     //xám
    glVertex3f(x0 + x1, y0, z0);
    glVertex3f(x0 + x1, y0, z0 + z1);
    glVertex3f(x0 + x1, y0 + y1, z0 + z1);
    glVertex3f(x0 + x1, y0 + y1, z0);
    glEnd();  // End of drawing color-cube
    
    
     glBegin(GL_LINES);
    //canh 1
    glColor3ub(0, 0, 0);
    glVertex3f(x0, y0, z0);
    glVertex3f(x0 + x1, y0, z0);
    //canh 2
    glColor3ub(0, 0, 0);
    glVertex3f(x0, y0, z0);
    glVertex3f(x0, y0 + y1, z0);
    //canh 3
    glColor3ub(0, 0, 0);
    glVertex3f(x0, y0, z0);
    glVertex3f(x0, y0, z0 + z1);
    //canh 4
    glColor3ub(0, 0, 0);
    glVertex3f(x0 + x1, y0, z0);
    glVertex3f(x0 + x1, y0 + y1, z0);
    //canh 5
    glColor3ub(0, 0, 0);
    glVertex3f(x0 + x1, y0, z0);
    glVertex3f(x0 + x1, y0, z0 + z1);
    //canh 6
    glColor3ub(0, 0, 0);
    glVertex3f(x0, y0 + y1, z0);
    glVertex3f(x0 + x1, y0 + y1, z0);
    //canh 7
    //glColor3ub(0, 0, 0);
    glVertex3f(x0, y0 + y1, z0);
    glVertex3f(x0, y0 + y1, z0 + z1);
    //canh 8
    glColor3ub(0, 0, 0);
    glVertex3f(x0, y0, z0 + z1);
    glVertex3f(x0 + x1, y0, z0 + z1);
    //canh 9
    glColor3ub(0, 0, 0);
    glVertex3f(x0, y0, z0 + z1);
    glVertex3f(x0, y0 + y1, z0 + z1);
    //canh 10
    //glColor3ub(0, 0, 0);
    glVertex3f(x0 + x1, y0, z0 + z1);
    glVertex3f(x0 + x1, y0 + y1, z0 + z1);
    //canh 11
    glColor3ub(0, 0, 0);
    glVertex3f(x0 + x1, y0 + y1, z0);
    glVertex3f(x0 + x1, y0 + y1, z0 + z1);
    //canh 12
    glColor3ub(0, 0, 0);
    glVertex3f(x0, y0 + y1, z0 + z1);
    glVertex3f(x0 + x1, y0 + y1, z0 + z1);
    glEnd();
    
    glPopMatrix();
    
}

GLvoid drawSky()
{
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glRotatef(-90, 1, 0, 0);
    glColor3ub(255, 255, 255);
    glTranslatef(-2, -12, -2);
    gluCylinder(g_normalObject, 100, 100, 30, 32, 4);
    glPopMatrix();
    //drawCube(-100, -9, -100, 200, 50, 200, 201, 243, 235);
    
}
void drawFlag()
{
    // cot co
    //glEnable(GL_BLEND);     // Turn Blending On
    //glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glRotatef(-90, 1, 0, 0);
    glColor3ub(99, 96, 95);
    glTranslatef(-2, -2, -4);
    gluCylinder(g_normalObject, 0.2, 0.2, 8 + 15, 32, 4);
    glPopMatrix();
    //glDisable(GL_BLEND);        // Turn Blending Off
    //glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
    //la co
    glBegin(GL_QUADS);
    float z = 2;
    glColor3ub(128, 0, 0);
    glVertex3f(-2, 4 + 15, z);
    glVertex3f(4, 4 + 15, z);
    glVertex3f(4, 0 + 15, z);
    glVertex3f(-2, 0 + 15, z);
    glEnd();
    //Ngoi sao
    //Tam Giac 1 2 10
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1.0, 3.2 + 15, z + 0.1);
    glVertex3f(1.2, 2.5 + 15, z + 0.1);
    glVertex3f(0.8, 2.5 + 15, z + 0.1);

    //Tam giac 2 3 4
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1.2, 2.5 + 15, z + 0.1);
    glVertex3f(2.0, 2.5 + 15, z + 0.1);
    glVertex3f(1.4, 1.9 + 15, z + 0.1);

    //Tam giac 4 5 6
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1.4, 1.9 + 15, z + 0.1);
    glVertex3f(1.6, 1.2 + 15, z + 0.1);
    glVertex3f(1, 1.6 + 15, z + 0.1);

    //Tam giac 6 7 8
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1, 1.6 + 15, z + 0.1);
    glVertex3f(0.4, 1.2 + 15, z + 0.1);
    glVertex3f(0.6, 1.9 +15, z + 0.1);

    //Tam giac 8 9 10
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(0.6, 1.9 + 15, z + 0.1);
    glVertex3f(0, 2.5 + 15, z + 0.1);
    glVertex3f(0.8, 2.5 + 15, z + 0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(128, 128, 0);
    glVertex3f(1.2, 2.5 + 15, z + 0.1);
    glVertex3f(1.4, 1.9 + 15, z + 0.1);
    glVertex3f(1, 1.6 + 15, z + 0.1);
    glVertex3f(0.6, 1.9 + 15, z + 0.1);
    glVertex3f(0.8, 2.5 + 15, z + 0.1);
    glEnd();
    
}
void drawQuad(GLfloat x1, GLfloat y1, GLfloat z1,
    GLfloat x2, GLfloat y2, GLfloat z2,
    GLfloat x3, GLfloat y3, GLfloat z3,
    GLfloat x4, GLfloat y4, GLfloat z4,
    GLint r, GLint g, GLint b)
{
    glPushMatrix();
    glMateriali(GL_FRONT, GL_SHININESS, 50);
    glBegin(GL_QUADS);
    glColor3ub(r, g, b);
    glVertex3f(x1, y1, z1);
    glColor3ub(r, g, b);
    glVertex3f(x2, y2, z2);
    glColor3ub(r, g, b);
    glVertex3f(x3, y3, z3);
    glColor3ub(r, g, b);
    glVertex3f(x4, y4, z4);
    glEnd();

    
    glBegin(GL_LINES);

    glColor3ub(0, 0, 0);
    glVertex3f(x1, y1, z1);
    glVertex3f(x2, y2, z2);

    glColor3ub(0, 0, 0);
    glVertex3f(x2, y2, z2);
    glVertex3f(x3, y3, z3);

    glColor3ub(0, 0, 0);
    glVertex3f(x3, y3, z3);
    glVertex3f(x4, y4, z4);

    glColor3ub(0, 0, 0);
    glVertex3f(x4, y4, z4);
    glVertex3f(x1, y1, z1);
    glEnd();
    glPopMatrix();
}
void drawRoof(GLint r, GLint g, GLint b)
{
    GLfloat xUp = 35.5;
    GLfloat xDown = 36;
    //GLfloat h;
    GLfloat aUp = 17;
    GLfloat aDown = 16;
    drawQuad(xUp, 13.5, xUp, xUp + aUp,13.5, xUp, xUp + aUp, 13.5, xUp + aUp, xUp, 13.5, xUp + aUp, r, g, b);
    drawQuad(xDown, 11.5, xDown, xDown + aDown, 11.5, xDown, xUp + aUp, 13.5, xUp, xUp, 13.5, xUp, r, g, b);
    drawQuad(xDown + aDown, 11.5, xDown + aDown, xDown, 11.5, xDown + aDown, xUp, 13.5, xUp + aUp, xUp + aUp, 13.5, xUp + aUp, r, g, b);
    drawQuad(xDown, 11.5, xDown + aDown, xDown, 11.5, xDown, xUp, 13.5, xUp, xUp, 13.5, xUp + aUp, r, g, b);
    drawQuad(xDown + aDown, 11.5, xDown, xDown + aDown, 11.5, xDown + aDown, xUp + aUp, 13.5, xUp + aUp, xUp + aUp, 13.5, xUp, r, g, b);
    
}
void drawStair(GLint r, GLint g, GLint b)   
{
    GLfloat ChieuCaoBac = 0.5;
    GLfloat ChieuRongBac = 0.541;
    GLfloat ChieuDaiBac = 1.5 - 0.05;
    GLfloat DoDaiKhoi = 7.5;
    //Cầu thang trái
    //drawCube(30, -4, 28.5, ChieuRongBac, ChieuCaoBac, ChieuDaiBac, 70, 80, 90);
    for (int i = 0; i < 11; i++)
    {
        drawCube(30 + ChieuRongBac * i, -4 + ChieuCaoBac * i, 28.5, ChieuRongBac, ChieuCaoBac, ChieuDaiBac, r, g, b);
    }
    drawCube(30 + ChieuRongBac * 11, -4 + ChieuCaoBac * 11, 28.5, ChieuRongBac+1, ChieuCaoBac, ChieuDaiBac, r, g, b);
    glBegin(GL_POLYGON);
    glColor3ub(r,g,b);
    glVertex3f(30, -4, 28);
    glVertex3f(38, -4, 28);
    glVertex3f(38, 4, 28);
    glVertex3f(36.5, 4, 28);
    glVertex3f(30, -2.5, 28);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(r,g,b);
    glVertex3f(30, -4, 28.5);
    glVertex3f(37.4, -4, 28.5);
    glVertex3f(37.4, 4, 28.5);
    glVertex3f(36.5, 4, 28.5);
    glVertex3f(30, -2.5, 28.5);
    glEnd();

    drawCube(37.5, -4, 28, 0.5, 8, 2, r,g,b);
    drawQuad(30, -4, 28,
            30, -2.5, 28,
            30, -2.5, 28.5,
            30, -4, 28.5, r,g,b);
    drawQuad(36.5, 4, 28,
        36.5, 4, 28.5,
        30, -2.5, 28.5,
        30, -2.5, 28, r,g,b);
    drawQuad(38, 4, 28,
        38, 4, 28.5,
        36.5, 4, 28.5,
        36.5, 4, 28, r,g,b);
    //Cầu thang phải
    for (int i = 0; i < 11; i++)
    {
        drawCube(30 + ChieuRongBac * i, -4 + ChieuCaoBac * i, 58+0.05, ChieuRongBac, ChieuCaoBac, ChieuDaiBac - 0.05, r, g, b);
    }
    drawCube(30 + ChieuRongBac * 11, -4 + ChieuCaoBac * 11, 58, ChieuRongBac + 1, ChieuCaoBac, ChieuDaiBac, r, g, b);
    glBegin(GL_POLYGON);
    glColor3ub(r, g, b);
    glVertex3f(30, -4, 60);
    glVertex3f(38, -4, 60);
    glVertex3f(38, 4, 60);
    glVertex3f(36.5, 4, 60);
    glVertex3f(30, -2.5, 60);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(r, g, b);
    glVertex3f(30, -4, 59.5);
    glVertex3f(37.4, -4, 59.5);
    glVertex3f(37.4, 4, 59.5);
    glVertex3f(36.5, 4, 59.5);
    glVertex3f(30, -2.5, 59.5);
    glEnd();

    drawCube(37.5, -4, 58, 0.5, 8, 2, r, g, b);
    drawQuad(30, -4, 59.5,
        30, -2.5, 59.5,
        30, -2.5, 60,
        30, -4, 60, r, g, b);
    drawQuad(36.5, 4, 59.5,
        36.5, 4, 60,
        30, -2.5, 60,
        30, -2.5, 59.5, r, g, b);
    drawQuad(38, 4, 59.5,
        38, 4, 60,
        36.5, 4, 60,
        36.5, 4, 59.5, r, g, b);
}
void drawTang1(GLint r, GLint g, GLint b)
{
    
    //Mặt chính
    //drawQuad(30, -4, 30, 30, -4, 38, 30, 4, 38, 30, 4, 30, r, g, b);
    glBegin(GL_QUADS);
    glColor3ub(r, g, b);
    glVertex3f(30, -4, 30);
    glVertex3f(30, -4, 38);
    glVertex3f(30, 4, 38);
    glVertex3f(30, 4, 30);

    glColor3ub(r, g, b);
    glVertex3f(30, -4, 50);
    glVertex3f(30, -4, 58);
    glVertex3f(30, 4, 58);
    glVertex3f(30, 4, 50);

    glColor3ub(r, g, b);
    glVertex3f(30, 1, 38);
    glVertex3f(30, 1, 50);
    glVertex3f(30, 4, 50);
    glVertex3f(30, 4, 38);
    glEnd();
    glBegin(GL_LINES);

    glColor3ub(0, 0, 0);
    glVertex3f(30, -4, 30);
    glVertex3f(30, 4, 30);

    glColor3ub(0, 0, 0);
    glVertex3f(30, 4, 30);
    glVertex3f(30, 4, 58);

    glColor3ub(0, 0, 0);
    glVertex3f(30, 4, 58);
    glVertex3f(30, -4, 58);

    glColor3ub(0, 0, 0);
    glVertex3f(30, -4, 58);
    glVertex3f(30, -4, 50);

    glColor3ub(0, 0, 0);
    glVertex3f(30, -4, 50);
    glVertex3f(30, 1, 50);

    glColor3ub(0, 0, 0);
    glVertex3f(30, 1, 50);
    glVertex3f(30, 1, 38);

    glColor3ub(0, 0, 0);
    glVertex3f(30, 1, 38);
    glVertex3f(30, -4, 38);

    glColor3ub(0, 0, 0);
    glVertex3f(30, -4, 38);
    glVertex3f(30, -4, 30);
    glEnd();
    //drawQuad(30, -4, 50, 30, -4, 58, 30, 4, 58, 30, 4, 50, r, g, b);

    //drawQuad(30, 1, 38, 30, 1, 50, 30, 4, 50, 30, 4, 38, r, g, b);
    
    //Mặt trong của cửa
    drawQuad(30, -4, 38, 32, -4, 38, 32, 1, 38, 30, 1, 38, r, g, b);
    drawQuad(30, -4, 50, 32, -4, 50, 32, 1, 50, 30, 1, 50, r, g, b);
    drawQuad(30, 1, 38, 32, 1, 38, 32, 1, 50, 30, 1, 50, r, g, b);

    //Cửa
    drawQuad(32, -4, 38, 32, -4, 40, 32, 1, 40, 32, 1, 38, 23, 26, 33);
    drawQuad(32, -4, 40, 32, -4, 42, 32, 1, 42, 32, 1, 40, 51, 33, 22);
    drawQuad(32, -4, 42, 32, -4, 44, 32, 1, 44, 32, 1, 42, 84, 43, 15);
    drawQuad(32, -4, 44, 32, -4, 46, 32, 1, 46, 32, 1, 44, 84, 43, 15);
    drawQuad(32, -4, 46, 32, -4, 48, 32, 1, 48, 32, 1, 46, 51, 33, 22);
    drawQuad(32, -4, 48, 32, -4, 50, 32, 1, 50, 32, 1, 48, 23, 26, 33);

    //mặt trái
    drawQuad(30, -4, 30, 36.5, -4, 30, 36.5, 4, 30, 30, 4, 30, r, g, b);
    drawQuad(37.5, -4, 30, 58, -4, 30, 58, 4, 30, 37.5, 4, 30, r, g, b);
    

    //mặt phải
    drawQuad(30, -4, 58, 36.5, -4, 58, 36.5, 4, 58, 30, 4, 58, r, g, b);
    drawQuad(37.5, -4, 58, 58, -4, 58, 58, 4, 58, 37.5, 4, 58, r, g, b);
    

    //mặt sau
    drawQuad(58, -4, 30, 58, -4, 58, 58, 4, 58, 58, 4, 30, r, g, b);
    

    //Hành lang
    // Nền hành lang
    glBegin(GL_QUADS);
    glColor3ub(r,g,b);
    glVertex3f(30.5, 2, 30.5);
    glVertex3f(30.5, 2, 57.5);
    glVertex3f(57.5, 2, 57.5);
    glVertex3f(57.5, 2, 30.5);
    glEnd();

    //Mặt trong thành hành lang
    //Trái
    drawQuad(30.5, 2, 30.5, 36.5, 2, 30.5, 36.5, 4, 30.5, 30.5, 4, 30.5, r,g,b);
    drawQuad(37.5, 2, 30.5, 57.5, 2, 30.5, 57.5, 4, 30.5, 37.5, 4, 30.5, r,g,b);
    drawQuad(36.5, 2, 30, 36.5, 2, 30.5, 36.5, 4, 30.5, 36.5, 4, 30, r,g,b);
    drawQuad(37.5, 2, 30, 37.5, 2, 30.5, 37.5, 4, 30.5, 37.5, 4, 30, r,g,b);

    //Trước
    drawQuad(30.5, 2, 30.5, 30.5, 2, 57.5, 30.5, 4, 57.5, 30.5, 4, 30.5, r,g,b);

    //Phải
    drawQuad(30.5, 2, 57.5, 36.5, 2, 57.5, 36.5, 4, 57.5, 30.5, 4, 57.5, r,g,b);
    drawQuad(37.5, 2, 57.5, 57.5, 2, 57.5, 57.5, 4, 57.5, 37.5, 4, 57.5, r,g,b);
    drawQuad(36.5, 2, 57.5, 36.5, 2, 58, 36.5, 4, 58, 36.5, 4, 57.5, r,g,b);
    drawQuad(37.5, 2, 57.5, 37.5, 2, 58, 37.5, 4, 58, 37.5, 4, 57.5, r,g,b);

    //Sau
    drawQuad(57.5, 2, 30.5, 57.5, 2, 57.5, 57.5, 4, 57.5, 57.5, 4, 30.5, r,g,b);

    //Mặt trên thành hành lang
    glBegin(GL_QUADS);
    
    //trái
    glColor3ub(r, g, b);
    glVertex3f(30, 3.9, 30);
    glVertex3f(36.5, 3.9, 30);
    glVertex3f(36.5, 3.9, 30.5);
    glVertex3f(30, 3.9, 30.5);

    glColor3ub(r, g, b);
    glVertex3f(37.5, 3.9, 30);
    glVertex3f(58, 3.9, 30);
    glVertex3f(58, 3.9, 30.5);
    glVertex3f(37.5, 3.9, 30.5);

    //trước
    glColor3ub(r, g, b);
    glVertex3f(30, 3.9, 30);
    glVertex3f(30, 3.9, 58);
    glVertex3f(30.5, 3.9, 58);
    glVertex3f(30.5, 3.9, 30);

    //phải
    glColor3ub(r, g, b);
    glVertex3f(30, 3.9, 57.5);
    glVertex3f(36.5, 3.9, 57.5);
    glVertex3f(36.5, 3.9, 58);
    glVertex3f(30, 3.9, 58);

    glColor3ub(r, g, b);
    glVertex3f(37.5, 3.9, 57.5);
    glVertex3f(58, 3.9, 57.5);
    glVertex3f(58, 3.9, 58);
    glVertex3f(37.5, 3.9, 58);

    //sau
    glColor3ub(r, g, b);
    glVertex3f(57.5, 3.9, 30);
    glVertex3f(57.5, 3.9, 58);
    glVertex3f(58, 3.9, 58);
    glVertex3f(58, 3.9, 30);
    glEnd();

    //Trong tầng 1
    drawCube(32, 2+0.05, 32, 24, 2-0.05, 24, r, g, b);
}
void drawLangBac()
{
    //glEnable(GL_DEPTH_TEST);
    //63,63,70
    //113,113,122
    GLint r = 113;
    GLint g = 113;
    GLint b = 122;
    GLint t = 5;
    GLfloat xCurrent = 30;
    //drawCube(30, -4, 30, 28, 8 , 28, 113, 113, 122);//tang 1
    drawTang1(r, g, b);
    drawStair(r, g, b);
    r -= t;
    g -= t;
    b -= t;
    drawCube(32.5, 4+0.05, 32.5, 23, 1.5 - 0.05, 23, r,g,b); // tang 2
    r -= t;
    g -= t;
    b -= t;
    drawCube(35, 5.5 + 0.05, 35, 18, 1.5 - 0.05, 18, r , g , b ); //tang 3
    r -= t;
    g -= t;
    b -= t;
    GLfloat ChieuCaoCot = 4;
    GLfloat CanhCot = 1.5;
    GLfloat KhooangCachCot = 1;
    drawCube(36.5, 7+0.05, 36.5, CanhCot, ChieuCaoCot, CanhCot, r, g, b); //cot 1
    drawCube(50, 7+0.05, 36.5, CanhCot, ChieuCaoCot, CanhCot, r, g, b); //cot 2
    drawCube(36.5, 7+0.05, 50, CanhCot, ChieuCaoCot, CanhCot, r, g, b); //cot 3
    drawCube(50, 7+0.05, 50, CanhCot, ChieuCaoCot, CanhCot, r, g, b); //cot 4
    //Ve cot 1 den cot 2
    for (int i = 0; i < 4; i++) 
    {
        drawCube(39.5 + i * CanhCot + KhooangCachCot * i, 7.1, 36.5, CanhCot, ChieuCaoCot, CanhCot, r, g, b);
    }
    //ve cot 2 den cot 3
    for (int i = 0; i < 4; i++)
    {
        drawCube(50, 7.1, 39.5 + i * CanhCot + KhooangCachCot * i, CanhCot, ChieuCaoCot, CanhCot, r, g, b);
    }
    //ve cot 3 den cot 4
    for (int i = 0; i < 4; i++)
    {
        drawCube(47 - i * CanhCot - KhooangCachCot * i, 7.1, 50 , CanhCot, ChieuCaoCot, CanhCot, r, g, b);
    }
    //ve cot 4 den cot 1
    for (int i = 0; i < 4; i++)
    {
        drawCube(36.5, 7.1, 47 - i * CanhCot - KhooangCachCot * i, CanhCot, ChieuCaoCot, CanhCot, r, g, b);
    }
    drawCube(38.5, 7.1, 38.5, 11, ChieuCaoCot, 11, r, g, b); // Tang 4 ben trong
    r -= t;
    g -= t;
    b -= t;
    drawCube(36, 11+0.05, 36, 16-0.05, 0.5, 16, r, g, b); //tang 5
    r -= t;
    g -= t;
    b -= t;
    drawRoof(r,g,b); //Tang 6
    r -= t;
    g -= t;
    b -= t;
    //glBegin(GL_QUADS)
    drawCube(38.5, 13.5+0.05, 38.5, 11, 2, 11, r, g, b);
    
}
void drawGate()
{

}
void drawAxis()
{
    /* Create a display list for drawing axes */
   
    axes_list = glGenLists(1);
    glNewList(axes_list, GL_COMPILE);

    glColor4ub(0, 0, 255, 255);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.75f, 0.25f, 0.0f);
    glVertex3f(0.75f, -0.25f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glVertex3f(0.75f, 0.0f, 0.25f);
    glVertex3f(0.75f, 0.0f, -0.25f);
    glVertex3f(1.0f, 0.0f, 0.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 0.75f, 0.25f);
    glVertex3f(0.0f, 0.75f, -0.25f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.25f, 0.75f, 0.0f);
    glVertex3f(-0.25f, 0.75f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glEnd();
    glBegin(GL_LINE_STRIP);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.25f, 0.0f, 0.75f);
    glVertex3f(-0.25f, 0.0f, 0.75f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.25f, 0.75f);
    glVertex3f(0.0f, -0.25f, 0.75f);
    glVertex3f(0.0f, 0.0f, 1.0f);
    glEnd();

    glColor4ub(255, 255, 0, 255);
    glRasterPos3f(1.1f, 0.0f, 0.0f);

    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'x');
    glRasterPos3f(0.0f, 1.1f, 0.0f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'y');
    glRasterPos3f(0.0f, 0.0f, 1.1f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'z');

    glEndList();
}
void drawGrass()
{
    glBegin(GL_QUADS);
    glColor3ub(0, 128, 0);
    glVertex3f(28, -3.9, 28);
    glVertex3f(28, -3.9, 60);
    glVertex3f(60, -3.9, 60);
    glVertex3f(60, -3.9, 28);
    glEnd();
}
void drawTree(GLfloat x, GLfloat z)
{
   
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glRotatef(-90, 1, 0, 0);
    glColor3ub(153, 106, 81);
    glTranslatef(-4, -5, -4);
    gluCylinder(g_normalObject, 1, 1, 6.0, 32, 4);
    glPopMatrix();

    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3ub(0, 128, 0);
    glTranslatef(-4, 2, 5);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluSphere(g_flatshadedObject, 2, 16, 16);
    glPopMatrix();
}
//=========================================================//

//=========================================================//
GLvoid DrawNormalObjects()
{

    
    // save the existing color properties
    
    //glLoadIdentity();
    glPushAttrib(GL_CURRENT_BIT);
    glEnable(GL_LIGHTING);

    GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    GLfloat pos[4] = { 5.0, 5.0, 5.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    //drawCube(4, 5, 6, 1, 2, 3, 191, 242, 235);
    drawFlag();
    //glLoadIdentity();
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);
    //glLineWidth(0.4);
    glEnable(GL_LINE_SMOOTH);
    drawGround();
    drawLangBac();
    drawSky();
    drawGrass();
    //drawTree(5, 6);
    
    drawAxis();
    glPopMatrix();
    glPopAttrib();
    
}


//=========================================================//

static void display(void)
{
    update_camera();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHTING);

    // position the light
    //GLfloat pos[4] = { 5.0, 5.0, 5.0, 0.0 };
    //glLightfv(GL_LIGHT0, GL_POSITION, pos);

    
    DrawNormalObjects();


    //glDisable(GL_LIGHTING);
    glColor3d(1, 1, 1);

    glutSwapBuffers();
}

//=========================================================//
//=========================================================//
static void keyboard(unsigned char key, int x, int y)
{
    int number = -1;

    move_camera(number, key);

    switch (key)
    {
    case 'l':
        rotateBase_degrees--;
        break;
    case 'L':
        rotateBase_degrees--;
        break;
    case 'r':
        rotateBase_degrees++;
        break;
    case 'R':
        rotateBase_degrees++;
        break;
    case '1':
        wheelRotateFactor = 1.0;
        break;
    case '2':
        wheelRotateFactor = 2.0;
        break;
    case '3':
        wheelRotateFactor = 3.0;
        break;
    default:
        break;
    }


    glutPostRedisplay();
}
//=========================================================//
//=========================================================//
void move_camera(int specialKEY, char normalKEY)
{
    // keyboard :: normal keys
    switch (normalKEY)
    {   // looking up
    case 'A':
    case 'a':    g_elevationAngle += 2.0; break;
        // looking down
    case 'Z':
    case 'z':g_elevationAngle -= 2.0;  break;

    case 's':
        g_playerPos[1] += 2.0; break;
    case 'x':
        g_playerPos[1] -= 2.0; break;
    default:
    {    break;
    }
    }

    // special :: special keys
    switch (specialKEY)
    {   // camera setup
        // check if it is moving the view to look left
    case GLUT_KEY_LEFT:
    {
        g_viewAngle -= 2.0;
        // calculate camera rotation angle radians
        rad = float(3.14159 * g_viewAngle / 180.0f);
        break;
    }
    // check if it is moving the view to look right
    case GLUT_KEY_RIGHT:
    {
        g_viewAngle += 2.0;
        // calculate camera rotation angle radians
        rad = float(3.14159 * g_viewAngle / 180.0f);
        break;
    }
    // pressing keys Up/Down, update coordinates "x" and "z"
    // based on speed and angle of view.
    case GLUT_KEY_UP:
    {
        g_playerPos[2] += sin(rad) * DEFAULT_SPEED;
        g_playerPos[0] += cos(rad) * DEFAULT_SPEED;
        break;
    }
    case GLUT_KEY_DOWN:
    {
        g_playerPos[2] -= sin(rad) * DEFAULT_SPEED;
        g_playerPos[0] -= cos(rad) * DEFAULT_SPEED;
        break;
    }
    default:
    {   break;
    }
    }
}
//=========================================================//
//=========================================================//
static void special(int key, int x, int y)
{
    char letter = ' ';

    move_camera(key, letter);

    glutPostRedisplay();
}

//=========================================================//
//=========================================================//
static void idle(void)
{
    glutPostRedisplay();
}
//=========================================================//
//=========================================================//
void update_camera()
{
    // don't allow the player to wander past the "edge of the world"
    if (g_playerPos[0] < -(WORLDSIZE - 50))
        g_playerPos[0] = -(WORLDSIZE - 50);
    if (g_playerPos[0] > (WORLDSIZE - 50))
        g_playerPos[0] = (WORLDSIZE - 50);
    if (g_playerPos[2] < -(WORLDSIZE - 50))
        g_playerPos[2] = -(WORLDSIZE - 50);
    if (g_playerPos[2] > (WORLDSIZE - 50))
        g_playerPos[2] = (WORLDSIZE - 50);

    // calculate the player's angle of rotation in radians
    float rad = float(3.14159 * g_viewAngle / 180.0f);
    // use the players view angle to correctly set up the view matrix
    g_lookAt[0] = float(g_playerPos[0] + 100 * cos(rad));
    g_lookAt[2] = float(g_playerPos[2] + 100 * sin(rad));

    rad = float(3.13149 * g_elevationAngle / 180.0f);

    g_lookAt[1] = float(g_playerPos[1] + 100 * sin(rad));

    // clear the modelview matrix
    glLoadIdentity();

    // setup the view matrix
    gluLookAt(g_playerPos[0], g_playerPos[1], g_playerPos[2],
        g_lookAt[0], g_lookAt[1], g_lookAt[2],
        0.0, 1.0, 0.0);
}
//=========================================================//
//=========================================================//
void setup_sceneEffects(void)
{
    // enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    // enable using glColor to change material properties
    // we'll use the default glColorMaterial setting (ambient and diffuse)
    glEnable(GL_COLOR_MATERIAL);

    // set the default blending function
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // set up the fog parameters for reflections
    glFogi(GL_FOG_MODE, GL_LINEAR);
    glFogf(GL_FOG_START, -100.0);
    glFogf(GL_FOG_END, 100.0);

    // enable line anti-aliasing and make the lines slightly bigger than default
    glEnable(GL_LINE_SMOOTH);
    glLineWidth(1.5f);
}
//=========================================================//
//=========================================================//
void init_dados(void)
{
    setup_sceneEffects();
    // create a normal quadric (uses default settings)
    g_normalObject = gluNewQuadric();

    g_wireframeObject = gluNewQuadric();
    gluQuadricDrawStyle(g_wireframeObject, GLU_LINE);

    // create an object that uses flat shading
    g_flatshadedObject = gluNewQuadric();
    gluQuadricNormals(g_flatshadedObject, GLU_FLAT);

}
//=========================================================//
//=========================================================//
void cleanUP_data(void)
{  // delete all quadratic objects
    if (g_normalObject)
        gluDeleteQuadric(g_normalObject);
    if (g_wireframeObject)
        gluDeleteQuadric(g_wireframeObject);
    if (g_flatshadedObject)
        gluDeleteQuadric(g_flatshadedObject);
}
//=========================================================//
//=========================================================//
int main(int argc, char* argv[])
{
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(40, 40);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    init_dados();

    glutCreateWindow("Snow storm");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutIdleFunc(idle);

    // environment background color
    //glClearColor(1,1,1,0);//(1,1,1,1);
    // deepth efect to objects
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    // light and material in the environment
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glutMainLoop();
    cleanUP_data();

    return EXIT_SUCCESS;
}
//=========================================================//
//=========================================================//
    
