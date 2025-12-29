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
	${GEN_DIR}/movers/cow/9.png   32  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/10.png  32 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/11.png  32 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/12.png  48  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/13.png  48 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/14.png  48 28 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/cow/18.png  64  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/19.png  64 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/20.png  64 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/21.png  80  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/22.png  80 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/23.png  80 28 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/cow/27.png  96  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/28.png  96 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/29.png  96 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/30.png 112  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/31.png 112 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/32.png 112 28 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/cow/36.png 128  0 16 14 #x0y0
	${GEN_DIR}/movers/cow/37.png 128 14 16 14 #x0y1
	${GEN_DIR}/movers/cow/38.png 128 28 16 14 #x0y2
	${GEN_DIR}/movers/cow/39.png 144  0 16 14 #x1y0
	${GEN_DIR}/movers/cow/40.png 144 14 16 14 #x1y1
	${GEN_DIR}/movers/cow/41.png 144 28 16 14 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_COW_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/cow/0.png ${GEN_DIR}/movers/cow/1.png ${GEN_DIR}/movers/cow/2.png # phase 0
		${GEN_DIR}/movers/cow/9.png ${GEN_DIR}/movers/cow/10.png ${GEN_DIR}/movers/cow/11.png # phase 1
		${GEN_DIR}/movers/cow/18.png ${GEN_DIR}/movers/cow/19.png ${GEN_DIR}/movers/cow/20.png # phase 2
		${GEN_DIR}/movers/cow/27.png ${GEN_DIR}/movers/cow/28.png ${GEN_DIR}/movers/cow/29.png # phase 3
		${GEN_DIR}/movers/cow/36.png ${GEN_DIR}/movers/cow/37.png ${GEN_DIR}/movers/cow/38.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/cow/6.png ${GEN_DIR}/movers/cow/7.png ${GEN_DIR}/movers/cow/8.png
		${GEN_DIR}/movers/cow/15.png ${GEN_DIR}/movers/cow/16.png ${GEN_DIR}/movers/cow/17.png
		${GEN_DIR}/movers/cow/24.png ${GEN_DIR}/movers/cow/25.png ${GEN_DIR}/movers/cow/26.png
		${GEN_DIR}/movers/cow/33.png ${GEN_DIR}/movers/cow/34.png ${GEN_DIR}/movers/cow/35.png
		${GEN_DIR}/movers/cow/42.png ${GEN_DIR}/movers/cow/43.png ${GEN_DIR}/movers/cow/44.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/cow DESTINATION ${GEN_DIR}/movers/cow.png
	TILE_PATHS ${TILES_MOVER_COW_LIST};${TILES_MOVER_COW_LIST_FLIPPED}
)
