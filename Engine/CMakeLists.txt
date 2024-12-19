#II. ENGINE ->			[Application]->[Entry]->CLIENT
#0_Setup infomation
project(VIEngine VERSION 0.1)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

#1_Build VIEngine.lib -> active
file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/VIEngine/*.cpp CMAKE_CONFIGURE_DEPENDS)
add_library(${PROJECT_NAME} STATIC ${SRC_FILES} )


#2_Build VIEngine.dll -> nonActive
target_compile_definitions(${PROJECT_NAME} PUBLIC ON_VI_ENGINE DYNAMIC_LIB=0 DYNAMIC_BUILD=0)

#5_PCH build DLL ON_VI_ENGINE
#target_compile_definitions(${PROJECT_NAME} PUBLIC ON_VI_ENGINE DYNAMIC_LIB=0 DYNAMIC_BUILD=1)

#3_Add all of library
target_include_directories(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/VIEngine
	${CMAKE_SOURCE_DIR}/Vendors/include #add file vendor
	${CMAKE_SOURCE_DIR}/Vendors/glfw/include
)
#4.2_Add logger target link -> directory and library
#6.1_Add glfw target link -> library
target_link_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/Vendors/bin)
target_link_libraries(${PROJECT_NAME} PUBLIC spdlogd glfw)

#4.1_Add precompile_headers: pch.h
#6.2_Add precompile_headers: gl.h
target_precompile_headers(${PROJECT_NAME} PUBLIC 
	${CMAKE_CURRENT_SOURCE_DIR}/VIEngine/pch.h 
	${CMAKE_SOURCE_DIR}/Vendors/include/glad/gl.h
)