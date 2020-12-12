/*
 * GLUT Shapes Demo
 *
 * Written by Nigel Stewart November 2003
 *
 * This program is test harness for the sphere, cone
 * and torus shapes in GLUT.
 *
 * Spinning wireframe and smooth shaded shapes are
 * displayed until the ESC or q key is pressed.  The
 * number of geometry stacks and slices can be adjusted
 * using the + and - keys.
 */

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>

#endif
#define pi 3.1416
#include <stdlib.h>
#include<bits/stdc++.h>
#include "RGBpixmap.cpp"
#include <time.h>
using namespace std;

RGBpixmap pix[10];
void fan();
void cube();
void cube2();
void wall();
void floor();
//void quads();
void Object();
void cilinder();
void polygon ();
void table();
//void hali(double a);

static int slices = 16;
static int stacks = 16;

/* GLUT callback Handlers */

float dx=0,dy=0,dz=0,sx=1,sy=1,sz=1,cx=0,cy=1,cz=-6,upx=0,upy=1,upz=0,pitch=0,roll=0;
float z=-15;
float i=0;
float j=0;
float r=0;
float p=0;
float q=0,A=0,B=0,C=0;
int l=0;
int f=0;
float ez=4;
float scale = .18;
float eye_x = 0.0,eye_y = 0.0,zom=50.0;
time_t fandy;
int radius=1,aperture=1;

int flag = 0;

float sn = 100;



const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat light_position[] = { 0.0f, -5.0f, 8.0f, 1.0f };


GLfloat mat_ambient[]    = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat mat_diffuse[]    = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat mat_specular[]   = { 0.1f, 0.1f, 0.1f, 1.0f };
GLfloat high_shininess[] = { sn };


const GLfloat light1_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light1_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light1_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
const GLfloat light1_position[] = {0.0, -2.0, -8.0, 1.0 };

const GLfloat light2_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light2_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light2_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light2_position[] = { 0.5f, 0.0f, 8.0f, 1.0f };
const GLfloat spot_direction[] = { 0.0, -1.0, -15.0 };



void material()
{
        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
}

///drawkoch******************************


int Depth=1;

void drawkoch(GLfloat x,GLfloat y, GLfloat len, GLint iter) {

	if (iter == -1) {
        return;
	}


	else {

		iter--;

		glBegin(GL_QUADS);
            glVertex2f(x+len/3.0, y+2.0*len/3.0);
            glVertex2f(x+len/3.0, y+len/3.0);
            glVertex2f(x+2.0*len/3.0, y+len/3.0);
            glVertex2f(x+2.0*len/3.0, y+2.0*len/3.0);
		glEnd();

		drawkoch(x,y, len/3.0, iter);
		drawkoch(x+len/3.0,y, len/3.0, iter);
		drawkoch(x+2.0*len/3.0,y, len/3.0, iter);

		drawkoch(x,y+len/3.0, len/3.0, iter);
		drawkoch(x+2.0*len/3.0,y+len/3.0, len/3.0, iter);

        drawkoch(x,y+2.0*len/3.0, len/3.0, iter);
		drawkoch(x+len/3.0,y+2.0*len/3.0, len/3.0, iter);
		drawkoch(x+2.0*len/3.0,y+2.0*len/3.0, len/3.0, iter);




	}
}

void KochCurve(int depth) {
	glClear(GL_COLOR_BUFFER_BIT);

	drawkoch(0,0,9, depth);

	glFlush();
}



static void resize(int width, int height)
{
const float ar = (float) width / (float) height;


    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2, 100.0);
    gluPerspective(zom,(float)width/(float)height,1,50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;



}

static void Own_scalf(float x,float y,float z)
{
    GLfloat m[16];
    m[0] = x;  m[1] = 0; m[2] = 0; m[3] = 0;
    m[4] = 0;  m[5] = y; m[6] = 0; m[7] = 0;
    m[8] = 0;  m[9] = 0; m[10] = z; m[11] = 0;
    m[12] = 0;  m[13] = 0; m[14] = 0; m[15] = 1;
    glMatrixMode(GL_MODELVIEW);
    glMultMatrixf(m);
}
GLfloat vertices[] = {0,0,0, 6,0,0, 6,0,6, 0,0,6, 0,6,6, 0,6,0, 6,6,0, 6,6,6};
GLubyte quad_faces[] = {7,4,3,2, 6,7,2,1, 5,6,1,0, 4,5,0,3, 6,5,4,7, 3,0,1,2};
GLfloat colors[] = {0,0,1, 0,1,0, 1,0,0, 1,1,0, 1,0,1, 0,1,1};




