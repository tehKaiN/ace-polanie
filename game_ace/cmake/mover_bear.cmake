# bearman is split to 16/32px-wide images
file(MAKE_DIRECTORY ${GEN_DIR}/movers/bear16)
file(MAKE_DIRECTORY ${GEN_DIR}/movers/bear32)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game4.png
	GENERATED_FILE_LIST "TILES_MOVER_BEAR16_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/bear16/0.png    0 0 16 14 #x0y0
	${GEN_DIR}/movers/bear16/1.png    0 14 16 14 #x0y1
	${GEN_DIR}/movers/bear16/2.png    0 28 16 14 #x0y2
	${GEN_DIR}/movers/bear16/3.png   16 0 16 14 #x1y0
	${GEN_DIR}/movers/bear16/4.png   16 14 16 14 #x1y1
	${GEN_DIR}/movers/bear16/5.png   16 28 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/bear16/9.png   32 0 16 14 #x0y0
	${GEN_DIR}/movers/bear16/10.png  32 14 16 14 #x0y1
	${GEN_DIR}/movers/bear16/11.png  32 28 16 14 #x0y2
	${GEN_DIR}/movers/bear16/12.png  48 0 16 14 #x1y0
	${GEN_DIR}/movers/bear16/13.png  48 14 16 14 #x1y1
	${GEN_DIR}/movers/bear16/14.png  48 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/bear16/18.png  64 0 16 14 #x0y0
	${GEN_DIR}/movers/bear16/19.png  64 14 16 14 #x0y1
	${GEN_DIR}/movers/bear16/20.png  64 28 16 14 #x0y2
	${GEN_DIR}/movers/bear16/21.png  80 0 16 14 #x1y0
	${GEN_DIR}/movers/bear16/22.png  80 14 16 14 #x1y1
	${GEN_DIR}/movers/bear16/23.png  80 28 16 14 #x1y2
)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game4.png
	GENERATED_FILE_LIST "TILES_MOVER_BEAR32_LIST"
	DESTINATIONS
	# phase 3:
	${GEN_DIR}/movers/bear32/0.png  96 7 24 21 #x0y0
	${GEN_DIR}/movers/bear32/1.png  96 28 24 14 #x0y1
	${GEN_DIR}/movers/bear32/2.png 152 0 24 21 #x0y2
	${GEN_DIR}/movers/bear32/3.png 120 7 16 21 #x1y0
	${GEN_DIR}/movers/bear32/4.png 120 28 16 14  #x1y1
	${GEN_DIR}/movers/bear32/5.png 136 0 16 21  #x1y2
	# phase 4:
	${GEN_DIR}/movers/bear32/9.png  176 7 24 21 #x0y0
	${GEN_DIR}/movers/bear32/10.png 176 28 24 14 #x0y1
	${GEN_DIR}/movers/bear32/11.png 152 0 24 21 #x0y2
	${GEN_DIR}/movers/bear32/12.png 200 7 16 21 #x1y0
	${GEN_DIR}/movers/bear32/13.png 200 28 16 14 #x1y1
	${GEN_DIR}/movers/bear32/14.png 136 0 16 21 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_BEAR16_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/bear16/0.png ${GEN_DIR}/movers/bear16/1.png ${GEN_DIR}/movers/bear16/2.png # phase 0
		${GEN_DIR}/movers/bear16/9.png ${GEN_DIR}/movers/bear16/10.png ${GEN_DIR}/movers/bear16/11.png # phase 1
		${GEN_DIR}/movers/bear16/18.png ${GEN_DIR}/movers/bear16/19.png ${GEN_DIR}/movers/bear16/20.png # phase 2
	DESTINATIONS
		${GEN_DIR}/movers/bear16/6.png ${GEN_DIR}/movers/bear16/7.png ${GEN_DIR}/movers/bear16/8.png
		${GEN_DIR}/movers/bear16/15.png ${GEN_DIR}/movers/bear16/16.png ${GEN_DIR}/movers/bear16/17.png
		${GEN_DIR}/movers/bear16/24.png ${GEN_DIR}/movers/bear16/25.png ${GEN_DIR}/movers/bear16/26.png
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_BEAR32_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/axe32/0.png ${GEN_DIR}/movers/axe32/1.png ${GEN_DIR}/movers/axe32/2.png # phase 3
		${GEN_DIR}/movers/axe32/9.png ${GEN_DIR}/movers/axe32/10.png ${GEN_DIR}/movers/axe32/11.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/axe32/6.png ${GEN_DIR}/movers/axe32/7.png ${GEN_DIR}/movers/axe32/8.png
		${GEN_DIR}/movers/axe32/15.png ${GEN_DIR}/movers/axe32/16.png ${GEN_DIR}/movers/axe32/17.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/bear16 DESTINATION ${GEN_DIR}/movers/bear16.png
	TILE_PATHS ${TILES_MOVER_BEAR16_LIST};${TILES_MOVER_BEAR16_LIST_FLIPPED}
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 32 VARIABLE_HEIGHT PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/bear32 DESTINATION ${GEN_DIR}/movers/bear32.png
	TILE_PATHS ${TILES_MOVER_BEAR32_LIST};${TILES_MOVER_BEAR32_LIST_FLIPPED}
)
