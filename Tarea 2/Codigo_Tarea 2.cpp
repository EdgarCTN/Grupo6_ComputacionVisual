#include <GL/glut.h>
#include <cmath>

GLfloat anguloCuboX = 0.0f;
GLfloat anguloCuboY = 0.0f;
GLfloat posX = 0.0f;
GLfloat posY = 0.0f;
GLfloat posZ = -5.0f;

GLfloat velocidadMovimiento = 0.1f;
GLfloat velocidadRotacion = 1.0f;

GLint ancho, alto;
int hazPerspectiva = 0;

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (hazPerspectiva)
		gluPerspective(60.0f, (GLfloat)width / (GLfloat)height, 1.0f,
					   20.0f);
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
	glVertex3f(-1.0f, -1.0f,  1.0f); // Vértice 1
	glVertex3f( 1.0f, -1.0f,  1.0f); // Vértice 2
	glVertex3f( 1.0f,  1.0f,  1.0f); // Vértice 3
	glVertex3f(-1.0f,  1.0f,  1.0f); // Vértice 4
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara trasera
	glColor3f(0.0f, 1.0f, 0.0f); // Verde
	glVertex3f( 1.0f, -1.0f, -1.0f); // Vértice 1
	glVertex3f(-1.0f, -1.0f, -1.0f); // Vértice 2
	glVertex3f(-1.0f,  1.0f, -1.0f); // Vértice 3
	glVertex3f( 1.0f,  1.0f, -1.0f); // Vértice 4
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara lateral izquierda
	glColor3f(0.0f, 0.0f, 1.0f); // Azul
	glVertex3f(-1.0f, -1.0f, -1.0f); // Vértice 1
	glVertex3f(-1.0f, -1.0f,  1.0f); // Vértice 2
	glVertex3f(-1.0f,  1.0f,  1.0f); // Vértice 3
	glVertex3f(-1.0f,  1.0f, -1.0f); // Vértice 4
	glEnd();
	
	glBegin(GL_QUADS);  // Cara lateral derecha
	glColor3f(1.0f, 1.0f, 0.0f); // Amarillo
	glVertex3f( 1.0f, -1.0f,  1.0f); // Vértice 1
	glVertex3f( 1.0f, -1.0f, -1.0f); // Vértice 2
	glVertex3f( 1.0f,  1.0f, -1.0f); // Vértice 3
	glVertex3f( 1.0f,  1.0f,  1.0f); // Vértice 4
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara superior
	glColor3f(0.0f, 1.0f, 1.0f); // Cian
	glVertex3f(-1.0f,  1.0f,  1.0f); // Vértice 1
	glVertex3f( 1.0f,  1.0f,  1.0f); // Vértice 2
	glVertex3f( 1.0f,  1.0f, -1.0f); // Vértice 3
	glVertex3f(-1.0f,  1.0f, -1.0f); // Vértice 4
	glEnd(); 
	
	glBegin(GL_QUADS);  // Cara inferior
	glColor3f(1.0f, 0.0f, 1.0f); // Magenta
	glVertex3f( 1.0f, -1.0f, -1.0f); // Vértice 1
	glVertex3f( 1.0f, -1.0f,  1.0f); // Vértice 2
	glVertex3f(-1.0f, -1.0f,  1.0f); // Vértice 3
	glVertex3f(-1.0f, -1.0f, -1.0f); // Vértice 4
	glEnd(); 
} 



void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glTranslatef(posX, posY, posZ);
	glRotatef(anguloCuboX, 1.0f, 0.0f, 0.0f);
	glRotatef(anguloCuboY, 0.0f, 1.0f, 0.0f);
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

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'w':
		posX -= sin(anguloCuboY * 3.14159265 / 180) * velocidadMovimiento;
		posZ += cos(anguloCuboY * 3.14159265 / 180) * velocidadMovimiento;
		break;
	case 's':
		posX += sin(anguloCuboY * 3.14159265 / 180) * velocidadMovimiento;
		posZ -= cos(anguloCuboY * 3.14159265 / 180) * velocidadMovimiento;
		break;
	case 'a':
		posX -= sin((anguloCuboY - 90) * 3.14159265 / 180) * velocidadMovimiento;
		posZ += cos((anguloCuboY - 90) * 3.14159265 / 180) * velocidadMovimiento;
		break;
	case 'd':
		posX -= sin((anguloCuboY + 90) * 3.14159265 / 180) * velocidadMovimiento;
		posZ += cos((anguloCuboY + 90) * 3.14159265 / 180) * velocidadMovimiento;
		break;
	case 'q':
		anguloCuboY -= velocidadRotacion;
		break;
	case 'e':
		anguloCuboY += velocidadRotacion;
		break;
	case 27: // escape
		exit(0);
		break;
	}
	
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ancho, alto);
	glutCreateWindow("Cubo");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
