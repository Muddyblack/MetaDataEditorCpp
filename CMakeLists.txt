
set(CMAKE_PREFIX_PATH "C:/Qt/6.6.2/mingw_64")

cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_COMPILER "C:/Qt/Tools/mingw1120_64/bin/c++.exe")
set(CMAKE_C_COMPILER "C:/Qt/Tools/mingw1120_64/bin/gcc.exe")


project(MetaDataEditor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)  # Add MultimediaWidgets here
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets Multimedia MultimediaWidgets REQUIRED)  # Add MultimediaWidgets here


set(PROJECT_SOURCES
        src/app/main.cpp
        src/app/src/ImageEditorGUI.cpp
        src/app/src/Styles.cpp
        src/app/src/TagWidget.cpp
        src/app/src/TagTexEdit.cpp
        src/app/src/MetaDataHandler.cpp
)

set(PROJECT_HEADERS
        src/app/include/ImageEditorGUI.h
        src/app/include/Styles.h
        src/app/include/TagWidget.h
        src/app/include/TagTextEdit.h
        src/app/include/MetaDataHandler.h
)

set(PROJECT_RESOURCES
        src/app/resources.qrc
        app.rc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(MetaDataEditor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        ${PROJECT_HEADERS}
        ${PROJECT_RESOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET MetaDataEditor APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(MetaDataEditor SHARED
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_RESOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(MetaDataEditor
            ${PROJECT_SOURCES}
            ${PROJECT_HEADERS}
            ${PROJECT_RESOURCES}
        )
    endif()
endif()

target_include_directories(MetaDataEditor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(MetaDataEditor PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src/app/include)


target_link_libraries(MetaDataEditor PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Multimedia Qt${QT_VERSION_MAJOR}::MultimediaWidgets)  

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.MetaDataEditor)
endif()

if(WIN32)
    target_sources(MetaDataEditor PRIVATE app.rc)
endif()
set_target_properties(MetaDataEditor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE FALSE
)

include(GNUInstallDirs)
install(TARGETS MetaDataEditor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(MetaDataEditor)
endif()

add_custom_command(TARGET MetaDataEditor POST_BUILD
    COMMAND "${CMAKE_PREFIX_PATH}/bin/windeployqt.exe" "$<TARGET_FILE:MetaDataEditor>"
)