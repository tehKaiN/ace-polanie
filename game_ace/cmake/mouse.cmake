file(MAKE_DIRECTORY ${GEN_DIR}/mouse)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game1.png
	GENERATED_FILE_LIST "TILES_MOUSE_LIST"
	DESTINATIONS
	${GEN_DIR}/mouse/1.png   11 8 16 14
	${GEN_DIR}/mouse/2.png   27 8 16 14
	${GEN_DIR}/mouse/3.png   43 8 16 14
	${GEN_DIR}/mouse/4.png   59 8 16 14
	${GEN_DIR}/mouse/5.png   75 8 16 14
	${GEN_DIR}/mouse/6.png   91 8 16 14
	${GEN_DIR}/mouse/7.png  107 8 16 14
	${GEN_DIR}/mouse/8.png  123 8 16 14
	${GEN_DIR}/mouse/9.png  139 8 16 14
	${GEN_DIR}/mouse/10.png  155 8 16 14
	${GEN_DIR}/mouse/11.png 171 8 16 14
	${GEN_DIR}/mouse/12.png 187 8 16 14
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/mouse DESTINATION ${GEN_DIR}/mouse.png
	TILE_PATHS ${TILES_MOUSE_LIST}
)
