cmake_minimum_required(VERSION 3.15)

# Nombre del proyecto
project(BrikoEngineECS LANGUAGES CXX)

# Usa C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Genera compile_commands.json para clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Build tipo Debug por defecto si no se especifica
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Opciones de compilación para Debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")

# Especifica la ruta de SFML si no está en el sistema
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib/SFML-3.0.2/lib/cmake/SFML")

# Busca SFML 3 con los módulos que necesitas
find_package(SFML 3 REQUIRED COMPONENTS Graphics Window Audio Network)

# Busca recursivamente todos los .cpp en src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

# Opcional: añade también los headers para que aparezcan en el IDE
file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp"
)

# Define el ejecutable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS} # opcional, no compilan pero el IDE los muestra
)

# Incluye la carpeta src/ para los #include
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# Vincula SFML a tu proyecto
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        SFML::Graphics
        SFML::Window
        SFML::Audio
        SFML::Network
)

# Flags de compilación
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
