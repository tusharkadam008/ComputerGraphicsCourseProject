
#include <windows.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#include <math.h>
#define winx 800 //500 1500 //window width
#define winy 600 //500 800  //window height
#define winpx -10 //450     //window position horizontal
#define winpy -10 //150     //window position horizontal

//variables required
int x1=0,x2=0,y1=0,y2=0,c=0;            //(x1,y1) & (x2,y2) VERTICES
int polx[10],poly[10],poln=0,polc=0;    //Polygon Rendering Variables
int polavgx=0,polavgy=0;                //Average Polygon Vertex
int shapestate=0,shavertex=2;           //Polygon State
int transtate=0;        //Transformation State
int traX=0,traY=0;      //Translation variables
float scaX=1,scaY=1;    //Scaling variables
int rotX=0,rotY=0;      //Rotation variables
int refX=0,refY=0;      //Reflection variables
int axe=0;              //AxisMode state
int pnt=0;
////////////////////////////////////////////////////////////////////
void displayTest(void); //Displays Origin
void displayXAxis(void);    //Displays X-Axis
void displayYAxis(void);    //Displays Y-Axis
void AxisMode(int i);       //Displays Both Axes
void displayCircle(void);   //Displays Circle
void displayPolygon(void);  //Displays Polygon
void displayLine(void);     //Displays Line
void displayEllipse(void);  //Displays Ellipse
void MouseMotion(int x, int y);  //tracks the motion of the mouse
void MouseButton(int button,int state,int x, int y);    //Returns position where mouse was clicked (Double)
void MouseButton2(int button,int state,int x, int y);   //Returns position where mouse was clicked (Multiple)
void specialKeysTranslate( int key, int x, int y );     //Assigns direction keys to change Translation variables
void specialKeysRotate( int key, int x, int y );        //Assigns direction keys to change Rotation variables
void specialKeysReflect( int key, int x, int y );       //Assigns direction keys to change Reflection variables
void specialKeysScale( int key, int x, int y );         //Assigns direction keys to change Scaling variables
void init2D (float r, float g, float b);   //Initializes the co-ordinate system and projection mode
void clearall();    //clears all variables and sets everything to default
void initpol();     //Resets polygon variables to default
void chancolor(int i);      //Changes Drawing Color
void chanbgcolor(int i);    //Changes Background Color
void transhape(int i);      //Changes Transformation State
void polyshape(int i);      //Changes Polygon State or Types
void menu(int id);          //Main Menu choice list
////////////////////////////////////////////////////////////////////

void init2D (float r, float g, float b)//Initializes the co-ordinate system and projection mode
{
	glClearColor(r,g,b,1.0);        //Sets BG color
	glMatrixMode(GL_PROJECTION);    //
    gluOrtho2D(-winx/2,winx/2,winy/2,-winy/2);     //Sets Boundaries for the Co-ordinate System
}

