import serial
import numpy as np
import matplotlib.pyplot as plt

# CAMBIA EL PUERTO SI ES NECESARIO
ser = serial.Serial('COM3', 115200)

plt.ion()
fig = plt.figure(figsize=(7,7))
ax = fig.add_subplot(111, projection='polar')
ax.set_theta_zero_location("W")
ax.set_theta_direction(-1)
ax.set_ylim(0, 100) # Rango máximo de 100cm

# Lista para guardar los puntos detectados
puntos_detectados = []

print("Radar básico iniciado. Escaneando...")

while True:
    if ser.in_waiting:
        linea = ser.readline().decode('utf-8').strip()
        if "," in linea:
            try:
                ang, dist = map(int, linea.split(','))
                
                # Si detecta algo entre 5cm y 90cm, lo guarda
                if 5 < dist < 90:
                    rad = np.radians(ang)
                    puntos_detectados.append((rad, dist))
                    
                    # Dibujar todos los puntos guardados
                    ax.clear()
                    ax.set_theta_zero_location("W")
                    ax.set_theta_direction(-1)
                    ax.set_ylim(0, 100)
                    
                    for p in puntos_detectados:
                        ax.plot(p[0], p[1], 'ro', markersize=5)
                        
                    fig.canvas.draw()
                    fig.canvas.flush_events()
            except: pass