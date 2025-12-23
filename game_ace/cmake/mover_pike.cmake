file(MAKE_DIRECTORY ${GEN_DIR}/movers/pike)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MOVER_PIKE_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/pike/0.png    0  84 16 14 #x0y0
	${GEN_DIR}/movers/pike/1.png    0  98 16 14 #x0y1
	${GEN_DIR}/movers/pike/2.png    0 112 16 14 #x0y2
	${GEN_DIR}/movers/pike/3.png   16  84 16 14 #x1y0
	${GEN_DIR}/movers/pike/4.png   16  98 16 14 #x1y1
	${GEN_DIR}/movers/pike/5.png   16 112 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/pike/6.png   32  84 16 14 #x0y0
	${GEN_DIR}/movers/pike/7.png   32  98 16 14 #x0y1
	${GEN_DIR}/movers/pike/8.png   32 112 16 14 #x0y2
	${GEN_DIR}/movers/pike/9.png   48  84 16 14 #x1y0
	${GEN_DIR}/movers/pike/10.png  48  98 16 14 #x1y1
	${GEN_DIR}/movers/pike/11.png  48 112 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/pike/12.png  64  84 16 14 #x0y0
	${GEN_DIR}/movers/pike/13.png  64  98 16 14 #x0y1
	${GEN_DIR}/movers/pike/14.png  64 112 16 14 #x0y2
	${GEN_DIR}/movers/pike/15.png  80  84 16 14 #x1y0
	${GEN_DIR}/movers/pike/16.png  80  98 16 14 #x1y1
	${GEN_DIR}/movers/pike/17.png  80 112 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/pike/18.png  96  84 16 14 #x0y0
	${GEN_DIR}/movers/pike/19.png  96  98 16 14 #x0y1
	${GEN_DIR}/movers/pike/20.png  96 112 16 14 #x0y2
	${GEN_DIR}/movers/pike/21.png 112  84 16 14 #x1y0
	${GEN_DIR}/movers/pike/22.png 112  98 16 14 #x1y1
	${GEN_DIR}/movers/pike/23.png 112 112 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/pike/24.png 128  84 16 14 #x0y0
	${GEN_DIR}/movers/pike/25.png 128  98 16 14 #x0y1
	${GEN_DIR}/movers/pike/26.png 128 112 16 14 #x0y2
	${GEN_DIR}/movers/pike/27.png 144  84 16 14 #x1y0
	${GEN_DIR}/movers/pike/28.png 144  98 16 14 #x1y1
	${GEN_DIR}/movers/pike/29.png 144 112 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/pike DESTINATION ${GEN_DIR}/movers/pike.png
	TILE_PATHS ${TILES_MOVER_PIKE_LIST}
)
