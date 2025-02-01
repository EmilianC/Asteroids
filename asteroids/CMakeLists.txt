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
add_dependencies(asteroids ASSETS)
sf_target_compile_warnings(asteroids)
sf_target_compile_warnings_as_errors(asteroids OPTIONAL)

target_include_directories(asteroids PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
set_target_properties(asteroids PROPERTIES
	VS_DEBUGGER_WORKING_DIRECTORY
		"${CMAKE_SOURCE_DIR}"
)

target_link_libraries(asteroids PUBLIC gemcutter)

target_precompile_headers(asteroids
	PRIVATE
		<algorithm>
		<string>
		<vector>
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Application/Logging.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Application/Reflection.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Entity/Entity.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Math/Matrix.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Math/Quaternion.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Math/Transform.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Math/Vector.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Resource/Shareable.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Utilities/Meta.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Utilities/Random.h
		${CMAKE_SOURCE_DIR}/external/gemcutter/gemcutter/Utilities/ScopeGuard.h
)