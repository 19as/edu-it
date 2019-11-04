add_executable( executor executor.cpp)

target_link_libraries (executor PRIVATE matrix)
target_include_directories (executor PRIVATE ../matrix)

