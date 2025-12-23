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
	${GEN_DIR}/movers/priest/6.png   32  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/7.png   32 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/8.png   32 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/9.png   48  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/10.png  48 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/11.png  48 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/priest/12.png  64  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/13.png  64 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/14.png  64 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/15.png  80  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/16.png  80 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/17.png  80 28 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/priest/18.png  96  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/19.png  96 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/20.png  96 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/21.png 112  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/22.png 112 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/23.png 112 28 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/priest/24.png 128  0 16 14 #x0y0
	${GEN_DIR}/movers/priest/25.png 128 14 16 14 #x0y1
	${GEN_DIR}/movers/priest/26.png 128 28 16 14 #x0y2
	${GEN_DIR}/movers/priest/27.png 144  0 16 14 #x1y0
	${GEN_DIR}/movers/priest/28.png 144 14 16 14 #x1y1
	${GEN_DIR}/movers/priest/29.png 144 28 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/priest DESTINATION ${GEN_DIR}/movers/priest.png
	TILE_PATHS ${TILES_MOVER_PRIEST_LIST}
)
