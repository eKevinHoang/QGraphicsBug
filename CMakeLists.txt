cmake_minimum_required(VERSION 3.0...3.5)
project(QGraphicsBug LANGUAGES CXX)

# Specify the available build types (configuration types)
set(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "Configs" FORCE)

# Set CXX flags for debug and release
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -march=native -funroll-loops")

# if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
#     set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the type of build." FORCE)
# endif()

# Set C++ standard to C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/cmake")

# QT6
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

# set(UI_FILES ui/MainWindow.ui)
# qt6_wrap_ui(GENERATED_UI_HEADERS ${UI_FILES})

set(HEADERS # Header files with Q_OBJECT
    include/MyRectItem.h
    include/ImageViewer.h
    include/MainWindow.h
)

# Source files
set(SOURCES
    main.cpp
    src/ImageViewer.cpp
    src/MainWindow.cpp
    src/MyRectItem.cpp
    # ${GENERATED_UI_HEADERS}
)

qt_wrap_cpp(MOC_SOURCES ${HEADERS}) # Generate moc files for headers with Q_OBJECT

# Specify include dirs
include_directories(include ${CMAKE_BINARY_DIR})
link_directories(/usr/local/lib)

# Add executables
qt_add_executable(${PROJECT_NAME} ${SOURCES} ${MOC_SOURCES})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)