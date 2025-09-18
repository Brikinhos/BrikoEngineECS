cmake_minimum_required(VERSION 3.15)

# Nombre del proyecto
project(BrikoEngineECS LANGUAGES CXX)

# Usa C++20 (cámbialo si quieres otra versión)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Genera compile_commands.json para clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Busca recursivamente todos los .cpp en src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# (Opcional) Añadimos también los headers para que aparezcan en el IDE
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS} # opcional, no compilan pero VSCode/IDE los muestra
)

# Incluye la carpeta src/ para que #include "loquesea.hpp" funcione
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Puedes añadir flags de compilación si quieres
# target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
