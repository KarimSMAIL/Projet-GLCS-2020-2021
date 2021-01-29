cmake_minimum_required(VERSION 3.18)

add_library(boost
		src/cmdline.cpp
		src/config_file.cpp
		src/convert.cpp
		src/options_description.cpp
		src/parsers.cpp
		src/positional_options.cpp
		src/split.cpp
		src/utf8_codecvt_facet.cpp
		src/value_semantic.cpp
		src/variables_map.cpp
		src/winmain.cpp
)
target_include_directories(boost PUBLIC include/)
target_link_libraries(boost PUBLIC GLCS2020_project::baselib)
add_library(GLCS2020_project::boost ALIAS boost)