static void display(void)
{

    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    const double a = t*90.0*10;

    const double k = t*.1;
    const double o = t*.1;
    const double g = t*.1;

    float h = glutGet(GLUT_WINDOW_HEIGHT);
    float w = glutGet(GLUT_WINDOW_WIDTH);

     //int a=0;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ////glColor3d(0,1,0);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(zom,(float)1500/(float)1000,1,50);
        glMatrixMode(GL_MODELVIEW);


    glLoadIdentity();
    //glFrustum(-1, 1, -1.0, 1.0, -zom, 100.0);
    //gluLookAt(eye_x,eye_y,4,0,1,-4,0,1,0);
   // gluLookAt(eye_x,eye_y,4,,j,-4,upx,upy,upz);
    gluLookAt(eye_x,eye_y,ez, i,j,1, p,1,q);

    glPushMatrix();


        Own_scalf(scale*1.5,scale*.8,scale);
        glRotated(dx,1,0,0);
        glRotated(dy,0,1,0);
        glRotated(dz,0,0,1);


    ///viewport1**********************************************************************
    glPushMatrix();
    glViewport(0,0,w/2,h);


     ///koch

    glPushMatrix();


        mat_diffuse[0]=A;
        mat_diffuse[1]=B;
        mat_diffuse[2]=C;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();


    glTranslated(-7.3,-5,4);
    glRotated(90,0,1,0);
    glScaled(1,1.8,.5);
    //glColor3d(0,1,0);
    KochCurve(Depth);
    glPopMatrix();

    ///hali1
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,4);
    glEnable(GL_TEXTURE_2D);



    //HALI
    glPushMatrix();

        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(0,-.3,0);
    glScaled(.4,.4,.4);


