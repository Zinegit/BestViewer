# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (MonProjet)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)
find_package(Qt5Widgets)
find_package(Qt5Xml)
find_package(Qt5OpenGL)
find_package(QGLViewer REQUIRED)
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

include_directories(
	${OPENGL_INCLUDE_DIR}
	${GLEW_INCLUDE_DIRS}
	${GLM_INCLUDE_DIRS}
	${Qt5Widgets_INCLUDE_DIRS}
	${Qt5Xml_INCLUDE_DIRS}
	${Qt5OpenGL_INCLUDE_DIRS}
	${QGLVIEWER_INCLUDE_DIR}
	${Boost_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
	.
)

INCLUDE(${QT_USE_FILE})

set(ALL_LIBS
	${OPENGL_LIBRARY}
	${GLEW_LIBRARIES}
	${Qt5Widgets_LIBRARIES}
	${Qt5Xml_LIBRARIES}
	${Qt5OpenGL_LIBRARIES}
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
	${Qt5Widgets_DEFINITIONS}
	${Qt5Xml_DEFINITIONS}
	${Qt5OpenGL_DEFINITIONS}
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

# QT5_WRAP_CPP(INCLUDE_FILES_MOC ${INCLUDE_FILES})

add_executable(bestView
  "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
	${SRC_FILES}
	${INCLUDE_FILES_MOC}
	${INCLUDE_FILES}
	${SHADER_FILES}
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11
	${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}
	${Qt5Xml_EXECUTABLE_COMPILE_FLAGS}
	${Qt5OpenGL_EXECUTABLE_COMPILE_FLAGS}")

target_link_libraries(bestView ${ALL_LIBS})
