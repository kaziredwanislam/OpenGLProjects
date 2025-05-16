#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<random>

#include<GL/glut.h>

float eyex=4.0f,eyey=4.0f,eyez=4.0f; //Camera Position Coordinates
float centerx=0,centery=0,centerz=0;  //Look at point Coordinates
float upx=0,upy=1,upz=0;  //up vector coordinates
float angle=0.0f;
bool isAxes=true;
bool isCube=false;
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
float spinAxisZ=Vx*upy-Vy*upx;

//function declaration
void initGL();
void display();
void drawAxes();
void reshapeListener(GLsizei width, GLsizei height);
void specialKeyListener(int key, int x, int y);
void keyboardListener(unsigned char key, int x, int y);
void drawCircle(float centerX,float centerY,float radius,int segments,char color);
void drawLine(float x1,float y1,float z1,float x2,float y2,float z2,char color);
float radianAngle(float degreeAngle);
void drawCube();
void drawSphere(float radius, int slices, int stacks);
void drawSquare(float x,float y,float z,float arm,int color);
void drawVelocityDirectionLine();
float getRandomFloat(float min,float max);
float max(int num1,int num2);
float min(int num1,int num2);

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


void drawLine(float x1,float y1,float z1,float x2,float y2,float z2,char color)
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
        glVertex3f(x1,y1,z1);
        glVertex3f(x2,y2,z2);
    }glEnd();
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


void drawSquareInColumns(float x,float y,float z,float arm,int color)
{
    for(int i=0;i<20;i++)
    {
        drawSquare(x,y,z,arm,color);
        z+=arm;
        color=1-color;
    }
}


void drawCube()
{
    glBegin(GL_QUADS);{
    // Top face (y = 1.0f) - Green
    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);

    // Bottom face (y = -1.0f) - Orange
    
    //glColor3f(0.0f,1.0f,1.0f);
    //glVertex3f(1.0f, -1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, 1.0f);
    //glVertex3f(-1.0f, -1.0f, -1.0f);
    //glVertex3f(1.0f, -1.0f, -1.0f);
    
    

    // Front face  (z = 1.0f) - Red
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);

    // Back face (z = -1.0f) - Yellow
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);

    // Left face (x = -1.0f) - Blue
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);

    // Right face (x = 1.0f) - Magenta
    glColor3f(1.0f, 0.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    }
    glEnd();

    int color=0;
    for(int j=0;j<20;j++)
    {
        drawSquareInColumns(-1.0f+j*0.1,-1.0f,-1.0f,0.1f,color);
        color=1-color;
    }
}

void drawVelocityDirectionLine()
{
    float length=sqrt(Vx*Vx+Vy*Vy+Vz*Vz);
    if(isMove)
    {
        float scale=0.3f;
        float dx=scale*Vx/length;
        float dy=scale*Vy/length;
        float dz=scale*Vz/length;
        glLineWidth(2.0f);
        glColor3f(0.0f,1.0f,0.0f);
        glBegin(GL_LINES);
        {
            glVertex3f(ballx,bally,ballz);
            glVertex3f(ballx+dx,bally+dy,ballz+dz);
        }
        glEnd();
    }
}

void drawCircle(float centerX,float centerz,float radius,int segments,char color)
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
            float z=radius*sinf(theta);
            glVertex3f(centerX+x,0,centerz+z);
        }
        glEnd();
    }
}



