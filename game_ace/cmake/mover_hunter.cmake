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
	${GEN_DIR}/movers/hunter/6.png   32  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/7.png   32  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/8.png   32 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/9.png   48  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/10.png  48  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/11.png  48 112 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/hunter/12.png  64  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/13.png  64  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/14.png  64 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/15.png  80  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/16.png  80  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/17.png  80 112 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/hunter/18.png  96  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/19.png  96  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/20.png  96 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/21.png 112  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/22.png 112  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/23.png 112 112 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/hunter/24.png 128  84 16 14 #x0y0
	${GEN_DIR}/movers/hunter/25.png 128  98 16 14 #x0y1
	${GEN_DIR}/movers/hunter/26.png 128 112 16 14 #x0y2
	${GEN_DIR}/movers/hunter/27.png 144  84 16 14 #x1y0
	${GEN_DIR}/movers/hunter/28.png 144  98 16 14 #x1y1
	${GEN_DIR}/movers/hunter/29.png 144 112 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/hunter DESTINATION ${GEN_DIR}/movers/hunter.png
	TILE_PATHS ${TILES_MOVER_HUNTER_LIST}
)
