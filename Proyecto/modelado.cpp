#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

// Puntos 3D del láser
std::vector<std::vector<float>> laserPoints3D;

// Función para leer puntos 3D desde un archivo
void readPoints(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error al abrir el archivo " << filename << std::endl;
		return;
	}
	
	std::string line;
	while (std::getline(file, line)) {
		std::istringstream iss(line);
		float x, y, z;
		if (!(iss >> x >> y >> z)) {
			break;
		}
		laserPoints3D.push_back({x, y, z});
	}
}

// Función de renderización de OpenGL
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for (const auto& point : laserPoints3D) {
		glVertex3f(point[0], point[1], point[2]);
	}
	glEnd();
	
	glutSwapBuffers();
}

// Inicializar OpenGL
void initOpenGL() {
	glEnable(GL_DEPTH_TEST);
	glPointSize(2.0f);
}

// Función principal
int main(int argc, char** argv) {
	if (argc < 2) {
		std::cerr << "Uso: " << argv[0] << " <archivo_de_puntos>" << std::endl;
		return 1;
	}
	readPoints(argv[1]);  // Leer puntos desde el archivo
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Scanner Visualization");
	initOpenGL();
	glutDisplayFunc(display);
	glutMainLoop();
	
	return 0;
}

