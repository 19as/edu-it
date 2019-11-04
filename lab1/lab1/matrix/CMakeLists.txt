include(GenerateExportHeader)

add_library(matrix oper.cpp oper.h)
target_include_directories (matrix PUBLIC ${CMAKE_CURRENT_BINARY_DIR})

generate_export_header(matrix)