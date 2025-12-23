file(MAKE_DIRECTORY ${GEN_DIR}/missiles)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MISSILES_LIST"
	DESTINATIONS
	# type 0: arrow
	${GEN_DIR}/missiles/0.png  240   0 16 14 #x0y0
	${GEN_DIR}/missiles/1.png  240  14 16 14 #x0y1
	${GEN_DIR}/missiles/2.png  240  28 16 14 #x0y2
	${GEN_DIR}/missiles/3.png  256   0 16 14 #x1y0
	${GEN_DIR}/missiles/4.png  256  14 16 14 #x1y1
	${GEN_DIR}/missiles/5.png  256  28 16 14 #x1y2
	# type 1: lightning
	${GEN_DIR}/missiles/6.png  240  42 16 14 #x0y0
	${GEN_DIR}/missiles/7.png  240  56 16 14 #x0y1
	${GEN_DIR}/missiles/8.png  240  70 16 14 #x0y2
	${GEN_DIR}/missiles/9.png  256  42 16 14 #x1y0
	${GEN_DIR}/missiles/10.png 256  56 16 14 #x1y1
	${GEN_DIR}/missiles/11.png 256  70 16 14 #x1y2
	# type 2: fireball
	${GEN_DIR}/missiles/12.png 240  84 16 14 #x0y0
	${GEN_DIR}/missiles/13.png 240  98 16 14 #x0y1
	${GEN_DIR}/missiles/14.png 240 112 16 14 #x0y2
	${GEN_DIR}/missiles/15.png 256  84 16 14 #x1y0
	${GEN_DIR}/missiles/16.png 256  98 16 14 #x1y1
	${GEN_DIR}/missiles/17.png 256 112 16 14 #x1y2
	# type 3: pike
	${GEN_DIR}/missiles/18.png 240 126 16 14 #x0y0
	${GEN_DIR}/missiles/19.png 240 140 16 14 #x0y1
	${GEN_DIR}/missiles/20.png 240 154 16 14 #x0y2
	${GEN_DIR}/missiles/21.png 256 126 16 14 #x1y0
	${GEN_DIR}/missiles/22.png 256 140 16 14 #x1y1
	${GEN_DIR}/missiles/23.png 256 154 16 14 #x1y2
	# type 4: phantom
	${GEN_DIR}/missiles/24.png 272   0 16 14 #x0y0
	${GEN_DIR}/missiles/25.png 272  14 16 14 #x0y1
	${GEN_DIR}/missiles/26.png 272  28 16 14 #x0y2
	${GEN_DIR}/missiles/27.png 288   0 16 14 #x1y0
	${GEN_DIR}/missiles/28.png 288  14 16 14 #x1y1
	${GEN_DIR}/missiles/29.png 288  28 16 14 #x1y2
	# type 5: xbow
	${GEN_DIR}/missiles/30.png 272  42 16 14 #x0y0
	${GEN_DIR}/missiles/31.png 272  56 16 14 #x0y1
	${GEN_DIR}/missiles/32.png 272  70 16 14 #x0y2
	${GEN_DIR}/missiles/33.png 288  42 16 14 #x1y0
	${GEN_DIR}/missiles/34.png 288  56 16 14 #x1y1
	${GEN_DIR}/missiles/35.png 288  70 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/missiles DESTINATION ${GEN_DIR}/missiles.png
	TILE_PATHS ${TILES_MISSILES_LIST}
)

convertBitmaps(
	INTERLEAVED TARGET ${GAME_EXECUTABLE} PALETTE ${GAME_PLT_PATH}
	MASK_COLOR "#000000"
	SOURCES
		${GEN_DIR}/missiles.png
	DESTINATIONS
		${DATA_DIR}/missiles.bm
	MASKS
		${DATA_DIR}/missiles_mask.bm
)
