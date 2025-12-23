file(MAKE_DIRECTORY ${GEN_DIR}/movers/priestess)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_MOVER_PRIESTESS_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/priestess/0.png    0 126 16 14 #x0y0
	${GEN_DIR}/movers/priestess/1.png    0 140 16 14 #x0y1
	${GEN_DIR}/movers/priestess/2.png    0 154 16 14 #x0y2
	${GEN_DIR}/movers/priestess/3.png   16 126 16 14 #x1y0
	${GEN_DIR}/movers/priestess/4.png   16 140 16 14 #x1y1
	${GEN_DIR}/movers/priestess/5.png   16 154 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/priestess/6.png   32 126 16 14 #x0y0
	${GEN_DIR}/movers/priestess/7.png   32 140 16 14 #x0y1
	${GEN_DIR}/movers/priestess/8.png   32 154 16 14 #x0y2
	${GEN_DIR}/movers/priestess/9.png   48 126 16 14 #x1y0
	${GEN_DIR}/movers/priestess/10.png  48 140 16 14 #x1y1
	${GEN_DIR}/movers/priestess/11.png  48 154 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/priestess/12.png  64 126 16 14 #x0y0
	${GEN_DIR}/movers/priestess/13.png  64 140 16 14 #x0y1
	${GEN_DIR}/movers/priestess/14.png  64 154 16 14 #x0y2
	${GEN_DIR}/movers/priestess/15.png  80 126 16 14 #x1y0
	${GEN_DIR}/movers/priestess/16.png  80 140 16 14 #x1y1
	${GEN_DIR}/movers/priestess/17.png  80 154 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/priestess/18.png  96 126 16 14 #x0y0
	${GEN_DIR}/movers/priestess/19.png  96 140 16 14 #x0y1
	${GEN_DIR}/movers/priestess/20.png  96 154 16 14 #x0y2
	${GEN_DIR}/movers/priestess/21.png 112 126 16 14 #x1y0
	${GEN_DIR}/movers/priestess/22.png 112 140 16 14 #x1y1
	${GEN_DIR}/movers/priestess/23.png 112 154 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/priestess/24.png 128 126 16 14 #x0y0
	${GEN_DIR}/movers/priestess/25.png 128 140 16 14 #x0y1
	${GEN_DIR}/movers/priestess/26.png 128 154 16 14 #x0y2
	${GEN_DIR}/movers/priestess/27.png 144 126 16 14 #x1y0
	${GEN_DIR}/movers/priestess/28.png 144 140 16 14 #x1y1
	${GEN_DIR}/movers/priestess/29.png 144 154 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/priestess DESTINATION ${GEN_DIR}/movers/priestess.png
	TILE_PATHS ${TILES_MOVER_PRIESTESS_LIST}
)
