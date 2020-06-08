#Hey oh, let's go !
import os
import matplotlib.pyplot as plt
import numpy as np

cycles = input("Nombre de cycles de calcul: ")
children = input("Nombre de descendants attendus: ")
name_file = input("Fichier à exploiter: ")

os.system("g++ -o test main.cpp")
command = "./test " + cycles + " " + children + " " + name_file;
os.system(command)

x, y = np.loadtxt('fitness_progression.out', delimiter='\t', unpack=True)
plt.plot(x,y, label='fitness value')

plt.xlabel('Cycle')
plt.ylabel('Fitness')
plt.title('Fitness evolution for each cycle')
plt.legend()
plt.show()