void drawSphere(float radius, int slices, int stacks)
{
    for(int i=0;i<stacks;i++) {
        float lat0=M_PI*(-0.5+(float)i/stacks);
        float z0=radius*sin(lat0);
        float zr0=radius*cos(lat0);

        float lat1=M_PI*(-0.5+(float)(i + 1)/ stacks);
        float z1=radius*sin(lat1);
        float zr1=radius*cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for (int j=0;j<=slices;++j) {
            float lng=2 * M_PI*(float)(j%slices)/slices;
            float x=cos(lng);
            float y=sin(lng);

            if (j%2==0)
                glColor3f(1, 0, 0);
            else
                glColor3f(0, 1, 0);

            glVertex3f(x*zr0, y*zr0, z0);
            glVertex3f(x*zr1, y*zr1, z1);
        }
        glEnd();
    }
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

    if(isCube)
    {
        
        drawCube();
      
    }
    drawCircle(0,0,1,500,'r');

    glPushMatrix();
    {
        float radius=1.0f;
        drawSquare(radius*cosf(radianAngle(angle)),-0.5f,radius*sinf(radianAngle(angle)),0.2f,1);
        drawSquare(radius*cosf(radianAngle(angle+60)),-0.5f,radius*sinf(radianAngle(angle+60)),0.2f,1);
        drawSquare(radius*cosf(radianAngle(angle+120)),-0.5f,radius*sinf(radianAngle(angle+120)),0.2f,1);
        drawSquare(radius*cosf(radianAngle(angle+180)),-0.5f,radius*sinf(radianAngle(angle+180)),0.2f,1);
        drawSquare(radius*cosf(radianAngle(angle+240)),-0.5f,radius*sinf(radianAngle(angle+240)),0.2f,1);
        drawSquare(radius*cosf(radianAngle(angle+300)),-0.5f,radius*sinf(radianAngle(angle+300)),0.2f,1);
        drawLine(radius*cosf(radianAngle(angle)),-0.5f,radius*sinf(radianAngle(angle)),radius*cosf(radianAngle(angle)),0.0f,radius*sinf(radianAngle(angle)),'g');
        drawLine(radius*cosf(radianAngle(angle+60)),-0.5f,radius*sinf(radianAngle(angle+60)),radius*cosf(radianAngle(angle+60)),0.0f,radius*sinf(radianAngle(angle+60)),'g');
        drawLine(radius*cosf(radianAngle(angle+120)),-0.5f,radius*sinf(radianAngle(angle+120)),radius*cosf(radianAngle(angle+120)),0.0f,radius*sinf(radianAngle(angle+120)),'g');
        drawLine(radius*cosf(radianAngle(angle+180)),-0.5f,radius*sinf(radianAngle(angle+180)),radius*cosf(radianAngle(angle+180)),0.0f,radius*sinf(radianAngle(angle+180)),'g');
        drawLine(radius*cosf(radianAngle(angle+240)),-0.5f,radius*sinf(radianAngle(angle+240)),radius*cosf(radianAngle(angle+240)),0.0f,radius*sinf(radianAngle(angle+240)),'g');
        drawLine(radius*cosf(radianAngle(angle+300)),-0.5f,radius*sinf(radianAngle(angle+300)),radius*cosf(radianAngle(angle+300)),0.0f,radius*sinf(radianAngle(angle+300)),'g');
    }glPopMatrix();

    /*glPushMatrix();
    glTranslatef(ballx,bally,ballz);
    float speed=sqrt(Vx*Vx+Vy*Vy+Vz*Vz);
    if(speed>0.0001)
    {
        glRotatef(spin, spinAxisX, spinAxisY, spinAxisZ);
    }
    //glRotatef(spin,0,1,0);
    drawSphere(radius,20,20);
    glPopMatrix();

    glPushMatrix();
    drawVelocityDirectionLine();
    glPopMatrix();*/
    glutSwapBuffers();
}



