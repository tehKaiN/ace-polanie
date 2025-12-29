file(MAKE_DIRECTORY ${GEN_DIR}/movers/hunter)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_MOVER_HUNTER_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/hunter/0.png    0  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/1.png    0  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/2.png    0 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/3.png   16  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/4.png   16  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/5.png   16 112 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/hunter/9.png   32  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/10.png   32  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/11.png   32 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/12.png   48  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/13.png  48  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/14.png  48 112 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/hunter/18.png  64  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/19.png  64  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/20.png  64 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/21.png  80  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/22.png  80  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/23.png  80 112 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/hunter/27.png  96  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/28.png  96  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/29.png  96 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/30.png 112  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/31.png 112  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/32.png 112 112 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/hunter/36.png 128  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/37.png 128  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/38.png 128 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/39.png 144  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/40.png 144  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/41.png 144 112 16 14 #x1y2
)

flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MOVER_HUNTER_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/movers/hunter/0.png ${GEN_DIR}/movers/hunter/1.png ${GEN_DIR}/movers/hunter/2.png # phase 0
		${GEN_DIR}/movers/hunter/9.png ${GEN_DIR}/movers/hunter/10.png ${GEN_DIR}/movers/hunter/11.png # phase 1
		${GEN_DIR}/movers/hunter/18.png ${GEN_DIR}/movers/hunter/19.png ${GEN_DIR}/movers/hunter/20.png # phase 2
		${GEN_DIR}/movers/hunter/27.png ${GEN_DIR}/movers/hunter/28.png ${GEN_DIR}/movers/hunter/29.png # phase 3
		${GEN_DIR}/movers/hunter/36.png ${GEN_DIR}/movers/hunter/37.png ${GEN_DIR}/movers/hunter/38.png # phase 4
	DESTINATIONS
		${GEN_DIR}/movers/hunter/6.png ${GEN_DIR}/movers/hunter/7.png ${GEN_DIR}/movers/hunter/8.png
		${GEN_DIR}/movers/hunter/15.png ${GEN_DIR}/movers/hunter/16.png ${GEN_DIR}/movers/hunter/17.png
		${GEN_DIR}/movers/hunter/24.png ${GEN_DIR}/movers/hunter/25.png ${GEN_DIR}/movers/hunter/26.png
		${GEN_DIR}/movers/hunter/33.png ${GEN_DIR}/movers/hunter/34.png ${GEN_DIR}/movers/hunter/35.png
		${GEN_DIR}/movers/hunter/42.png ${GEN_DIR}/movers/hunter/43.png ${GEN_DIR}/movers/hunter/44.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/hunter DESTINATION ${GEN_DIR}/movers/hunter.png
	TILE_PATHS ${TILES_MOVER_HUNTER_LIST};${TILES_MOVER_HUNTER_LIST_FLIPPED}
)
