#include <GL/glut.h>

GLfloat anguloX = 0.0f;
GLfloat anguloY = 0.0f;
GLfloat angulo = 0.0f;
GLint ancho, alto;
int hazPerspectiva = 1;

// Parámetros de la proyección ortogonal
GLfloat orthoLeft = -4.0f, orthoRight = 4.0f, orthoBottom = -4.0f, orthoTop = 4.0f, orthoZNear = 1.0f, orthoZFar = 7.0f;
// Parámetros de la proyección en perspectiva
GLfloat perspectiveAngle = 45.0f, perspectiveZNear = 1.0f, perspectiveZFar = 4.8f;

void reshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	if (hazPerspectiva)
		gluPerspective(perspectiveAngle, (GLfloat)width / (GLfloat)height, perspectiveZNear, perspectiveZFar);
	else
		glOrtho(orthoLeft, orthoRight, orthoBottom, orthoTop, orthoZNear, orthoZFar);
	
	glMatrixMode(GL_MODELVIEW);
	
	ancho = width;
	alto = height;
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -5.0f);
	
	glRotatef(anguloX, 1.0f, 0.0f, 0.0f);
	glRotatef(anguloY, 0.0f, 1.0f, 0.0f);
	glutWireTeapot(1.5f);
	
	glLoadIdentity();
	
	glTranslatef(0.0f, 0.0f, -5.0f);
	glRotatef(angulo, 0.0f, 1.0f, 0.0f);
	glTranslatef(3.0f, 0.0f, 0.0f);
	
	glColor3f(1.0f, 1.0f, 1.0f);
	
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

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'p':
	case 'P':
		hazPerspectiva = 1;
		reshape(ancho, alto);
		break;
		
	case 'o':
	case 'O':
		hazPerspectiva = 0;
		reshape(ancho, alto);
		break;
		
		// Modificación de parámetros ortogonales
	case 'i':
		orthoLeft -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'd':
		orthoRight += 0.1f;
		reshape(ancho, alto);
		break;
	case 'a':
		orthoBottom -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'u':
		orthoTop += 0.1f;
		reshape(ancho, alto);
		break;
	case 'n':
		orthoZNear -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'N':
		orthoZNear += 0.1f;
		reshape(ancho, alto);
		break;
	case 'f':
		orthoZFar -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'F':
		orthoZFar += 0.1f;
		reshape(ancho, alto);
		break;
		
		// Modificación de parámetros de perspectiva
	case 'b':
		perspectiveAngle -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'B':
		perspectiveAngle += 0.1f;
		reshape(ancho, alto);
		break;
	case 'm':
		perspectiveZNear -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'M':
		perspectiveZNear += 0.1f;
		reshape(ancho, alto);
		break;
	case 'k':
		perspectiveZFar -= 0.1f;
		reshape(ancho, alto);
		break;
	case 'K':
		perspectiveZFar += 0.1f;
		reshape(ancho, alto);
		break;
		
	case 27: // escape
		exit(0);
		break;
	}
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(ancho, alto);
	glutCreateWindow("Tetera");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
