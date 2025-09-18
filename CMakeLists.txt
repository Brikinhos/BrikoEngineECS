cmake_minimum_required(VERSION 3.16)
project(BrikoEngineECS)

set(CMAKE_CXX_STANDARD 23)

# Genera compile_commands.json (para clangd)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Carpeta de includes
include_directories(${CMAKE_SOURCE_DIR}/src, ${CMAKE_SOURCE_DIR}/src/datastructs, ${CMAKE_SOURCE_DIR}/src/ecs)

# Busca todos los .cpp en src/
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

# Crea el ejecutable
add_executable(BrikoEngineECS ${SOURCES})
