// Draw an Icosahedron
// ECE4893/8893 Project 4
// Yash Shah

#include <iostream>
#include <math.h>
#include <GL/glut.h>  
#include <GL/glext.h>
#include <GL/gl.h>
#include <GL/glu.h>

using namespace std;

#define NFACE 20
#define NVERTEX 12

#define X .525731112119133606 
#define Z .850650808352039932


static GLfloat vdata[NVERTEX][3] = {    
   {-X, 0.0, Z}, {X, 0.0, Z}, {-X, 0.0, -Z}, {X, 0.0, -Z},    
   {0.0, Z, X}, {0.0, Z, -X}, {0.0, -Z, X}, {0.0, -Z, -X},    
   {Z, X, 0.0}, {-Z, X, 0.0}, {Z, -X, 0.0}, {-Z, -X, 0.0} 
};


static GLint tindices[NFACE][3] = { 
   {0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
   {8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
   {7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
   {6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

GLfloat light_position[] = {1.5, 1.0, -2.0, 0.0}; 
GLfloat colorArray[3];

int testNumber; 
int subdiv = 0;     

double rotate_y=0; 
double rotate_x=0;

static int updateRate = 10;


void normalize(GLfloat v[3])
{
  GLfloat d = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  v[0] /= d; v[1] /= d; v[2] /= d;
}

void drawTriangle(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3])
{
  glBegin(GL_LINES);
    glLineWidth(2.5); 
    glColor3f(1.0, 1.0, 1.0);

    glVertex3fv(v1);
    glVertex3fv(v2);

    glVertex3fv(v3);
    glVertex3fv(v2);

    glVertex3fv(v3);
    glVertex3fv(v2);

  glEnd();

  //COMMENT the following to stop random color assignment
  glColor3ub( rand()%255, rand()%255, rand()%255 );
  glBegin(GL_TRIANGLES);

    //UNCOMMENT the following to make polygon of solod blue color
    //glColor3f(0.0, 0.0, 1.0);

    glNormal3fv(v1);
    glVertex3fv(v1);
    glNormal3fv(v2);
    glVertex3fv(v2);
    glNormal3fv(v3);
    glVertex3fv(v3);

  glEnd();
}


 

void Test1(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth)
{
  GLfloat v12[3], v23[3], v31[3];
  int i;
  drawTriangle(v1, v2, v3);
  return;
}

void Test3(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth){

  GLfloat v12[3], v23[3], v31[3];

  if (depth == 0) {
    drawTriangle(v1, v2, v3);
    return;
  }


  for (int i = 0; i < 3; i++) {
    v12[i] = (v1[i]+v2[i])/2.0;
    v23[i] = (v2[i]+v3[i])/2.0;
    v31[i] = (v3[i]+v1[i])/2.0;
  }

  normalize(v12);
  normalize(v23);
  normalize(v31);


  Test3(v1, v12, v31, depth-1);
  Test3(v2, v23, v12, depth-1);
  Test3(v3, v31, v23, depth-1);
  Test3(v12, v23, v31, depth-1);
}


void Test6(GLfloat v1[3], GLfloat v2[3], GLfloat v3[3], int depth){

  GLfloat v12[3], v23[3], v31[3];

  if (depth == 0) {
    drawTriangle(v1, v2, v3);
    return;
  }

  for (int i = 0; i < 3; i++) {
    v12[i] = (v1[i]+v2[i])/2.0;
    v23[i] = (v2[i]+v3[i])/2.0;
    v31[i] = (v3[i]+v1[i])/2.0;
  }


  normalize(v12);
  normalize(v23);
  normalize(v31);

  Test6(v1, v12, v31, depth-1);
  Test6(v2, v23, v12, depth-1);
  Test6(v3, v31, v23, depth-1);
  Test6(v12, v23, v31, depth-1);
}



void display(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(0.5, 0.5, -1.5, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

  if(testNumber % 2 == 0){
    rotate_y += 5;
    rotate_x += 5;
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);
  }

  for (int i = 0; i < 20; i++) {
    if(testNumber == 1 || testNumber == 2){
      Test1(&vdata[tindices[i][0]][0], &vdata[tindices[i][1]][0],
          &vdata[tindices[i][2]][0], subdiv);}
    else if(testNumber == 3 || testNumber == 4){
      subdiv = 1;
      Test3(&vdata[tindices[i][0]][0], &vdata[tindices[i][1]][0],
          &vdata[tindices[i][2]][0], subdiv);}
    else{
      Test6(&vdata[tindices[i][0]][0], &vdata[tindices[i][1]][0],
          &vdata[tindices[i][2]][0], subdiv);
    }
    
  }


  glFlush();
}

void reshape(int w, int h)
{
  GLfloat aspect = (GLfloat) w / (GLfloat) h;
  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (w <= h)
    glOrtho(-1.25, 1.25, -1.25 * aspect, 1.25 * aspect, -2.0, 2.0);
  else
    glOrtho(-1.25 * aspect, 1.25 * aspect, -1.25, 1.25, -2.0, 2.0);
  glMatrixMode(GL_MODELVIEW);

  glutPostRedisplay();
}


void timer(int)
{
  glutPostRedisplay();
  glutTimerFunc(1000.0 / updateRate, timer, 0);
}



// to change the random color assignment of polygon 
//make changes to drawTriangle() method 

int main(int argc, char** argv)
{
  if (argc < 2)
    {
      std::cout << "Usage: icosahedron testnumber" << endl;
      std::cout << "Usage: icosahedron testnumber5/6 depth" << endl;
      exit(1);
    }

  testNumber = atol(argv[1]);


  if(testNumber > 4 ){
    if (argc > 2){
      subdiv = atol(argv[2]);}
  }



  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH);

  glutInitWindowSize(500, 500);
  glutCreateWindow("icosahedron");

  glClearColor(0.0, 0.0, 0.0, 0.0);
  glEnable(GL_DEPTH_TEST);


  glutReshapeFunc(reshape);
  glutDisplayFunc(display);

  if(testNumber % 2 == 0){
    glutTimerFunc(1000.0 / updateRate, timer, 0);
  }


  glutMainLoop();
  return 0;
}