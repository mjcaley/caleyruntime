project (tests)
cmake_minimum_required (VERSION 3.8)

add_executable (test_gc_app src/test_gc.c)
target_link_libraries (test_gc_app caleyruntime unity)
add_test (test_gc test_gc_app)

add_executable (test_tags_app src/test_tags.c)
target_link_libraries (test_tags_app caleyruntime unity)
add_test (test_tags test_tags_app)
