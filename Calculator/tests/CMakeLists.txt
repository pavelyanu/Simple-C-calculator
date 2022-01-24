include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(
    tests
    tokenizer_tests.cpp
    calc_tests.cpp
    parser_tests.cpp
)

target_link_libraries(
    tests
    calculator_library
    gtest_main
    gmock_main
)

include(GoogleTest)
gtest_discover_tests(tests)