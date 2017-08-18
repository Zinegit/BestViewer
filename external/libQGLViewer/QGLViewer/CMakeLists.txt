PROJECT(QGLViewer)
FIND_PACKAGE(OpenGL REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS Core Gui Widgets Xml OpenGL REQUIRED)

# in order to be able to include generated files (ui and moc)
include_directories(
    ${CMAKE_CURRENT_BINARY_DIR}
    )

set(HEADER_FILES
	qglviewer.h
	camera.h
	manipulatedFrame.h
	manipulatedCameraFrame.h
	frame.h
	keyFrameInterpolator.h
	)

set(SOURCE_FILES
	qglviewer.cpp
	camera.cpp
	manipulatedFrame.cpp
	manipulatedCameraFrame.cpp
	frame.cpp
	saveSnapshot.cpp
	constraint.cpp
	keyFrameInterpolator.cpp
	mouseGrabber.cpp
	quaternion.cpp
	vec.cpp
	VRender/BackFaceCullingOptimizer.cpp
	VRender/EPSExporter.cpp
	VRender/FIGExporter.cpp
	VRender/NVector3.cpp
	VRender/Primitive.cpp
	VRender/TopologicalSortMethod.cpp
	VRender/Vector3.cpp
	VRender/VRender.cpp
	VRender/BSPSortMethod.cpp
	VRender/Exporter.cpp
	VRender/gpc.cpp
	VRender/ParserGL.cpp
	VRender/PrimitivePositioning.cpp
	VRender/Vector2.cpp
	VRender/VisibilityOptimizer.cpp
	)

set(UI_FILES
	ImageInterface.ui
	VRenderInterface.ui
	)

 qt5_wrap_ui(UI_FILES_MOC ${UI_FILES})

# these header files do not need MOCcing
list(APPEND HEADER_FILES
	config.h
	constraint.h
	domUtils.h
	mouseGrabber.h
	quaternion.h
	vec.h
	VRender/AxisAlignedBox.h
	VRender/Exporter.h
	VRender/gpc.h
	VRender/NVector3.h
	VRender/Optimizer.h
	VRender/ParserGL.h
	VRender/Primitive.h
	VRender/PrimitivePositioning.h
	VRender/SortMethod.h
	VRender/Types.h
	VRender/Vector2.h
	VRender/Vector3.h
	VRender/VRender.h
        )

include_directories("..")

if(WIN32)
    ADD_DEFINITIONS(-DCREATE_QGLVIEWER_DLL -DNOMINMAX)
else()
	ADD_DEFINITIONS(-fPIC)
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")

add_library(QGLViewer SHARED ${HEADER_FILES} ${SOURCE_FILES} ${UI_FILES_MOC})

target_link_libraries(QGLViewer
    ${OPENGL_LIBRARY}
    Qt5::Gui
    Qt5::Widgets
    Qt5::Xml
    Qt5::OpenGL)