////////////////////////////////////////////////////////////////////
void clearall() //clears all variables and sets everything to default
{
   	glClear(GL_COLOR_BUFFER_BIT);       //Clear Color Buffer to preset value
  	x1=0,x2=0,y1=0,y2=0,c=0,polc=0;
  	polavgx=0,polavgy=0;
    transtate=0;
    traX=0,traY=0;
    scaX=1,scaY=1;          //Default Values
    rotX=0,rotY=0;
    refX=0,refY=0;
    AxisMode(axe); //Draws the Axes
}
////////////////////////////////////////////////////////////////////
void initpol()  //Resets polygon variables to default
{
    polavgx=0;polavgy=0;
    for(int i=0;i<10;i++){polx[i]=0;poly[i]=0;} //Default Values
    poln=shavertex;polc=0;
}
////////////////////////////////////////////////////////////////////
void chancolor(int i)   //Changes Drawing Color
{
    if(i==1)glColor3f(1.0, 0.0, 0.0);//red
    if(i==2)glColor3f(0.0, 1.0, 0.0);//green
    if(i==3)glColor3f(0.0, 0.0, 1.0);//blue
    if(i==4)glColor3f(1.0, 1.0, 1.0);//white
    if(i==5)glColor3f(0.0, 0.0, 0.0);//black
    glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void chanbgcolor(int i) //Changes Background Color
{
    if(i==1)glClearColor(1.0,0.0,0.0,1.0);//red
    if(i==2)glClearColor(0.0,1.0,0.0,1.0);//green
    if(i==3)glClearColor(0.0,0.0,1.0,1.0);//blue
    if(i==4)glClearColor(1.0,1.0,1.0,1.0);//white
    if(i==5)glClearColor(0.0,0.0,0.0,1.0);//black
    glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void transhape(int i)   //Changes Transformation State
{
    switch(i)
    {
    case 1://Translate
        glutSpecialFunc(specialKeysTranslate);
        break;
    case 2://Rotate
        glutSpecialFunc(specialKeysRotate);
        break;
    case 3://Scale
        glutSpecialFunc(specialKeysScale);
        break;
    case 4://Reflect
        glutSpecialFunc(specialKeysReflect);
        break;
    }
    glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void polyshape(int i)
{
    int jkl=0;
    if(i==10){scanf("%d",&jkl);i=jkl-2;}
    shapestate=i;shavertex=i+2;poln=i+2;
    glClear(GL_COLOR_BUFFER_BIT);
    x1=0,x2=0,y1=0,y2=0,c=0,polc=0;
    glutDisplayFunc(displayPolygon);
    glutMouseFunc(MouseButton2);
    glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void menu(int id)
{
    pnt=0;
   switch(id)
   {

       case 1:
      //glfwGetMousePos(&xpos,&ypos);
        clearall();
        glutPostRedisplay();
       break;
       case 2:
        clearall();
        glutDisplayFunc(displayCircle);
        glutMouseFunc(MouseButton);
        glutPostRedisplay();
       break;
       case 3:
        clearall();
        glutDisplayFunc(displayLine);
        glutMouseFunc(MouseButton);
        glutPostRedisplay();
       break;
       case 4:
        clearall();
        glutDisplayFunc(displayEllipse);
        glutMouseFunc(MouseButton);
        glutPostRedisplay();
       break;
       case 5:
        axe++;
        glutPostRedisplay();
       break;
       case 6:
        pnt=1;
        clearall();
        glutDisplayFunc(displayTest);
        glutMouseFunc(MouseButton);
        glutPostRedisplay();
       break;
     }
  }
////////////////////////////////////////////////////////////////////
void specialKeysTest( int key, int x, int y )
{
    int qwer =5;float qwer1=0.1;
  if (key == GLUT_KEY_RIGHT)
    {rotX+=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_LEFT)
    {rotX-=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_UP)
    {scaX+=qwer1;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_DOWN)
    {scaX-=qwer1;glClear(GL_COLOR_BUFFER_BIT);}
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void specialKeysRotate( int key, int x, int y )
{
    int qwer=5;
  if (key == GLUT_KEY_RIGHT)
    {rotX+=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_LEFT)
    {rotX-=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_UP)
    {rotX+=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_DOWN)
    {rotX-=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void specialKeysTranslate( int key, int x, int y )
{
    int qwer=5;
  if (key == GLUT_KEY_RIGHT)
    {traX+=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_LEFT)
    {traX-=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_UP)
    {traY-=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_DOWN)
    {traY+=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void specialKeysScale( int key, int x, int y )
{
    float qwer =0.1;
  if (key == GLUT_KEY_RIGHT)
    {scaX+=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_LEFT)
    {scaX-=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_UP)
    {scaY+=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_DOWN)
    {scaY-=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void specialKeysReflect( int key, int x, int y )
{
    float qwer =1;
  if (key == GLUT_KEY_RIGHT)
    {scaX=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_LEFT)
    {scaX=-qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_UP)
    {scaY=qwer;glClear(GL_COLOR_BUFFER_BIT);}
  else if (key == GLUT_KEY_DOWN)
    {scaY=-qwer;glClear(GL_COLOR_BUFFER_BIT);}
  glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void displayPolygon(void)
{
    AxisMode(axe);
    glPushMatrix();
    glRotated(rotX,0,0,1);
    glScalef(scaX,scaY,1);
	glBegin(GL_POLYGON);
	if(polc==poln)
	for(int i=0;i<polc;i++)
    glVertex2i(polx[i]+traX,poly[i]+traY);
	glEnd();
	glPopMatrix();
	glFlush();
}
////////////////////////////////////////////////////////////////////
void displayTest(void)
{
    int i=0,j=0,q=1,w=1;
    glPushMatrix();
	glBegin(GL_POINTS);
    glVertex2i(x2,y2);
    glEnd();
	glPopMatrix();
	glFlush();
}
////////////////////////////////////////////////////////////////////
void displayXAxis(void)
{
    int i=0,q=winx/2,j=5,k=10;
    glPushMatrix();
	glBegin(GL_LINES);
	for(i=-q;i<=q;i++)
    {glVertex2i(i,0);}
    glEnd();
	glPopMatrix();
	glFlush();
}
////////////////////////////////////////////////////////////////////
void displayYAxis(void)
{
    int i=0,q=winy/2,j=5,k=10;
    glPushMatrix();
	glBegin(GL_LINES);
	for(i=-q;i<=q;i++)
    {glVertex2i(0,i);}
    glEnd();
	glPopMatrix();
	glFlush();
}
////////////////////////////////////////////////////////////////////
void AxisMode(int i)
{
    if(i%2!=0)
    {displayTest();
    displayXAxis();
    displayYAxis();}
}
////////////////////////////////////////////////////////////////////
void displayLine(void)
{
    AxisMode(axe);
    glPushMatrix();
    int px1,px2,py1,py2,avx,avy;
    px1=x1+traX;
    px2=x2+traX;
    py1=y1+traY;
    py2=y2+traY;
    avx=(px1+px2)/2;
    avy=(py1+py2)/2;
    glRotated(rotX,0,0,1);
    glScalef(scaX,scaY,1);
	glBegin(GL_LINES);
        glVertex2i(px1,py1);
		glVertex2i(px2,py2);
	glEnd();
	glPopMatrix();
	glFlush();
}
////////////////////////////////////////////////////////////////////
void displayCircle(void)
{
    AxisMode(axe);
    glPushMatrix();
    glRotated(rotX,0,0,1);
    glScalef(scaX,scaY,1);
    glBegin(GL_POINTS);
	int a=(x2>x1)?x2-x1:x1-x2, b=(y2>y1)?y2-y1:y1-y2;
    int rad =(a>b)?a:b;
	int q=0,w=0;
    int i=1;
    int j=1;
	int t=y1;
	int r=x1;
    int x11=0,y11=rad;
	int p = 3/2 - rad;
       while(x11<=y11)
    {
        {
        glVertex2i(r+x11+i*q,t+y11+j*w);
        glVertex2i(r+y11+i*q,t+x11+j*w);
        glVertex2i(r-x11+i*q,t+y11+j*w);
        glVertex2i(r+y11+i*q,t-x11+j*w);
        glVertex2i(r-x11+i*q,t-y11+j*w);
        glVertex2i(r-y11+i*q,t-x11+j*w);
        glVertex2i(r+x11+i*q,t-y11+j*w);
        glVertex2i(r-y11+i*q,t+x11+j*w);
        }
        if (p<0)
            p+=(2*x11)+3;
        else
        {
            p+=(2*(x11-y11))+5;
            y11-=1;
        }
        x11++;
    }
	glEnd();
	glPopMatrix();
	glFlush();
}
////////////////////////////////////////////////////////////////////
void displayEllipse(void)
{
        float xc=x1, yc=y1,  a=(x2>x1)?x2-x1:x1-x2, b=(y2>y1)?y2-y1:y1-y2;
        float rxSq = a * a;
        float rySq = b * b;
        float x = 0, y = b, p;
        float px = 0, py = 2 * rxSq * y;
        AxisMode(axe);
        glPushMatrix();
        glRotated(rotX,0,0,1);
        glScalef(scaX,scaY,1);
        glBegin(GL_POINTS);
        glVertex2d(xc+x+traX,yc-y+traY);
        glVertex2d(xc-x+traX,yc-y+traY);
        glVertex2d(xc-x+traX,yc+y+traY);
        glEnd();
        p = rySq - (rxSq * b) + (0.25 * rxSq);
        while (px < py)
        {
                        x++;
                        px = px + 2 * rySq;
                        if (p < 0)
                        p = p + rySq + px;
                        else
                        {
                        y--;
                        py = py - 2 * rxSq;
                        p = p + rySq + px - py;
                        }
                         glBegin(GL_POINTS);
                         glVertex2d(xc+x+traX,yc+y+traY);
                         glVertex2d(xc+x+traX,yc-y+traY);
                         glVertex2d(xc-x+traX,yc-y+traY);
                         glVertex2d(xc-x+traX,yc+y+traY);
                        glEnd();
        }

        p = rySq*(x+0.5)*(x+0.5) + rxSq*(y-1)*(y-1) - rxSq*rySq;
        while (y > 0)
        {
                y--;
                py = py - 2 * rxSq;
                if (p > 0)
                p = p + rxSq - py;
                else
                {
                x++;
                px = px + 2 * rySq;
                p = p + rxSq - py + px;
                }
               glBegin(GL_POINTS);
         glVertex2d(xc+x+traX,yc+y+traY);
         glVertex2d(xc+x+traX,yc-y+traY);
         glVertex2d(xc-x+traX,yc-y+traY);
         glVertex2d(xc-x+traX,yc+y+traY);
        }
        glEnd();
        glPopMatrix();
        glFlush();
}

////////////////////////////////////////////////////////////////////
void MouseButton(int button,int state,int x, int y)
{

	if (state == GLUT_DOWN)
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
            if(pnt==0)
            clearall();
			x1=x-winx/2;x2=x1;
            y1=y-winy/2;y2=y1;
            traX=0;traY=0;rotX=0;
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	}
	else
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			x2=x-winx/2;
            y2=y-winy/2;
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	}
	glutPostRedisplay();
}
///////////////////////////////////////////////////////////////////
void MouseButton2(int button,int state,int x, int y)
{

	if (state == GLUT_DOWN)
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			if(polc==poln){polc=0;clearall();glutPostRedisplay();}
			polx[polc]=x-winx/2;
            poly[polc]=y-winy/2;
            polavgx+=polx[polc];
            polavgy+=poly[polc];
            polc++;
			break;
		case GLUT_MIDDLE_BUTTON:
            clearall();
            initpol();
            glutPostRedisplay();
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	}
	else
	{
		switch(button)
		{
		case GLUT_LEFT_BUTTON:
			x2=x-winx/2;
            y2=y-winy/2;
			break;
		case GLUT_MIDDLE_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			break;
		}
	}
	glutPostRedisplay();
}
////////////////////////////////////////////////////////////////////
void MouseMotion(int x, int y)//tracks the motion of the mouse
{
	//printf("new mouse pos = (%d,%d)\n",x,y);
    x2=x-winx/2;
    y2=y-winy/2;
    if(pnt==0)
    glClear(GL_COLOR_BUFFER_BIT);
	glutPostRedisplay();
}

////////////////////////////////////////////////////////////////////
int main(int argc,char *argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize (winx,winy);
	glutInitWindowPosition (winpx,winpy);
	glutCreateWindow ("SimpleShapeSimulator");
	init2D(0.0,0.0,0.0);
	//glutFullScreen();

    initpol();
    clearall();

	glutDisplayFunc(displayLine);
    glutSpecialFunc(specialKeysTest);

	glutMouseFunc(MouseButton);
    glutMotionFunc(MouseMotion);

	int sub1=glutCreateMenu(chancolor);
	glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("White",4);
    glutAddMenuEntry("Black",5);

    int sub2=glutCreateMenu(chanbgcolor);
	glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("White",4);
    glutAddMenuEntry("Black",5);

    int sub3=glutCreateMenu(transhape);
	glutAddMenuEntry("Translate",1);
    glutAddMenuEntry("Rotate",2);
    glutAddMenuEntry("Scaling",3);
    glutAddMenuEntry("Reflection",4);

    int sub4=glutCreateMenu(polyshape);
	glutAddMenuEntry("Triangle",1);
    glutAddMenuEntry("Quadrilateral",2);
    glutAddMenuEntry("Pentagon",3);
    glutAddMenuEntry("Hexagon",4);
    glutAddMenuEntry("Heptagon",5);
    glutAddMenuEntry("Heptagon",6);
    glutAddMenuEntry("Octagon",7);
    glutAddMenuEntry("Nonagon",8);
    glutAddMenuEntry("Decagon",9);
    glutAddMenuEntry("X Sided Polygon",10);

	int menu1=glutCreateMenu(menu);
    glutAddMenuEntry("Clear",1);
    glutAddMenuEntry("Line",3);
    glutAddMenuEntry("Circle",2);
    glutAddMenuEntry("Ellipse",4);
    glutAddMenuEntry("FreeDrawing",6);
    glutAddMenuEntry("AxisMode",5);
    glutAddSubMenu("Polygon",sub4);
    glutAddSubMenu("Transform",sub3);
    glutAddSubMenu("Color",sub1);
    glutAddSubMenu("BGColor",sub2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
	return 0;
}
////////////////////////////////////////////////////////////////////
