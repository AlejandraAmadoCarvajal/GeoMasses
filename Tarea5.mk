Results_hw5.pdf: grafica.png
		pdflatex Results_hw5.tex

grafica.png: datos.dat
		python Plots.py

datos.dat: CurvaRotacion.c
		gcc CurvaRotacion.c -lm -o CurvaRotacion.out
			./CurvaRotacion.out

clean:
		rm *.tarea *.png *.log *.aux
