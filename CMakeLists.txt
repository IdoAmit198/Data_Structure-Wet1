cmake_minimum_required(VERSION 3.0.0)
project(partB VERSION 0.1.0)

set(MIVNI_FLAGS_DEBUG "-std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG")
set(MIVNI_FLAGS_RELEASE "${MIVNI_FLAGS_DEBUG} -DNDBUG")

set(CMAKE_CXX_FLAGS ${MIVNI_FLAGS_DEBUG})

add_executable(myprog main.cpp CoursesManager.cpp Course.cpp Lecture.cpp CourseWithoutTime.cpp)