file(MAKE_DIRECTORY ${GEN_DIR}/movers/xbow)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game4.png
	GENERATED_FILE_LIST "TILES_MOVER_XBOW_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/xbow/0.png 224  0 16 14 #x0y0
	${GEN_DIR}/movers/xbow/1.png 224 14 16 14 #x0y1
	${GEN_DIR}/movers/xbow/2.png 224 28 16 14 #x0y2
	${GEN_DIR}/movers/xbow/3.png 240  0 16 14 #x1y0
	${GEN_DIR}/movers/xbow/4.png 240 14 16 14 #x1y1
	${GEN_DIR}/movers/xbow/5.png 240 28 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/xbow/6.png  256  0 16 14 #x0y0
	${GEN_DIR}/movers/xbow/7.png  256 14 16 14 #x0y1
	${GEN_DIR}/movers/xbow/8.png  256 28 16 14 #x0y2
	${GEN_DIR}/movers/xbow/9.png  272  0 16 14 #x1y0
	${GEN_DIR}/movers/xbow/10.png 272 14 16 14 #x1y1
	${GEN_DIR}/movers/xbow/11.png 272 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/xbow/12.png 288  0 16 14 #x0y0
	${GEN_DIR}/movers/xbow/13.png 288 14 16 14 #x0y1
	${GEN_DIR}/movers/xbow/14.png 288 28 16 14 #x0y2
	${GEN_DIR}/movers/xbow/15.png 224 42 16 14 #x1y0
	${GEN_DIR}/movers/xbow/16.png 224 56 16 14 #x1y1
	${GEN_DIR}/movers/xbow/17.png 224 70 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/xbow/18.png 240 42 16 14 #x0y0
	${GEN_DIR}/movers/xbow/19.png 240 56 16 14 #x0y1
	${GEN_DIR}/movers/xbow/20.png 240 70 16 14 #x0y2
	${GEN_DIR}/movers/xbow/21.png 256 42 16 14 #x1y0
	${GEN_DIR}/movers/xbow/22.png 256 56 16 14 #x1y1
	${GEN_DIR}/movers/xbow/23.png 256 70 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/xbow/24.png 272 42 16 14 #x0y0
	${GEN_DIR}/movers/xbow/25.png 272 56 16 14 #x0y1
	${GEN_DIR}/movers/xbow/26.png 272 70 16 14 #x0y2
	${GEN_DIR}/movers/xbow/27.png 288 42 16 14 #x1y0
	${GEN_DIR}/movers/xbow/28.png 288 56 16 14 #x1y1
	${GEN_DIR}/movers/xbow/29.png 288 70 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/xbow DESTINATION ${GEN_DIR}/movers/xbow.png
	TILE_PATHS ${TILES_MOVER_XBOW_LIST}
)
