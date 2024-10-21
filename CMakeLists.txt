cmake_minimum_required(VERSION 3.16)

project(bkt VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#  your home director
if(UNIX OR APPLE)
    set(HOME_DIR $ENV{HOME})
elseif(WIN32)
    set(HOME_DIR $ENV{USERPROFILE})
endif()

# print for debugging
message(STATUS "Home directory: ${HOME_DIR}")

#set(QT_DEBUG_FIND_PACKAGE ON)

# Add WebEngineWidgets to your needs.
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql Network Multimedia MultimediaWidgets Designer Charts WebView) # WebEngineWidgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql Network Multimedia MultimediaWidgets Designer Charts WebView) # WebEngineWidgets)
#find_package(Qt6 REQUIRED COMPONENTS WebEngineWidgets)

# Set variables.
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

# Set includepaths for header files etc.
include_directories(${SRC_DIR}/../)
include_directories(${SRC_DIR}/../../)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/emc)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/emc)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/emc/nml_intf)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/emc/motion)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/rtapi)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/libnml/nml)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/libnml/rcs)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/libnml/cms)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/libnml/posemath)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/emc/rs274ngc)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/emc/usr_intf/axis/extensions)
include_directories(${HOME_DIR}/linuxcnc-source-dir/src/hal)
include_directories(${HOME_DIR}/Qt/Tools/QtCreator/lib/Qt/plugins/designer)
include_directories(${HOME_DIR}/.progetti/wled-designer-plugin)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        WLED.cpp
        WLED.h
        mainwindow.ui
        #hal_priv.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(bkt
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET bkt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
#else()
#    if(ANDROID)
#        add_library(bkt SHARED
#            ${PROJECT_SOURCES}
#        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    else()
#        add_executable(bkt
#            ${PROJECT_SOURCES}
#        )
#    endif()
endif()

# Set include paths for libraries to link.
add_library(linuxcnchal SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(linuxcnchal PROPERTIES
    IMPORTED_LOCATION "${HOME_DIR}/linuxcnc-source-dir/lib/liblinuxcnchal.so"
    INTERFACE_INCLUDE_DIRECTORIES "${HOME_DIR}/linuxcnc-source-dir/include"
    )

add_library(linuxcncini SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(linuxcncini PROPERTIES
  IMPORTED_LOCATION "${HOME_DIR}/linuxcnc-source-dir/lib/liblinuxcncini.so"
  INTERFACE_INCLUDE_DIRECTORIES "${HOME_DIR}/linuxcnc-source-dir/include"
)

add_library(linuxcnc_a STATIC IMPORTED) # or STATIC instead of SHARED
set_target_properties(linuxcnc_a PROPERTIES
  # IMPORTED_LOCATION "/home/user/lcncladdertest/lib/liblinuxcnc.a"
  IMPORTED_LOCATION "${HOME_DIR}/linuxcnc-source-dir/lib//liblinuxcnc.a"
  INTERFACE_INCLUDE_DIRECTORIES "${HOME_DIR}/linuxcnc-source-dir/include"
)

# Set include paths for libraries to link.
add_library(nml SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(nml PROPERTIES
  IMPORTED_LOCATION "${HOME_DIR}/linuxcnc-source-dir/lib/libnml.so"
  INTERFACE_INCLUDE_DIRECTORIES "${HOME_DIR}/linuxcnc-source-dir/include"
)

add_library(rs274_ SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(rs274_ PROPERTIES
    IMPORTED_LOCATION "${HOME_DIR}/linuxcnc-source-dir/lib/librs274.so"
    INTERFACE_INCLUDE_DIRECTORIES "${HOME_DIR}/linuxcnc-source-dir/include"
    )

add_library(tooldata SHARED IMPORTED) # or STATIC instead of SHARED
set_target_properties(tooldata PROPERTIES
    # IMPORTED_LOCATION "/home/user/lcncladdertest/lib/libtooldata.so"
    IMPORTED_LOCATION "${HOME_DIR}/linuxcnc-source-dir/lib/libtooldata.so"
    INTERFACE_INCLUDE_DIRECTORIES "${HOME_DIR}/linuxcnc-source-dir/include"
    )

if (BUILD_USPACE)
    add_definitions(-DULAPI)
else ()
    add_definitions(-DRTAPI)
endif ()


target_link_libraries(bkt PRIVATE

    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Multimedia
    Qt${QT_VERSION_MAJOR}::MultimediaWidgets
    Qt${QT_VERSION_MAJOR}::Designer
    Qt${QT_VERSION_MAJOR}::Charts
    #Qt${QT_VERSION_MAJOR}::WebEngineWidgets
    Qt${QT_VERSION_MAJOR}::WebView

    linuxcnchal linuxcncini linuxcnc_a nml rs274_ tooldata
    GLU GL tirpc
    )

#target_link_libraries(bkt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.bkt)
endif()
set_target_properties(bkt PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS bkt
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(bkt)
endif()