//fan1
        glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();


        //fan_rotation(fandy);
        //glRotated(dx,1,0,0);
        glRotated(a,0,1,0);
        //glRotated(dz,0,0,1);

        glPushMatrix();
         glTranslated(0,4,-3);
         glRotated(180,1,0,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

        glPushMatrix();
         glTranslated(0,4.2,3);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

        glTranslated(-0.5,4,-3);
        glScaled(1,.2,6);
        cube2();
        glPopMatrix();

        glPopMatrix();

//2nd fan

        glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        //glRotated(dx,1,0,0);
        glRotated(a,0,1,0);
        //glRotated(dz,0,0,1);


        glPushMatrix();
         glTranslated(3,4.2,-0);
         glRotated(90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();



        glPushMatrix();
         glTranslated(-3,4.2,0);
         glRotated(-90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        //glTranslated(2,1,1);
        glTranslated(-3,4,-.5);
        glScaled(6,.2,1);
        cube2();
    glPopMatrix();


    glPopMatrix();



    ///back fan

    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

         glTranslated(8.2,2.3,2.5);
         glRotated(180,1,0,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.5);

        glPushMatrix();
        glRotated(a,0,1,0);

        glPushMatrix();
         glTranslated(0,4,-3);
         glRotated(180,1,0,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

        glPushMatrix();
         glTranslated(0,4.2,3);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

        glTranslated(-0.5,4,-3);
        glScaled(1,.2,6);
        cube2();
        glPopMatrix();

//2nd fan

        glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();


        glPushMatrix();
         glTranslated(3,4.2,-0);
         glRotated(90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();



        glPushMatrix();
         glTranslated(-3,4.2,0);
         glRotated(-90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        //glTranslated(2,1,1);
        glTranslated(-3,4,-.5);
        glScaled(6,.2,1);
        cube2();
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();



    //cilinder
    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        glTranslated(0,4.2,0);
        glScaled(.2,2,.2);
        glRotated(90,1,0,0);
        cilinder();
    glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(-4,0,2);
    glScaled(6,3,4);
    polygon();
    glPopMatrix();



    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(-4,0,-2);
    glScaled(6,3,4);
    polygon();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-4,0,-1.9);
    glScaled(6,1.2,3.8);
    //glRotated(90,1,0,0);
    //glRotated(90,0,1,0);
    cube2();
  //  //glColor3d(0,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-1,3,-2);
    glScaled(3,0.2,3.90);
    glRotated(90,1,0,0);
    glRotated(90,0,1,0);
    cube2();
  //  //glColor3d(0,1,0);
    glPopMatrix();

   glPushMatrix();
    glTranslated(1,0,-2);
    glScaled(1,3,3.9);
    //glRotated(90,1,0,0);
    //glRotated(90,0,1,0);
    cube2();
  //  //glColor3d(0,1,0);
    glPopMatrix();



    glPushMatrix();
    glTranslated(-1,-1,1.4);
    glScaled(2,1,.2);

    cube2();

    glPopMatrix();


    glPushMatrix();
    glTranslated(-1,-1,-1.6);
    glScaled(2,1,.2);

    cube2();

    glPopMatrix();


    glPushMatrix();
    glTranslated(-1,-1.0,-2);
    glScaled(2,.2,1);

    cube2();

    glPopMatrix();

    glPushMatrix();
    glTranslated(-1,-1.0,1);
    glScaled(2,.2,1);

    cube2();

    glPopMatrix();


    glPushMatrix();
    ////glColor3d(0,1,0);
    glTranslated(-1,-1.0,1);
    glScaled(2,.2,1);

    cube2();

    glPopMatrix();

 //back
     glPushMatrix();


        //glTranslated(2,1,1);
        glTranslated(2,.3,-.4);
        glScaled(5,1.2,.8);
        cube2();
    glPopMatrix();


    glPushMatrix();
        glTranslated(7,.3,-.4);
        glRotated(45,0,0,1);
        glScaled(2,1,.8);
        cube2();
    glPopMatrix();


    glPushMatrix();
        glTranslated(8,2,-.4);
        glRotated(-45,0,0,1);
        //glRotated(90,1,0,0);
        glScaled(.5,.8,.8);
        fan();
    glPopMatrix();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();



     ///wall********************************
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,2);

        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-8,-5,-6);
    glScaled(16,16,.5);
    wall();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();




    ///frame********************
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,6);
    //glTexImage2D(GL_TEXTURE_2D,100,GL_RGBA,100,100,0,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,6);


        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-5.5,-.5,-5.9);
    glScaled(12,9,.5);
    wall();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();





    ///wall2
    glPushMatrix();

        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glBindTexture(GL_TEXTURE_2D,2);
    glEnable(GL_TEXTURE_2D);

    glTranslated(-8,-5,4);
    glRotated(90,0,1,0);
    glScaled(10,16,.5);
    wall();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    //wall3
    glPushMatrix();

        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glBindTexture(GL_TEXTURE_2D,7);
    glEnable(GL_TEXTURE_2D);

    glTranslated(-8,-5,-6);
    glRotated(90,1,0,0);
    glScaled(16,10,.5);
    floor();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();


    //wall4


   /* glPushMatrix();
    glTranslated(7.5,-5,4);
    glRotated(90,0,1,0);
    glScaled(10,16,.5);
    wall();

    glPopMatrix();
*/

    //object1
    glPushMatrix();
    glTranslated(-3,0.4,0);
    glRotated(45,1,0,0);
    Object();
    glPopMatrix();

    //object2
    glPushMatrix();
    glTranslated(-3,0.4,0);
    glRotated(90,0,0,1);
    glRotated(90,1,1,0);
    //glRotated(-45,1,0,0);
    glRotated(55,0,1,0);
    Object();
    glPopMatrix();

    //object3
    glPushMatrix();
    glTranslated(-3,0.4,0);
    glRotated(90,1,1,1);
    glRotated(90,0,1,1);
    Object();
    glPopMatrix();


    //table
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D,5);
    glEnable(GL_TEXTURE_2D);

        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-4.2,-.5,-3);
    glRotated(90,1,0,0);
    glScaled(8,6,.5);
    table();

    glPopMatrix();

    //leg1
    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-4.2,-4.5,-2.8);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    table();
    glPopMatrix();


    //leg2

    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-4.2,-4.5,2.5);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    table();
    glPopMatrix();


    //leg3


    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(3.5,-4.5,-2.8);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    table();
    glPopMatrix();


    //leg4

  glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(3.55,-4.5,2.5);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    table();
    glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glPopMatrix();


    ///viewport2***********************************************************************
    glPushMatrix();
    glViewport(w/2,0,w/2,h);


    ///hali2
    glPushMatrix();

    //HALI
    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(0,-.3,0);
    glScaled(.4,.4,.4);


