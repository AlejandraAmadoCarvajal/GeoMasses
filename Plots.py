from numpy import genfromtxt, linspace, min, max
import matplotlib.pyplot as plt

##### Extracion de datos ####
datos_binarios = genfromtxt('datos.dat', delimiter=',')
datos_originales = genfromtxt("RadialVelocities.dat", delimiter=' ')
datos_originales = datos_originales[1:,:]
datos_binarios = datos_binarios[1:,:]

min_rang = min(datos_originales[:,0])
max_rang = max(datos_originales[:,0])
n = len(datos_originales)

r = linspace(min_rang, max_rang, n)

### Plot
plt.plot(datos_originales[:,0], datos_originales[:,1])
Mb = datos_binarios[-1,0]
Md = datos_binarios[-1,1]
Mh = datos_binarios[-1,2]
velocidad_modelo = Mb**0.5*r/(r**2+0.2497**2)**0.75 + Md**0.5*r/( r**2+(5.16+0.3105)**2)**0.75 + Mh**0.5/(r**2+64.3**2)**0.25

## PLOT 2
plt.plot(r, velocidad_modelo, color="red")
plt.legend(['Datos', 'Modelo'])
plt.xlabel('r'); plt.ylabel('Velocidad [km/s]')
plt.savefig('grafica.png')
