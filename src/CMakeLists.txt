find_package(OpenGL REQUIRED)
find_package(SDL REQUIRED)
find_package(SDL_image REQUIRED)
find_package(Freetype REQUIRED)
find_package(OpenAL REQUIRED)

include_directories(
    ${OPENGL_INCLUDE_DIRS}
    ${SDL_INCLUDE_DIRS}
    ${SDL_IMAGE_INCLUDE_DIRS}
    ${FREETYPE_INCLUDE_DIRS}
    ${OPENAL_INCLUDE_DIRS})

set(Drex_SRCS
    camera.cpp
    creation.cpp
    dragon.cpp
    enemy.cpp
    fog.cpp
    game.cpp
    heightmap.cpp
    hud.cpp
    imageloader.cpp
    main.cpp
    maplist.cpp
    menu.cpp
    missiles.cpp
    objects.cpp
    particles.cpp
    quaternion.cpp
    skybox.cpp
    sound.cpp
    userlist.cpp
    weather.cpp
    wings.cpp
    world.cpp

    ../vendor/OGLFT.cpp)

add_executable(drex ${Drex_SRCS})
target_link_libraries(drex
    ${OPENGL_LIBRARIES}
    ${SDL_LIBRARY}
    ${SDL_IMAGE_LIBRARIES}
    ${FREETYPE_LIBRARIES}
    ${OPENAL_LIBRARY})

install(TARGETS drex DESTINATION ${DREX_INSTALL_DIR})

if(WIN32)
    # Hide that ugly black thing called console
    set_target_properties(drex PROPERTIES WIN32_EXECUTABLE TRUE)

    include(UseMingw)
    mingw_bundle_dlls(${DREX_INSTALL_DIR}
        libfreetype-6.dll
        libgcc_s_sjlj-1.dll
        libpng14-14.dll
        libstdc++-6.dll
        OpenAL32.dll
        SDL.dll
        SDL_image.dll
        zlib1.dll)
endif()
