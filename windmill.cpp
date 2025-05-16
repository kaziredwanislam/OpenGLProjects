#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<random>

#include<GL/glut.h>

float eyex=4.0f,eyey=4.0f,eyez=4.0f; //Camera Position Coordinates
float centerx=0,centery=0,centerz=0;  //Look at point Coordinates
float upx=0,upy=1,upz=0;  //up vector coordinates
bool isAxes=true;
float angle=0.0f;
float speed=0.2f;
/*bool isCube=true;
bool isMove=false;
float cubeLowx=-0.75f,cubeLowy=-0.9f,cubeLowz=-0.9f;
float cubeUpx=0.9f,cubeUpy=0.9f,cubeUpz=0.95f;
float ballx=0.5f,bally=-0.8f,ballz=-0.3f;
float radius=0.06;
float Vx=0.02f,Vy=0.002f,Vz=0.01f;
int timeInterval=16;
float g=-0.00098;
float restitution=0.8f;
float spin=2;
float spinAxisX=Vy*upz-Vz*upy;
float spinAxisY=Vz*upx-Vx*upz;
float spinAxisZ=Vx*upy-Vy*upx;*/

//function declaration
void initGL();
void display();
void drawAxes();
void reshapeListener(GLsizei width, GLsizei height);
//void specialKeyListener(int key, int x, int y);
//void keyboardListener(unsigned char key, int x, int y);
float radianAngle(float degreeAngle);
//void drawCube();
//void drawSphere(float radius, int slices, int stacks);
void drawSquare(float x,float y,float z,float arm,int color);
//void drawVelocityDirectionLine();
//float getRandomFloat(float min,float max);
//float max(int num1,int num2);
//float min(int num1,int num2);

float max(int num1,int num2)
{
    if(num1>=num2)return num1;
    return num2;
}

float min(int num1,int num2)
{
    if(num1<=num2)return num1;
    return num2;
}

float getRandomFloat(float min,float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<float>dist(min,max);
    return dist(gen);
}

void drawSquare(float x,float y,float z,float arm,int color)
{
    switch(color)
    {
        case 1:glColor3f(1,1,1);
                break;
        case 0:glColor3f(0,0,0);
                break;
    }

    glBegin(GL_QUADS);
    {
        glVertex3f(x,y,z);
        glVertex3f(x+arm,y,z);
        glVertex3f(x+arm,y,z+arm);
        glVertex3f(x,y,z+arm);
    }glEnd();
}

void drawTriangle(float x1,float y1,float z1,float x2,float y2,float z2,float x3,float y3,float z3)
{
    glColor3f(1,1,1);
    glBegin(GL_TRIANGLES);
    {
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
        glVertex3f(x3,y3,z3);
    }glEnd();
}


void drawSquareInColumns(float x,float y,float z,float arm,int color)
{
    for(int i=0;i<20;i++)
    {
        drawSquare(x,y,z,arm,color);
        z+=arm;
        color=1-color;
    }
}

void drawHandle()
{
    glBegin(GL_QUADS);{
        //top face
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.3f, 1.1f, 0.0f);
        glVertex3f(-1.3f, 1.1f, 0.0f);
        glVertex3f(-1.3f, 1.1f, -0.3f);
        glVertex3f(1.3f, 1.1f, -0.3f);
        
    
        // Front face  
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.3f, 1.1f, 0.0f);
        glVertex3f(-1.3f, 1.1f, 0.0f);
        glVertex3f(-1.3f, 1.0f, 0.0f);
        glVertex3f(1.3f, 1.0f, 0.0f);
    
    
        //Right face 
        glColor3f(1.0f, 0.0f, 0.0f);
        glVertex3f(1.3f, 1.1f, 0.0f);
        glVertex3f(1.3f, 1.1f, -0.3f);
        glVertex3f(1.3f, 1.0f, -0.3f);
        glVertex3f(1.3f, 1.0f, 0.0f);
        }
        glEnd();

}

void drawCube()
{
    glBegin(GL_QUADS);{
    // Front face  
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, -2.0f, 1.0f);
    glVertex3f(1.0f, -2.0f, 1.0f);

    // Back face 
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, -2.0f, -1.0f);
    glVertex3f(-1.0f, -2.0f, -1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);

    // Left face 
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, 2.0f, 1.0f);
    glVertex3f(-1.0f, 2.0f, -1.0f);
    glVertex3f(-1.0f, -2.0f, -1.0f);
    glVertex3f(-1.0f, -2.0f, 1.0f);

    // Right face 
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 2.0f, -1.0f);
    glVertex3f(1.0f, 2.0f, 1.0f);
    glVertex3f(1.0f, -2.0f, 1.0f);
    glVertex3f(1.0f, -2.0f, -1.0f);
    }
    glEnd();
}


void initGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_TEST);
}


void reshapeListener(GLsizei width, GLsizei height)
{
    if(height==0)height=1;

    GLfloat aspect=(GLfloat)width/(GLfloat)height;

    glViewport(0,0,width,height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, aspect, 0.01f, 100.0f);
}

