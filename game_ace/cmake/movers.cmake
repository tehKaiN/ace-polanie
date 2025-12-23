file(MAKE_DIRECTORY ${GEN_DIR}/movers)
file(MAKE_DIRECTORY ${DATA_DIR}/movers)

include(cmake/mover_cow.cmake)
include(cmake/mover_axe.cmake)
include(cmake/mover_hunter.cmake)
include(cmake/mover_priestess.cmake)
include(cmake/mover_farmer.cmake)
include(cmake/mover_mage.cmake)
include(cmake/mover_priest.cmake)
include(cmake/mover_sword.cmake)
include(cmake/mover_pike.cmake)
include(cmake/mover_knight.cmake)
include(cmake/mover_bear.cmake)
include(cmake/mover_beast.cmake)
include(cmake/mover_xbow.cmake)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game3.png
	GENERATED_FILE_LIST "TILES_MOVER_SHADOW_LIST"
	DESTINATIONS
	${GEN_DIR}/movers/shadow.png 192 168 32 28
)

convertBitmaps(
	INTERLEAVED TARGET ${GAME_EXECUTABLE} PALETTE ${GAME_PLT_PATH}
	MASK_COLOR "#000000"
	SOURCES
		${GEN_DIR}/movers/axe16.png ${GEN_DIR}/movers/axe32.png
		${GEN_DIR}/movers/bear16.png ${GEN_DIR}/movers/bear32.png
		${GEN_DIR}/movers/beast16.png ${GEN_DIR}/movers/beast32.png
		${GEN_DIR}/movers/cow.png ${GEN_DIR}/movers/farmer.png ${GEN_DIR}/movers/hunter.png
		${GEN_DIR}/movers/knight16.png ${GEN_DIR}/movers/knight32.png
		${GEN_DIR}/movers/mage.png ${GEN_DIR}/movers/pike.png ${GEN_DIR}/movers/priest.png
		${GEN_DIR}/movers/priestess.png ${GEN_DIR}/movers/shadow.png ${GEN_DIR}/movers/xbow.png
		${GEN_DIR}/movers/sword16.png ${GEN_DIR}/movers/sword32.png
	DESTINATIONS
		${DATA_DIR}/movers/axe16.bm ${DATA_DIR}/movers/axe32.bm
		${DATA_DIR}/movers/bear16.bm ${DATA_DIR}/movers/bear32.bm
		${DATA_DIR}/movers/beast16.bm ${DATA_DIR}/movers/beast32.bm
		${DATA_DIR}/movers/cow.bm ${DATA_DIR}/movers/farmer.bm ${DATA_DIR}/movers/hunter.bm
		${DATA_DIR}/movers/knight16.bm ${DATA_DIR}/movers/knight32.bm
		${DATA_DIR}/movers/mage.bm ${DATA_DIR}/movers/pike.bm ${DATA_DIR}/movers/priest.bm
		${DATA_DIR}/movers/priestess.bm ${DATA_DIR}/movers/shadow.bm ${DATA_DIR}/movers/xbow.bm
		${DATA_DIR}/movers/sword16.bm ${DATA_DIR}/movers/sword32.bm
	MASKS
		${DATA_DIR}/movers/axe16_mask.bm ${DATA_DIR}/movers/axe32_mask.bm
		${DATA_DIR}/movers/bear16_mask.bm ${DATA_DIR}/movers/bear32_mask.bm
		${DATA_DIR}/movers/beast16_mask.bm ${DATA_DIR}/movers/beast32_mask.bm
		${DATA_DIR}/movers/cow_mask.bm ${DATA_DIR}/movers/farmer_mask.bm ${DATA_DIR}/movers/hunter_mask.bm
		${DATA_DIR}/movers/knight16_mask.bm ${DATA_DIR}/movers/knight32_mask.bm
		${DATA_DIR}/movers/mage_mask.bm ${DATA_DIR}/movers/pike_mask.bm ${DATA_DIR}/movers/priest_mask.bm
		${DATA_DIR}/movers/priestess_mask.bm ${DATA_DIR}/movers/shadow_mask.bm ${DATA_DIR}/movers/xbow_mask.bm
		${DATA_DIR}/movers/sword16_mask.bm ${DATA_DIR}/movers/sword32_mask.bm
)

# X0Y0 NW
# X0Y1 W
# X0Y2 SW
# X1Y0 N
# X1Y1 Center
# X1Y2 S

# Phase:
# 0: stand
# 1-2: walk
# 3-4: action
