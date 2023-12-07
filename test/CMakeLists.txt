add_executable(test test_functions.c)
target_link_libraries(test app-library.h)

add_executable(test_functions.c
        library/app-library.c
        library/load-library.c
)

add_test(NAME test_functions.c COMMAND tests)
