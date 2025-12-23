file(MAKE_DIRECTORY ${GEN_DIR}/button_bg)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game1.png
	GENERATED_FILE_LIST "TILES_BUTTON_BG_LIST"
	DESTINATIONS
	# ${GEN_DIR}/button_bg/0.png 108 142 111 18 # Tiles, wtf
	# ${GEN_DIR}/button_bg/1.png 108 114 111 18 # Trees, wtf
	${GEN_DIR}/button_bg/0.png 274 38 32 16 # moved from 2
	${GEN_DIR}/button_bg/1.png 274 58 32 16 # moved from 3
)

# Original size: 18x16
convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 32 HEIGHT 16 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/button_bg DESTINATION ${GEN_DIR}/button_bg.png
	TILE_PATHS ${TILES_BUTTON_BG_LIST}
)

convertBitmaps(
	INTERLEAVED TARGET ${GAME_EXECUTABLE} PALETTE ${GAME_PLT_PATH}
	MASK_COLOR "#000000"
	SOURCES
		${GEN_DIR}/button_bg.png
	DESTINATIONS
		${DATA_DIR}/button_bg.bm
	MASKS
		${DATA_DIR}/button_bg_mask.bm
)