//fan1
        glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();


        //fan_rotation(fandy);
        //glRotated(dx,1,0,0);
        glRotated(a,0,1,0);
        //glRotated(dz,0,0,1);

        glPushMatrix();
         glTranslated(0,4,-3);
         glRotated(180,1,0,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

        glPushMatrix();
         glTranslated(0,4.2,3);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

        glTranslated(-0.5,4,-3);
        glScaled(1,.2,6);
        cube();
        glPopMatrix();

        glPopMatrix();

//2nd fan

        glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        //glRotated(dx,1,0,0);
        glRotated(a,0,1,0);
        //glRotated(dz,0,0,1);


        glPushMatrix();
         glTranslated(3,4.2,-0);
         glRotated(90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();



        glPushMatrix();
         glTranslated(-3,4.2,0);
         glRotated(-90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        //glTranslated(2,1,1);
        glTranslated(-3,4,-.5);
        glScaled(6,.2,1);
        cube();
    glPopMatrix();


    glPopMatrix();



    //back fan

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

         glTranslated(8.2,2.3,2.5);
         glRotated(180,1,0,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.5);

        glPushMatrix();
        glRotated(a,0,1,0);

        glPushMatrix();
         glTranslated(0,4,-3);
         glRotated(180,1,0,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

        glPushMatrix();
         glTranslated(0,4.2,3);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

        glTranslated(-0.5,4,-3);
        glScaled(1,.2,6);
        cube();
        glPopMatrix();

//2nd fan

        glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();


        glPushMatrix();
         glTranslated(3,4.2,-0);
         glRotated(90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();



        glPushMatrix();
         glTranslated(-3,4.2,0);
         glRotated(-90,0,1,0);
         glRotated(90,1,0,0);
         glScaled(.5,.5,.2);
         fan();
        glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        //glTranslated(2,1,1);
        glTranslated(-3,4,-.5);
        glScaled(6,.2,1);
        cube();
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();



    //cilinder
    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        glTranslated(0,4.2,0);
        glScaled(.2,2,.2);
        glRotated(90,1,0,0);
        cilinder();
    glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(-4,0,2);
    glScaled(6,3,4);
    polygon();
    glPopMatrix();



    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(-4,0,-2);
    glScaled(6,3,4);
    polygon();
    glPopMatrix();


    glPushMatrix();
    glTranslated(-4,0,-1.9);
    glScaled(6,1.2,3.8);
    //glRotated(90,1,0,0);
    //glRotated(90,0,1,0);
    cube();
  //  //glColor3d(0,1,0);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-1,3,-2);
    glScaled(3,0.2,3.90);
    glRotated(90,1,0,0);
    glRotated(90,0,1,0);
    cube();
  //  //glColor3d(0,1,0);
    glPopMatrix();

   glPushMatrix();
    glTranslated(1,0,-2);
    glScaled(1,3,3.9);
    //glRotated(90,1,0,0);
    //glRotated(90,0,1,0);
    cube();
  //  //glColor3d(0,1,0);
    glPopMatrix();



    glPushMatrix();
    glTranslated(-1,-1,1.4);
    glScaled(2,1,.2);

    cube();

    glPopMatrix();


    glPushMatrix();
    glTranslated(-1,-1,-1.6);
    glScaled(2,1,.2);

    cube();

    glPopMatrix();


    glPushMatrix();
    glTranslated(-1,-1.0,-2);
    glScaled(2,.2,1);

    cube();

    glPopMatrix();

    glPushMatrix();
    glTranslated(-1,-1.0,1);
    glScaled(2,.2,1);

    cube();

    glPopMatrix();


    glPushMatrix();
    ////glColor3d(0,1,0);
    glTranslated(-1,-1.0,1);
    glScaled(2,.2,1);

    cube();

    glPopMatrix();

 //back
     glPushMatrix();


        //glTranslated(2,1,1);
        glTranslated(2,.3,-.4);
        glScaled(5,1.2,.8);
        cube();
    glPopMatrix();


    glPushMatrix();
        glTranslated(7,.3,-.4);
        glRotated(45,0,0,1);
        glScaled(2,1,.8);
        cube();
    glPopMatrix();


    glPushMatrix();
        glTranslated(8,2,-.4);
        glRotated(-45,0,0,1);
        //glRotated(90,1,0,0);
        glScaled(.5,.8,.8);
        fan();
    glPopMatrix();

    glPopMatrix();
    glPopMatrix();

     //wall
    glPushMatrix();
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-8,-5,-6);
    glScaled(16,16,.5);
    wall();

    glPopMatrix();

    //wall2
    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-8,-5,4);
    glRotated(90,0,1,0);
    glScaled(10,16,.5);
    wall();

    glPopMatrix();

    //wall3
    glPushMatrix();

        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-8,-5,-6);
    glRotated(90,1,0,0);
    glScaled(16,10,.5);
    floor();

    glPopMatrix();


    //wall4


   /* glPushMatrix();
    glTranslated(7.5,-5,4);
    glRotated(90,0,1,0);
    glScaled(10,16,.5);
    wall();

    glPopMatrix();
*/

///frame********************
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D,6);
    glTexImage2D(GL_TEXTURE_2D,100,GL_RGBA,100,100,0,GL_RGBA,GL_UNSIGNED_BYTE,checkImage);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D,6);


        mat_diffuse[0]=1.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-4.5,-.5,-5.9);
    glScaled(9,8,.5);
    wall();
    glDisable(GL_TEXTURE_2D);


    glPopMatrix();

    //object1
    glPushMatrix();
    glTranslated(-3,0.4,0);
    glRotated(45,1,0,0);
    Object();
    glPopMatrix();

    //object2
    glPushMatrix();
    glTranslated(-3,0.4,0);
    glRotated(90,0,0,1);
    glRotated(90,1,1,0);
    //glRotated(-45,1,0,0);
    glRotated(55,0,1,0);
    Object();
    glPopMatrix();

    //object3
    glPushMatrix();
    glTranslated(-3,0.4,0);
    glRotated(90,1,1,1);
    glRotated(90,0,1,1);
    Object();
    glPopMatrix();


    //table
    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-4.2,-.5,-3);
    glRotated(90,1,0,0);
    glScaled(8,6,.5);
    table();
    glPopMatrix();

    //leg1
    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-4.2,-4.5,-2.8);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    cube();
    glPopMatrix();


    //leg2

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    glTranslated(-4.2,-4.5,2.5);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    cube();
    glPopMatrix();


    //leg3


    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(3.5,-4.5,-2.8);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    cube();
    glPopMatrix();


    //leg4

  glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
    glTranslated(3.55,-4.5,2.5);
    glScaled(.2,4,.2);
    glRotated(0,90,90,0);
    cube();
    glPopMatrix();

    glPopMatrix();


    glPopMatrix();



    glutSwapBuffers();
}



