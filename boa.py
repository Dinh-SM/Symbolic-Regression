#Hey
import subprocess

cycles = input("Nombre de cycles de calcul: ")
children = input("Nombre de descendants attendus: ")
name_file = input("Fichier à exploiter: ")

subprocess.Popen("g++ -o test main.cpp")
command = "./test " + cycles + " " + children + " " + name_file;
print(command)
subprocess.Popen(command)
