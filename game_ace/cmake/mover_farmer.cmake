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
	${GEN_DIR}/movers/farmer/6.png  192  0 16 14 #x0y0
	${GEN_DIR}/movers/farmer/7.png  192 14 16 14 #x0y1
	${GEN_DIR}/movers/farmer/8.png  192 28 16 14 #x0y2
	${GEN_DIR}/movers/farmer/9.png  208  0 16 14 #x1y0
	${GEN_DIR}/movers/farmer/10.png 208 14 16 14 #x1y1
	${GEN_DIR}/movers/farmer/11.png 208 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/farmer/12.png 224  0 16 14 #x0y0
	${GEN_DIR}/movers/farmer/13.png 224 14 16 14 #x0y1
	${GEN_DIR}/movers/farmer/14.png 224 28 16 14 #x0y2
	${GEN_DIR}/movers/farmer/15.png 240  0 16 14 #x1y0
	${GEN_DIR}/movers/farmer/16.png 240 14 16 14 #x1y1
	${GEN_DIR}/movers/farmer/17.png 240 28 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/farmer/18.png 256   0 16 14 #x0y0
	${GEN_DIR}/movers/farmer/19.png 256  14 16 14 #x0y1
	${GEN_DIR}/movers/farmer/20.png 256  28 16 14 #x0y2
	${GEN_DIR}/movers/farmer/21.png 160  84 16 14 #x1y0
	${GEN_DIR}/movers/farmer/22.png 160  98 16 14 #x1y1
	${GEN_DIR}/movers/farmer/23.png 160 112 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/farmer/24.png 176  84 16 14 #x0y0
	${GEN_DIR}/movers/farmer/25.png 176  98 16 14 #x0y1
	${GEN_DIR}/movers/farmer/26.png 176 112 16 14 #x0y2
	${GEN_DIR}/movers/farmer/27.png 192  84 16 14 #x1y0
	${GEN_DIR}/movers/farmer/28.png 192  98 16 14 #x1y1
	${GEN_DIR}/movers/farmer/29.png 192 112 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/farmer DESTINATION ${GEN_DIR}/movers/farmer.png
	TILE_PATHS ${TILES_MOVER_FARMER_LIST}
)