void Object(){

    glPushMatrix(); //Object

        mat_diffuse[0]=1.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        glScaled(.1,.5,.1);


        glutSolidSphere(2,10,10);
    glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        glTranslated(0,1,0);
        glScaled(.1,.1,.1);


        glutSolidSphere(2,10,10);
    glPopMatrix();

    glPushMatrix();
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
        glTranslated(0,-1,0);
        glScaled(.1,.1,.1);


        glutSolidSphere(2,10,10);
    glPopMatrix();
}

void polygon()
{

    glBegin(GL_POLYGON);
    //glColor3d(0,0,.7);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glVertex3f(.5,1,0);
    glVertex3f(0,0.4,0);

    glEnd();


    glBegin(GL_POLYGON);
    //glColor3d(0,0,.7);
    glVertex3f(0,0,0);
    glVertex3f(0,0.4,0);
    glVertex3f(.5,1,0);
    glVertex3f(1,1,0);
    glVertex3f(1,0,0);




    glEnd();

    glBegin(GL_POLYGON);
    //glColor3d(0,0,.7);
    glVertex3f(0,0,0);
    glVertex3f(1,0,0);
    glVertex3f(1,1,0);
    glVertex3f(.5,1,0);
    glVertex3f(0,0.4,0);

    glEnd();



}


void cilinder()
{
    float x,y;
    vector<float>xx;
    vector<float>yy;
    for(int i=0; i<=360; i++){
        x= 1*cos(pi *(i)/180);
        xx.push_back(x);
        y= 1*sin(pi*(i)/180);
        yy.push_back(y);
    }

    glBegin(GL_POLYGON);
        //glColor3d(0,1,0);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

        for(int i=xx.size()-1; i>=0; i--){
            glVertex3d(xx[i], yy[i], 0);
        }
    glEnd();


    glBegin(GL_POLYGON);
        //glColor3d(0,1,0);

        for(int i=0; i<xx.size(); i++){
            glVertex3d(xx[i], yy[i], 1);
        }

    glEnd();

        glBegin(GL_POLYGON);
        //glColor3d(0,1,0);

        for(int i=0; i<xx.size(); i++){
            glVertex3d(xx[i], yy[i], 1);
        }

    glEnd();

    glBegin(GL_QUAD_STRIP);

      for(int i=xx.size()-1; i>=0; i--){
        glVertex3d(xx[i],yy[i],0);
        glVertex3d(xx[i],yy[i],1);
      }
      glVertex3d(xx[xx.size()-1],yy[xx.size()-1],0);
      glVertex3d(xx[xx.size()-1],yy[xx.size()-1],1);
    glEnd();
}

