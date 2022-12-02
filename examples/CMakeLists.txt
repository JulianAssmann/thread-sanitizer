cmake_minimum_required(VERSION 3.5)
project(examples)

# add_compile_options(-fsanitize=thread)
add_link_options(-fsanitize=thread)

add_executable(tiny_race tiny_race.cc)
add_executable(tiny_race_sanitized tiny_race.cc)
set_target_properties(tiny_race_sanitized PROPERTIES COMPILE_FLAGS "-fsanitize=thread -g -O")