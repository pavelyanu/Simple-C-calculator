add_library(calculator_library SHARED 
    calculator.cpp
    expression.cpp
    lexer.cpp
    parser.cpp
    tokenizer.cpp
    policy.cpp
)

add_library(calculator::library ALIAS calculator_library)

target_include_directories(calculator_library
PUBLIC 
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries( calculator_library
PRIVATE 
    calculator::library
)