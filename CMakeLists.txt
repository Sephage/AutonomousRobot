cmake_minimum_required (VERSION 2.8)


# Nom du projet
project (datas)


find_package (OpenCV REQUIRED)


# Exécutable "hello", compilé à partir du fichier helloworld.c
add_executable (datas src/rasp/main.c src/rasp/imageProcessing/imageUtility.c)


add_executable (serial tests/serialTest.c src/serial/Serial.c)

# Hello sera linké avec les bibliothèques d'OpenCV
target_link_libraries (datas ${OpenCV_LIBS})
