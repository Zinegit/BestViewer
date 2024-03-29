
# CMake entry point
cmake_minimum_required (VERSION 2.8.12)

project (BestViewer)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(Qt5 COMPONENTS Core Gui Widgets Xml OpenGL REQUIRED)
find_package(Eigen3 REQUIRED)

add_subdirectory(
	"${CMAKE_SOURCE_DIR}/external/libQGLViewer/QGLViewer"
		"${CMAKE_SOURCE_DIR}/external/libQGLViewer/QGLViewer/build"
)

find_package(Boost COMPONENTS filesystem regex system REQUIRED)

if(APPLE)
	set("OpenCV_DIR" "/usr/local/Cellar/opencv3/3.2.0/share/OpenCV/")
endif(APPLE)
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

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

include_directories(
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
	"${CMAKE_CURRENT_SOURCE_DIR}/external/I3S-Meshing/include/"
	"${CMAKE_CURRENT_SOURCE_DIR}/external/libQGLViewer/"
	${CMAKE_CURRENT_BINARY_DIR}
		.
)

set(ALL_LIBS
	${OPENGL_LIBRARY}
	${GLEW_LIBRARIES}
	QGLViewer
	${OpenCV_LIBRARIES}
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

#BestViewer
file(
	GLOB
	SRC_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/external/I3S-Meshing/src/*.cpp"
)

file(
	GLOB
	INCLUDE_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*"
	"${CMAKE_CURRENT_SOURCE_DIR}/*.h"
	"${CMAKE_CURRENT_SOURCE_DIR}/external/I3S-Meshing/include/*.h*"
)


file(
	GLOB
	SHADER_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.vert"
	"${CMAKE_CURRENT_SOURCE_DIR}/shaders/*.frag"
)

file(
	GLOB
	UI_FILES
	"${CMAKE_CURRENT_SOURCE_DIR}/forms/*.ui"
)

qt5_wrap_ui(UI_FILES_MOC ${UI_FILES})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -O3")

add_executable(bestView
	"${CMAKE_CURRENT_SOURCE_DIR}/src/main/main.cpp"
	${SRC_FILES}
	${INCLUDE_FILES}
	${SHADER_FILES}
	${UI_FILES_MOC}
)

#add_executable(bestViewServer
#	"${CMAKE_CURRENT_SOURCE_DIR}/src/main/mainServer.cpp"
#		${SRC_FILES}
#	${INCLUDE_FILES}
#	${SHADER_FILES}
#)

target_link_libraries(bestView
	${ALL_LIBS}
	Qt5::Gui
	Qt5::Widgets
	Qt5::Xml
	Qt5::OpenGL
)

#target_link_libraries(bestViewServer
#${ALL_LIBS}
#)
