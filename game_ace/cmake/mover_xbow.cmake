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
	${GEN_DIR}/movers/xbow/9.png  256  0 16 14 #x0y0
	${GEN_DIR}/movers/xbow/10.png  256 14 16 14 #x0y1
	${GEN_DIR}/movers/xbow/11.png  256 28 16 14 #x0y2
	${GEN_DIR}/movers/xbow/12.png  272  0 16 14 #x1y0
	${GEN_DIR}/movers/xbow/13.png 272 14 16 14 #x1y1
	${GEN_DIR}/movers/xbow/14.png 272 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/xbow/18.png 288  0 16 14 #x0y0
	${GEN_DIR}/movers/xbow/19.png 288 14 16 14 #x0y1
	${GEN_DIR}/movers/xbow/20.png 288 28 16 14 #x0y2
	${GEN_DIR}/movers/xbow/21.png 224 42 16 14 #x1y0
	${GEN_DIR}/movers/xbow/22.png 224 56 16 14 #x1y1
	${GEN_DIR}/movers/xbow/23.png 224 70 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/xbow/27.png 240 42 16 14 #x0y0
	${GEN_DIR}/movers/xbow/28.png 240 56 16 14 #x0y1
	${GEN_DIR}/movers/xbow/29.png 240 70 16 14 #x0y2
	${GEN_DIR}/movers/xbow/30.png 256 42 16 14 #x1y0
	${GEN_DIR}/movers/xbow/31.png 256 56 16 14 #x1y1
	${GEN_DIR}/movers/xbow/32.png 256 70 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/xbow/36.png 272 42 16 14 #x0y0
	${GEN_DIR}/movers/xbow/37.png 272 56 16 14 #x0y1
	${GEN_DIR}/movers/xbow/38.png 272 70 16 14 #x0y2
	${GEN_DIR}/movers/xbow/39.png 288 42 16 14 #x1y0
	${GEN_DIR}/movers/xbow/40.png 288 56 16 14 #x1y1
	${GEN_DIR}/movers/xbow/41.png 288 70 16 14 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_XBOW_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/xbow/0.png ${GEN_DIR}/movers/xbow/1.png ${GEN_DIR}/movers/xbow/2.png # phase 0
		${GEN_DIR}/movers/xbow/9.png ${GEN_DIR}/movers/xbow/10.png ${GEN_DIR}/movers/xbow/11.png # phase 1
		${GEN_DIR}/movers/xbow/18.png ${GEN_DIR}/movers/xbow/19.png ${GEN_DIR}/movers/xbow/20.png # phase 2
		${GEN_DIR}/movers/xbow/27.png ${GEN_DIR}/movers/xbow/28.png ${GEN_DIR}/movers/xbow/29.png # phase 3
		${GEN_DIR}/movers/xbow/36.png ${GEN_DIR}/movers/xbow/37.png ${GEN_DIR}/movers/xbow/38.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/xbow/6.png ${GEN_DIR}/movers/xbow/7.png ${GEN_DIR}/movers/xbow/8.png
		${GEN_DIR}/movers/xbow/15.png ${GEN_DIR}/movers/xbow/16.png ${GEN_DIR}/movers/xbow/17.png
		${GEN_DIR}/movers/xbow/24.png ${GEN_DIR}/movers/xbow/25.png ${GEN_DIR}/movers/xbow/26.png
		${GEN_DIR}/movers/xbow/33.png ${GEN_DIR}/movers/xbow/34.png ${GEN_DIR}/movers/xbow/35.png
		${GEN_DIR}/movers/xbow/42.png ${GEN_DIR}/movers/xbow/43.png ${GEN_DIR}/movers/xbow/44.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/xbow DESTINATION ${GEN_DIR}/movers/xbow.png
	TILE_PATHS ${TILES_MOVER_XBOW_LIST};${TILES_MOVER_XBOW_LIST_FLIPPED}
)
