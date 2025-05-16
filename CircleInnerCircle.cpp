#ifdef __linux__
#include <GL/glut.h> // For Linux systems
#elif defined(_WIN32) || defined(WIN32)
#include <windows.h>
#include <GL/glut.h> // For Windows systems
#elif defined(__APPLE__)
#include <GLUT/glut.h> // For macOS systems
#else
#include <GL/glut.h> // Default fallback
#endif

#include <cstdio>
#include <cmath>

float angleOfBig=0;
float angleOfSmall=0;
float timeInterval=16;
//Min eq: y=3.5x

void init()
{
    glClearColor(0.0f,0.0f, 0.2f,1.0f);
    glMatrixMode(GL_PROJECTION);
    //glEnable(GL_DEPTH_TEST);
    glLoadIdentity();
    gluPerspective(80,	1,	1,	1000.0);
    //glOrtho(-100, 100, -100, 100, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    gluLookAt(0,0,50 ,0,0,0, 0,1,0);
}

void reshape(int width, int height)
{
    // Prevent division by zero
    if (height == 0)
        height = 1;

    // Set the viewport to the entire window
    glViewport(0, 0, width, height);

    // Set the projection matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // Set perspective projection
    float aspectRatio=(float)width/(float)height;
    gluPerspective(80, aspectRatio, 1,1000);

    // Switch back to modelview matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    printf("Window resized to %d x %d\n", width, height);
}

void drawPoint(float x,float y,char color)
{
    switch(color)
    {
        case 'r':glColor3f(1,0,0);
                break;
        case 'g':glColor3f(0,1,0);
                break;
        case 'b':glColor3f(0,0,1);
                break;
        case 'y':glColor3f(1,1,0);
                break;
        default:glColor3f(1,1,1);
    }

    glBegin(GL_POINTS);
    {
        glVertex3f(x,y,0);
    }glEnd();
}

void drawLine(float x1,float y1,float x2,float y2,char color)
{
    switch(color)
    {
        case 'r':glColor3f(1,0,0);
                break;
        case 'g':glColor3f(0,1,0);
                break;
        case 'b':glColor3f(0,0,1);
                break;
        case 'y':glColor3f(1,1,0);
                break;
        default:glColor3f(1,1,1);
    }
    
    //printf("%c",color);
    glBegin(GL_LINES);
    {
        glVertex3f(x1,y1,0);
        glVertex3f(x2,y2,0);
    }glEnd();
}

void drawSquare(float x1,float y1,float radius,char color)
{
    switch(color)
    {
        case 'r':glColor4f(1,0,0,0);
                break;
        case 'g':glColor4f(0,1,0,0);
                break;
        case 'b':glColor4f(0,0,1,0);
                break;
        case 'y':glColor4f(1,1,0,0);
                break;
        default:glColor4f(1,1,1,0);
    }

    x1-=radius/2;
    y1-=radius/2;
    glBegin(GL_QUADS);
    {
        glVertex3f(x1,y1,0);
        glVertex3f(x1+radius,y1,0);
        glVertex3f(x1+radius,y1+radius,0);
        glVertex3f(x1,y1+radius,0);
    }glEnd();
}

void drawCircle(float centerX,float centerY,float radius,int segments,char color)
{
    switch(color)
    {
        case 'g':glColor3f(0,1,0);
                break;
        case 'r':glColor3f(1,0,0);
                break;
        case 'b':glColor3f(0,0,1);
                break;
        default:
            glColor3f(1,1,1);
    }
    glBegin(GL_LINE_LOOP);{
        for(int i=0;i<segments;i++)
        {
            float theta=2.0f*3.1415926f *float(i)/float(segments);
            float x=radius*cosf(theta);
            float y=radius*sinf(theta);
            glVertex3f(centerX+x,centerY+y,0);
        }
   
    }     glEnd();
}


void display()
{
    //Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Reset Transformation
    glLoadIdentity();

    gluLookAt(0,0,200, 0,0,0, 0,1,0);
    drawCircle(0,0,50,200,'w');
    glPushMatrix();
    {
        glRotatef(angleOfBig,0,0,1);
        drawLine(0,0,50,0,'r');
    }glPopMatrix();

    glPushMatrix();
    {
        glRotatef(angleOfBig,0,0,1);
        drawCircle(50,0,20,200,'r');
        glTranslatef(50,0,0);
        glRotatef(angleOfSmall,0,0,1);
        drawLine(0,0,10,0,'g');
        drawCircle(20,0,5,200,'w');
    }glPopMatrix();

    /*glPushMatrix();
    {
        glTranslatef(50,0,0);
        glRotatef(angleOfBig,0,0,1);
        glRotatef(angleOfSmall,0,0,1);
        drawLine(0,0,10,0,'g');
    }glPopMatrix();*/

    /*glPushMatrix();
    {
        glRotatef(angleOfBig,0,0,1);
        drawCircle(50,0,20,200,'g');
        glTranslatef(50,0,0);
        glRotatef(angleOfSmall,0,0,1);
        drawLine(0,0,20,0,'y');
        drawCircle(20,0,5,200,'w');
    }glPopMatrix();*/
    glutSwapBuffers();
}

void timerFunc(int value)
{
    angleOfBig-=0.1f;
    if(angleOfBig<-360)angleOfBig=0;
    glutPostRedisplay();
    glutTimerFunc(timeInterval,timerFunc,0);
}

void timerFuncforSmall(int value)
{
    angleOfSmall+=0.5f;
    if(angleOfSmall>360)angleOfSmall=0;
    glutPostRedisplay();
    glutTimerFunc(timeInterval/10,timerFuncforSmall,0);
    //printf("%f",angleOfSmall);
}


int main(int argc,char** argv)
{
    //Initialize glut
    glutInit(&argc,argv);

    //set the window size nd position
    glutInitWindowSize(800,800);
    //glutInitWindowPosition(100,100);

    //set display mode:RGB coloring, Double Buffering, Depth Buffering
    glutInitDisplayMode(GLUT_RGB| GLUT_DOUBLE| GLUT_DEPTH);
    
    //create a window with a title
    glutCreateWindow("Analog Clock");

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);            // Called when window is resized
    
    glutTimerFunc(angleOfBig,timerFunc,0);
    glutTimerFunc(angleOfSmall,timerFuncforSmall,0);
    init();

    //Start the glut Main Loop
    glutMainLoop();

    return 0;
}