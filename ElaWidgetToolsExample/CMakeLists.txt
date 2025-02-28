cmake_minimum_required(VERSION 3.5)

project(ElaWidgetToolsExample VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

FILE(GLOB ORIGIN *.cpp *.h)
FILE(GLOB MODELVIEW ModelView/*.h ModelView/*.cpp)
FILE(GLOB EAXMPLEPAGE ExamplePage/*.h ExamplePage/*.cpp)

source_group(ModelView FILES ${MODELVIEW})
source_group(ExamplePage FILES ${EAXMPLEPAGE})


set(PROJECT_SOURCES
    ${ORIGIN}
    ${MODELVIEW}
    ${EAXMPLEPAGE}
)

if (${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(${PROJECT_NAME}
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    #遍历所有资源文件
    file(GLOB_RECURSE RES_PATHS *.png *.jpg *.svg *.ico *.ttf *.webp *.js)
    foreach (filepath ${RES_PATHS})
        string(REPLACE "${CMAKE_CURRENT_SOURCE_DIR}/" "" filename ${filepath})
        list(APPEND resource_files ${filename})
    endforeach (filepath)

    qt_add_resources(${PROJECT_NAME} "ElaWidgetToolsExample"
        RESOURCES PREFIX "/"
        FILES
        ${resource_files}
    )
else ()
    qt5_add_big_resources(PROJECT_SOURCES
        ElaWidgetToolsExample.qrc
    )
    add_executable(${PROJECT_NAME}
        ${PROJECT_SOURCES}
    )
endif ()

#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
if (WIN32)
    target_include_directories(${PROJECT_NAME} PUBLIC
        ExamplePage
        ModelView
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        ElaWidgetTools
        ElaPacketIO
    )
else ()
    target_include_directories(${PROJECT_NAME} PUBLIC
        ExamplePage
        ModelView
    )
    target_link_libraries(${PROJECT_NAME} PRIVATE
        Qt${QT_VERSION_MAJOR}::Widgets
        ElaWidgetTools
    )
endif ()

if (${QT_VERSION} VERSION_LESS 6.1.0)
    set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.${PROJECT_NAME})
endif ()
set_target_properties(${PROJECT_NAME} PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if (QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(${PROJECT_NAME})
endif ()

# 添加以下代码，用于复制运行时依赖到构建目录
if (WIN32)
    # 定义构建目录中可执行文件所在的目录
    set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/${PROJECT_NAME})

    # 复制 Qt 依赖 DLL 到构建目录
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            # 创建必要的子目录
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EXECUTABLE_OUTPUT_PATH}/platforms"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EXECUTABLE_OUTPUT_PATH}/generic"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EXECUTABLE_OUTPUT_PATH}/imageformats"
            COMMAND ${CMAKE_COMMAND} -E make_directory "${EXECUTABLE_OUTPUT_PATH}/styles"

            # 复制 Qt 平台插件
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QT_SDK_DIR}/plugins/platforms/qwindows.dll"
            "${EXECUTABLE_OUTPUT_PATH}/platforms/"

            # 复制 Qt 触摸插件
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QT_SDK_DIR}/plugins/generic/qtuiotouchplugin.dll"
            "${EXECUTABLE_OUTPUT_PATH}/generic/"

            # 复制 Qt 样式插件
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QT_SDK_DIR}/plugins/styles/qmodernwindowsstyle.dll"
            "${EXECUTABLE_OUTPUT_PATH}/styles/"

            # 复制 Qt 核心 DLL
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Widgets.dll"
            "${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Core.dll"
            "${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Gui.dll"
            "${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Network.dll"
            "${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Xml.dll"
            "${EXECUTABLE_OUTPUT_PATH}/"
    )

    # 复制项目 DLL
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "$<TARGET_FILE:ElaWidgetTools>"
            "${EXECUTABLE_OUTPUT_PATH}/"
    )

    if (TARGET ElaPacketIO)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "$<TARGET_FILE:ElaPacketIO>"
                "${EXECUTABLE_OUTPUT_PATH}/"
        )
    endif()

    # 复制图像格式插件
    foreach(imgfmt qgif qicns qico qjpeg qtga qtiff qwbmp qwebp)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                "${QT_SDK_DIR}/plugins/imageformats/${imgfmt}.dll"
                "${EXECUTABLE_OUTPUT_PATH}/imageformats/"
        )
    endforeach()
endif()


if (WIN32)
    include(GNUInstallDirs)
    install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
    )
    if (MSVC)
        install(
            FILES $<TARGET_PDB_FILE:${PROJECT_NAME}>
            DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME} OPTIONAL)
    endif ()
    # QT依赖安装 只做Release安装 Debug自行打包
    install(FILES ${QT_SDK_DIR}/plugins/platforms/qwindows.dll DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/platforms)
    install(FILES ${QT_SDK_DIR}/plugins/generic/qtuiotouchplugin.dll DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/generic)
    install(
        FILES ${QT_SDK_DIR}/plugins/imageformats/qgif.dll
        FILES ${QT_SDK_DIR}/plugins/imageformats/qicns.dll
        FILES ${QT_SDK_DIR}/plugins/imageformats/qico.dll
        FILES ${QT_SDK_DIR}/plugins/imageformats/qjpeg.dll
        FILES ${QT_SDK_DIR}/plugins/imageformats/qtga.dll
        FILES ${QT_SDK_DIR}/plugins/imageformats/qtiff.dll
        FILES ${QT_SDK_DIR}/plugins/imageformats/qwbmp.dll
        FILES ${QT_SDK_DIR}/plugins/imageformats/qwebp.dll
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/imageformats
    )
    install(FILES ${QT_SDK_DIR}/plugins/styles/qmodernwindowsstyle.dll DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/styles)
    FILE(GLOB TRANSLATIONS ${QT_SDK_DIR}/translations_install/*.qm)
    install(FILES ${TRANSLATIONS} DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}/translations)
    install(
        FILES ${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Widgets.dll
        FILES ${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Core.dll
        FILES ${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Gui.dll
        FILES ${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Network.dll
        FILES ${QT_SDK_DIR}/bin/Qt${QT_VERSION_MAJOR}Xml.dll
        DESTINATION ${CMAKE_INSTALL_PREFIX}/${PROJECT_NAME}
    )
endif ()

