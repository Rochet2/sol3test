project(testproj)

if (MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
else ()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-long-long -Wno-format-security")
endif ()

set(CMAKE_MACOSX_RPATH 1)
set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
add_definitions(-DSOL_CHECK_ARGUMENTS)

add_subdirectory(lua51)
add_subdirectory(sol)

file(GLOB LOCAL_SOURCES
	*.c *.cpp *.h *.hpp
)
add_executable(test "${LOCAL_SOURCES}")
target_include_directories(test PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(test lualib sol)

if (MSVC)
else ()
  target_link_libraries(test ${CMAKE_DL_LIBS} m)
endif ()

if (MSVC)
  install(TARGETS test DESTINATION "${CMAKE_INSTALL_PREFIX}")
  install(FILES $<TARGET_PDB_FILE:test> DESTINATION "${CMAKE_INSTALL_PREFIX}" OPTIONAL)
  #set_target_properties(test PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$(OutDir)")
else()
  install(TARGETS test DESTINATION "${CMAKE_INSTALL_PREFIX}/bin")
endif ()
