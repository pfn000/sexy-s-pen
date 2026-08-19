cmake_minimum_required(VERSION 3.21)
project(SexySPen VERSION 0.3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 6.4 REQUIRED COMPONENTS Core Gui DBus Qml Quick QuickControls2)

qt_add_executable(sexy-s-pen
    src/main.cpp
    src/PenController.cpp
    src/PenController.h
)

qt_add_qml_module(sexy-s-pen
    URI SexySPen
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(sexy-s-pen PRIVATE
    Qt6::Core Qt6::Gui Qt6::DBus Qt6::Qml Qt6::Quick Qt6::QuickControls2
)

target_compile_definitions(sexy-s-pen PRIVATE QT_NO_KEYWORDS)

install(TARGETS sexy-s-pen RUNTIME DESTINATION bin)
install(FILES scripts/sexy-s-pen.desktop DESTINATION share/applications)
