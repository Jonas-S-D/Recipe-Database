project(food_app)

add_executable(food_app
        app.c
        library/app-library.c
        library/load-library.c
        Compare ingredients/compare-library.c
        Compare ingredients/compare-library.h
        Compare ingredients/compare-ingredients.c
)

add_subdirectory(Compare test)

target_include_directories(food_app PRIVATE "Compare ingredients")

add_library(app app.c)
target_link_libraries(app m)
target_include_directories(app PUBLIC .)

add_test(NAME test_functions.c COMMAND tests)

