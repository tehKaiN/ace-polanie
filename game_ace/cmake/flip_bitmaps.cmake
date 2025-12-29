function(flipBitmaps)
	getToolPath(bitmap_transform TOOL_BITMAP_TRANSFORM)
	set(oneValArgs TARGET GENERATED_FILE_LIST)
	set(multiValArgs SOURCES DESTINATIONS)
	cmake_parse_arguments(
		args "${options}" "${oneValArgs}" "${multiValArgs}" ${ARGN}
	)

	list(LENGTH args_SOURCES srcCount)
	list(LENGTH args_DESTINATIONS dstCount)
	if(NOT ${srcCount} EQUAL ${dstCount})
		message(FATAL_ERROR "[flipBitmaps] SOURCES count doesn't match DESTINATIONS count")
	endif()

	MATH(EXPR srcCount "${srcCount}-1")
	foreach(bitmap_idx RANGE ${srcCount}) # /path/file.png
		list(GET args_SOURCES ${bitmap_idx} bitmapPath)
		toAbsolute(bitmapPath)
		list(GET args_DESTINATIONS ${bitmap_idx} outPath)
		toAbsolute(outPath)

		add_custom_command(
			OUTPUT ${outPath}
			COMMAND ${TOOL_BITMAP_TRANSFORM} ${bitmapPath} ${outPath} -mirror y
			WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
			DEPENDS ${bitmapPath}
		)
		target_sources(${args_TARGET} PUBLIC ${outPath})
		set(generatedFiles "${generatedFiles};${outPath}")
	endforeach()

	if(DEFINED args_GENERATED_FILE_LIST)
		set(${args_GENERATED_FILE_LIST} ${generatedFiles} PARENT_SCOPE)
	endif()

endfunction()
