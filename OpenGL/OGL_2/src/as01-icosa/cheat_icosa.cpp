#include <stdio.h>
#include <GL/glut.h>
#define X .525731112119133606
#define Z .850650808352039932

void mouseEventHandler(int button, int state, int x, int y){
}

void display() {
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	static GLfloat vdata[12][3] = {
		{-X,0.0,Z}, {X,0.0,Z}, {-X,0.0,-Z}, {X,0.0,-Z},
		{0.0,Z,X}, {0.0,Z,-X}, {0.0,-Z,X}, {0.0,-Z,-X},
		{Z,X,0.0}, {-Z,X,0.0}, {Z,-X,0.0}, {-Z,-X,0.0},
	};

	static GLuint tindices[20][3] = { 
		{0,4,1}, {0,9,4}, {9,5,4}, {4,5,8}, {4,8,1},    
		{8,10,1}, {8,3,10}, {5,3,8}, {5,2,3}, {2,7,3},    
		{7,10,3}, {7,6,10}, {7,11,6}, {11,0,6}, {0,1,6}, 
		{6,1,10}, {9,0,11}, {9,11,2}, {9,2,5}, {7,2,11} };

	int i;
	GLfloat nx,ny,nz;
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glBegin(GL_TRIANGLES);
	for (i = 0; i < 20; i++){
	    nx =vdata[tindices[i][0]][0];
	    ny =vdata[tindices[i][0]][1];
	    nz =vdata[tindices[i][0]][2];
	    nx+=vdata[tindices[i][1]][0];
	    ny+=vdata[tindices[i][1]][1];
	    nz+=vdata[tindices[i][1]][2];
	    nx+=vdata[tindices[i][2]][0]; nx/=3.0;
	    ny+=vdata[tindices[i][2]][1]; ny/=3.0;
	    nz+=vdata[tindices[i][2]][2]; nz/=3.0;
	    glNormal3f(nx,ny,nz);
	    glVertex3fv(vdata[tindices[i][0]]);
	    glVertex3fv(vdata[tindices[i][1]]);
	    glVertex3fv(vdata[tindices[i][2]]);
	}
	glEnd();
	glFlush ( );
}

void windowSetup(){
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutInitWindowPosition(80, 80);
    glutInitWindowSize(1000,1000);

    glutCreateWindow("OpenGL Ico");

    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode( GL_MODELVIEW);
    glLoadIdentity();           
    gluOrtho2D( -2.0, 2.0, -2.0, 2.0 );
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);
    windowSetup();

    glutDisplayFunc(display);
    glutMouseFunc(&mouseEventHandler);
    glutMainLoop();
}