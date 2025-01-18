include_directories(${WormsRemade_SOURCE_DIR}/include)

set(CppFiles "App.cpp" "WindowManager.cpp" "CameraControlSystem.cpp" "PhysicsSystem.cpp" "PlayerControlSystem.cpp" "RenderSystem.cpp")
list(APPEND CppFiles "App.cpp" "WindowManager.cpp" "CameraControlSystem.cpp" "PhysicsSystem.cpp" "PlayerControlSystem.cpp" "RenderSystem.cpp")

add_executable(${PROJECT_NAME} ${CppFiles})

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE 
    /opt/homebrew/include/SDL2
)

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    /opt/homebrew/Cellar/sdl2_image/2.8.4/include
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    /opt/homebrew/lib/libSDL2.dylib
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    /opt/homebrew/Cellar/sdl2_image/2.8.4/lib/libSDL2_image.dylib
)

# To link a library 