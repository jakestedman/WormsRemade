include_directories(
    ${WormsRemade_SOURCE_DIR}/include/
    ${WormsRemade_SOURCE_DIR}/include/Components
    ${WormsRemade_SOURCE_DIR}/include/EcsCore
    ${WormsRemade_SOURCE_DIR}/include/Maths
    ${WormsRemade_SOURCE_DIR}/include/Systems
    ${WormsRemade_SOURCE_DIR}/include/Utilities
)

set(CppFiles "App.cpp" "WindowManager.cpp" "Systems/CameraControlSystem.cpp" "Systems/PhysicsSystem.cpp" "Systems/PlayerControlSystem.cpp" "Systems/RenderSystem.cpp")
list(APPEND CppFiles "App.cpp" "WindowManager.cpp" "Systems/CameraControlSystem.cpp" "Systems/PhysicsSystem.cpp" "Systems/PlayerControlSystem.cpp" "Systems/RenderSystem.cpp")

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