void cube()
{
    glBegin(GL_QUADS);
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    //glColor3d(0,0,.7);
    glVertex3f(0,0,1);
     glVertex3f(1,0,1);
     glVertex3f(1,1,1);
     glVertex3f(0,1,1);

     //glColor3d(1,0,1);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
      glVertex3f(0,0,1);
     glVertex3f(0,1,1);
     glVertex3f(0,1,0);
     glVertex3f(0,0,0);

     //glColor3d(0,0,1);
     mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
     glVertex3f(1,0,0);
     glVertex3f(0,0,0);
     glVertex3f(0,1,0);
     glVertex3f(1,1,0);

     //glColor3d(0,0,1);
     mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
     glVertex3f(1,0,0);
     glVertex3f(1,1,0);
     glVertex3f(1,1,1);
     glVertex3f(1,0,1);

     //glColor3d(0,0,1);
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
     glVertex3f(0,0,0);
     glVertex3f(1,0,0);
     glVertex3f(1,0,1);
     glVertex3f(0,0,1);

      //glColor3d(0,0,1);
        mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=1.0;
        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

     glVertex3f(0,1,1);
     glVertex3f(1,1,1);
     glVertex3f(1,1,0);
     glVertex3f(0,1,0);
    glEnd();
}


void cube2()
{
    glBegin(GL_QUADS);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

    //glColor3d(0,0,.7);
    glVertex3f(0,0,1);
     glVertex3f(1,0,1);
     glVertex3f(1,1,1);
     glVertex3f(0,1,1);

     //glColor3d(1,0,1);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
      glVertex3f(0,0,1);
     glVertex3f(0,1,1);
     glVertex3f(0,1,0);
     glVertex3f(0,0,0);

     //glColor3d(0,0,1);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
     glVertex3f(1,0,0);
     glVertex3f(0,0,0);
     glVertex3f(0,1,0);
     glVertex3f(1,1,0);

     //glColor3d(0,0,1);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
     glVertex3f(1,0,0);
     glVertex3f(1,1,0);
     glVertex3f(1,1,1);
     glVertex3f(1,0,1);

     //glColor3d(0,0,1);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
     glVertex3f(0,0,0);
     glVertex3f(1,0,0);
     glVertex3f(1,0,1);
     glVertex3f(0,0,1);

      //glColor3d(0,0,1);
        mat_diffuse[0]=1.0;
        mat_diffuse[1]=1.0;
        mat_diffuse[2]=1.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();

     glVertex3f(0,1,1);
     glVertex3f(1,1,1);
     glVertex3f(1,1,0);
     glVertex3f(0,1,0);
    glEnd();
}

void wall()
{
    glBegin(GL_QUADS);

    //glColor3d(.8,.8,.8);

    glVertex3f(0,0,1);
     glVertex3f(1,0,1);
     glVertex3f(1,1,1);
     glVertex3f(0,1,1);

     //glColor3d(.8,.8,.8);
      mat_diffuse[0]=0.0;
        mat_diffuse[1]=0.0;
        mat_diffuse[2]=0.0;

        mat_specular[0]=0;
        mat_specular[1]=0;
        mat_specular[2]=0;

        material();
      glVertex3f(0,0,1);
     glVertex3f(0,1,1);
     glVertex3f(0,1,0);
     glVertex3f(0,0,0);

     //glColor3d(.8,.8,.8);
     glVertex3f(1,0,0);
     glVertex3f(0,0,0);
     glVertex3f(0,1,0);
     glVertex3f(1,1,0);

     //glColor3d(.8,.8,.8);
     glVertex3f(1,0,0);
     glVertex3f(1,1,0);
     glVertex3f(1,1,1);
     glVertex3f(1,0,1);

     //glColor3d(.8,.8,.8);
     glVertex3f(0,0,0);
     glVertex3f(1,0,0);
     glVertex3f(1,0,1);
     glVertex3f(0,0,1);

      //glColor3d(.8,.8,.8);

     glVertex3f(0,1,1);
     glVertex3f(1,1,1);
     glVertex3f(1,1,0);
     glVertex3f(0,1,0);
    glEnd();

}
void table()
{
    glBegin(GL_QUADS);

    //glColor3d(.2,.2,.2);
    glVertex3f(0,0,1);
     glVertex3f(1,0,1);
     glVertex3f(1,1,1);
     glVertex3f(0,1,1);

     //glColor3d(.2,.2,.2);

      glVertex3f(0,0,1);
     glVertex3f(0,1,1);
     glVertex3f(0,1,0);
     glVertex3f(0,0,0);

     //glColor3d(.2,.2,.2);

     glVertex3f(1,0,0);
     glVertex3f(0,0,0);
     glVertex3f(0,1,0);
     glVertex3f(1,1,0);

     //glColor3d(.2,.2,.2);

     glVertex3f(1,0,0);
     glVertex3f(1,1,0);
     glVertex3f(1,1,1);
     glVertex3f(1,0,1);

     //glColor3d(.2,.2,.2);

     glVertex3f(0,0,0);
     glVertex3f(1,0,0);
     glVertex3f(1,0,1);
     glVertex3f(0,0,1);

      //glColor3d(.2,.2,.2);

     glVertex3f(0,1,1);
     glVertex3f(1,1,1);
     glVertex3f(1,1,0);
     glVertex3f(0,1,0);
    glEnd();

}

