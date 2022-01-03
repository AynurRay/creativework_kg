#include <iostream>
#include <glut.h>
#include<math.h>
#include <stdlib.h>

//#include "stdafx.h"
//#include "stdlib.h"
//#include <GL/glut.h>
//#include <math.h>

double x = 10, y = -15, x1 = 0, yf1 = 0, angle = 0;

double x_ob = 0, y_ob = 0, x_ob1 = -35, y_ob1 = 0;

double x_sun = 0, y_sun = 0, x_sun1 = 0, y_sun1 = 0; 

int R = 1, W = 1080, H = 1080;

void myReshape(int W, int H)
{
    if (R > W / H) glViewport(0, 0, W, W / R);
    else glViewport(0, 0, H * R, H);
}
  
void SAMOLET(GLdouble an, GLdouble x, GLdouble y, GLdouble z);
void OBLAKA(GLdouble an, GLdouble x, GLdouble y, GLdouble z);
void SUN(GLdouble an, GLdouble x, GLdouble y, GLdouble z);

void init(void)
{    
    GLfloat light_position[] = { 20.0, 20.0, 20.0, 1 };
    GLfloat white_light[] = { 0.125, 0.5, 0.0, 1 };
    GLfloat ambient_light[] = { 1.0, 1.0, 1.0, 1 };
    GLfloat specular_light[] = { 0.125, 0.5, 0.0, 1 };  

    glClearColor(0, 0.80, 0.90, 0); //Задний фон

    glShadeModel(GL_SMOOTH);//Сглаживание включено

    /* устанавливаем параметры источника света */
    glLightfv(GL_LIGHT0, GL_POSITION, light_position); //
    glLightfv(GL_LIGHT0, GL_DIFFUSE, white_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    
    /* включаем освещение и источник света */
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    /* включаем z-буфер */
    glEnable(GL_DEPTH_TEST);//Тест глубины включен

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(-20, 20, -20, 20, -20, 20);

    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_LIGHTING);
    
    gluLookAt(-100, -100, 100, 0, 0, 0, 10, 10, -10);
    glLoadIdentity();
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, W, H);

    //ОБЛАКА
    x_ob = x_ob1;
    y_ob = y_ob1;
    x_ob1 += 0.003; y_ob1 += 0.003;

    if (x_ob < 40)//проверка границ движения
    {    
        glPushMatrix();
        glTranslated(x_ob, 0, 1);
        glRotated(0, x_ob, 30, 30);
        glScaled(0.1, 0.1, 0.1);
        OBLAKA(0, 0, 0, 0);
        glPopMatrix();
    
    }

    else x_ob1 = -35; //переход в начальное положение

    //СОЛНЦЕ
    x_sun = x_sun1;
    x_sun1 -= 0.0005;
    y_sun1 -= 0.0005;

    glPushMatrix();
    glTranslated(x_sun, sin(x_sun1), 0);
    glRotated(0, x_sun, sin(x_sun1), 0);
    glScaled(0.1, 0.1, 0.1);
    SUN(0, 0, 0, 0);
    glPopMatrix();

    //САМОЛЕТ
    x = 2 * cos(x1);
    y = 2 * sin(yf1);
    x1 += 0.0005; yf1 += 0.0005; angle += 0.005;

    glPushMatrix();
    glTranslated(5*x, 5 * y, 0);
    glRotated(45 + angle, x, y, 1);
    glScaled(0.06, 0.06, 0.06);
    SAMOLET(35, 0, 0, 0);
    glPopMatrix();

    //ЗЕМЛЯ
    glPushMatrix();
    glColor3ub(30, 170, 50);
    glRectf(-W, -25, W, -15);
    glPopMatrix();

    //ГОРЫ
    //#1
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(0, 0, -10);
    glVertex3f(4.1675, -5, -10);
    glVertex3f(-4.1675, -5, -10);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-2, -6.5, -10);
    glVertex3f(3, -5, -10);
    glVertex3f(-4.1675, -5, -10);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(2.5, -6.2, -10);
    glVertex3f(-1, -5, -10);
    glVertex3f(4.1675, -5, -10);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.1, 0.2, 0.4);
    glVertex3f(0, 0, -10);
    glVertex3f(25, -30, -20);
    glVertex3f(-25, -30, -20);
    glEnd();

    //#2
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-4, -8, -10);
    glVertex3f(-2.825, -10, -5);
    glVertex3f(-5.325, -10, -5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(-4.5, -11, -10);
    glVertex3f(-2.825, -10, -5);
    glVertex3f(-5.325, -10, -5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2, 0.3, 0.4);
    glVertex3f(-4, -8, -10);
    glVertex3f(15, -40, -20);
    glVertex3f(-25, -40, -20);
    glEnd();

    //#3
    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f( 4, -6, -10);
    glVertex3f( 2.425, -8, -5);
    glVertex3f( 5.625, -8, -5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 1.0);
    glVertex3f(5, -8.8, -10);
    glVertex3f(2.425, -8, -5);
    glVertex3f(5.625, -8, -5);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.2, 0.5, 0.7);
    glVertex3f( 4, -6, -10);
    glVertex3f( -22, -38, -20);
    glVertex3f( 30, -38, -20);
    glEnd();


    //ДЕРЕВЬЯ
    //#1
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(14, -10, 0);
    glVertex3f(15, -8, 0);
    glVertex3f(16, -10, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(13, -11, 0);
    glVertex3f(15, -9, 0);
    glVertex3f(17, -11, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(13, -12, 0);
    glVertex3f(15, -10, 0);
    glVertex3f(17, -12, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(13, -13, 0);
    glVertex3f(15, -11, 0);
    glVertex3f(17, -13, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(13, -14, 0);
    glVertex3f(15, -12, 0);
    glVertex3f(17, -14, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.6, 0.4, 0.12);
    glVertex3f(14.5, -14, 0);
    glVertex3f(15.5, -14, 0);
    glVertex3f(15.5, -19, 0);
    glVertex3f(14.5, -19, 0);
    glEnd();

    //#2
    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(-14, -10, 0);
    glVertex3f(-15, -8, 0);
    glVertex3f(-16, -10, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(-13, -11, 0);
    glVertex3f(-15, -9, 0);
    glVertex3f(-17, -11, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(-13, -12, 0);
    glVertex3f(-15, -10, 0);
    glVertex3f(-17, -12, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(-13, -13, 0);
    glVertex3f(-15, -11, 0);
    glVertex3f(-17, -13, 0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f(0.0, 0.470, 0.1);
    glVertex3f(-13, -14, 0);
    glVertex3f(-15, -12, 0);
    glVertex3f(-17, -14, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.6, 0.4, 0.12);
    glVertex3f(-14.5, -14, 0);
    glVertex3f(-15.5, -14, 0);
    glVertex3f(-15.5, -19, 0);
    glVertex3f(-14.5, -19, 0);  
    glEnd();

    glutSwapBuffers();
    glutPostRedisplay();
}
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(W, H);
    glutCreateWindow("Творческая работа");
    init();
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}

void SAMOLET(GLdouble an, GLdouble x, GLdouble y, GLdouble z)
{
    glPushMatrix();
    glRotated(an, x, y, z);

    //КОРПУС
    glPushMatrix();
    glColor3f(0.125, 0.5, 0);
    glScalef(3.0, 0.7, 0.7);
    glutSolidSphere(22, 50, 25);
    glPopMatrix();

    //КАБИНА
    glPushMatrix();
    glColor3f(0.0, 0.5, 0.8);
    glTranslatef(0, 0, 10);
    glScalef(0.9, 0.6, 0.8);
    glutSolidSphere(17, 50, 25);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    
    //КРЫЛЬЯ
    glBegin(GL_QUADS);   
    glColor3f(0.125, 0.5, 0);
    glVertex3f(5, -60, 0);
    glVertex3f(5, 0, 0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-10, -60, 0);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.125, 0.5, 0);
    glVertex3f(5, 60, 0);
    glVertex3f(5, 0, 0);
    glVertex3f(-30, 0, 0);
    glVertex3f(-10, 60, 0);
    glEnd();
     
    //ХВОСТ 
    glBegin(GL_POLYGON);
    glColor3f(0.125, 0.5, 0);
    glVertex3f(70, -25, 0);
    glVertex3f(50, 0, 0);
    glVertex3f(70, 25, 0);
    glVertex3f(80, 25, 0);
    glVertex3f(80, -25, 0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(0.125, 0.5, 0);
    glVertex3f(80, 0, 30);
    glVertex3f(70, 0, 30);
    glVertex3f(40, 0, 0);
    glVertex3f(80, 0, 0);
    glEnd();

    glEnable(GL_LIGHTING);
    glPopMatrix();
}

void OBLAKA(GLdouble an, GLdouble x, GLdouble y, GLdouble z)
{
    glPushMatrix();
    glRotated(an, x, y, z);

    //#1
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(120, 150, 10);
    glScalef(0.9, 0.4, 0.6);
    glutSolidSphere(50, 50, 25);
    glPopMatrix();

    //#2
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(50, 80, 10);
    glScalef(0.6, 0.4, 0.8);
    glutSolidSphere(50, 50, 25);
    glPopMatrix();

    //#3
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-40, 100, 10);
    glScalef(0.7, 0.5, 0.7);
    glutSolidSphere(20, 45, 25);
    glPopMatrix();

    //#4
    glPushMatrix();
    glColor3f(1, 1, 1);
    glTranslatef(-100, 130, 10);
    glScalef(0.9, 0.4, 0.8);
    glutSolidSphere(50, 50, 25);
    glPopMatrix();

    glPopMatrix();
}

void SUN(GLdouble an, GLdouble x, GLdouble y, GLdouble z)
{
    glPushMatrix();
    glRotated(an, x, y, z);

    glPushMatrix();
    glColor3f(1, 1, 0);
    glTranslatef(160, 155, 0);
    glScalef(0.5, 0.5, 0.5);
    glutSolidSphere(50, 50, 50);
    glPopMatrix();

    glPopMatrix();
}
