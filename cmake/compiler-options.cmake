
function(enable_wall TARGET)
  if("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
    # GCC
    target_compile_options(${TARGET} PRIVATE "-Wall" "-Wextra" "-pedantic")
  elseif("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
         OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
    # Clang
    target_compile_options(${TARGET} PRIVATE "-Wall" "-Wextra" "-pedantic")
  elseif(MSVC)
    # MSVC
    target_compile_options(${TARGET} PRIVATE "/W4")
  endif()
endfunction()

function(enable_wnone TARGET)
  if("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
    # GCC
    target_compile_options(${TARGET} PRIVATE "-w")
  elseif("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
         OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
    # Clang
    target_compile_options(${TARGET} PRIVATE "-w")
  elseif(MSVC)
    # MSVC
    target_compile_options(${TARGET} PRIVATE "/w")
  endif()
endfunction()


function(set_std_properties TARGET STANDARD)
  set_target_properties(${TARGET} PROPERTIES CXX_STANDARD ${STANDARD}
                                             CXX_STANDARD_REQUIRED ON
                                             CXX_EXTENSIONS OFF)
endfunction()

function(msvc_option TARGET STANDARD)
  if(MSVC_VERSION GREATER_EQUAL "1900" AND CMAKE_VERSION LESS 3.10)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("/std:c++${STANDARD}" _cpp_latest_flag_supported)
    if(_cpp_latest_flag_supported)
      target_compile_options(${TARGET} PRIVATE "/std:c++${STANDARD}")
    endif()
  endif()
endfunction()

# Set the compiler standard to C++11
function(cxx_11 TARGET)
  set_std_properties(${TARGET} 11)
  msvc_option(${TARGET} 11)
endfunction()

# Set the compiler standard to C++14
function(cxx_14 TARGET)
  set_std_properties(${TARGET} 14)
  msvc_option(${TARGET} 14)
endfunction()

# Set the compiler standard to C++17
function(cxx_17 TARGET)
  set_std_properties(${TARGET} 17)
  msvc_option(${TARGET} 17)
endfunction()

# Set the compiler standard to C++20
function(cxx_20 TARGET)
  set_std_properties(${TARGET} 20)
endfunction()