void floor()
{
    glBegin(GL_QUADS);

    //glColor3d(0,.5,0);
    glVertex3f(0,0,1);
     glVertex3f(1,0,1);
     glVertex3f(1,1,1);
     glVertex3f(0,1,1);

     //glColor3d(0,.5,0);
      glVertex3f(0,0,1);
     glVertex3f(0,1,1);
     glVertex3f(0,1,0);
     glVertex3f(0,0,0);

     //glColor3d(0,.5,0);
     glVertex3f(1,0,0);
     glVertex3f(0,0,0);
     glVertex3f(0,1,0);
     glVertex3f(1,1,0);

     //glColor3d(0,.5,0);
     glVertex3f(1,0,0);
     glVertex3f(1,1,0);
     glVertex3f(1,1,1);
     glVertex3f(1,0,1);

     //glColor3d(0,.5,0);
     glVertex3f(0,0,0);
     glVertex3f(1,0,0);
     glVertex3f(1,0,1);
     glVertex3f(0,0,1);

      //glColor3d(0,.5,0);

     glVertex3f(0,1,1);
     glVertex3f(1,1,1);
     glVertex3f(1,1,0);
     glVertex3f(0,1,0);
    glEnd();

}

void fan()
{
    float x,y;
    vector<float>xx;
    vector<float>yy;
    for(int i=0; i<=180; i++){
        x= 1*cos(pi *(i)/180);
        xx.push_back(x);
        y= 1*sin(pi*(i)/180);
        yy.push_back(y);
    }

    glBegin(GL_POLYGON);
        //glColor3d(0,0,1);

        for(int i=xx.size()-1; i>=0; i--){
            glVertex3d(xx[i], yy[i], 0);
        }
    glEnd();


    glBegin(GL_POLYGON);
        //glColor3d(0,0,1);

        for(int i=0; i<xx.size(); i++){
            glVertex3d(xx[i], yy[i], 1);
        }

    glEnd();

    glBegin(GL_QUAD_STRIP);

      for(int i=xx.size()-1; i>=0; i--){
        glVertex3d(xx[i],yy[i],0);
        glVertex3d(xx[i],yy[i],1);
      }
      glVertex3d(xx[xx.size()-1],yy[xx.size()-1],0);
      glVertex3d(xx[xx.size()-1],yy[xx.size()-1],1);
    glEnd();
}

