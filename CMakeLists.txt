cmake_minimum_required(VERSION 3.9)

project (Font-Renderer)

# list the header files
set(HEADER_FILES
	include/fontstash.h
	include/ShaderProgram.h
	include/stb_truetype.h
	include/FontLib.h
)

# list the source files
set(SOURCE_FILES
	src/main.cpp
	src/ShaderProgram.cpp
)

# add library target
add_executable(Font-Renderer
	${HEADER_FILES}
	${SOURCE_FILES}
)

# make it reflect the same structure as the one on disk
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADER_FILES})
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SOURCE_FILES})

target_link_libraries(Font-Renderer
	PUBLIC
		opengl32
		glew32
		glfw3
)


if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")

	add_custom_command(
    TARGET Font-Renderer POST_BUILD
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/x64/glew32.dll
	$<TARGET_FILE_DIR:Font-Renderer>
)
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "4")
add_custom_command(
    TARGET Font-Renderer POST_BUILD
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/bin/Win32/glew32.dll
	$<TARGET_FILE_DIR:Font-Renderer>
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/Alin_Square_Emoji.ttf
	$<TARGET_FILE_DIR:Font-Renderer>
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSansArabic.ttf
	$<TARGET_FILE_DIR:Font-Renderer>
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSansJapanese.ttf
	$<TARGET_FILE_DIR:Font-Renderer>
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSerif-Italic.ttf
	$<TARGET_FILE_DIR:Font-Renderer>
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSerif-Regular.ttf
	$<TARGET_FILE_DIR:Font-Renderer>
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/emoticons.otf
	$<TARGET_FILE_DIR:Font-Renderer>
	
		COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/Alin_Square_Emoji.ttf
	${CMAKE_CURRENT_BINARY_DIR}
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSansArabic.ttf
	${CMAKE_CURRENT_BINARY_DIR}
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSansJapanese.ttf
	${CMAKE_CURRENT_BINARY_DIR}
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSerif-Italic.ttf
	${CMAKE_CURRENT_BINARY_DIR}
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/DroidSerif-Regular.ttf
	${CMAKE_CURRENT_BINARY_DIR}
	
	COMMAND ${CMAKE_COMMAND} -E copy 
	${CMAKE_CURRENT_SOURCE_DIR}/resources/emoticons.otf
	${CMAKE_CURRENT_BINARY_DIR}
)

ENDIF()


if(WIN32)
	target_compile_definitions(Font-Renderer
		PRIVATE
			OS_WINDOWS=1
	)
	target_compile_options(Font-Renderer
		PRIVATE
			/WX
	)
endif(WIN32)

# enable C++17
# disable any compiler specifc extensions
# add d suffix in debug mode
target_compile_features(Font-Renderer PUBLIC cxx_std_17)
set_target_properties(Font-Renderer PROPERTIES
	CXX_EXTENSIONS OFF
)


# list include directories
target_include_directories(Font-Renderer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/include/Renderer3D
	${CMAKE_CURRENT_SOURCE_DIR}/external/
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/include
	${CMAKE_CURRENT_SOURCE_DIR}/external/glm
	${CMAKE_CURRENT_SOURCE_DIR}/external/stb_image
	${CMAKE_CURRENT_SOURCE_DIR}/resources
)

# list Libs directories
if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 64 bits")
	target_link_directories (Font-Renderer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/x64
    ${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/$<CONFIG>/x64lib/
)	
else("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
	message(STATUS "Target is 32 bits")
		target_link_directories (Font-Renderer
	PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/external/glew/lib/Win32
	${CMAKE_CURRENT_SOURCE_DIR}/external/glfw/lib/$<CONFIG>/win32lib/
)
ENDIF()
