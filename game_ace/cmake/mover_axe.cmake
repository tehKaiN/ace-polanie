# axeman is split to 16/32px-wide images
file(MAKE_DIRECTORY ${GEN_DIR}/movers/axe16)
file(MAKE_DIRECTORY ${GEN_DIR}/movers/axe32)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_MOVER_AXE16_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/axe16/0.png    0 42 16 14 #x0y0
	${GEN_DIR}/movers/axe16/1.png    0 56 16 14 #x0y1
	${GEN_DIR}/movers/axe16/2.png    0 70 16 14 #x0y2
	${GEN_DIR}/movers/axe16/3.png   16 42 16 14 #x1y0
	${GEN_DIR}/movers/axe16/4.png   16 56 16 14 #x1y1
	${GEN_DIR}/movers/axe16/5.png   16 70 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/axe16/6.png   32 42 16 14 #x0y0
	${GEN_DIR}/movers/axe16/7.png   32 56 16 14 #x0y1
	${GEN_DIR}/movers/axe16/8.png   32 70 16 14 #x0y2
	${GEN_DIR}/movers/axe16/9.png   48 42 16 14 #x1y0
	${GEN_DIR}/movers/axe16/10.png  48 56 16 14 #x1y1
	${GEN_DIR}/movers/axe16/11.png  48 70 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/axe16/12.png  64 42 16 14 #x0y0
	${GEN_DIR}/movers/axe16/13.png  64 56 16 14 #x0y1
	${GEN_DIR}/movers/axe16/14.png  64 70 16 14 #x0y2
	${GEN_DIR}/movers/axe16/15.png  80 42 16 14 #x1y0
	${GEN_DIR}/movers/axe16/16.png  80 56 16 14 #x1y1
	${GEN_DIR}/movers/axe16/17.png  80 70 16 14 #x1y2
)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_MOVER_AXE32_LIST"
	DESTINATIONS
	# phase 3:
	${GEN_DIR}/movers/axe32/0.png  96 49 24 21 #x0y0
	${GEN_DIR}/movers/axe32/1.png  96 70 24 14 #x0y1
	${GEN_DIR}/movers/axe32/2.png 152 42 24 21 #x0y2
	${GEN_DIR}/movers/axe32/3.png 120 49 16 21 #x1y0
	${GEN_DIR}/movers/axe32/4.png 120 70 16 14  #x1y1
	${GEN_DIR}/movers/axe32/5.png 136 42 16 21  #x1y2
	# phase 4:
	${GEN_DIR}/movers/axe32/6.png  176 49 24 21 #x0y0
	${GEN_DIR}/movers/axe32/7.png  176 70 24 14 #x0y1
	${GEN_DIR}/movers/axe32/8.png  152 63 24 21 #x0y2
	${GEN_DIR}/movers/axe32/9.png  200 49 16 21 #x1y0
	${GEN_DIR}/movers/axe32/10.png 200 70 16 14 #x1y1
	${GEN_DIR}/movers/axe32/11.png 136 63 16 21 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/axe16 DESTINATION ${GEN_DIR}/movers/axe16.png
	TILE_PATHS ${TILES_MOVER_AXE16_LIST}
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 32 VARIABLE_HEIGHT PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/axe32 DESTINATION ${GEN_DIR}/movers/axe32.png
	TILE_PATHS ${TILES_MOVER_AXE32_LIST}
)