static void key(unsigned char key, int x, int y)
{



    switch (key)
    {

        case '0':
            exit(0);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;
        case 'o':
            dx+=5;
            break;
        case 'p':
            dx-=5;
            break;
        case 'k':
            dy+=5;
            break;
        case 'l':
            dy-=5;
            break;
        case 'n':
            dz+=5;
            break;
        case 'm':
            dz-=5;
            break;
        case '[':
            z+=2;
            break;
        case ']':
            z-=2;
            break;

        case '1':
            sx+=.2;
            break;
        case '2':
            sx-=.2;
            break;
        case '3':
            sy+=.2;
            break;
        case '4':
            sy-=.2;
            break;
        case '5':
            sz+=.2;
            break;
        case '6':
            sz-=.2;
            break;


         //own scale
        case 'q':
            scale+=.05;
            break;
        case 'w':
            scale-=.05;
            break;


        //look
        case 'a':
            eye_x-=.5;
            break;
        case 's':
            eye_x+=.5;
            break;

        case 'z':
            eye_y-=.5;
            break;
        case 'x':
            eye_y+=.5;
            break;



        case '7':
            fandy+=500;

            break;

        case '8':
            fandy-=100;
            break;

    ///yaw*****************

    case 'y':
            while( f<=5520)
            {

                i+=pow(2,-8);
                if(i>4)
                {
                    for(;i>-4;)
                    {
                        i-=pow(2,-8);
                        display();
                    }
                }
            f++;
            display();
            }
            i=1;
            f=0;
            break;
        case 'c':
            while(f<=2120)
            {
                j+=pow(2,-10);
                if(j>2)
                {
                    for(;j>-4;)
                    {
                        j-=pow(2,-10);
                        display();
                    }
                }
            f++;
            display();
            }
            j=0;
            f=0;
            break;
        case 'r':
            while(f<=2120)
            {
                p+=pow(2,-10);
                q-=pow(2,-10);
                if(p>1&&q<-1)
                {
                    for(;p>-1&&q<1;)
                    {
                        p-=pow(2,-10);
                        q+=pow(2,-10);
                        display();
                    }
                }
            f++;
            display();
            }
            p=0;
            q=0;
            f=0;
            break;

            ///for light on off************************
        case 'F':
            glDisable(GL_LIGHT0);
            break;
        case 'G':
            glEnable(GL_LIGHT0);
            break;

        case 'H':
            glDisable(GL_LIGHT1);
            break;
        case 'J':
            glEnable(GL_LIGHT1);
            break;


        ///zoom*********************************
        case 'A':
            zom+=.4;
            break;
        case 'S':
            zom-=.4;
            break;

///KOCH DEPTH***************

        case 'N':
            Depth+=1;
             break;
        case 'M':
            Depth-=1;
            break;

///KOCH COLOR***************
        case 'R':
            A+=.1;
             break;
        case 'T':
            A-=.1;
            break;

        case 'V':
            B+=.1;
             break;
        case 'B':
            B-=.1;
            break;

        case 'Z':
            C+=.1;
             break;
        case 'X':
            C-=.1;
            break;










/*


        //Pitch
         case 'c':
             pitch+=5;
             cy=cos(pitch*pi/180)-sin(pitch*pi/180);
             cz=cos(pitch*pi/180)+sin(pitch*pi/180)-30;
             break;

    //yaw
        case 'y':
             pitch+=5;
             cx=5*cos(pitch*pi/180)+5*sin(pitch*pi/180);
             cz=5*cos(pitch*pi/180)-5*sin(pitch*pi/180)-30;
             break;
     //roll
         case 'r':
             roll+=5;
             upx=5*cos(roll*pi/180)-5*sin(roll*pi/180);
             upy=5*cos(roll*pi/180)+5*sin(roll*pi/180);
             //rrrrrrrrrrupz=5*sin(roll*pi/180)-5*cos(roll*pi/180);

*/




    }

    glutPostRedisplay();


}



static void idle(void)
{
    glutPostRedisplay();
}
/*
const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
*/
/* Program entry point */




///texture files************************************************************
void Init()
{
	glEnable(GL_TEXTURE_2D);


    pix[0].makeCheckImage();
	pix[0].setTexture(1);

	pix[1].readBMPFile("F:\\New folder (3)\\graphic_design_project\\download.bmp");
	pix[1].setTexture(2);

	pix[2].readBMPFile("F:\\New folder (3)\\graphic_design_project\\wood.bmp");
	pix[2].setTexture(3);

	pix[3].readBMPFile("F:\\New folder (3)\\graphic_design_project\\heli.bmp");
	pix[3].setTexture(4);

    pix[4].readBMPFile("F:\\New folder (3)\\graphic_design_project\\jack.bmp");
	pix[4].setTexture(5);

	pix[5].readBMPFile("F:\\New folder (3)\\graphic_design_project\\images.bmp");
	pix[5].setTexture(6);

	pix[6].readBMPFile("F:\\New folder (3)\\graphic_design_project\\floor.bmp");
	pix[6].setTexture(7);




}


int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1500,1000);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("GLUT Shapes");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);

    glEnable(GL_NORMALIZE);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);


    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 8.0);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    //glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
    glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 10.0);


    Init();


    cout<<"key instruction:"<<endl;
    cout<<"Rotation: "<<endl;
    cout<<"X-axis: o,p"<<endl;
    cout<<"Y-axis: k,l"<<endl;
    cout<<"Z-axis: m,n"<<endl<<endl;
    cout<<"Scaling: q,w"<<endl<<endl;
    cout<<"Lights:"<<endl;
    cout<<"Light0: F(OFF),G(ON)"<<endl;
    cout<<"Light1: H(OFF),J(ON)"<<endl<<endl;
    cout<<"Koch Curve"<<endl;
    cout<<"Depth: M,N"<<endl;
    cout<<"color: R(red),T(red),V(green),B(green),Z(blue),X(blue)"<<endl<<endl;
    cout<<"LookAt eye position"<<endl;
    cout<<"X-axis: a,s"<<endl;
    cout<<"Y-axis: z,x"<<endl<<endl;
    cout<<"Yaw: y"<<endl;
    cout<<"Role: r"<<endl;
    cout<<"Pitch: c"<<endl<<endl;
    cout<<"Zoom using Aperture: A,S"<<endl<<endl;

    glutMainLoop();
}
