import cv2
import numpy as np
import math

# Función para extraer la línea del láser de una imagen
def extraer_linea_laser(frame):
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    rojo_bajo = np.array([0, 100, 100])
    rojo_alto = np.array([10, 255, 255])
    mascara = cv2.inRange(hsv, rojo_bajo, rojo_alto)
    bordes = cv2.Canny(mascara, 50, 150)
    puntos_laser = np.column_stack(np.where(bordes > 0))
    return puntos_laser

# Función para capturar y procesar imágenes
def capturar_y_procesar_frames(pasos):
    cap = cv2.VideoCapture(0)
    if not cap.isOpened():
        print("Error al abrir la cámara")
        return []

    puntos_laser_3d = []

    for i in range(pasos):
        ret, frame = cap.read()
        if not ret:
            print("Error al capturar el frame")
            break

        linea_laser = extraer_linea_laser(frame)

        # Calcular coordenadas 3D (esto es un ejemplo y necesita ajustes específicos)
        for punto in linea_laser:
            x = punto[1] / frame.shape[1] * 2 - 1
            y = punto[0] / frame.shape[0] * 2 - 1
            angulo = i / pasos * 360
            z = math.sin(math.radians(angulo))

            puntos_laser_3d.append((x, y, z))

        cv2.imshow("Frame", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    cap.release()
    cv2.destroyAllWindows()
    return puntos_laser_3d

# Guardar los puntos 3D en un archivo
def guardar_puntos(puntos, nombre_archivo):
    with open(nombre_archivo, 'w') as f:
        for punto in puntos:
            f.write(f"{punto[0]} {punto[1]} {punto[2]}\n")

def main():
    pasos = 360  # Número de pasos de rotación
    puntos_laser_3d = capturar_y_procesar_frames(pasos)
    guardar_puntos(puntos_laser_3d, 'laser_points.txt')

if __name__ == "__main__":
    main()