void display()
{
    //clear color and depth buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //set up the model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //position camera
    gluLookAt(
        eyex,eyey,eyez,     //Camera Position
        centerx,centery,centerz,  //Look at Point
        upx,upy,upz          // Up Vector
    );

    if(isAxes)
    {
        drawAxes();
    }

    drawCube();
    drawHandle();
    glPushMatrix();
    {
        float r=1.7f;
        drawTriangle(1.3,1.1,0.0, 1.3,1.1+r*sinf(radianAngle(angle)),0.0+r*cosf(radianAngle(angle)),1.3,1.1+r*sinf(radianAngle(angle+20)),0.0+r*cosf(radianAngle(angle+20)));
        drawTriangle(1.3,1.1,0.0, 1.3,1.1+r*sinf(radianAngle(angle+100)),0.0+r*cosf(radianAngle(angle+100)),1.3,1.1+r*sinf(radianAngle(angle+120)),0.0+r*cosf(radianAngle(angle+120)));
        drawTriangle(1.3,1.1,0.0, 1.3,1.1+r*sinf(radianAngle(angle+220)),0.0+r*cosf(radianAngle(angle+220)),1.3,1.1+r*sinf(radianAngle(angle+240)),0.0+r*cosf(radianAngle(angle+240)));
    }glPopMatrix();
    glutSwapBuffers();
}



void keyboardListener(unsigned char key, int x, int y)
{
   switch(key)
   {
    case('w'):
    {
        speed+=0.1f;
        break;
    }
    case('s'):
    {
        speed-=0.1f;
        break;
    }
   }
   glutPostRedisplay();
}

void specialKeyListener(int key, int x, int y)
{
    double v=0.04; //Movement Increment
    switch(key)
    {
        // --- Camera Position Controls (eye coordinates) ---
        case GLUT_KEY_UP:
        {
            float dirx = centerx - eyex;
            float diry = centery - eyey;
            float dirz = centerz - eyez;
            eyex=eyex+v*dirx;
            eyey=eyey+v*diry;
            eyez=eyez+v*dirz;
            centerx=centerx+v*dirx;
            centery=centery+v*diry;
            centerz=centerz+v*dirz;
            break;
        }
        case GLUT_KEY_DOWN:
        {
            float dirx = centerx - eyex;
            float diry = centery - eyey;
            float dirz = centerz - eyez;
            eyex=eyex-v*(centerx-eyex);
            eyey=eyey-v*(centery-eyey);
            eyez=eyez-v*(centerz-eyez);
            centerx=centerx-v*dirx;
            centery=centery-v*diry;
            centerz=centerz-v*dirz;
            break;
        }
            
        case GLUT_KEY_LEFT: {
            float sidex=upy*(centerz-eyez)-upz*(centery-eyey);
            float sidey=-(upx*(centerz-eyez)-upz*(centerx-upx));
            float sidez=upx*(centery-eyey)-upy*(centerx-eyex);
            eyex=eyex+v*sidex;
            eyey=eyey+v*sidey;
            eyez=eyez+v*sidez;
            centerx=centerx+v*sidex;
            centery=centery+v*sidey;
            centerz=centerz+v*sidez;
            break;
        }
        case GLUT_KEY_RIGHT:{
            float sidex=upy*(centerz-eyez)-upz*(centery-eyey);
            float sidey=-(upx*(centerz-eyez)-upz*(centerx-upx));
            float sidez=upx*(centery-eyey)-upy*(centerx-eyex);
            eyex=eyex-v*sidex;
            eyey=eyey-v*sidey;
            eyez=eyez-v*sidez;
            centerx=centerx-v*sidex;
            centery=centery-v*sidey;
            centerz=centerz-v*sidez;
            break;
        }
            
        case GLUT_KEY_PAGE_DOWN:
            eyex=eyex-v*upx;
            eyey=eyey-v*upy;
            eyez=eyez-v*upz;
            centerx=centerx-v*upx;
            centery=centery-v*upy;
            centerz=centerz-v*upz;
            break;
        case GLUT_KEY_PAGE_UP:
            eyex=eyex+v*upx;
            eyey=eyey+v*upy;
            eyez=eyez+v*upz;
            centerx=centerx+v*upx;
            centery=centery+v*upy;
            centerz=centerz+v*upz;
            break; 
    }
    glutPostRedisplay();
}

float radianAngle(float degreeAngle)
{
    return (3.1416*degreeAngle)/180;
}


void drawAxes()
{
    glLineWidth(1); //set Line Thickness
    //printf("Drawing axes\n");
    glBegin(GL_LINES);
    {
        //X axis (white)
        glColor3f(1,1,1);
        glVertex3f(-10,0,0);
        glVertex3f(10,0,0);

        //Y axis (white)
        glColor3f(1,1,1);
        glVertex3f(0,-10,0);
        glVertex3f(0,10,0);

        //Z axis(white)
        glColor3f(1,1,1);
        glVertex3f(0,0,-10);
        glVertex3f(0,0,10);
    }
    glEnd();
}

void timerFunc(int value)
{
   angle+=speed;
   if(angle>360)angle=0;
   glutPostRedisplay();
   glutTimerFunc(16,timerFunc,0);
}

int main(int argc, char **argv)
{
    //Initialize Glut
    glutInit(&argc,argv);

    //configure display mode and window
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(50,50);
    glutCreateWindow("OpenGL 3d drawing");

    //Register callback function
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeListener);
    glutKeyboardFunc(keyboardListener);
    glutSpecialFunc(specialKeyListener);

    glutTimerFunc(16,timerFunc,0);

    //Initialize OpenGL settings
    initGL();

    //Enter the GLUT event Loop
    glutMainLoop();

    return 0;
}