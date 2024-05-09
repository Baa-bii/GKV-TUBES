#include <stdlib.h> // standard definitions
#include <stdio.h> // C I/O (for sprintf)
#include <math.h> // standard definitions
#include <GL/glut.h> // GLUT
double rotAngle = 10; // rotation angle (BEWARE: Global)
double rotAngle1 = 10; // rotation angle (BEWARE: Global)
//------------------------------------------------------------------
// init
// Sets up some default OpenGL values.
//------------------------------------------------------------------
float angle=0.0, deltaAngle = 0.0, ratio;
float x=20.0f,y=40.0f,z=80.0f; // posisi awal kamera
float lx=0.0f,ly=-0.6f,lz=-1.0f;
int deltaMove = 0,h,w;
static int rotAngleX =0, rotAngleY =0, rotAngleZ =0;
GLUquadricObj *IDquadric;
static int platform=0;
//-------------------------------------------------------------------
void orientMe(float ang)
{
 // Fungsi ini untuk memutar arah kamera (tengok kiri/kanan)
 lx = sin(ang/10);
 lz = -cos(ang/30);
 glLoadIdentity();
 gluLookAt(x, y, z,x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
} 
//-------------------------------------------------------------------
void moveMeFlat(int i)
{
 // Fungsi ini untuk maju mundur kamera
 x = x + i*(lx)*0.1;
 z = z + i*(lz)*0.1;
 glLoadIdentity();
gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
} 
//---------------------------------------------------------------------
void init(void)
{
glEnable (GL_DEPTH_TEST);
glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
IDquadric=gluNewQuadric(); // Create A Pointer To The Quadric Object ( NEW )
 gluQuadricNormals(IDquadric, GLU_SMOOTH); // Create Smooth Normals( NEW )
 gluQuadricTexture(IDquadric, GL_TRUE); // Create Texture Coords (NEW )
} 
//--------------------------------------------------------------------
void Grid()
{
 // Fungsi untuk membuat grid di "lantai"
 double i;
 const float Z_MIN = -10, Z_MAX = 50;
 const float X_MIN = -10, X_MAX = 50;
 const float gap = 2;
 glColor3f(0.5, 0.5, 0.5);
 glBegin(GL_LINES);
 for(i=Z_MIN;i<Z_MAX;i+=gap)
 {
 glVertex3f(i, 0, Z_MIN);
 glVertex3f(i, 0, Z_MAX);
 }
 for(i=X_MIN;i<X_MAX;i+=gap)
 {
 glVertex3f(X_MIN, 0, i);
 glVertex3f(X_MAX, 0, i);
 }
 glEnd();
} 
//---------------------------------------------------------------------
void Reshape(int w1, int h1)
{
// Fungsi reshape
 if(h1 == 0)
h1 = 1;
 w = w1;
 h = h1;
 ratio = 1.0f * w / h;
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
glViewport(0, 0, w, h);
 gluPerspective(45,ratio,0.1,1000);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(x, y, z, x + lx,y + ly,z + lz, 0.0f,1.0f,0.0f);
} 
//----------------------------------------------------------------------
void Object(){
	glPushMatrix();
    	glScalef(1.0, 1.0, 1.0);
        glPushMatrix();
            // Bagian badan mobil depan
            glRotatef ((GLfloat) platform, 0.0, 1.0, 0.0);
            glRotatef(45.0, 0.0, 1.0, 0.0);
            glPushMatrix();
                glTranslatef(15, 0.0, 15);               
                glScalef(15, 1, 15);  
                glColor3f(1.0, 0.0, 0.0);
                glutSolidCube(1.0);
			glPopMatrix();  
		glPopMatrix();
		glPushMatrix();
            // Bagian badan mobil depan
            glRotatef ((GLfloat) platform, 0.0, 1.0, 0.0);
			glRotatef(45.0, 0.0, 1.0, 0.0);
            glPushMatrix();
                glTranslatef(14.5, 7.5, 8.2);              
                glRotatef(90.0, 1.0, 0.0, 0.0);
                glScalef(15, 1, 15);  
                glColor3f(0.0, 1.0, 0.0);
                glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
            // Bagian badan mobil depan
            glRotatef ((GLfloat) platform, 0.0, 1.0, 0.0);
			glRotatef(-45.0, 0.0, 1.0, 0.0);
            glPushMatrix();
                glTranslatef(15.5, 7.5, -21.8);               
                glRotatef(90.0, 1.0, 0.0, 0.0);
                glScalef(15, 1, 15);  
                glColor3f(0.0, 0.0, 1.0);
                glutSolidCube(1.0);
			glPopMatrix();
		glPopMatrix();
	glPopMatrix();
}
//----------------------------------------------------------------------
void keyboard(unsigned char key, int x, int y) {
switch (key) {
 case 'a': platform = (platform + 5) % 360;
glutPostRedisplay(); break;
 case 'd': platform = (platform - 5) % 360;
glutPostRedisplay(); break;
 case 'w': platform = (platform + 5) % 360;
glutPostRedisplay(); break;
 case 's': platform = (platform - 5) % 360;
glutPostRedisplay(); break;
case 27: exit(0); break;
default: break;
 }
}
 //---------------------------------------------------------------------
void display() {
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 // Kalau move dan angle tidak nol, gerakkan kamera...
 if (deltaMove) {
 	moveMeFlat(deltaMove);
 }
 if (deltaAngle) {
 	angle += deltaAngle;
 orientMe(angle); }

 glPushMatrix();
glRotated(rotAngleX, 1, 0, 0);
 glRotated(rotAngleY, 0, 1, 0);
 glRotated(rotAngleZ, 0, 0, 1);
// Gambar grid
 Grid();
 //Grid2();
// Gambar objek di sini...
 Object();
glPopMatrix();
glFlush();
glutSwapBuffers();
} 

int main()
{
 glutInitDisplayMode( // initialize GLUT
 GLUT_DOUBLE | // use double buffering
 GLUT_DEPTH | // request memory for z-buffer
 GLUT_RGB ); // set RGB color mode
 glutCreateWindow("GLUT Example"); // create the window
 glutDisplayFunc(display); // call display() to redraw window
 glutReshapeFunc(Reshape);//reshape function 
 glutKeyboardFunc(keyboard); // call keyboard() when key is hit
 init(); // our own initializations
 glutMainLoop(); // let GLUT take care of everything
 return 0;
}
