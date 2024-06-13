#include <GL/glut.h>
#include <GL/glu.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

// Puntos 3D del láser
std::vector<std::vector<float>> laserPoints3D;
float centroid[3] = {0.0, 0.0, 0.0};
float scale = 1.0;

// Variables de rotación
float rotateX = 0.0;
float rotateY = 0.0;
int prevMouseX, prevMouseY;
bool leftMouseButtonDown = false;

// Función para leer puntos 3D desde un archivo
void readPoints(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		std::cerr << "Error al abrir el archivo " << filename << std::endl;
		return;
	}
	
	std::string line;
	float minX = std::numeric_limits<float>::max();
	float minY = std::numeric_limits<float>::max();
	float minZ = std::numeric_limits<float>::max();
	float maxX = std::numeric_limits<float>::min();
	float maxY = std::numeric_limits<float>::min();
	float maxZ = std::numeric_limits<float>::min();
	
	while (std::getline(file, line)) {
		// Solo procesar líneas que comiencen con 'v '
		if (line.rfind("v ", 0) == 0) {
			std::istringstream iss(line.substr(2)); // Ignorar 'v '
			float x, y, z;
			if (iss >> x >> y >> z) {
				laserPoints3D.push_back({x, y, z});
				if (x < minX) minX = x;
				if (y < minY) minY = y;
				if (z < minZ) minZ = z;
				if (x > maxX) maxX = x;
				if (y > maxY) maxY = y;
				if (z > maxZ) maxZ = z;
			}
		}
	}
	
	// Calcular el centroide
	centroid[0] = (minX + maxX) / 2.0f;
	centroid[1] = (minY + maxY) / 2.0f;
	centroid[2] = (minZ + maxZ) / 2.0f;
	
	// Calcular la escala
	float maxDistanceX = maxX - minX;
	float maxDistanceY = maxY - minY;
	float maxDistanceZ = maxZ - minZ;
	float maxDistance = std::max(std::max(maxDistanceX, maxDistanceY), maxDistanceZ);
	scale = 1.0f / maxDistance;
}

// Función de renderización de OpenGL
void display() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // Ajustar la posición de la cámara
	
	// Aplicar rotaciones
	glRotatef(rotateX, 1.0, 0.0, 0.0);
	glRotatef(rotateY, 0.0, 1.0, 0.0);
	
	glBegin(GL_POINTS);
	glColor3f(1.0, 0.0, 0.0);
	for (const auto& point : laserPoints3D) {
		glVertex3f((point[0] - centroid[0]) * scale, (point[1] - centroid[1]) * scale, (point[2] - centroid[2]) * scale);
	}
	glEnd();
	
	glutSwapBuffers();
}

// Inicializar OpenGL
void initOpenGL() {
	glEnable(GL_DEPTH_TEST);
	glPointSize(2.0f);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Fondo negro
}

// Función para redimensionar la ventana
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 500.0); // Ajustar perspectiva
	glMatrixMode(GL_MODELVIEW);
}

// Función de temporizador para redibujar
void timer(int) {
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0); // Aproximadamente 60 FPS
}

// Función para manejar eventos del mouse
void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) {
			leftMouseButtonDown = true;
			prevMouseX = x;
			prevMouseY = y;
		} else if (state == GLUT_UP) {
			leftMouseButtonDown = false;
		}
	}
}

// Función para manejar el movimiento del mouse
void motion(int x, int y) {
	if (leftMouseButtonDown) {
		rotateY += (x - prevMouseX) * 0.5f;
		rotateX += (y - prevMouseY) * 0.5f;
		prevMouseX = x;
		prevMouseY = y;
	}
}

// Función principal
int main(int argc, char** argv) {
	std::string filename = "C:\\Users\\PC\\Desktop\\laser_points.txt"; // Ruta al archivo ATV.txt
	readPoints(filename);  // Leer puntos desde el archivo
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("3D Scanner Visualization");
	initOpenGL();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutTimerFunc(0, timer, 0);
	glutMainLoop();
	
	return 0;
}
