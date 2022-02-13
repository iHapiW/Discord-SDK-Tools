cmake_minimum_required (VERSION 3.8)

project(DiscordSDKTools VERSION 1.1.0)

if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

set(buildArch "x86_64")                                                     # Should be "x86" or "x86_64"

find_package(nlohmann_json CONFIG REQUIRED)

file(GLOB SRC_List 
	"${CMAKE_CURRENT_SOURCE_DIR}/discord-files/*.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

add_executable(${PROJECT_NAME} ${SRC_List})

target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include" ${CMAKE_CURRENT_SOURCE_DIR})

target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/lib/${buildArch}")
target_link_libraries(${PROJECT_NAME} discord_game_sdk.dll.lib nlohmann_json)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD                        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different                           # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/lib/${buildArch}/discord_game_sdk.dll"       # <--this is in-file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>)                                 # <--this is out-file path