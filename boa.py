#Hey
import os

cycles = input("Nombre de cycles de calcul: ")
children = input("Nombre de descendants attendus: ")
name_file = input("Fichier à exploiter: ")

os.system("g++ -o test main.cpp")
command = "./test " + cycles + " " + children + " " + name_file;
os.system(command)
