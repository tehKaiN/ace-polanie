file(MAKE_DIRECTORY ${GEN_DIR}/picture)
file(MAKE_DIRECTORY ${GEN_DIR}/picture_dry_earth)
file(MAKE_DIRECTORY ${GEN_DIR}/picture_tree)
file(MAKE_DIRECTORY ${DATA_DIR}/picture)

# INCONSISTENT SIZE: 23x18
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game1.png
	GENERATED_FILE_LIST "TILES_PICTURE_LIST_DRY_EARTH"
	DESTINATIONS
	${GEN_DIR}/picture_dry_earth/0.png 235 134 32 18 # 22: DRY_EARTH_0
	${GEN_DIR}/picture_dry_earth/1.png 235 153 32 18 # 23: DRY_EARTH_1
	${GEN_DIR}/picture_dry_earth/2.png 235 172 32 18 # 24: DRY_EARTH_2
)

# INCONSISTENT SIZE: 32x14
extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game1.png
	GENERATED_FILE_LIST "TILES_PICTURE_LIST_TREE"
	DESTINATIONS
	${GEN_DIR}/picture_tree/0.png   11 120 32 14 # 113: TREE_0_BOTTOM
	${GEN_DIR}/picture_tree/1.png   43 120 32 14 # 114: TREE_1_BOTTOM
	${GEN_DIR}/picture_tree/2.png   75 120 32 14 # 115: TREE_2_BOTTOM
	${GEN_DIR}/picture_tree/3.png  107 120 32 14 # 116: TREE_3_BOTTOM
	${GEN_DIR}/picture_tree/4.png  139 120 32 14 # 117: TREE_4_BOTTOM
	${GEN_DIR}/picture_tree/5.png  171 120 32 14 # 118: TREE_5_BOTTOM
	${GEN_DIR}/picture_tree/6.png  203 120 32 14 # 119: TREE_6_BOTTOM

	${GEN_DIR}/picture_tree/7.png   11 106 32 14 # 120: TREE_0_TOP
	${GEN_DIR}/picture_tree/8.png   43 106 32 14 # 121: TREE_1_TOP
	${GEN_DIR}/picture_tree/9.png   75 106 32 14 # 122: TREE_2_TOP
	${GEN_DIR}/picture_tree/10.png 107 106 32 14 # 123: TREE_3_TOP
	${GEN_DIR}/picture_tree/11.png 139 106 32 14 # 124: TREE_4_TOP
	${GEN_DIR}/picture_tree/12.png 171 106 32 14 # 125: TREE_5_TOP
	${GEN_DIR}/picture_tree/13.png 203 106 32 14 # 126: TREE_6_TOP
)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game1.png
	GENERATED_FILE_LIST "TILES_PICTURE_LIST_GAME1"
	DESTINATIONS

	${GEN_DIR}/picture/0.png  11 36 16 14 # GRASS_0
	${GEN_DIR}/picture/1.png  27 36 16 14 # GRASS_1
	${GEN_DIR}/picture/2.png  43 36 16 14 # GRASS_2

	${GEN_DIR}/picture/9.png  11 92 16 14 # ROCK_0
	${GEN_DIR}/picture/10.png 11 92 16 14 # ROCK_1
	${GEN_DIR}/picture/11.png 11 92 16 14 # ROCK_2
	${GEN_DIR}/picture/12.png 11 92 16 14 # ROCK_3
	${GEN_DIR}/picture/13.png 11 92 16 14 # ROCK_4
	${GEN_DIR}/picture/14.png 11 92 16 14 # ROCK_5
	${GEN_DIR}/picture/15.png 11 92 16 14 # ROCK_6
	${GEN_DIR}/picture/16.png 11 92 16 14 # ROCK_7
	${GEN_DIR}/picture/17.png 11 92 16 14 # ROCK_8
	${GEN_DIR}/picture/18.png 11 92 16 14 # ROCK_9
	${GEN_DIR}/picture/19.png 11 92 16 14 # ROCK_10
	${GEN_DIR}/picture/20.png 11 92 16 14 # ROCK_11
	${GEN_DIR}/picture/21.png 11 92 16 14 # ROCK_12

	# 22..24: Dry earth stored separately

	${GEN_DIR}/picture/25.png  11 134 16 14 # ROAD_0
	${GEN_DIR}/picture/26.png  27 134 16 14 # ROAD_1
	${GEN_DIR}/picture/27.png  43 134 16 14 # ROAD_2
	${GEN_DIR}/picture/28.png  59 134 16 14 # ROAD_3
	${GEN_DIR}/picture/29.png  75 134 16 14 # ROAD_4
	${GEN_DIR}/picture/30.png  91 134 16 14 # ROAD_5
	${GEN_DIR}/picture/31.png 107 134 16 14 # ROAD_6
	${GEN_DIR}/picture/32.png 123 134 16 14 # ROAD_7
	${GEN_DIR}/picture/33.png 139 134 16 14 # ROAD_8
	${GEN_DIR}/picture/34.png 155 134 16 14 # ROAD_9

	${GEN_DIR}/picture/35.png  11 148 16 14 # ROAD_10
	${GEN_DIR}/picture/36.png  27 148 16 14 # ROAD_11
	${GEN_DIR}/picture/37.png  43 148 16 14 # ROAD_12
	${GEN_DIR}/picture/38.png  59 148 16 14 # ROAD_13
	${GEN_DIR}/picture/39.png  75 148 16 14 # ROAD_14
	${GEN_DIR}/picture/40.png  91 148 16 14 # ROAD_15
	${GEN_DIR}/picture/41.png 107 148 16 14 # ROAD_16
	${GEN_DIR}/picture/42.png 123 148 16 14 # ROAD_17
	${GEN_DIR}/picture/43.png 139 148 16 14 # ROAD_18
	${GEN_DIR}/picture/44.png 155 148 16 14 # ROAD_19
	${GEN_DIR}/picture/45.png 171 148 16 14 # ROAD_20

	${GEN_DIR}/picture/46.png  11 162 16 14 # BRIDGE_0
	${GEN_DIR}/picture/47.png  27 162 16 14 # BRIDGE_1
	${GEN_DIR}/picture/48.png  43 162 16 14 # BRIDGE_2
	${GEN_DIR}/picture/49.png  59 162 16 14 # BRIDGE_3
	${GEN_DIR}/picture/50.png  75 162 16 14 # BRIDGE_4
	${GEN_DIR}/picture/51.png  91 162 16 14 # BRIDGE_5
	${GEN_DIR}/picture/52.png 107 162 16 14 # BRIDGE_6
	${GEN_DIR}/picture/53.png 123 162 16 14 # BRIDGE_7

	${GEN_DIR}/picture/54.png 59 36 16 14 # GADGET_0
	${GEN_DIR}/picture/55.png 75 36 16 14 # GADGET_1
	${GEN_DIR}/picture/56.png 91 36 16 14 # GADGET_2
	${GEN_DIR}/picture/57.png 107 36 16 14 # GADGET_3
	${GEN_DIR}/picture/58.png 123 36 16 14 # GADGET_4
	${GEN_DIR}/picture/59.png 139 36 16 14 # GADGET_5
	${GEN_DIR}/picture/60.png 155 36 16 14 # GADGET_6
	${GEN_DIR}/picture/61.png 171 36 16 14 # GADGET_7
	${GEN_DIR}/picture/62.png 187 36 16 14 # GADGET_8
	${GEN_DIR}/picture/63.png 203 36 16 14 # GADGET_9
	${GEN_DIR}/picture/64.png 219 36 16 14 # GADGET_10

	${GEN_DIR}/picture/65.png 187 148 16 14 # GADGET_11
	${GEN_DIR}/picture/66.png 203 148 16 14 # GADGET_12
	${GEN_DIR}/picture/67.png 219 148 16 14 # GADGET_13

	${GEN_DIR}/picture/68.png 139 162 16 14 # GADGET_14
	${GEN_DIR}/picture/69.png 155 162 16 14 # GADGET_15
	${GEN_DIR}/picture/70.png 171 162 16 14 # GADGET_16
	${GEN_DIR}/picture/71.png 187 162 16 14 # GADGET_17
	${GEN_DIR}/picture/72.png 203 162 16 14 # GADGET_18
	${GEN_DIR}/picture/73.png 219 162 16 14 # GADGET_19

	${GEN_DIR}/picture/74.png  11 50 16 14 # WATER_0
	${GEN_DIR}/picture/75.png  27 50 16 14 # WATER_1
	${GEN_DIR}/picture/76.png  43 50 16 14 # WATER_2
	${GEN_DIR}/picture/77.png  59 50 16 14 # WATER_3
	${GEN_DIR}/picture/78.png  75 50 16 14 # WATER_4
	${GEN_DIR}/picture/79.png  91 50 16 14 # WATER_5
	${GEN_DIR}/picture/80.png 107 50 16 14 # WATER_6
	${GEN_DIR}/picture/81.png 123 50 16 14 # WATER_7
	${GEN_DIR}/picture/82.png 139 50 16 14 # WATER_8
	${GEN_DIR}/picture/83.png 155 50 16 14 # WATER_9
	${GEN_DIR}/picture/84.png 171 50 16 14 # WATER_10
	${GEN_DIR}/picture/85.png 187 50 16 14 # WATER_11
	${GEN_DIR}/picture/86.png 203 50 16 14 # WATER_12

	${GEN_DIR}/picture/87.png  11 64 16 14 # WATER_13
	${GEN_DIR}/picture/88.png  27 64 16 14 # WATER_14
	${GEN_DIR}/picture/89.png  43 64 16 14 # WATER_15
	${GEN_DIR}/picture/90.png  59 64 16 14 # WATER_16
	${GEN_DIR}/picture/91.png  75 64 16 14 # WATER_17
	${GEN_DIR}/picture/92.png  91 64 16 14 # WATER_18
	${GEN_DIR}/picture/93.png 107 64 16 14 # WATER_19
	${GEN_DIR}/picture/94.png 123 64 16 14 # WATER_20
	${GEN_DIR}/picture/95.png 139 64 16 14 # WATER_21
	${GEN_DIR}/picture/96.png 155 64 16 14 # WATER_22
	${GEN_DIR}/picture/97.png 171 64 16 14 # WATER_23
	${GEN_DIR}/picture/98.png 187 64 16 14 # WATER_24
	${GEN_DIR}/picture/99.png 203 64 16 14 # WATER_25

	${GEN_DIR}/picture/100.png  11 78 16 14 # WATER_26
	${GEN_DIR}/picture/101.png  27 78 16 14 # WATER_27
	${GEN_DIR}/picture/102.png  43 78 16 14 # WATER_28
	${GEN_DIR}/picture/103.png  59 78 16 14 # WATER_29
	${GEN_DIR}/picture/104.png  75 78 16 14 # WATER_30
	${GEN_DIR}/picture/105.png  91 78 16 14 # WATER_31
	${GEN_DIR}/picture/106.png 107 78 16 14 # WATER_32
	${GEN_DIR}/picture/107.png 123 78 16 14 # WATER_33
	${GEN_DIR}/picture/108.png 139 78 16 14 # WATER_34
	${GEN_DIR}/picture/109.png 155 78 16 14 # WATER_35
	${GEN_DIR}/picture/110.png 171 78 16 14 # WATER_36
	${GEN_DIR}/picture/111.png 187 78 16 14 # WATER_37
	${GEN_DIR}/picture/112.png 203 78 16 14 # WATER_38

	# 113..119: Tree stored separately
)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game2.png
	GENERATED_FILE_LIST "TILES_PICTURE_LIST_GAME2"
	DESTINATIONS

	${GEN_DIR}/picture/3.png 303 28 16 14 # GRASS_3
	${GEN_DIR}/picture/4.png 303 42 16 14 # GRASS_4
	${GEN_DIR}/picture/5.png 303 56 16 14 # GRASS_5
	${GEN_DIR}/picture/6.png 303 70 16 14 # GRASS_6
	${GEN_DIR}/picture/7.png 303 84 16 14 # GRASS_7
	${GEN_DIR}/picture/8.png 303 98 16 14 # GRASS_8

	${GEN_DIR}/picture/266.png 287   0 16 14 # WALL_0
	${GEN_DIR}/picture/267.png 287  14 16 14 # WALL_1
	${GEN_DIR}/picture/268.png 287  28 16 14 # WALL_2
	${GEN_DIR}/picture/269.png 287  42 16 14 # WALL_3
	${GEN_DIR}/picture/270.png 287  56 16 14 # WALL_4
	${GEN_DIR}/picture/271.png 287  70 16 14 # WALL_5
	${GEN_DIR}/picture/272.png 287  84 16 14 # WALL_6
	${GEN_DIR}/picture/273.png 287  98 16 14 # WALL_7
	${GEN_DIR}/picture/274.png 287 112 16 14 # WALL_8
	${GEN_DIR}/picture/275.png 287 126 16 14 # WALL_9
	${GEN_DIR}/picture/276.png 287 140 16 14 # WALL_10
	${GEN_DIR}/picture/277.png 287 154 16 14 # WALL_11

	${GEN_DIR}/picture/278.png 303 112 16 14 # SHIELD_0
	${GEN_DIR}/picture/279.png 303 126 16 14 # SHIELD_1
	${GEN_DIR}/picture/280.png 303 140 16 14 # SHIELD_2
	${GEN_DIR}/picture/281.png 303 154 16 14 # SHIELD_3

	${GEN_DIR}/picture/282.png 303  0 16 14 # HEAL_0
	${GEN_DIR}/picture/283.png 303 14 16 14 # HEAL_1
)

