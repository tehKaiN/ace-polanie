file(MAKE_DIRECTORY ${GEN_DIR}/movers/mage)
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_MOVER_MAGE_LIST"
	DESTINATIONS
	# phase 0:
	${GEN_DIR}/movers/mage/0.png 160 126 16 14 #x0y0
	${GEN_DIR}/movers/mage/1.png 160 140 16 14 #x0y1
	${GEN_DIR}/movers/mage/2.png 160 154 16 14 #x0y2
	${GEN_DIR}/movers/mage/3.png 176 126 16 14 #x1y0
	${GEN_DIR}/movers/mage/4.png 176 140 16 14 #x1y1
	${GEN_DIR}/movers/mage/5.png 176 154 16 14 #x1y2
	# phase 1:
	${GEN_DIR}/movers/mage/6.png  192 126 16 14 #x0y0
	${GEN_DIR}/movers/mage/7.png  192 140 16 14 #x0y1
	${GEN_DIR}/movers/mage/8.png  192 154 16 14 #x0y2
	${GEN_DIR}/movers/mage/9.png  208 126 16 14 #x1y0
	${GEN_DIR}/movers/mage/10.png 208 140 16 14 #x1y1
	${GEN_DIR}/movers/mage/11.png 208 154 16 14 #x1y2
	# phase 2:
	${GEN_DIR}/movers/mage/12.png 224 126 16 14 #x0y0
	${GEN_DIR}/movers/mage/13.png 224 140 16 14 #x0y1
	${GEN_DIR}/movers/mage/14.png 224 154 16 14 #x0y2
	${GEN_DIR}/movers/mage/15.png 240 126 16 14 #x1y0
	${GEN_DIR}/movers/mage/16.png 240 140 16 14 #x1y1
	${GEN_DIR}/movers/mage/17.png 240 154 16 14 #x1y2
	# phase 3:
	${GEN_DIR}/movers/mage/18.png 208  84 16 14 #x0y0
	${GEN_DIR}/movers/mage/19.png 208  98 16 14 #x0y1
	${GEN_DIR}/movers/mage/20.png 208 112 16 14 #x0y2
	${GEN_DIR}/movers/mage/21.png 224  84 16 14 #x1y0
	${GEN_DIR}/movers/mage/22.png 224  98 16 14 #x1y1
	${GEN_DIR}/movers/mage/23.png 224 112 16 14 #x1y2
	# phase 4:
	${GEN_DIR}/movers/mage/24.png 240  84 16 14 #x0y0
	${GEN_DIR}/movers/mage/25.png 240  98 16 14 #x0y1
	${GEN_DIR}/movers/mage/26.png 240 112 16 14 #x0y2
	${GEN_DIR}/movers/mage/27.png 256  84 16 14 #x1y0
	${GEN_DIR}/movers/mage/28.png 256  98 16 14 #x1y1
	${GEN_DIR}/movers/mage/29.png 256 112 16 14 #x1y2
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/movers/mage DESTINATION ${GEN_DIR}/movers/mage.png
	TILE_PATHS ${TILES_MOVER_MAGE_LIST}
)
