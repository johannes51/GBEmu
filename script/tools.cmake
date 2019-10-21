#
# Copyright (C) 2018 by George Cave - gcave@stablecoder.ca
#
# Licensed under the Apache License, Version 2.0 (the "License"); you may not
# use this file except in compliance with the License. You may obtain a copy of
# the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
# WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
# License for the specific language governing permissions and limitations under
# the License.

find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
if(CLANG_TIDY_EXE)
  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
else()
  message(STATUS "clang-tidy not found!")
  set(CMAKE_CXX_CLANG_TIDY "" CACHE STRING "" FORCE) # delete it
endif()
find_program(CPPCHECK_EXE NAMES "cppcheck")
if(CPPCHECK_EXE)
  message(STATUS "cppcheck found: ${CPPCHECK_EXE}")
else()
  message(STATUS "cppcheck not found!")
  set(CMAKE_CXX_CPPCHECK "" CACHE STRING "" FORCE) # delete it
endif()


# Adds clang-tidy checks to the compilation, with the given arguments being used
# as the options set.
function(clang_tidy TARGET_NAME)
  if(CLANG_TIDY_EXE)
    set_target_properties(${TARGET_NAME} PROPERTIES CXX_CLANG_TIDY "${CLANG_TIDY_EXE};${ARGN}")
  else()
    message(FATAL_ERROR "clang-tidy is needed.")
  endif()
endfunction()

# Adds cppcheck to the compilation, with the given arguments being used as the
# options set.
function(cppcheck TARGET_NAME)
  if(CPPCHECK_EXE)
    set_target_properties(${TARGET_NAME} PROPERTIES CMAKE_CXX_CPPCHECK
        "${CPPCHECK_EXE};--enable=warning,performance,portability,missingInclude;--template=\"[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)\";--suppress=missingIncludeSystem;--quiet;--verbose;--force"
        )
    else()
      message(FATAL_ERROR "cppcheck is needed.")
  endif()
endfunction()


