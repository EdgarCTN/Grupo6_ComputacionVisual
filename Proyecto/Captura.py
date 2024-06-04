import cv2
import numpy as np
import math

# Función para extraer la línea del láser de una imagen
def extract_laser_line(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    lower_red = np.array([0, 100, 100])
    upper_red = np.array([10, 255, 255])
    mask = cv2.inRange(hsv, lower_red, upper_red)
    edges = cv2.Canny(mask, 50, 150)
    laser_points = np.column_stack(np.where(edges > 0))
    return laser_points

# Función para capturar y procesar imágenes
def capture_and_process_frames(steps):
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("Error al abrir la cámara")
        return []

    laser_points_3d = []

    for i in range(steps):
        ret, frame = cap.read()
        if not ret:
            print("Error al capturar el frame")
            break

        laser_line = extract_laser_line(frame)

        # Calcular coordenadas 3D (esto es un ejemplo y necesita ajustes específicos)
        for point in laser_line:
            x = point[1] / frame.shape[1] * 2 - 1
            y = point[0] / frame.shape[0] * 2 - 1
            angle = i / steps * 360
            z = math.sin(math.radians(angle))

            laser_points_3d.append((x, y, z))

        cv2.imshow("Frame", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
    return laser_points_3d

# Guardar los puntos 3D en un archivo
def save_points(points, filename):
    with open(filename, 'w') as f:
        for point in points:
            f.write(f"{point[0]} {point[1]} {point[2]}\n")

def main():
    steps = 360  # Número de pasos de rotación
    laser_points_3d = capture_and_process_frames(steps)
    save_points(laser_points_3d, 'laser_points.txt')

if __name__ == "__main__":
    main()
