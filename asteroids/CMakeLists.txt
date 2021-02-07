list(APPEND asteroids_files
	"Asteroids.cpp"
	"Asteroids.h"
	"Bullet.cpp"
	"Bullet.h"
	"Debris.cpp"
	"Debris.h"
	"Game.cpp"
	"Game.h"
	"main.cpp"
	"Persistent.cpp"
	"Persistent.h"
	"SpaceShip.cpp"
	"SpaceShip.h"
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${asteroids_files})

add_executable(asteroids WIN32 ${asteroids_files})
sf_target_compile_warnings(asteroids)
sf_target_compile_warnings_as_errors(asteroids OPTIONAL)

target_include_directories(asteroids PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(asteroids PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY
		"${CMAKE_SOURCE_DIR}"
)

target_link_libraries(asteroids PUBLIC gemcutter)
