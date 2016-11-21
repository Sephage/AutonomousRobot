cmake_minimum_required (VERSION 2.8)


# Nom du projet
project (datas)


find_package (OpenCV REQUIRED)


# Exécutable "hello", compilé à partir du fichier helloworld.c
add_executable (datas src/main.c src/imageUtility.c)


# Hello sera linké avec les bibliothèques d'OpenCV
target_link_libraries (datas ${OpenCV_LIBS})
