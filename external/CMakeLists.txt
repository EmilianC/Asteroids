# Append to any IDE folders already set be calling scripts.
set(PARENT_FOLDER ${CMAKE_FOLDER})

# Gemcutter #
set(CMAKE_FOLDER "${PARENT_FOLDER}/Engine")
set(ENABLE_IMGUI_SUPPORT OFF CACHE BOOL "")
add_subdirectory(gemcutter)
