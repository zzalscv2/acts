add_library(ActsExamplesTraccc INTERFACE)

target_include_directories(
    ActsExamplesTraccc
    INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)

target_link_libraries(
    ActsExamplesTraccc
    INTERFACE
        ActsCore
        ActsExamplesFramework
        ActsExamplesPropagation
        ActsPluginDetray
)

acts_compile_headers(ActsExamplesTraccc GLOB "include/**/*.hpp")

install(TARGETS ActsExamplesTraccc LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