void keyboardListener(unsigned char key, int x, int y)
{
   float v=6; //increase angle in degree
    float radangle1,radangle2,radangle3;
    float tempx,tempz,tempy;
    switch(key)
    {
        case '1':
        {
            float angle=radianAngle(-5.0f);
            float dx=centerx-eyex;
            float dz=centerz-eyez;
            float new_dx=dx*cos(angle)-dz*sin(angle);
            float new_dz=dx*sin(angle)+dz*cos(angle);
            centerx=eyex+new_dx;
            centerz=eyez+new_dz;
            break;
        }

        case '2':
        {
            float angle=radianAngle(5.0f);
            float dx=centerx-eyex;
            float dz=centerz-eyez;
            float new_dx=dx*cos(angle)-dz*sin(angle);
            float new_dz=dx*sin(angle)+dz*cos(angle);
            centerx=eyex+new_dx;
            centerz=eyez+new_dz;
            break;    
        }
        
        case '3':                                 //like rotate around x axis
        {
            float angle=radianAngle(5.0f);
            float dy=centery-eyey;
            float dz=centerz-eyez;
            float new_dy=dy*cos(angle)-dz*sin(angle);
            float new_dz=dy*sin(angle)+dz*cos(angle);
            centery=eyey+new_dy;
            centerz=eyez+new_dz;
            break;    
        }

        case '4':
        {
            float angle=radianAngle(-5.0f);
            float dy=centery-eyey;
            float dz=centerz-eyez;
            float new_dy=dy*cos(angle)-dz*sin(angle);
            float new_dz=dy*sin(angle)+dz*cos(angle);
            centery=eyey+new_dy;
            centerz=eyez+new_dz;
            break;  
        }
        case '5':
        {
            float lx=centerx-eyex;
            float ly=centery-eyey;
            float lz=centerz-eyez;
            float len=sqrt(lx*lx+ly*ly+lz*lz);
            lx/=len;
            ly/=len;
            lz/=len;
            float new_upx=ly*upz-upy*lz;
            float new_upy=-(lx*upz-lz*upx);
            float new_upz=lx*upy-ly*upx;
            upx+=0.05*new_upx;
            upy+=0.05*new_upy;
            upz+=0.05*new_upz;
            float uplen=sqrt(upy*upy+upx*upx+upz*upz);
            upx/=uplen;
            upy/=uplen;
            upz/=uplen;
            break;
        }

        
        case '6':
        {
            float lx=centerx-eyex;
            float ly=centery-eyey;
            float lz=centerz-eyez;
            float len=sqrt(lx*lx+ly*ly+lz*lz);
            lx/=len;
            ly/=len;
            lz/=len;
            float new_upx=ly*upz-upy*lz;
            float new_upy=-lx*upz-lz*upx;
            float new_upz=lx*upy-ly*upx;
            upx-=0.05*new_upx;
            upy-=0.05*new_upy;
            upz-=0.05*new_upz;
            float uplen=sqrt(upy*upy+upx*upx+upz*upz);
            upx/=uplen;
            upy/=uplen;
            upz/=uplen;
            break;
        }

        case 'w':
        {
            float step=0.1f;
            eyex+=step;
            eyey+=step;
            eyez+=step;
            break;
        }

        case 's':
        {
            float step=0.1f;
            eyex-=step;
            eyey-=step;
            eyez-=step;
            break;
        }

        case ' ':
        {
            isMove=!isMove;
            if(isMove)
            {
                Vx+=0.004f;
                Vy+=0.005f;
                Vz+=0.008f;
            }
            
            break;
        }

        case 'r':
        {
            ballx=getRandomFloat(-0.6,0.6);
            bally=getRandomFloat(-0.6,0.6);
            ballz=getRandomFloat(-0.6,0.6);

            Vx=getRandomFloat(-0.09,0.07);
            Vy=getRandomFloat(0.09,0.15);
            Vz=getRandomFloat(-0.09,0.07);
            isMove=true;
            break;
        }

        case '+':
        {
            float dvx=getRandomFloat(0.01,0.09);
            float dvy=getRandomFloat(0.01,0.09);
            float dvz=getRandomFloat(0.01,0.09);
            if(Vx>0)Vx+=dvx;
            if(Vy>0)Vy+=dvy;
            if(Vz>0)Vz+=dvz;
            break;
        }

        case '-':
        {
            float dvx=getRandomFloat(0.01,0.09);
            float dvy=getRandomFloat(0.01,0.09);
            float dvz=getRandomFloat(0.01,0.09);
            if(Vx>0)Vx=max(0,Vx-dvx);
            if(Vy>0)Vy=max(0,Vy-dvy);
            if(Vz>0)Vz=max(0,Vx-dvz);
            if(Vx<0)Vx=min(0,Vx+dvx);
            if(Vy<0)Vy=min(0,Vy+dvy);
            if(Vz<0)Vz=min(0,Vz+dvz);
            break;
        }

        case 'v':
        {
            Vx=-Vx;
            Vy=-Vy;
            Vz=-Vz;
            break;
        }

        case 'a':
            isAxes=!isAxes;
            break;
        case 'c':
            isCube=!isCube;
            break;
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
    glLineWidth(3); //set Line Thickness
    //printf("Drawing axes\n");
    glBegin(GL_LINES);
    {
        //X axis (red)
        glColor3f(1,1,1);
        glVertex3f(-8,0,0);
        glVertex3f(8,0,0);

        //Y axis (green)
        glColor3f(1,1,1);
        glVertex3f(0,-8,0);
        glVertex3f(0,8,0);

        //Z axis(blue)
        glColor3f(1,1,1);
        glVertex3f(0,0,-8);
        glVertex3f(0,0,8);
    }
    glEnd();
}

void timerFunc(int value)
{
    //spin+=2.0f;
    //if(spin>=360)spin=2;
    //if(spin<=-360)spin=2;
    //printf("%f\n",spin);
    if(isMove)
    {
      
        ballx+=Vx;
        bally+=Vy;
        ballz+=Vz;
        /*if(Vy!=0 &&bally>cubeLowy+radius)*/Vy+=g;
        float speed=sqrt(ballx*ballx+bally*bally+ballz*ballz);
        spin+=speed*300;
        spinAxisX=Vy*upz-Vz*upy;
        spinAxisY=Vz*upx-Vx*upz;
        spinAxisZ=Vx*upy-Vy*upx;
        float axisLen=sqrt(spinAxisX*spinAxisX+spinAxisY*spinAxisY+spinAxisZ*spinAxisZ);
        if(axisLen>0.0001f)
        {
            spinAxisX/=axisLen;
            spinAxisY/=axisLen;
            spinAxisZ/=axisLen;
        }
        if(spin>360)spin-=100;
        if(spin<-360)spin+=100;
        
        //printf("Here    %f %f %f\n",ballx,bally,ballz);
        if(ballx<cubeLowx+radius)
        {
            //printf("%f %f %f",ballx,bally,ballz);
            ballx=cubeLowx+0.2f;
            Vx=-Vx;
            Vx*=restitution;
            Vy*=restitution;
            Vz*=restitution;
            //exit(1);
            //printf("cubeLowx\n");
        }
        
        if(ballx>cubeUpx-radius){
            //printf("%f %f %f",ballx,bally,ballz);
            ballx=cubeUpx-0.2f;
            Vx=-Vx;
            Vx*=restitution;
            Vy*=restitution;
            Vz*=restitution;
            //exit(1);
            //printf("cubeupx\n");
        }


        if(bally<cubeLowy+radius){
            if(Vy<0)
            {
                bally=cubeLowy+radius;
                if(fabs(Vy)<0.002f)
                {
                    Vy=0.0f;
                    Vx*=restitution;
                    Vy*=restitution;
                    Vz*=restitution;
                }
                else
                {
                    Vy=-Vy*restitution;
                    Vx*=restitution;
                    Vy*=restitution;
                    Vz*=restitution;
                } 
               
            }
            else
            {
                //printf("%f %f %f",ballx,bally,ballz);
                bally=cubeLowy+radius;
                Vy=-Vy;
                Vx*=restitution;
                Vy*=restitution;
                Vz*=restitution;
                //exit(1);
                //printf("cubelowy\n");
            }
        }
        if(bally>cubeUpy-radius){
            //printf("%f %f %f",ballx,bally,ballz);
            bally=cubeUpy-0.2f;
            Vy=-Vy;
            Vx*=restitution;
            Vy*=restitution;
            Vz*=restitution;
            //exit(1);
            //printf("%f %f %f",ballx,bally,ballz);
            //printf("cubeupy\n");
        }
        if(ballz<cubeLowz+radius){
            //printf("%f %f %f",ballx,bally,ballz);
            ballz=cubeLowz+0.2f;
            Vz=-Vz;
            Vx*=restitution;
            Vy*=restitution;
            Vz*=restitution;
            //exit(1);
            //printf("%f %f %f",ballx,bally,ballz);
            //printf("cubelowz\n");
        }
        if(ballz>cubeUpz-radius){
            //printf("%f %f %f",ballx,bally,ballz);
            ballz=cubeUpz-0.2f;
            Vz=-Vz;
            Vx*=restitution;
            Vy*=restitution;
            Vz*=restitution;
            //exit(1);
            //printf("%f %f %f",ballx,bally,ballz);
            //printf("cubeupz\n");
        }
        float currentV=sqrt(Vx*Vx+Vy*Vy+Vz*Vz);
        if(currentV<0.0004)isMove=false;
       
    }
    glutPostRedisplay();
    glutTimerFunc(timeInterval,timerFunc,0);
}

void timerFuncRide(int value)
{
    angle-=0.3f;
    if(angle<-360.0f)angle+=360.0f;
    glutPostRedisplay();
    glutTimerFunc(timeInterval,timerFuncRide,0);
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

    //glutTimerFunc(timeInterval,timerFunc,0);
    glutTimerFunc(timeInterval,timerFuncRide,0);

    //Initialize OpenGL settings
    initGL();

    //Enter the GLUT event Loop
    glutMainLoop();

    return 0;
}