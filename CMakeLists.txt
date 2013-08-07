
cmake_minimum_required(VERSION 2.8)

project(items)
find_package(Qt5Core REQUIRED)

set(SOURCE_LIB constructor.cpp  factory.cpp)
set(HEADER_LIB constructor.h  factory.h  item.h)

QT5_WRAP_CPP(HEADERS_MOC ${HEADER_LIB})

INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS})
ADD_DEFINITIONS(${QT_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Core_EXECUTABLE_COMPILE_FLAGS}")

add_library(itemsS STATIC ${SOURCE_LIB} ${HEADERS_MOC})
add_library(items SHARED ${SOURCE_LIB} ${HEADERS_MOC})

set_target_properties(items PROPERTIES
	  VERSION 1.0.0
	  SOVERSION 1.0
	)

INSTALL(TARGETS itemsS items
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

INSTALL(FILES ${HEADER_LIB} 
	DESTINATION include)
