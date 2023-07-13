add_custom_target(
	copy_configs ALL
	COMMAND ${CMAKE_COMMAND} -E copy_directory
	${PROJECT_SOURCE_DIR}/configs
	${PROJECT_BINARY_DIR}/proxy/configs
	COMMENT "Copying configs...."
)
