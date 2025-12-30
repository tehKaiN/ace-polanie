cmake_minimum_required(VERSION 3.14.0)
project(polanie)

if(NOT AMIGA)
	message(SEND_ERROR "This project only compiles for Amiga")
endif()

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

# ACE
add_compile_definitions(FIXMATH_NO_OVERFLOW)
set(AUDIO_MIXER_HW_CHANNEL_MODE "SINGLE")
set(AUDIO_MIXER_WORD_SIZED ON)
set(AUDIO_MIXER_ROUND_TO_32 ON)
set(AUDIO_MIXER_PROFILER OFF)
set(AUDIO_MIXER_HW_CHANNELS 3)
set(AUDIO_MIXER_SW_CHANNEL_COUNT 3)
set(AUDIO_MIXER_PERIOD 161)
set(ACE_BOB_PRISTINE_BUFFER ON)
set(ACE_BOB_WRAP_Y OFF)
add_subdirectory(deps/ace ace)
add_subdirectory(deps/ace_audio_mixer ace_audio_mixer)
file(GLOB_RECURSE GAME_src src/*.c src/*.cpp src/*.h)

set(GAME_EXECUTABLE_STEM polanie)
if(ELF2HUNK)
	set(GAME_EXECUTABLE ${GAME_EXECUTABLE_STEM}.elf)
	set(GAME_OUTPUT_EXECUTABLE ${GAME_EXECUTABLE_STEM}.exe)
	add_executable(${GAME_EXECUTABLE} ${GAME_src})
	target_link_options(${GAME_EXECUTABLE} PUBLIC -Wno-attributes)
	target_link_libraries(${GAME_EXECUTABLE} -Wl,-Map=${GAME_EXECUTABLE_STEM}.map)

	if (CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
		set(ELF2HUNK_EXTRA_OPTS "-s")
	endif()

	add_custom_command(
		TARGET ${GAME_EXECUTABLE} POST_BUILD
		COMMAND ${ELF2HUNK} ${GAME_EXECUTABLE} ${GAME_OUTPUT_EXECUTABLE} ${ELF2HUNK_EXTRA_OPTS}
	)
	add_custom_command(
		TARGET ${GAME_EXECUTABLE} POST_BUILD
		COMMAND ${OBJDUMP} --disassemble -S ${GAME_EXECUTABLE} > ${GAME_EXECUTABLE_STEM}.s
	)
else()
	SET(GAME_EXECUTABLE ${GAME_EXECUTABLE_STEM})
	SET(GAME_OUTPUT_EXECUTABLE ${GAME_EXECUTABLE_STEM})
	add_executable(${GAME_EXECUTABLE} ${GAME_src})
endif()

target_include_directories(${GAME_EXECUTABLE} PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_compile_options(${GAME_EXECUTABLE} PUBLIC -Wall -Wextra -Wimplicit-fallthrough=2)
target_compile_options(${GAME_EXECUTABLE} PRIVATE -Werror)
target_link_libraries(${GAME_EXECUTABLE} ace_audio_mixer ace)
if(GAME_DEBUG)
  target_compile_definitions(${GAME_EXECUTABLE} PRIVATE GAME_DEBUG)
endif()

set(RES_DIR ${CMAKE_CURRENT_LIST_DIR}/res)
set(DATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/data)
set(GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)

file(MAKE_DIRECTORY ${DATA_DIR})
file(MAKE_DIRECTORY ${GEN_DIR})
# file(MAKE_DIRECTORY ${GEN_DIR}/ramka)
# file(MAKE_DIRECTORY ${GEN_DIR}/drewno)

file(GLOB COPY_FILES ${RES_DIR}/copied/*)
file(COPY ${COPY_FILES} DESTINATION ${DATA_DIR})

set(GAME_PLT_PATH ${RES_DIR}/polanie.gpl)
convertPalette(${GAME_EXECUTABLE} ${GAME_PLT_PATH} ${DATA_DIR}/battle.plt)
convertBitmaps(INTERLEAVED TARGET ${GAME_EXECUTABLE} PALETTE ${GAME_PLT_PATH}
	SOURCES
		${RES_DIR}/game1.png
	DESTINATIONS
		${DATA_DIR}/battle_ui.bm
)

include(cmake/flip_bitmaps.cmake)
include(cmake/mouse.cmake)
include(cmake/button.cmake)
include(cmake/button_bg.cmake)
include(cmake/tree.cmake)
include(cmake/hit.cmake)
include(cmake/dead.cmake)
include(cmake/fire.cmake)
include(cmake/picture.cmake)
include(cmake/movers.cmake)
include(cmake/missiles.cmake)

# Version stuff
string(TIMESTAMP YEAR "%y")
string(TIMESTAMP DAY "%d")
string(TIMESTAMP MONTH "%m")
MATH(EXPR VER_MAJOR "0 + ${YEAR}")
MATH(EXPR VER_MINOR "0 + ${MONTH}")
MATH(EXPR VER_FIX "0 + ${DAY}")
set(VERSION "${VER_MAJOR}.${VER_MINOR}.${VER_FIX}")
target_compile_definitions(${GAME_EXECUTABLE} PRIVATE GAME_VERSION="${VERSION}")

# Generating ZIP
set(GAME_PACKAGE_NAME "${CMAKE_PROJECT_NAME}_${VER_MAJOR}_${VER_MINOR}_${VER_FIX}")
add_custom_target(generateZip COMMAND
	${CMAKE_COMMAND} -E tar "cf" "${GAME_PACKAGE_NAME}.zip" --format=zip
	"${CMAKE_CURRENT_BINARY_DIR}/${GAME_OUTPUT_EXECUTABLE}"
	# "${CMAKE_CURRENT_BINARY_DIR}/${GAME_OUTPUT_EXECUTABLE}.info"
	"${DATA_DIR}"
	COMMENT "Generating ZIP file ${GAME_PACKAGE_NAME}.zip"
)
