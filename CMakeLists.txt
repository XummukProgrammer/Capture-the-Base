cmake_minimum_required(VERSION 3.8.2)

project(Capture-the-Base)

set(CMAKE_CXX_STANDARD 17)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT Capture-the-Base)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML COMPONENTS audio graphics main network system window REQUIRED)

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/pugixml" "${CMAKE_CURRENT_BINARY_DIR}/libs/pugixml")
set_target_properties(pugixml-static PROPERTIES FOLDER "libs")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/fmt" "${CMAKE_CURRENT_BINARY_DIR}/libs/fmt")
set_target_properties(fmt PROPERTIES FOLDER "libs")

add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/libs/entt" "${CMAKE_CURRENT_BINARY_DIR}/libs/entt")
set_target_properties(EnTT PROPERTIES FOLDER "libs")

include(cmake/src.cmake)
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}/src" FILES ${GAME_HEADERS} ${GAME_SOURCES})
add_executable(Capture-the-Base ${GAME_HEADERS} ${GAME_SOURCES})
target_include_directories(Capture-the-Base PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")
target_link_libraries(Capture-the-Base PUBLIC 
	sfml-audio
	sfml-graphics
	sfml-main
	sfml-network
	sfml-system
	sfml-window
	pugixml-static
	fmt
	EnTT
)

set(GAME_BIN_DIR "${CMAKE_CURRENT_SOURCE_DIR}/bin/$<$<BOOL:FALSE>:>")

set_target_properties(Capture-the-Base PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${GAME_BIN_DIR}
	DEBUG_POSTFIX "_d"
	CXX_STANDARD 17 CXX_STANDARD_REQUIRED ON
)

set(SFML_BIN "${SFML_DIR}/../../../bin")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy
	${SFML_BIN}/openal32.dll $<TARGET_FILE_DIR:${PROJECT_NAME}>)
