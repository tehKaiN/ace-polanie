# knightman is split to 16/32px-wide images
file(MAKE_DIRECTORY ${GEN_DIR}/movers/knight16)
file(MAKE_DIRECTORY ${GEN_DIR}/movers/knight32)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MOVER_KNIGHT16_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/knight16/0.png    0 126 16 14 #x0y0
	${GEN_DIR}/movers/knight16/1.png    0 140 16 14 #x0y1
	${GEN_DIR}/movers/knight16/2.png    0 154 16 14 #x0y2
	${GEN_DIR}/movers/knight16/3.png   16 126 16 14 #x1y0
	${GEN_DIR}/movers/knight16/4.png   16 140 16 14 #x1y1
	${GEN_DIR}/movers/knight16/5.png   16 154 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/knight16/9.png   32 126 16 14 #x0y0
	${GEN_DIR}/movers/knight16/10.png  32 140 16 14 #x0y1
	${GEN_DIR}/movers/knight16/11.png  32 154 16 14 #x0y2
	${GEN_DIR}/movers/knight16/12.png  48 126 16 14 #x1y0
	${GEN_DIR}/movers/knight16/13.png  48 140 16 14 #x1y1
	${GEN_DIR}/movers/knight16/14.png  48 154 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/knight16/18.png  64 126 16 14 #x0y0
	${GEN_DIR}/movers/knight16/19.png  64 140 16 14 #x0y1
	${GEN_DIR}/movers/knight16/20.png  64 154 16 14 #x0y2
	${GEN_DIR}/movers/knight16/21.png  80 126 16 14 #x1y0
	${GEN_DIR}/movers/knight16/22.png  80 140 16 14 #x1y1
	${GEN_DIR}/movers/knight16/23.png  80 154 16 14 #x1y2
)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MOVER_KNIGHT32_LIST"
	DESTINATIONS
	# phase 3:
	${GEN_DIR}/movers/knight32/0.png  96 133 24 21 #x0y0
	${GEN_DIR}/movers/knight32/1.png  96 154 24 14 #x0y1
	${GEN_DIR}/movers/knight32/2.png 152 126 24 21 #x0y2
	${GEN_DIR}/movers/knight32/3.png 120 133 16 21 #x1y0
	${GEN_DIR}/movers/knight32/4.png 120 154 16 14  #x1y1
	${GEN_DIR}/movers/knight32/5.png 136 126 16 21  #x1y2
	# phase 4:
	${GEN_DIR}/movers/knight32/9.png  176 133 24 21 #x0y0
	${GEN_DIR}/movers/knight32/10.png 176 154 24 14 #x0y1
	${GEN_DIR}/movers/knight32/11.png 152 126 24 21 #x0y2
	${GEN_DIR}/movers/knight32/12.png 200 133 16 21 #x1y0
	${GEN_DIR}/movers/knight32/13.png 200 154 16 14 #x1y1
	${GEN_DIR}/movers/knight32/14.png 136 126 16 21 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_KNIGHT16_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/knight16/0.png ${GEN_DIR}/movers/knight16/1.png ${GEN_DIR}/movers/knight16/2.png # phase 0
		${GEN_DIR}/movers/knight16/9.png ${GEN_DIR}/movers/knight16/10.png ${GEN_DIR}/movers/knight16/11.png # phase 1
		${GEN_DIR}/movers/knight16/18.png ${GEN_DIR}/movers/knight16/19.png ${GEN_DIR}/movers/knight16/20.png # phase 2
	DESTINATIONS
		${GEN_DIR}/movers/knight16/6.png ${GEN_DIR}/movers/knight16/7.png ${GEN_DIR}/movers/knight16/8.png
		${GEN_DIR}/movers/knight16/15.png ${GEN_DIR}/movers/knight16/16.png ${GEN_DIR}/movers/knight16/17.png
		${GEN_DIR}/movers/knight16/24.png ${GEN_DIR}/movers/knight16/25.png ${GEN_DIR}/movers/knight16/26.png
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_KNIGHT32_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/knight32/0.png ${GEN_DIR}/movers/knight32/1.png ${GEN_DIR}/movers/knight32/2.png # phase 3
		${GEN_DIR}/movers/knight32/9.png ${GEN_DIR}/movers/knight32/10.png ${GEN_DIR}/movers/knight32/11.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/knight32/6.png ${GEN_DIR}/movers/knight32/7.png ${GEN_DIR}/movers/knight32/8.png
		${GEN_DIR}/movers/knight32/15.png ${GEN_DIR}/movers/knight32/16.png ${GEN_DIR}/movers/knight32/17.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/knight16 DESTINATION ${GEN_DIR}/movers/knight16.png
	TILE_PATHS ${TILES_MOVER_KNIGHT16_LIST};${TILES_MOVER_KNIGHT16_LIST_FLIPPED}
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 32 VARIABLE_HEIGHT PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/knight32 DESTINATION ${GEN_DIR}/movers/knight32.png
	TILE_PATHS ${TILES_MOVER_KNIGHT32_LIST};${TILES_MOVER_KNIGHT32_LIST_FLIPPED}
)
