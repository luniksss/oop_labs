cmake_minimum_required(VERSION 3.30)
project(updated_shapes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ./../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY  ./../lib)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

option(CODE_COVERAGE "Enable code coverage" OFF)
if (CODE_COVERAGE)
    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    endif ()
endif ()

set(SOURCE_FILES
        main.cpp
        src/ShapeController.cpp
        include/ShapeController.h
        src/ShapeCommandHandler.cpp
        include/ShapeCommandHandler.h
        src/ShapeMaker.cpp
        include/ShapeMaker.h
        src/CLineSegment.cpp
        include/CLineSegment.h
        src/CCircle.cpp
        include/CCircle.h
        src/CPoint.cpp
        include/CPoint.h
        src/CTriangle.cpp
        include/CTriangle.h
        src/CRectangle.cpp
        include/CRectangle.h
        src/Interface/IShape.h
        src/Interface/ISolidShape.h
        src/Interface/ICanvas.h
        src/Interface/ICanvasDrawable.h
        include/CCanvas.h
        src/CCanvas.cpp
)

set(TEST_SOURCE_FILES
        tests/CLineSegmentTest.cpp
        src/CLineSegment.cpp
        tests/CCircleTest.cpp
        src/CCircle.cpp
        tests/CTriangleTest.cpp
        src/CTriangle.cpp
        tests/CRectangleTest.cpp
        src/CRectangle.cpp
        tests/ShapeCommandHandlerTest.cpp
        src/ShapeCommandHandler.cpp
        src/ShapeController.cpp
        tests/ShapeMakerTest.cpp
        src/ShapeMaker.cpp
)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_executable(${PROJECT_NAME}_test ${TEST_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME}_test GTest::gtest_main)
enable_testing()
include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_test)