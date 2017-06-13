cmake_minimum_required (VERSION 2.8)


# Nom du projet
project (datas)


find_package (OpenCV REQUIRED)


# Creation of executable for the raspberry pi
add_executable (datas src/rasp/main.c src/rasp/imageProcessing/imageUtility.c src/serial/Serial.c src/rasp/imageProcessing/saveLoad.c src/rasp/server/server.c)

# Creation of executable for the client
add_executable (client src/controllerComputer/main.c src/controllerComputer/client.c)


#Creation of executable for test
add_executable (serial tests/serialTest.c src/serial/Serial.c src/rasp/imageProcessing/imageUtility.c src/rasp/imageProcessing/saveLoad.c)
add_executable (comparison tests/comparison.c src/rasp/recognition/recognition.c src/rasp/imageProcessing/imageUtility.c src/serial/Serial.c src/rasp/imageProcessing/saveLoad.c)
add_executable (compass tests/compass_test.c src/serial/Serial.c)

# Linking with opencv and math.h
target_link_libraries (datas ${OpenCV_LIBS} m)
target_link_libraries (serial ${OpenCV_LIBS} m)
target_link_libraries (comparison ${OpenCV_LIBS} m)
