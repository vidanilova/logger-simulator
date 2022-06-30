cmake_minimum_required(VERSION 3.9)
set(PROJECT_NAME "logger-simulator")
project(${PROJECT_NAME} VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_library(LIB_LOGGER_HUFFMAN NAMES "logger-huffman" HINTS "../logger-huffman" "C:\\Users\\XE\\src\\logger-huffman\\build\\Release" "C:\\Users\\XE\\src\\logger-huffman\\build\\Debug")
set(EXTRA_LIBS ${LIB_LOGGER_HUFFMAN} Threads::Threads)

set(LOGGER_SIMULATOR_SRC
	main.cpp
	third_party/argtable3/argtable3.c
)

include_directories("third_party")
add_executable(logger-simulator ${LOGGER_SIMULATOR_SRC})
target_link_libraries(logger-simulator PRIVATE ${EXTRA_LIBS})

target_compile_definitions(logger-simulator PRIVATE ${EXTRA_DEFS})

INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/logger-simulator DESTINATION cmake)
INSTALL(FILES README.md LICENSE HISTORY COPYING TODO CODE_OF_CONDUCT.md CONTRIBUTING.md DESTINATION doc)

include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "1")
include(CPack)

unset(ENABLE_LOGGER_PASSPORT CACHE)
