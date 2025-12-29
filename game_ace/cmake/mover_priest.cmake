file(MAKE_DIRECTORY ${GEN_DIR}/movers/priest)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MOVER_PRIEST_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/priest/0.png   0  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/1.png   0 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/2.png   0 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/3.png  16  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/4.png  16 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/5.png  16 28 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/priest/9.png   32  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/10.png   32 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/11.png   32 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/12.png   48  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/13.png  48 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/14.png  48 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/priest/18.png  64  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/19.png  64 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/20.png  64 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/21.png  80  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/22.png  80 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/23.png  80 28 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/priest/27.png  96  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/28.png  96 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/29.png  96 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/30.png 112  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/31.png 112 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/32.png 112 28 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/priest/36.png 128  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/37.png 128 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/38.png 128 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/39.png 144  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/40.png 144 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/41.png 144 28 16 14 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_PRIEST_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/priest/0.png ${GEN_DIR}/movers/priest/1.png ${GEN_DIR}/movers/priest/2.png # phase 0
		${GEN_DIR}/movers/priest/9.png ${GEN_DIR}/movers/priest/10.png ${GEN_DIR}/movers/priest/11.png # phase 1
		${GEN_DIR}/movers/priest/18.png ${GEN_DIR}/movers/priest/19.png ${GEN_DIR}/movers/priest/20.png # phase 2
		${GEN_DIR}/movers/priest/27.png ${GEN_DIR}/movers/priest/28.png ${GEN_DIR}/movers/priest/29.png # phase 3
		${GEN_DIR}/movers/priest/36.png ${GEN_DIR}/movers/priest/37.png ${GEN_DIR}/movers/priest/38.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/priest/6.png ${GEN_DIR}/movers/priest/7.png ${GEN_DIR}/movers/priest/8.png
		${GEN_DIR}/movers/priest/15.png ${GEN_DIR}/movers/priest/16.png ${GEN_DIR}/movers/priest/17.png
		${GEN_DIR}/movers/priest/24.png ${GEN_DIR}/movers/priest/25.png ${GEN_DIR}/movers/priest/26.png
		${GEN_DIR}/movers/priest/33.png ${GEN_DIR}/movers/priest/34.png ${GEN_DIR}/movers/priest/35.png
		${GEN_DIR}/movers/priest/42.png ${GEN_DIR}/movers/priest/43.png ${GEN_DIR}/movers/priest/44.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/priest DESTINATION ${GEN_DIR}/movers/priest.png
	TILE_PATHS ${TILES_MOVER_PRIEST_LIST};${TILES_MOVER_PRIEST_LIST_FLIPPED}
)
