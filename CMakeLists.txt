cmake_minimum_required(VERSION 3.10)

# Имя проекта
project(Writer)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указание директорий с заголовочными файлами
include_directories(
    include
)

# Укажите исходные файлы вашего проекта
set(SOURCE_FILES
    src/main.cpp
    src/writer.cpp
    src/format.cpp
    src/writeobj.cpp
    src/streamw.cpp
)

# Добавление исполняемого файла
add_executable(Writer ${SOURCE_FILES})
