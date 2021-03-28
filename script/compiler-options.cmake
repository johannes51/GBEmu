
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

function(enable_effcpp TARGET)
  if("${CMAKE_C_COMPILER_ID}" MATCHES "GNU")
    # GCC
    target_compile_options(${TARGET} PRIVATE "-Weffc++")
  elseif("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
         OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
    # Clang
    target_compile_options(${TARGET} PRIVATE "-Weffc++")
  endif()
endfunction()

