#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

float dameX(float R, int N, int n);
float dameZ(float R, int N, int n);
void anillo(float R, float y, int N);
float fFiguraEsfera(float y);
float fFiguraCono(float y);
void FiguraAlambre(int N, float(*f)(float y));
void formaAlambre(float H, int N, float(*f)(float y));
void ReduceToUnit(float vector[3]);
void RenderShaft(void);

int formaElegida = 1;  // Variable para guardar la elección de la figura
float dameX(float R, int N, int n) 
{
	float x = (float) R * cos(n * (2 * M_PI) / N);
	return x;
}

float dameZ(float R, int N, int n) 
{
	float z = (float) R * sin(n * (2 * M_PI) / N);
	return z;
}

void anillo(float R, float y, int N) 
{
	int i;
	float x, z;
	
	glBegin(GL_LINE_LOOP);
	for(i = 0; i < N; i++) 
	{
		x = dameX(R, N, i);
		z = dameZ(R, N, i);
		glVertex3f(x, y, z);
	}
	glEnd();
}

float fFiguraEsfera(float y) 
{
	// Radio de la esfera
	float radioFigura = 50.0;
	// Calcula el radio en función de la altura usando la ecuación de la circunferencia
	return sqrt(radioFigura * radioFigura - y * y);
}

float fFiguraCono(float y) 
{
	// Altura total del cono
	float alturaTotal = 100.0;
	// Calcula el radio como una función lineal de la altura
	return (50.0 * (1.0 - (y + (alturaTotal / 2)) / alturaTotal));
}

void FiguraAlambre(int N, float(*f)(float y)) 
{
	formaAlambre(100.0f, N, f);
}

void formaAlambre(float H, int N, float(*f)(float y)) 
{
	int i;
	float y, r;    
	for(i = 0; i < N; i++) 
	{ 
		y = i * H / N - (H / 2);    // Para cada nivel de altura
		r = f(y);           // obtenemos el radio
		anillo(r, y, N);    // y dibujamos un anillo
	}
}

void Key (unsigned char tecla, int x, int y) 
{
	switch (tecla)
	{
	case 27 :
		exit (0);
		break;
	}
}

void display(void) 
{
	glClearColor (1.0,1.0,1.0, 1.0);
	glClear (GL_COLOR_BUFFER_BIT);
	glColor3f(1.0f, 0.0f, 0.0f);
	glLoadIdentity ();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, -4.0f);
	glRotatef(15.0f, 1.0f, 0.0f, 0.0f);
	
	if (formaElegida == 1)
	{
		FiguraAlambre(20, fFiguraCono);
	}
	else if (formaElegida == 2)
	{
		FiguraAlambre(20, fFiguraEsfera);
	}
	
	glPopMatrix();
	glFlush ();
}

void inicializaVista(void) 
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0f, 100.0f, -100.0f, 100.0f, -100.0f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int width, int height) 
{
	glViewport (0, 0, width, height);
	inicializaVista ();
}

void inicializaVentana(int argc, char **argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize (700, 700);
	glutInitWindowPosition (200, 30);
	glutCreateWindow (argv[0]);
	glutDisplayFunc (display);
	glutReshapeFunc (reshape);
}

void iniciaOpenGL(int argc, char **argv) 
{
	inicializaVentana (argc, argv);
	inicializaVista ();
	glutMainLoop();
}


int main (int argc, char** argv) 
{	
		printf("Seleccione la figura a dibujar \n\n1 para cono \n2 para esfera\n\nEleccion--> ");
		scanf("%d", &formaElegida);
		
		if (formaElegida != 1 && formaElegida != 2) {
			printf("Opción no válida. Se dibujará un cono por defecto.\n");
			formaElegida = 1;
		}
	
	iniciaOpenGL(argc, argv);
	return (1);
}
