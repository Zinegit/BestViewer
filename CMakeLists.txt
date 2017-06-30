# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (MonProjet)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(Qt4 REQUIRED)
find_package(QGLViewer REQUIRED)
find_package(Boost COMPONENTS filesystem regex system REQUIRED)
find_package(OpenCV REQUIRED)

if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
	message( FATAL_ERROR "Please select another Build Directory !" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()

include_directories(
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
	${QT_INCLUDE_DIR}
	${QGLVIEWER_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
	.
)

INCLUDE(${QT_USE_FILE})

set(ALL_LIBS
	${OPENGL_LIBRARY}
	${GLEW_LIBRARIES}
	${QT_LIBRARIES}
	${QGLVIEWER_LIBRARY}
	${Boost_LIBRARIES}
        ${OpenCV_LIBRARIES}
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
	${QT_DEFINITIONS}
)

#MonProjet
file(
        GLOB_RECURSE
	SRC_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/external/I3S-Meshing/*.cpp"

)
list(REMOVE_ITEM SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/external/I3S-Meshing/main.cpp")
# Because of the presence of 2 main

file(
        GLOB_RECURSE
	INCLUDE_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/external/I3S-Meshing/*.h*"
)

file(
        GLOB_RECURSE
        SHADER_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vertexshader"
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.fragmentshader"
)

QT4_WRAP_CPP(INCLUDE_FILES_MOC ${INCLUDE_FILES})

add_executable(bestView
        "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
	${SRC_FILES}
	${INCLUDE_FILES_MOC}
	${INCLUDE_FILES}
	${SHADER_FILES}
)
target_compile_features(bestView
	PRIVATE
	cxx_range_for
)
target_link_libraries(bestView
	${ALL_LIBS}
)

