idf_build_get_property(project_dir PROJECT_DIR)
file(GLOB srcs *.c)
idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS "."
                    )