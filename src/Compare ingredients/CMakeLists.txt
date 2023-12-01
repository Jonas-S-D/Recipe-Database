add_library(compare-ingredients compare-ingredients.c)
target_include_directories(compare-ingredients PUBLIC .)

add_executable(Compare compare-ingredients.c)
target_link_libraries(Compare compare-ingredients)