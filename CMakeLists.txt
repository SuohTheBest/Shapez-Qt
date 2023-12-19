cmake_minimum_required(VERSION 3.24)
project(projDrill)
set(CMAKE_PREFIX_PATH "D:/qt/5.14.2/mingw73_64/lib/cmake")
set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(src/map)

add_executable(projDrill
        src/map/MapCreator.cpp
        src/map/MapCreator.h
        src/map/MapDisplayWidget.cpp
        src/map/MapDisplayWidget.h
        main.cpp
        src/action/ConstructionButton.cpp src/machine/MachineBase.cpp src/machine/MachineCenter.h src/machine/MachineCenter.cpp src/machine/MachineCutter.cpp src/machine/MachineRubbishBin.cpp src/map/MapBlockItem.cpp src/machine/MachineConveyor.cpp src/machine/ItemGetter.h src/machine/ItemSender.h src/machine/ItemSender.cpp src/machine/ItemGetter.cpp src/machine/MachineDriller.cpp src/item/MachineShadow.h src/item/MachineShadow.cpp src/action/RotateButton.h src/action/RotateButton.cpp src/item/ItemBase.cpp menuwidget.h menuwidget.cpp mainwindow.cpp mainwindow.h src/action/SaveButton.cpp src/action/SaveButton.h src/action/savewidget.cpp src/action/savewidget.h src/action/PauseButton.cpp src/action/PauseButton.h src/action/BackToMenu.h src/action/BackToMenu.cpp src/action/choosetask.cpp src/action/choosetask.h src/action/levelup.cpp src/action/levelup.h src/action/DeleteButton.h src/action/DeleteButton.cpp src/machine/MachineBallMill.cpp src/machine/MachineBallMill.h src/machine/MachineKiln.cpp src/machine/MachineKiln.h)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(projDrill
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets
        )

if (WIN32)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()

