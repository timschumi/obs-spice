cmake_minimum_required(VERSION 3.10)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

project(obs-spice)

find_package(LibObs REQUIRED)
find_package(GLib REQUIRED)
find_package(GTK3 REQUIRED)
find_package(Spice REQUIRED)

if(NOT GLib_FOUND)
	message(FATAL_ERROR "GLIB2 is required for this project")
endif()

if (NOT GTK3_FOUND)
	message(FATAL_ERROR "GTK3 is required for this project")
endif()

if(NOT SPICE_FOUND)
	message(FATAL_ERROR "SPICE is required for this project")
endif()

set(obs-spice_SOURCES
	obs-spice.c
	obs-spice-source.c
)

add_library(obs-spice MODULE ${obs-spice_SOURCES})
target_include_directories(obs-spice
	PRIVATE ${GLib_INCLUDE_DIRS}
	PRIVATE ${GMODULE_INCLUDE_DIR}
	PRIVATE ${GTK3_INCLUDE_DIRS}
	PRIVATE ${SPICE_INCLUDE_DIRS}
)
target_link_libraries(obs-spice
	libobs
	${SPICE_LIBRARIES}
)

set_target_properties(obs-spice PROPERTIES PREFIX "")

file(GLOB locale_files data/locale/*.ini)
set(CMAKE_INSTALL_DEFAULT_DIRECTORY_PERMISSIONS
    OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_WRITE GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)

if("${INSTALL_AS_USER}")
	install(TARGETS obs-spice LIBRARY
	        DESTINATION "$ENV{HOME}/.config/obs-studio/plugins/obs-spice/bin/64bit"
	        PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
	install(FILES ${locale_files}
	        DESTINATION "$ENV{HOME}/.config/obs-studio/plugins/obs-spice/data/locale")
else()
	include(GNUInstallDirs)
	install(TARGETS obs-spice LIBRARY
	        DESTINATION "${CMAKE_INSTALL_FULL_LIBDIR}/obs-plugins"
			PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ)
	install(FILES ${locale_files}
	        DESTINATION "${CMAKE_INSTALL_FULL_DATAROOTDIR}/obs/obs-plugins/obs-spice/locale")
endif()
