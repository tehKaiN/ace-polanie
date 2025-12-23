file(MAKE_DIRECTORY ${GEN_DIR}/button)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game1.png
	GENERATED_FILE_LIST "TILES_BUTTON_LIST"
	DESTINATIONS
	${GEN_DIR}/button/0.png   11 22 16 14
	${GEN_DIR}/button/1.png   27 22 16 14
	${GEN_DIR}/button/2.png   43 22 16 14
	${GEN_DIR}/button/3.png   59 22 16 14
	${GEN_DIR}/button/4.png   75 22 16 14
	${GEN_DIR}/button/5.png   91 22 16 14
	${GEN_DIR}/button/6.png  107 22 16 14
	${GEN_DIR}/button/7.png  123 22 16 14
	${GEN_DIR}/button/8.png  139 22 16 14
	${GEN_DIR}/button/9.png  155 22 16 14
	${GEN_DIR}/button/10.png 171 22 16 14
	${GEN_DIR}/button/11.png 187 22 16 14
	${GEN_DIR}/button/12.png 203 22 16 14
	${GEN_DIR}/button/13.png 219 22 16 14
	${GEN_DIR}/button/14.png 251 8 16 14
	${GEN_DIR}/button/15.png 235 8 16 14
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/button DESTINATION ${GEN_DIR}/button.png
	TILE_PATHS ${TILES_BUTTON_LIST}
)

convertBitmaps(
	INTERLEAVED TARGET ${GAME_EXECUTABLE} PALETTE ${GAME_PLT_PATH}
	MASK_COLOR "#000000"
	SOURCES
		${GEN_DIR}/button.png
	DESTINATIONS
		${DATA_DIR}/button.bm
	MASKS
		${DATA_DIR}/button_mask.bm
)
