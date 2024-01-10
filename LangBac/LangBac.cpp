//=========================================================//
//=========================================================//
//
// Supporting library
// http://www.wikihow.com/Install-Mesa-%28OpenGL%29-on-Linux-Mint
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

GLvoid  DrawNormalObjects(GLfloat rotation);
GLvoid  DrawWireframeObjects(GLfloat rotation);
GLvoid  DrawFlatshadedObjects(GLfloat rotation);
//=========================================================//
//=========================================================//
// Collision detection
GLfloat p1_radius = 0.3f;
GLfloat p2_radius = 0.3f;
GLfloat p1_x = -2.0f;
GLfloat p2_x = 2.0f;
GLfloat p1_y = 2.0f;
GLfloat p2_y = 2.0f;
GLfloat p1_z = 5.0f;
GLfloat p2_z = 5.0f;
GLfloat change_direction = 1.0;
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
static void text_onScreen(int row, int col, const char* fmt, ...)
{
    static char buf[256];
    int viewport[4];
    //void *font = GLUT_BITMAP_9_BY_15;
    va_list args;

    va_start(args, fmt);
    (void)printf(buf, fmt, args);
    va_end(args);

    glGetIntegerv(GL_VIEWPORT, viewport);

    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    glOrtho(0, viewport[2], 0, viewport[3], -1, 1);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}
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
    //draw white snow ground
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

GLvoid drawCollision()
{
    GLfloat alphaTransparency = 0.5;
    GLfloat distance;

    // move forward and backward
    p1_x += 0.05f * change_direction;
    p2_x -= 0.05f * change_direction;

    if (p1_x > 2) {
        change_direction = 1.0f - 2.0f;
    }
    if (p1_x < -2) {
        change_direction = 1.0f;
    }
    // check-collision
    distance = sqrt(((p1_x - p2_x) * (p1_x - p2_x))
        + ((p1_y - p2_y) * (p1_y - p2_y))
        + ((p1_z - p2_z) * (p1_z - p2_z)));
    if (distance <= p2_radius + p1_radius) {
        // Red :: collision
        change_collor = 0.0;
    }
    else {
        // Yellow :: no collision
        change_collor = 1.0;
    }
    // enable blending for transparent sphere
    glEnable(GL_BLEND);     // Turn Blending On
    glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // first sphere collides against the other
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor4f(1.0f, change_collor, 0.0f, alphaTransparency);
    glTranslatef(p1_x, p1_y, p1_z);
    gluSphere(g_normalObject, p1_radius, 16, 10);
    glPopMatrix();
    // second sphere collides against the first
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor4f(1.0f, change_collor, 0.0f, alphaTransparency);
    glTranslatef(p2_x, p2_y, p2_z);
    gluSphere(g_normalObject, p2_radius, 16, 10);
    glPopMatrix();

    glDisable(GL_BLEND);        // Turn Blending Off
    glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
}
//=========================================================//
//=========================================================//
GLvoid drawCone(void)
{
    GLfloat alphaTransparency = 0.5;
    // a transparency example: green cylinder
    // enable blending for transparent cylinder
    glEnable(GL_BLEND);     // Turn Blending On
    glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3f(1, 0.6, 0);
    glTranslatef(0.0, 0.4, 0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.15, 0.0, 0.4, 32, 8);
    glPopMatrix();


    //		  glPushMatrix();
    //			glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    //			glColor3f(0,0,0);
    //			glTranslatef(0.0, 0.4, 2);
    //			glRotatef(-90, 1.0, 0.0, 0.0);
    //			gluCylinder(g_normalObject, 0.15, 0.15, 0.5, 32, 8);
    //		  glPopMatrix();





    glDisable(GL_BLEND);        // Turn Blending Off
    glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
}

// func for generating random float for snow pos
float RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
    //return 1.0;
}

