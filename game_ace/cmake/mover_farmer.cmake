file(MAKE_DIRECTORY ${GEN_DIR}/movers/farmer)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_MOVER_FARMER_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/farmer/0.png 160  0 16 14 #x0y0
	${GEN_DIR}/movers/farmer/1.png 160 14 16 14 #x0y1
	${GEN_DIR}/movers/farmer/2.png 160 28 16 14 #x0y2
	${GEN_DIR}/movers/farmer/3.png 176  0 16 14 #x1y0
	${GEN_DIR}/movers/farmer/4.png 176 14 16 14 #x1y1
	${GEN_DIR}/movers/farmer/5.png 176 28 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/farmer/9.png  192  0 16 14 #x0y0
	${GEN_DIR}/movers/farmer/10.png  192 14 16 14 #x0y1
	${GEN_DIR}/movers/farmer/11.png  192 28 16 14 #x0y2
	${GEN_DIR}/movers/farmer/12.png  208  0 16 14 #x1y0
	${GEN_DIR}/movers/farmer/13.png 208 14 16 14 #x1y1
	${GEN_DIR}/movers/farmer/14.png 208 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/farmer/18.png 224  0 16 14 #x0y0
	${GEN_DIR}/movers/farmer/19.png 224 14 16 14 #x0y1
	${GEN_DIR}/movers/farmer/20.png 224 28 16 14 #x0y2
	${GEN_DIR}/movers/farmer/21.png 240  0 16 14 #x1y0
	${GEN_DIR}/movers/farmer/22.png 240 14 16 14 #x1y1
	${GEN_DIR}/movers/farmer/23.png 240 28 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/farmer/27.png 256   0 16 14 #x0y0
	${GEN_DIR}/movers/farmer/28.png 256  14 16 14 #x0y1
	${GEN_DIR}/movers/farmer/29.png 256  28 16 14 #x0y2
	${GEN_DIR}/movers/farmer/30.png 160  84 16 14 #x1y0
	${GEN_DIR}/movers/farmer/31.png 160  98 16 14 #x1y1
	${GEN_DIR}/movers/farmer/32.png 160 112 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/farmer/36.png 176  84 16 14 #x0y0
	${GEN_DIR}/movers/farmer/37.png 176  98 16 14 #x0y1
	${GEN_DIR}/movers/farmer/38.png 176 112 16 14 #x0y2
	${GEN_DIR}/movers/farmer/39.png 192  84 16 14 #x1y0
	${GEN_DIR}/movers/farmer/40.png 192  98 16 14 #x1y1
	${GEN_DIR}/movers/farmer/41.png 192 112 16 14 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_FARMER_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/farmer/0.png ${GEN_DIR}/movers/farmer/1.png ${GEN_DIR}/movers/farmer/2.png # phase 0
		${GEN_DIR}/movers/farmer/9.png ${GEN_DIR}/movers/farmer/10.png ${GEN_DIR}/movers/farmer/11.png # phase 1
		${GEN_DIR}/movers/farmer/18.png ${GEN_DIR}/movers/farmer/19.png ${GEN_DIR}/movers/farmer/20.png # phase 2
		${GEN_DIR}/movers/farmer/27.png ${GEN_DIR}/movers/farmer/28.png ${GEN_DIR}/movers/farmer/29.png # phase 3
		${GEN_DIR}/movers/farmer/36.png ${GEN_DIR}/movers/farmer/37.png ${GEN_DIR}/movers/farmer/38.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/farmer/6.png ${GEN_DIR}/movers/farmer/7.png ${GEN_DIR}/movers/farmer/8.png
		${GEN_DIR}/movers/farmer/15.png ${GEN_DIR}/movers/farmer/16.png ${GEN_DIR}/movers/farmer/17.png
		${GEN_DIR}/movers/farmer/24.png ${GEN_DIR}/movers/farmer/25.png ${GEN_DIR}/movers/farmer/26.png
		${GEN_DIR}/movers/farmer/33.png ${GEN_DIR}/movers/farmer/34.png ${GEN_DIR}/movers/farmer/35.png
		${GEN_DIR}/movers/farmer/42.png ${GEN_DIR}/movers/farmer/43.png ${GEN_DIR}/movers/farmer/44.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/farmer DESTINATION ${GEN_DIR}/movers/farmer.png
	TILE_PATHS ${TILES_MOVER_FARMER_LIST};${TILES_MOVER_FARMER_LIST_FLIPPED}
)
