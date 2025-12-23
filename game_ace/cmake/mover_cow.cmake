file(MAKE_DIRECTORY ${GEN_DIR}/movers/cow)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_MOVER_COW_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/cow/0.png   0  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/1.png   0 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/2.png   0 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/3.png  16  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/4.png  16 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/5.png  16 28 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/cow/6.png   32  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/7.png   32 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/8.png   32 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/9.png   48  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/10.png  48 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/11.png  48 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/cow/12.png  64  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/13.png  64 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/14.png  64 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/15.png  80  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/16.png  80 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/17.png  80 28 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/cow/18.png  96  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/19.png  96 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/20.png  96 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/21.png 112  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/22.png 112 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/23.png 112 28 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/cow/24.png 128  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/25.png 128 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/26.png 128 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/27.png 144  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/28.png 144 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/29.png 144 28 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/cow DESTINATION ${GEN_DIR}/movers/cow.png
	TILE_PATHS ${TILES_MOVER_COW_LIST}
)
