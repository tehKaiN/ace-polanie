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
	${GEN_DIR}/missiles/9.png  240  42 16 14 #x0y0
	${GEN_DIR}/missiles/10.png 240  56 16 14 #x0y1
	${GEN_DIR}/missiles/11.png 240  70 16 14 #x0y2
	${GEN_DIR}/missiles/12.png 256  42 16 14 #x1y0
	${GEN_DIR}/missiles/13.png 256  56 16 14 #x1y1
	${GEN_DIR}/missiles/14.png 256  70 16 14 #x1y2
	# type 2: fireball
	${GEN_DIR}/missiles/18.png 240  84 16 14 #x0y0
	${GEN_DIR}/missiles/19.png 240  98 16 14 #x0y1
	${GEN_DIR}/missiles/20.png 240 112 16 14 #x0y2
	${GEN_DIR}/missiles/21.png 256  84 16 14 #x1y0
	${GEN_DIR}/missiles/22.png 256  98 16 14 #x1y1
	${GEN_DIR}/missiles/23.png 256 112 16 14 #x1y2
	# type 3: pike
	${GEN_DIR}/missiles/27.png 240 126 16 14 #x0y0
	${GEN_DIR}/missiles/28.png 240 140 16 14 #x0y1
	${GEN_DIR}/missiles/29.png 240 154 16 14 #x0y2
	${GEN_DIR}/missiles/30.png 256 126 16 14 #x1y0
	${GEN_DIR}/missiles/31.png 256 140 16 14 #x1y1
	${GEN_DIR}/missiles/32.png 256 154 16 14 #x1y2
	# type 4: phantom
	${GEN_DIR}/missiles/36.png 272   0 16 14 #x0y0
	${GEN_DIR}/missiles/37.png 272  14 16 14 #x0y1
	${GEN_DIR}/missiles/38.png 272  28 16 14 #x0y2
	${GEN_DIR}/missiles/39.png 288   0 16 14 #x1y0
	${GEN_DIR}/missiles/40.png 288  14 16 14 #x1y1
	${GEN_DIR}/missiles/41.png 288  28 16 14 #x1y2
	# type 5: xbow
	${GEN_DIR}/missiles/45.png 272  42 16 14 #x0y0
	${GEN_DIR}/missiles/46.png 272  56 16 14 #x0y1
	${GEN_DIR}/missiles/47.png 272  70 16 14 #x0y2
	${GEN_DIR}/missiles/48.png 288  42 16 14 #x1y0
	${GEN_DIR}/missiles/49.png 288  56 16 14 #x1y1
	${GEN_DIR}/missiles/50.png 288  70 16 14 #x1y2
)

# flip missile frames
flipBitmaps(TARGET ${GAME_EXECUTABLE} GENERATED_FILE_LIST "TILES_MISSILES_LIST_FLIPPED"
	SOURCES
		${GEN_DIR}/missiles/0.png ${GEN_DIR}/missiles/1.png ${GEN_DIR}/missiles/2.png # arrow
		${GEN_DIR}/missiles/9.png ${GEN_DIR}/missiles/10.png ${GEN_DIR}/missiles/11.png # lightning
		${GEN_DIR}/missiles/18.png ${GEN_DIR}/missiles/19.png ${GEN_DIR}/missiles/20.png # fireball
		${GEN_DIR}/missiles/27.png ${GEN_DIR}/missiles/28.png ${GEN_DIR}/missiles/29.png # pike
		${GEN_DIR}/missiles/36.png ${GEN_DIR}/missiles/37.png ${GEN_DIR}/missiles/38.png # phantom
		${GEN_DIR}/missiles/45.png ${GEN_DIR}/missiles/46.png ${GEN_DIR}/missiles/47.png # xbow
	DESTINATIONS
		${GEN_DIR}/missiles/6.png ${GEN_DIR}/missiles/7.png ${GEN_DIR}/missiles/8.png
		${GEN_DIR}/missiles/15.png ${GEN_DIR}/missiles/16.png ${GEN_DIR}/missiles/17.png
		${GEN_DIR}/missiles/24.png ${GEN_DIR}/missiles/25.png ${GEN_DIR}/missiles/26.png
		${GEN_DIR}/missiles/33.png ${GEN_DIR}/missiles/34.png ${GEN_DIR}/missiles/35.png
		${GEN_DIR}/missiles/42.png ${GEN_DIR}/missiles/43.png ${GEN_DIR}/missiles/44.png
		${GEN_DIR}/missiles/51.png ${GEN_DIR}/missiles/52.png ${GEN_DIR}/missiles/53.png
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/missiles DESTINATION ${GEN_DIR}/missiles.png
	TILE_PATHS ${TILES_MISSILES_LIST};${TILES_MISSILES_LIST_FLIPPED}
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