GLvoid drawSnow(GLfloat snowloc)
{
    GLfloat alphaTransparency = 0.6;
    int max_snow = 10;
    // enable blending for transparent cylinder
    glEnable(GL_BLEND);     // Turn Blending On
    glDisable(GL_DEPTH_TEST);   // Turn Depth Testing Off
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //for (float x = 0.0; x > max_snow; x += 1)
    //{
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, alphaTransparency);
    //glColor3f(1.0f, 1.0f, 1.0f);
    glTranslatef(RandomFloat(-20.0, 20.0), snowloc + rand() % 70, RandomFloat(-20.0, 20.0));
    glutSolidSphere(0.03, 6, 6);
    glPopMatrix();
    //}

        //glPushMatrix();
          //glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
      //	glColor4f(0.0f,1.0f,0.0f,alphaTransparency);
          //glTranslatef(-5.0, 0.0, -5.0);
          //glRotatef(-90, 1.0, 0.0, 0.0);
          //gluCylinder(g_normalObject, 1.0, 0.0, 3.0, 32, 4);
        //glPopMatrix();

    glDisable(GL_BLEND);        // Turn Blending Off
    glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
}
void drawCube(GLfloat x0, GLfloat y0, GLfloat z0, GLfloat x1, GLfloat y1, GLfloat z1, GLint r, GLint g, GLint b)
{
    //glClear(GL_COLOR_BUFFER_BIT);
    //glColor3f(0.3f, 0.5f, 0.5f);
    //glNormal3f(1.0f, 1.0f, 1.0f);
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
    glTranslatef(-2, -2, -2);
    gluCylinder(g_normalObject, 0.2, 0.2, 6.0, 32, 4);
    glPopMatrix();
    //glDisable(GL_BLEND);        // Turn Blending Off
    //glEnable(GL_DEPTH_TEST);    // Turn Depth Testing On
    //la co
    glBegin(GL_QUADS);
    float z = 2;
    glColor3ub(128, 0, 0);
    glVertex3f(-2, 4, z);
    glVertex3f(4, 4, z);
    glVertex3f(4, 0, z);
    glVertex3f(-2, 0, z);
    glEnd();
    //Ngoi sao
    //Tam Giac 1 2 10
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1.0, 3.2, z + 0.1);
    glVertex3f(1.2, 2.5, z + 0.1);
    glVertex3f(0.8, 2.5, z + 0.1);

    //Tam giac 2 3 4
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1.2, 2.5, z + 0.1);
    glVertex3f(2.0, 2.5, z + 0.1);
    glVertex3f(1.4, 1.9, z + 0.1);

    //Tam giac 4 5 6
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1.4, 1.9, z + 0.1);
    glVertex3f(1.6, 1.2, z + 0.1);
    glVertex3f(1, 1.6, z + 0.1);

    //Tam giac 6 7 8
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(1, 1.6, z + 0.1);
    glVertex3f(0.4, 1.2, z + 0.1);
    glVertex3f(0.6, 1.9, z + 0.1);

    //Tam giac 8 9 10
    glBegin(GL_TRIANGLES);
    glColor3ub(128, 128, 0);
    glVertex3f(0.6, 1.9, z + 0.1);
    glVertex3f(0, 2.5, z + 0.1);
    glVertex3f(0.8, 2.5, z + 0.1);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3ub(128, 128, 0);
    glVertex3f(1.2, 2.5, z + 0.1);
    glVertex3f(1.4, 1.9, z + 0.1);
    glVertex3f(1, 1.6, z + 0.1);
    glVertex3f(0.6, 1.9, z + 0.1);
    glVertex3f(0.8, 2.5, z + 0.1);
    glEnd();
    
}
void drawQuad(GLfloat x1, GLfloat y1, GLfloat z1,
    GLfloat x2, GLfloat y2, GLfloat z2,
    GLfloat x3, GLfloat y3, GLfloat z3,
    GLfloat x4, GLfloat y4, GLfloat z4,
    GLint r, GLint g, GLint b)
{
    glBegin(GL_QUADS);
    glColor3ub(r, g, b);
    glVertex3f(x1, y1, z1);
    glColor3ub(r+2, g+2, b+2);
    glVertex3f(x2, y2, z2);
    glColor3ub(r+4, g+4, b+4);
    glVertex3f(x3, y3, z3);
    glColor3ub(r+6, g+6, b+6);
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
    
}
void drawRoof()
{
    GLfloat xUp = 35.5;
    GLfloat xDown = 36;
    //GLfloat h;
    GLfloat aUp = 17;
    GLfloat aDown = 16;
    glBegin(GL_QUADS);
    //Mái trên
    glColor3ub(128, 128, 0);
    glVertex3f(xUp, 13.5, xUp);
    glVertex3f(xUp + aUp, 13.5, xUp);
    glVertex3f(xUp + aUp, 13.5, xUp + aUp);
    glVertex3f(xUp, 13.5, xUp + aUp);
    //Mái xung quanh
    //Mái 1
    glColor3ub(128, 0, 0);
    glVertex3f(xDown, 11.5, xDown);
    glVertex3f(xDown + aDown, 11.5, xDown);
    glVertex3f(xUp + aUp, 13.5, xUp);
    glVertex3f(xUp, 13.5, xUp);
    
    
    //Mái 2
    glColor3ub(63, 63, 70);
    glVertex3f(xDown + aDown, 11.5, xDown);
    glVertex3f(xDown + aDown, 11.5, xDown + aDown);
    glVertex3f(xUp + aUp, 13.5, xUp + aUp);
    glVertex3f(xUp + aUp, 13.5, xUp);
    
    //Mái 3
    glColor3ub(63, 63, 70);
    glVertex3f(xDown + aDown, 11.5, xDown + aDown);
    glVertex3f(xDown, 11.5, xDown + aDown);
    glVertex3f(xUp, 13.5, xUp + aUp);
    glVertex3f(xUp + aUp, 13.5, xUp + aUp);
    
    //Mái 4
    glColor3ub(63, 63, 70);
    glVertex3f(xDown, 11.5, xDown + aDown);
    glVertex3f(xDown, 11.5, xDown);
    glVertex3f(xUp, 13.5, xUp);
    glVertex3f(xUp, 13.5, xUp + aUp);
    
    glEnd();
    
}
void drawStair()
{
    GLfloat ChieuCaoBac = 0.8;
    GLfloat ChieuRongBac = 0.5;
    GLfloat ChieuDaiBac = 1.5;
    GLfloat DoDaiKhoi = 9;
    //Cầu thang trái
    //drawCube(30, -4, 28.5, ChieuRongBac, ChieuCaoBac, ChieuDaiBac, 70, 80, 90);
    for (int i = 0; i < 10; i++)
    {
        drawCube(30 + ChieuRongBac * i, -4 + ChieuCaoBac * i, 28.5, ChieuRongBac, ChieuCaoBac, ChieuDaiBac, 70, 80, 90);
    }


    //Cầu thang phải
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
    drawQuad(32, -4, 38, 32, -4, 44, 32, 1, 44, 32, 1, 38, 128, 0, 0);
    drawQuad(32, -4, 44, 32, -4, 50, 32, 1, 50, 32, 1, 44, 128, 0, 0);
    //mặt trái
    drawQuad(30, -4, 30, 58, -4, 30, 58, 4, 30, 30, 4, 30, r, g, b);
    glColor3ub(r, g, b);
    glVertex3f(30, -4, 30);
    glVertex3f(58, -4, 30);
    glVertex3f(58, 4, 30);
    glVertex3f(30, 4, 30);
    //mặt phải
    drawQuad(30, -4, 58, 58, -4, 58, 58, 4, 58, 30, 4, 58, r, g, b);
    glColor3ub(r, g, b);
    glVertex3f(30, -4, 58);
    glVertex3f(58, -4, 58);
    glVertex3f(58, 4, 58);
    glVertex3f(30, 4, 58);
    //mặt sau
    drawQuad(58, -4, 30, 58, -4, 58, 58, 4, 58, 58, 4, 30, r, g, b);
    glColor3ub(r, g, b);
    glVertex3f(58, -4, 30);
    glVertex3f(58, -4, 58);
    glVertex3f(58, 4, 58);
    glVertex3f(58, 4, 30);

    //Hành lang
    // Nền hành lang
    glBegin(GL_QUADS);
    glColor3ub(155, 155, 122);
    glVertex3f(30.5, 2, 30.5);
    glVertex3f(30.5, 2, 57.5);
    glVertex3f(57.5, 2, 57.5);
    glVertex3f(57.5, 2, 30.5);
    glEnd();

    //Trái
    drawQuad(30.5, 2, 30.5, 36.5, 2, 30.5, 36.5, 4, 30.5, 30.5, 4, 30.5, 125, 126, 127);
    drawQuad(37.5, 2, 30.5, 57.5, 2, 30.5, 57.5, 4, 30.5, 37.5, 4, 30.5, 125, 126, 127);
    drawQuad(36.5, 2, 30, 36.5, 2, 30.5, 36.5, 4, 30.5, 36.5, 4, 30, 125, 126, 127);
    drawQuad(37.5, 2, 30, 37.5, 2, 30.5, 37.5, 4, 30.5, 37.5, 4, 30, 125, 126, 127);

    //Trước
    drawQuad(30.5, 2, 30.5, 30.5, 2, 57.5, 30.5, 4, 57.5, 30.5, 4, 30.5, 125, 126, 127);

    //Phải
    drawQuad(30.5, 2, 57.5, 36.5, 2, 57.5, 36.5, 4, 57.5, 30.5, 4, 57.5, 125, 126, 127);
    drawQuad(37.5, 2, 57.5, 57.5, 2, 57.5, 57.5, 4, 57.5, 37.5, 4, 57.5, 125, 126, 127);
    drawQuad(36.5, 2, 57.5, 36.5, 2, 58, 36.5, 4, 58, 36.5, 4, 57.5, 125, 126, 127);
    drawQuad(37.5, 2, 57.5, 37.5, 2, 58, 37.5, 4, 58, 37.5, 4, 57.5, 125, 126, 127);

    //Sau
    drawQuad(57.5, 2, 30.5, 57.5, 2, 57.5, 57.5, 4, 57.5, 57.5, 4, 30.5, 125, 126, 127);
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
    glVertex3f(37.5, 3.9, 30);
    glVertex3f(58, 3.9, 30);
    glVertex3f(58, 3.9, 30.5);
    glVertex3f(37.5, 3.9, 30.5);
    glEnd();

    drawCube(32, 2, 32, 24, 2, 24, r, g, b);
}
void drawLangBac()
{
    //63,63,70
    //113,113,122
    GLfloat xCurrent = 30;
    //drawCube(30, -4, 30, 28, 8 , 28, 113, 113, 122);//tang 1
    drawTang1(113, 113, 122);
    drawCube(32.5, 4, 32.5, 23, 1.5, 23, 113,113,122); // tang 2
    drawCube(35, 5.5, 35, 18, 1.5, 18, 128, 42, 45); //tang 3
    GLfloat ChieuCaoCot = 4;
    GLfloat CanhCot = 1.5;
    GLfloat KhooangCachCot = 1;
    drawCube(36.5, 7+0.1, 36.5, CanhCot, ChieuCaoCot, CanhCot, 128 , 0, 0); //cot 1
    drawCube(50, 7+0.1, 36.5, CanhCot, ChieuCaoCot, CanhCot, 128, 0, 0); //cot 2
    drawCube(36.5, 7+0.1, 50, CanhCot, ChieuCaoCot, CanhCot, 128, 0, 0); //cot 3
    drawCube(50, 7+0.1, 50, CanhCot, ChieuCaoCot, CanhCot, 128, 0, 0); //cot 4
    //Ve cot 1 den cot 2
    for (int i = 0; i < 4; i++) 
    {
        drawCube(39.5 + i * CanhCot + KhooangCachCot * i, 7.1, 36.5, CanhCot, ChieuCaoCot, CanhCot, 128, 0, 0);
    }
    //ve cot 2 den cot 3
    for (int i = 0; i < 4; i++)
    {
        drawCube(50, 7.1, 39.5 + i * CanhCot + KhooangCachCot * i, CanhCot, ChieuCaoCot, CanhCot, 128, 0, 0);
    }
    //ve cot 3 den cot 4
    for (int i = 0; i < 4; i++)
    {
        drawCube(47 - i * CanhCot - KhooangCachCot * i, 7.1, 50 , CanhCot, ChieuCaoCot, CanhCot, 128, 0, 0);
    }
    //ve cot 4 den cot 1
    for (int i = 0; i < 4; i++)
    {
        drawCube(36.5, 7.1, 47 - i * CanhCot - KhooangCachCot * i, CanhCot, ChieuCaoCot, CanhCot, 128, 0, 0);
    }
    drawCube(38.5, 7.1, 38.5, 11, ChieuCaoCot, 11, 128, 128, 128); // Tang 4 ben trong
    drawCube(36, 11+0.2, 36, 16, 0.5, 16, 128, 42, 45); //tang 5
    drawRoof(); //Tang 6
    //glBegin(GL_QUADS)
    drawCube(38.5, 13.5, 38.5, 11, 2, 11, 128, 128, 0);
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
void drawColorFan(GLfloat radius, int sections)
{
    //DRAWS A WHEEL WITH RAINBOW COLORS FOR SECTIONS

    //define light so rotation doesn't change the matrix
    GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    glBegin(GL_TRIANGLE_FAN);
    int i;
    glVertex2f(0.0, 0.0);
    for (i = 0; i <= sections; i++) {

        //circle-like triangle fan
        glVertex2f(radius * cos(i * 2.0 * 3.14159 / sections),
            radius * sin(i * 2.0 * 3.14159 / sections));

        //set color sections
        switch (i % 6)
        {
        case 0:
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case 1:
            glColor3f(1.0f, 0.5f, 0.0f);
            break;
        case 2:
            glColor3f(1.0f, 1.0f, 0.0f);
            break;
        case 3:
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case 4:
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case 5:
            glColor3f(1.0f, 0.0f, 1.0f);
            break;
        }
    }

    glEnd();
}

//=========================================================//
GLvoid DrawNormalObjects(GLfloat rotation, GLfloat snowloc, GLfloat snowloc2)
{

    
    // save the existing color properties
    
    glPushAttrib(GL_CURRENT_BIT);
    GLfloat light_ambient[] = { 1.0, 1.0, 1.0, 0 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    //drawCube(4, 5, 6, 1, 2, 3, 191, 242, 235);
    drawFlag();
    
    //drawCollision();
    //drawCone();
    //drawTransparentCylinder();
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    //glLineWidth(0.4);
    glEnable(GL_LINE_SMOOTH);
    drawGround();
    drawLangBac();
    drawSky();
    drawGrass();
    drawTree(5, 6);
    drawStair();
    drawAxis();
    glPopMatrix();
    // start snow
    // use snowloc for changing direction
    // 200 * 2 snowflakes
    /*
    int max_snow = 1000;

    for (int n = max_snow; n > 0; n--) {
        drawSnow(snowloc);
    }

    for (int n = max_snow; n > 0; n--) {
        drawSnow(snowloc2);
    }
    // make sure the random color values we get are the same every time
    srand(200);
    
    
    // tree #1
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3ub(102, 0, 0);
    glTranslatef(2.0, -2.0, -14.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.5, 0.5, 4.0, 32, 4);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 4.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);
    glPopMatrix();

    // tree #2
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3ub(0, 51, 0);
    glTranslatef(-5.0, -2.0, -10.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.5, 0.5, 4.0, 32, 4);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 4.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);
    glPopMatrix();

    // tree #3
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3ub(102, 51, 0);
    glTranslatef(-10.0, -2.0, -8.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.5, 0.5, 4.0, 32, 4);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 4.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);
    glPopMatrix();

    // tree #4
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3ub(102, 51, 0);
    glTranslatef(6.0, -2.0, -11.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.5, 0.5, 4.0, 32, 4);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 4.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);

    glColor3ub(0, 128, 0);
    glTranslatef(0.0, 0.0, 1.0);
    glRotatef(0, 0.0, 1.0, 0.0);
    gluCylinder(g_normalObject, 2.0, 0.0, 6.0, 32, 2);
    glPopMatrix();
    
    glPushMatrix();
    //STEM cylinder
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3f(0, 1, 1);
    glTranslatef(20, -5, -18);
    glRotatef(-90, 1.0, 0.0, 0);
    glRotatef(rotateBase_degrees, 0.0, 0.0, 1.0);
    gluCylinder(g_flatshadedObject, 0.5, 0.5, 10.0, 32, 4);

    //pipe on disks
    glTranslatef(0, 0, 9);
    glRotatef(-270, 1, 0, 0);
    gluCylinder(g_flatshadedObject, 0.4, 0.4, 4.0, 32, 4);

    //large windwheel
    glColor3f(1, 0, 0);
    glTranslatef(0, 0, 1);
    glRotatef(rotation * 3.0f * wheelRotateFactor, 0.0, 0.0, 1.0);
    drawColorFan(4, 36); // radius is 5, 36 is num triangles

    //medium wheel
    glColor3f(0, 1, 0);
    glTranslatef(0, 0, 1);
    glRotatef(rotation * -3.50f * wheelRotateFactor, 0.0, 0.0, 1.0);
    drawColorFan(3, 36);

    //small wheel
    glTranslatef(0, 0, 1);
    glRotatef(rotation * 0.25f * wheelRotateFactor, 0.0, 0.0, 1.0);
    drawColorFan(2, 36);
    glPopMatrix();

    
    // snowman
    glPushMatrix();

    //belly
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3f(1, 0.3, 1);
    glTranslatef(0.0f, -1.0f, -6.0f);
    glRotatef(-90, 1.0f, 0.0f, 0.0f);
    gluSphere(g_flatshadedObject, 1.0f, 16, 16);

    //torso
    glColor3f(1, 0.4, 1);
    glTranslatef(0, 0, 1);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluSphere(g_flatshadedObject, 0.75f, 16, 16);

    //head
    glColor3f(1, 0.5, 1);
    glTranslatef(0, 1, 0);
    glRotatef(90, 1.0f, 0.0f, 0.0f);
    gluSphere(g_flatshadedObject, 0.5f, 16, 16);

    // nose
    drawCone();

    //body details
    glPushMatrix();
    //eyes front:
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3f(0, 0, 0);
    glTranslatef(-0.2, 0.45, -0.2);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluDisk(g_normalObject, 0.01, 0.1, 32, 4); // iris1
    //back:
    glTranslatef(0, 0, -0.1);
    glRotatef(0, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.1, 0.1, 0.1, 32, 4);

    //front:
    glColor4f(0, 0, 0, 0.5);
    glTranslatef(0.4, 0, 0.1);
    gluDisk(g_normalObject, 0.01, 0.1, 32, 4); // iris2
    //back:
    glTranslatef(0, 0, -0.1);
    glRotatef(0, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.1, 0.1, 0.1, 32, 4);
    glPopMatrix();


    glPushMatrix();
    //buttons
    //front:
    glColor4f(1, 0, 0, 0.5);
    glTranslatef(0, 0.8, 1);
    glRotatef(-90.0, 1.0, 0.0, 0.0);
    gluDisk(g_normalObject, 0.01, 0.1, 32, 4); // iris2
    //back:
    glTranslatef(0, 0, -0.1);
    glRotatef(0, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.1, 0.1, 0.1, 32, 4);

    glColor4f(1, 0, 0, 0.5);
    glTranslatef(0, 0.4, 0);
    gluDisk(g_normalObject, 0.01, 0.1, 32, 4); // iris2
    //back:
    glTranslatef(0, 0, -0.1);
    glRotatef(0, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.1, 0.1, 0.1, 32, 4);
    glPopMatrix();
    glPopMatrix();
    //end of snowman


      //hat disk:
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3f(0, 0, 1);
    glTranslatef(0.0, 1.4, -6.0);
    glRotatef(90.0, 1.0, 0.0, 0.0);
    gluDisk(g_normalObject, 0.1, 0.5, 32, 4); // note inner
    glPopMatrix();

    //hat top:
    glPushMatrix();
    glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, rand() % 128);
    glColor3f(0, 0, 1);
    glTranslatef(0.0, 1.4, -6.0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    gluCylinder(g_normalObject, 0.3, 0.3, 0.4, 32, 4);
    glPopMatrix();

    */

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
    GLfloat pos[4] = { 5.0, 5.0, 5.0, 0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, pos);

    // rotation is used for animation
    static GLfloat rotation = 0.0;
    static GLfloat snowloc = 5.0;
    static GLfloat snowloc2 = snowloc + 50.0;
    // it's increased by one every frame
    rotation += 1.0;
    snowloc -= 0.1;
    snowloc2 -= 0.1;
    // and ranges between 0 and 360
    if (rotation > 360.0)
        rotation = 0.0;

    if (snowloc < -50.0)
        snowloc = 60.0;

    if (snowloc2 < -80.0)
        snowloc2 = snowloc + 50.0;
    // draw all of our objects in their normal position
    DrawNormalObjects(rotation, snowloc, snowloc2);


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