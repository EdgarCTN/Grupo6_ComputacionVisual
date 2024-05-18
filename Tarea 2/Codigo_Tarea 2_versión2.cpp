#include <GL/glut.h> 

GLfloat anguloCuboX = 0.0f;  
GLfloat anguloCuboY = 0.0f; 
GLfloat despZ = 0.0f;

GLint ancho, alto; 
int hazPerspectiva = 1;

void reshape(int width, int height) 
{ 
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	if (hazPerspectiva) 
		gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f, 20.0f); 
	else 
		glOrtho(-4, 4, -4, 4, 1, 10); 
	
	glMatrixMode(GL_MODELVIEW); 
	
	ancho = width; 
	alto = height; 
}

void drawCube(void) 
{ 
	glBegin(GL_QUADS);  // Cara frontal
	glColor3f(1.0f, 0.0f, 0.0f); // Rojo
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara trasera
	glColor3f(0.0f, 1.0f, 0.0f); // Verde
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara lateral izquierda
	glColor3f(0.0f, 0.0f, 1.0f); // Azul
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd();
	
	glBegin(GL_QUADS);  // Cara lateral derecha
	glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara superior
	glColor3f(0.0f, 1.0f, 1.0f); // Cian
	glVertex3f(-1.0f,  1.0f,  1.0f);
	glVertex3f( 1.0f,  1.0f,  1.0f);
	glVertex3f( 1.0f,  1.0f, -1.0f);
	glVertex3f(-1.0f,  1.0f, -1.0f);
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara inferior
	glColor3f(1.0f, 0.0f, 1.0f); // Magenta
	glVertex3f( 1.0f, -1.0f, -1.0f);
	glVertex3f( 1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glEnd(); 
} 

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	
	glLoadIdentity(); 
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f); 
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f); 
	glTranslatef(0.0f, 0.0f, despZ);
	drawCube(); 
	
	glFlush(); 
	glutSwapBuffers(); 
} 

void init() 
{ 
	glClearColor(0, 0, 0, 0); 
	glEnable(GL_DEPTH_TEST); 
	ancho = 400; 
	alto = 400; 
} 

void idle() 
{ 
	display(); 
} 

void forward() {
	despZ += 0.1f;
	display();
}

void back() {
	despZ -= 0.1f;
	display();
}

void right() {
	anguloCuboY += 5.0f;
	display();
}

void left() {
	anguloCuboY -= 5.0f;
	display();
}

void uppitch() {
	anguloCuboX += 5.0f;
	display();
}

void downpitch() {
	anguloCuboX -= 5.0f;
	display();
}

void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'f':
		forward();
		break;
	case 'r':
		right();
		break;
	case 'l':
		left();
		break;
	case 'b':
		back();
		break;
	case 'u':
		uppitch();
		break;
	case 'd':
		downpitch();
		break;
	case 27: // escape
		exit(0);
		break;
	}
}

int main(int argc, char **argv) 
{ 
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitWindowPosition(100, 100); 
	glutInitWindowSize(ancho, alto); 
	glutCreateWindow("Cubo"); 
	init(); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutIdleFunc(idle); 
	glutKeyboardFunc(keyboard); 
	glutMainLoop(); 
	return 0; 
}
