cmake_minimum_required (VERSION 2.8)


# Nom du projet
project (hello)


find_package (OpenCV REQUIRED)


# Exécutable "hello", compilé à partir du fichier helloworld.c
add_executable (hello src/inversColor.c)


# Hello sera linké avec les bibliothèques d'OpenCV
target_link_libraries (hello ${OpenCV_LIBS})
