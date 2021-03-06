message(status "** Using conan build")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)

if(NOT "${CMAKE_CXX_STANDARD}")
  set(CMAKE_CXX_STANDARD 17)
endif()

if (NOT "${SANITIZER}" STREQUAL "" )
    message(status "** Using sanitizer: ${SANITIZER}")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fsanitize=${SANITIZER}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=${SANITIZER}")
endif()

if (NOT "${COVERAGE}" STREQUAL "")
    message(status "** Enabling code coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    set(CMAKE_LD_FLAGS "${CMAKE_LD_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
endif()

conan_basic_setup()
conan_set_libcxx()