extractBitmaps(TARGET ${GAME_EXECUTABLE} SOURCE ${RES_DIR}/game4.png
GENERATED_FILE_LIST "TILES_PICTURE_LIST_GAME4"
DESTINATIONS

	# Missing: 120..126

	${GEN_DIR}/picture/127.png   0 168 16 14 # CONSTRUCTION_0
	${GEN_DIR}/picture/128.png  16 168 16 14 # CONSTRUCTION_1
	${GEN_DIR}/picture/129.png  32 168 16 14 # CONSTRUCTION_2
	${GEN_DIR}/picture/130.png  48 168 16 14 # CONSTRUCTION_3
	${GEN_DIR}/picture/131.png  64 168 16 14 # CONSTRUCTION_4
	${GEN_DIR}/picture/132.png  80 168 16 14 # CONSTRUCTION_5
	${GEN_DIR}/picture/133.png  96 168 16 14 # CONSTRUCTION_6
	${GEN_DIR}/picture/134.png 112 168 16 14 # CONSTRUCTION_7
	${GEN_DIR}/picture/135.png 128 168 16 14 # CONSTRUCTION_8

	# Missing: 136

	${GEN_DIR}/picture/137.png   0 84 16 14 # BUILDING_0_FULL_0
	${GEN_DIR}/picture/138.png  16 84 16 14 # BUILDING_0_FULL_1
	${GEN_DIR}/picture/139.png  32 84 16 14 # BUILDING_0_FULL_2
	${GEN_DIR}/picture/140.png  48 84 16 14 # BUILDING_0_FULL_3
	${GEN_DIR}/picture/141.png  64 84 16 14 # BUILDING_0_FULL_4
	${GEN_DIR}/picture/142.png  80 84 16 14 # BUILDING_0_FULL_5
	${GEN_DIR}/picture/143.png  96 84 16 14 # BUILDING_0_FULL_6
	${GEN_DIR}/picture/144.png 112 84 16 14 # BUILDING_0_FULL_7
	${GEN_DIR}/picture/145.png 128 84 16 14 # BUILDING_0_FULL_8
	${GEN_DIR}/picture/146.png 144 84 16 14 # BUILDING_0_FULL_9
	${GEN_DIR}/picture/147.png   0 84 16 14 # BUILDING_0_CTR_0
	${GEN_DIR}/picture/148.png  16 84 16 14 # BUILDING_0_CTR_1
	${GEN_DIR}/picture/149.png  32 84 16 14 # BUILDING_0_CTR_2
	${GEN_DIR}/picture/150.png  48 84 16 14 # BUILDING_0_CTR_3
	${GEN_DIR}/picture/151.png  64 84 16 14 # BUILDING_0_CTR_4
	${GEN_DIR}/picture/152.png  80 84 16 14 # BUILDING_0_CTR_5
	${GEN_DIR}/picture/153.png  96 84 16 14 # BUILDING_0_CTR_6
	${GEN_DIR}/picture/154.png 112 84 16 14 # BUILDING_0_CTR_7
	${GEN_DIR}/picture/155.png 128 84 16 14 # BUILDING_0_CTR_8
	${GEN_DIR}/picture/156.png 144 84 16 14 # BUILDING_0_CTR_9

	${GEN_DIR}/picture/157.png   0 98 16 14 # BUILDING_1_FULL_0
	${GEN_DIR}/picture/158.png  16 98 16 14 # BUILDING_1_FULL_1
	${GEN_DIR}/picture/159.png  32 98 16 14 # BUILDING_1_FULL_2
	${GEN_DIR}/picture/160.png  48 98 16 14 # BUILDING_1_FULL_3
	${GEN_DIR}/picture/161.png  64 98 16 14 # BUILDING_1_FULL_4
	${GEN_DIR}/picture/162.png  80 98 16 14 # BUILDING_1_FULL_5
	${GEN_DIR}/picture/163.png  96 98 16 14 # BUILDING_1_FULL_6
	${GEN_DIR}/picture/164.png 112 98 16 14 # BUILDING_1_FULL_7
	${GEN_DIR}/picture/165.png 128 98 16 14 # BUILDING_1_FULL_8
	${GEN_DIR}/picture/166.png 144 98 16 14 # BUILDING_1_FULL_9
	${GEN_DIR}/picture/167.png   0 98 16 14 # BUILDING_1_CTR_0
	${GEN_DIR}/picture/168.png  16 98 16 14 # BUILDING_1_CTR_1
	${GEN_DIR}/picture/169.png  32 98 16 14 # BUILDING_1_CTR_2
	${GEN_DIR}/picture/170.png  48 98 16 14 # BUILDING_1_CTR_3
	${GEN_DIR}/picture/171.png  64 98 16 14 # BUILDING_1_CTR_4
	${GEN_DIR}/picture/172.png  80 98 16 14 # BUILDING_1_CTR_5
	${GEN_DIR}/picture/173.png  96 98 16 14 # BUILDING_1_CTR_6
	${GEN_DIR}/picture/174.png 112 98 16 14 # BUILDING_1_CTR_7
	${GEN_DIR}/picture/175.png 128 98 16 14 # BUILDING_1_CTR_8
	${GEN_DIR}/picture/176.png 144 98 16 14 # BUILDING_1_CTR_9

	${GEN_DIR}/picture/177.png   0 112 16 14 # BUILDING_2_FULL_0
	${GEN_DIR}/picture/178.png  16 112 16 14 # BUILDING_2_FULL_1
	${GEN_DIR}/picture/179.png  32 112 16 14 # BUILDING_2_FULL_2
	${GEN_DIR}/picture/180.png  48 112 16 14 # BUILDING_2_FULL_3
	${GEN_DIR}/picture/181.png  64 112 16 14 # BUILDING_2_FULL_4
	${GEN_DIR}/picture/182.png  80 112 16 14 # BUILDING_2_FULL_5
	${GEN_DIR}/picture/183.png  96 112 16 14 # BUILDING_2_FULL_6
	${GEN_DIR}/picture/184.png 112 112 16 14 # BUILDING_2_FULL_7
	${GEN_DIR}/picture/185.png 128 112 16 14 # BUILDING_2_FULL_8
	${GEN_DIR}/picture/186.png 144 112 16 14 # BUILDING_2_FULL_9
	${GEN_DIR}/picture/187.png   0 112 16 14 # BUILDING_2_CTR_0
	${GEN_DIR}/picture/188.png  16 112 16 14 # BUILDING_2_CTR_1
	${GEN_DIR}/picture/189.png  32 112 16 14 # BUILDING_2_CTR_2
	${GEN_DIR}/picture/190.png  48 112 16 14 # BUILDING_2_CTR_3
	${GEN_DIR}/picture/191.png  64 112 16 14 # BUILDING_2_CTR_4
	${GEN_DIR}/picture/192.png  80 112 16 14 # BUILDING_2_CTR_5
	${GEN_DIR}/picture/193.png  96 112 16 14 # BUILDING_2_CTR_6
	${GEN_DIR}/picture/194.png 112 112 16 14 # BUILDING_2_CTR_7
	${GEN_DIR}/picture/195.png 128 112 16 14 # BUILDING_2_CTR_8
	${GEN_DIR}/picture/196.png 144 112 16 14 # BUILDING_2_CTR_9

	${GEN_DIR}/picture/197.png   0 126 16 14 # BUILDING_3_FULL_0
	${GEN_DIR}/picture/198.png  16 126 16 14 # BUILDING_3_FULL_1
	${GEN_DIR}/picture/199.png  32 126 16 14 # BUILDING_3_FULL_2
	${GEN_DIR}/picture/200.png  48 126 16 14 # BUILDING_3_FULL_3
	${GEN_DIR}/picture/201.png  64 126 16 14 # BUILDING_3_FULL_4
	${GEN_DIR}/picture/202.png  80 126 16 14 # BUILDING_3_FULL_5
	${GEN_DIR}/picture/203.png  96 126 16 14 # BUILDING_3_FULL_6
	${GEN_DIR}/picture/204.png 112 126 16 14 # BUILDING_3_FULL_7
	${GEN_DIR}/picture/205.png 128 126 16 14 # BUILDING_3_FULL_8
	${GEN_DIR}/picture/206.png 144 126 16 14 # BUILDING_3_FULL_9
	${GEN_DIR}/picture/207.png   0 126 16 14 # BUILDING_3_CTR_0
	${GEN_DIR}/picture/208.png  16 126 16 14 # BUILDING_3_CTR_1
	${GEN_DIR}/picture/209.png  32 126 16 14 # BUILDING_3_CTR_2
	${GEN_DIR}/picture/210.png  48 126 16 14 # BUILDING_3_CTR_3
	${GEN_DIR}/picture/211.png  64 126 16 14 # BUILDING_3_CTR_4
	${GEN_DIR}/picture/212.png  80 126 16 14 # BUILDING_3_CTR_5
	${GEN_DIR}/picture/213.png  96 126 16 14 # BUILDING_3_CTR_6
	${GEN_DIR}/picture/214.png 112 126 16 14 # BUILDING_3_CTR_7
	${GEN_DIR}/picture/215.png 128 126 16 14 # BUILDING_3_CTR_8
	${GEN_DIR}/picture/216.png 144 126 16 14 # BUILDING_3_CTR_9

	${GEN_DIR}/picture/217.png   0 140 16 14 # BUILDING_4_FULL_0
	${GEN_DIR}/picture/218.png  16 140 16 14 # BUILDING_4_FULL_1
	${GEN_DIR}/picture/219.png  32 140 16 14 # BUILDING_4_FULL_2
	${GEN_DIR}/picture/220.png  48 140 16 14 # BUILDING_4_FULL_3
	${GEN_DIR}/picture/221.png  64 140 16 14 # BUILDING_4_FULL_4
	${GEN_DIR}/picture/222.png  80 140 16 14 # BUILDING_4_FULL_5
	${GEN_DIR}/picture/223.png  96 140 16 14 # BUILDING_4_FULL_6
	${GEN_DIR}/picture/224.png 112 140 16 14 # BUILDING_4_FULL_7
	${GEN_DIR}/picture/225.png 128 140 16 14 # BUILDING_4_FULL_8
	${GEN_DIR}/picture/226.png 144 140 16 14 # BUILDING_4_FULL_9
	${GEN_DIR}/picture/227.png   0 140 16 14 # BUILDING_4_CTR_0
	${GEN_DIR}/picture/228.png  16 140 16 14 # BUILDING_4_CTR_1
	${GEN_DIR}/picture/229.png  32 140 16 14 # BUILDING_4_CTR_2
	${GEN_DIR}/picture/230.png  48 140 16 14 # BUILDING_4_CTR_3
	${GEN_DIR}/picture/231.png  64 140 16 14 # BUILDING_4_CTR_4
	${GEN_DIR}/picture/232.png  80 140 16 14 # BUILDING_4_CTR_5
	${GEN_DIR}/picture/233.png  96 140 16 14 # BUILDING_4_CTR_6
	${GEN_DIR}/picture/234.png 112 140 16 14 # BUILDING_4_CTR_7
	${GEN_DIR}/picture/235.png 128 140 16 14 # BUILDING_4_CTR_8
	${GEN_DIR}/picture/236.png 144 140 16 14 # BUILDING_4_CTR_9

	${GEN_DIR}/picture/237.png   0 154 16 14 # BUILDING_5_FULL_0
	${GEN_DIR}/picture/238.png  16 154 16 14 # BUILDING_5_FULL_1
	${GEN_DIR}/picture/239.png  32 154 16 14 # BUILDING_5_FULL_2
	${GEN_DIR}/picture/240.png  48 154 16 14 # BUILDING_5_FULL_3
	${GEN_DIR}/picture/241.png  64 154 16 14 # BUILDING_5_FULL_4
	${GEN_DIR}/picture/242.png  80 154 16 14 # BUILDING_5_FULL_5
	${GEN_DIR}/picture/243.png  96 154 16 14 # BUILDING_5_FULL_6
	${GEN_DIR}/picture/244.png 112 154 16 14 # BUILDING_5_FULL_7
	${GEN_DIR}/picture/245.png 128 154 16 14 # BUILDING_5_FULL_8
	${GEN_DIR}/picture/246.png 144 154 16 14 # BUILDING_5_FULL_9
	${GEN_DIR}/picture/247.png   0 154 16 14 # BUILDING_5_CTR_0
	${GEN_DIR}/picture/248.png  16 154 16 14 # BUILDING_5_CTR_1
	${GEN_DIR}/picture/249.png  32 154 16 14 # BUILDING_5_CTR_2
	${GEN_DIR}/picture/250.png  48 154 16 14 # BUILDING_5_CTR_3
	${GEN_DIR}/picture/251.png  64 154 16 14 # BUILDING_5_CTR_4
	${GEN_DIR}/picture/252.png  80 154 16 14 # BUILDING_5_CTR_5
	${GEN_DIR}/picture/253.png  96 154 16 14 # BUILDING_5_CTR_6
	${GEN_DIR}/picture/254.png 112 154 16 14 # BUILDING_5_CTR_7
	${GEN_DIR}/picture/255.png 128 154 16 14 # BUILDING_5_CTR_8
	${GEN_DIR}/picture/256.png 144 154 16 14 # BUILDING_5_CTR_9

	${GEN_DIR}/picture/257.png    0 182 16 14 # RUIN_0
	${GEN_DIR}/picture/258.png   16 182 16 14 # RUIN_1
	${GEN_DIR}/picture/259.png   32 182 16 14 # RUIN_2
	${GEN_DIR}/picture/260.png   48 182 16 14 # RUIN_3
	${GEN_DIR}/picture/261.png   64 182 16 14 # RUIN_4
	${GEN_DIR}/picture/262.png   80 182 16 14 # RUIN_5
	${GEN_DIR}/picture/263.png   96 182 16 14 # RUIN_6
	${GEN_DIR}/picture/264.png  112 182 16 14 # RUIN_7
	${GEN_DIR}/picture/265.png  128 182 16 14 # RUIN_8
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 16 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/picture DESTINATION ${GEN_DIR}/picture.png
	TILE_PATHS ${TILES_PICTURE_LIST_GAME1};${TILES_PICTURE_LIST_GAME2};${TILES_PICTURE_LIST_GAME4}
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 32 HEIGHT 18 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/picture_dry_earth DESTINATION ${GEN_DIR}/picture_dry_earth.png
	TILE_PATHS ${TILES_PICTURE_LIST_DRY_EARTH}
)

convertTileset(
	TARGET ${GAME_EXECUTABLE} SIZE 32 HEIGHT 14 PALETTE ${GAME_PLT_PATH}
	INTERLEAVED SOURCE ${GEN_DIR}/picture_tree DESTINATION ${GEN_DIR}/picture_tree.png
	TILE_PATHS ${TILES_PICTURE_LIST_TREE}
)

convertBitmaps(
	INTERLEAVED TARGET ${GAME_EXECUTABLE} PALETTE ${GAME_PLT_PATH}
	MASK_COLOR "#000000"
	SOURCES
		${GEN_DIR}/picture.png
		${GEN_DIR}/picture_dry_earth.png ${GEN_DIR}/picture_tree.png
	DESTINATIONS
		${DATA_DIR}/picture/picture.bm
		${DATA_DIR}/picture/dry_earth.bm ${DATA_DIR}/picture/tree.bm
	MASKS
		${DATA_DIR}/picture/picture_mask.bm
		${DATA_DIR}/picture/dry_earth_mask.bm ${DATA_DIR}/picture/tree_mask.bm
)
