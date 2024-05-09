#include <GL/glut.h> 
#include <stdio.h> 

int x1, y1, x2, y2;

void reshape(int width, int height) 
{ 
	glViewport(0, 0, width, height); 
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(-100, 100, -100, 100, -100, 100); 
	glMatrixMode(GL_MODELVIEW); 
} 

void write_pixel(int x, int y)
{
	glBegin(GL_POINTS); 
	glVertex3f(x, y, 0); 
	glEnd(); 
}

void draw_axes()
{
	glColor3f(1.0f, 1.0f, 1.0f); 
	glBegin(GL_LINES);
	// Eje X
	glVertex2f(-100.0f, 0.0f);
	glVertex2f(100.0f, 0.0f);
	// Eje Y
	glVertex2f(0.0f, -100.0f);
	glVertex2f(0.0f, 100.0f);
	glEnd();
}

void draw_line(int x1, int y1, int x2, int y2)
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int incX, incY, incE, incNE, d, x, y;
	
	if (dx < 0) {
		dx = -dx;
		incX = -1;
	} else {
		incX = 1;
	}
	
	if (dy < 0) {
		dy = -dy;
		incY = -1;
	} else {
		incY = 1;
	}
	
	x = x1;
	y = y1;
	
	write_pixel(x, y);
	
	if (dx > dy) {
		d = 2 * dy - dx;
		incE = 2 * dy;
		incNE = 2 * (dy - dx);
		
		while (x != x2) {
			x += incX;
			
			if (d < 0) {
				d += incE;
			} else {
				y += incY;
				d += incNE;
			}
			
			write_pixel(x, y);
		}
	} else {
		d = 2 * dx - dy;
		incE = 2 * dx;
		incNE = 2 * (dx - dy);
		
		while (y != y2) {
			y += incY;
			
			if (d < 0) {
				d += incE;
			} else {
				x += incX;
				d += incNE;
			}
			
			write_pixel(x, y);
		}
	}
}

void display() 
{ 
	glClear(GL_COLOR_BUFFER_BIT); 
	glLoadIdentity(); 
	
	draw_axes();

	glColor3f(0,1,0); 
	draw_line(x1, y1, x2, y2);
	
	glFlush(); 
} 

void init() 
{ 
	glClearColor(0,0,0,0); 
} 

int main(int argc, char **argv) 
{ 
	printf("Ingresar x1, y1, x2, y2 \n");
	scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
	
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); 
	glutInitWindowPosition(50, 50); 
	glutInitWindowSize(500, 500); 
	glutCreateWindow("Hello OpenGL"); 
	init(); 
	glutDisplayFunc(display); 
	glutReshapeFunc(reshape); 
	glutMainLoop(); 
	return 0; 
}
