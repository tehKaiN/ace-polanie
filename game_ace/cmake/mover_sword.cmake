# swordman is split to 16/32px-wide images
file(MAKE_DIRECTORY ${GEN_DIR}/movers/sword16)
file(MAKE_DIRECTORY ${GEN_DIR}/movers/sword32)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MOVER_SWORD16_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/sword16/0.png    0 42 16 14 #x0y0
	${GEN_DIR}/movers/sword16/1.png    0 56 16 14 #x0y1
	${GEN_DIR}/movers/sword16/2.png    0 70 16 14 #x0y2
	${GEN_DIR}/movers/sword16/3.png   16 42 16 14 #x1y0
	${GEN_DIR}/movers/sword16/4.png   16 56 16 14 #x1y1
	${GEN_DIR}/movers/sword16/5.png   16 70 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/sword16/9.png   32 42 16 14 #x0y0
	${GEN_DIR}/movers/sword16/10.png  32 56 16 14 #x0y1
	${GEN_DIR}/movers/sword16/11.png  32 70 16 14 #x0y2
	${GEN_DIR}/movers/sword16/12.png  48 42 16 14 #x1y0
	${GEN_DIR}/movers/sword16/13.png  48 56 16 14 #x1y1
	${GEN_DIR}/movers/sword16/14.png  48 70 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/sword16/18.png  64 42 16 14 #x0y0
	${GEN_DIR}/movers/sword16/19.png  64 56 16 14 #x0y1
	${GEN_DIR}/movers/sword16/20.png  64 70 16 14 #x0y2
	${GEN_DIR}/movers/sword16/21.png  80 42 16 14 #x1y0
	${GEN_DIR}/movers/sword16/22.png  80 56 16 14 #x1y1
	${GEN_DIR}/movers/sword16/23.png  80 70 16 14 #x1y2
)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MOVER_SWORD32_LIST"
	DESTINATIONS
	# phase 3:
	${GEN_DIR}/movers/sword32/0.png  96 49 24 21 #x0y0
	${GEN_DIR}/movers/sword32/1.png  96 70 24 14 #x0y1
	${GEN_DIR}/movers/sword32/2.png 152 42 24 21 #x0y2
	${GEN_DIR}/movers/sword32/3.png 120 49 16 21 #x1y0
	${GEN_DIR}/movers/sword32/4.png 120 70 16 14  #x1y1
	${GEN_DIR}/movers/sword32/5.png 136 42 16 21  #x1y2
	# phase 4:
	${GEN_DIR}/movers/sword32/9.png  176 49 24 21 #x0y0
	${GEN_DIR}/movers/sword32/10.png 176 70 24 14 #x0y1
	${GEN_DIR}/movers/sword32/11.png 152 63 24 21 #x0y2
	${GEN_DIR}/movers/sword32/12.png 200 49 16 21 #x1y0
	${GEN_DIR}/movers/sword32/13.png 200 70 16 14 #x1y1
	${GEN_DIR}/movers/sword32/14.png 136 63 16 21 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_SWORD16_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/sword16/0.png ${GEN_DIR}/movers/sword16/1.png ${GEN_DIR}/movers/sword16/2.png # phase 0
		${GEN_DIR}/movers/sword16/9.png ${GEN_DIR}/movers/sword16/10.png ${GEN_DIR}/movers/sword16/11.png # phase 1
		${GEN_DIR}/movers/sword16/18.png ${GEN_DIR}/movers/sword16/19.png ${GEN_DIR}/movers/sword16/20.png # phase 2
	DESTINATIONS
		${GEN_DIR}/movers/sword16/6.png ${GEN_DIR}/movers/sword16/7.png ${GEN_DIR}/movers/sword16/8.png
		${GEN_DIR}/movers/sword16/15.png ${GEN_DIR}/movers/sword16/16.png ${GEN_DIR}/movers/sword16/17.png
		${GEN_DIR}/movers/sword16/24.png ${GEN_DIR}/movers/sword16/25.png ${GEN_DIR}/movers/sword16/26.png
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_SWORD32_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/sword32/0.png ${GEN_DIR}/movers/sword32/1.png ${GEN_DIR}/movers/sword32/2.png # phase 3
		${GEN_DIR}/movers/sword32/9.png ${GEN_DIR}/movers/sword32/10.png ${GEN_DIR}/movers/sword32/11.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/sword32/6.png ${GEN_DIR}/movers/sword32/7.png ${GEN_DIR}/movers/sword32/8.png
		${GEN_DIR}/movers/sword32/15.png ${GEN_DIR}/movers/sword32/16.png ${GEN_DIR}/movers/sword32/17.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/sword16 DESTINATION ${GEN_DIR}/movers/sword16.png
	TILE_PATHS ${TILES_MOVER_SWORD16_LIST};${TILES_MOVER_SWORD16_LIST_FLIPPED}
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 32 VARIABLE_HEIGHT PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/sword32 DESTINATION ${GEN_DIR}/movers/sword32.png
	TILE_PATHS ${TILES_MOVER_SWORD32_LIST};${TILES_MOVER_SWORD32_LIST_FLIPPED}
)
