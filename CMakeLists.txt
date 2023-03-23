cmake_minimum_required(VERSION 3.23)

project(HuaweiContest)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:\\Users\\chenhong\\Desktop\\WindowsRelease\\WindowsRelease\\Demo")

add_executable( HuaweiContest
        main.cpp
        data_form.hpp
        huawei_io.h
        huawei_io.cpp
        planning.cpp
        planning.h
        navigation.cpp
        navigation.h
        game_map.cpp
        game_map.h
        router.cpp
        router.h
        robot_behavior.h
        robot_behavior.cpp
        planning_simple.cpp
        planning_simple.h
        planning_behaviortree.h
        )
