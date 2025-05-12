
# Programs
find_program(LLVM_COV_PATH llvm-cov)
find_program(LLVM_PROFDATA_PATH llvm-profdata)
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

# Variables
set(CMAKE_COVERAGE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/ccov)

# Common initialization/checks
if(NOT CODE_COVERAGE_ADDED)
  set(CODE_COVERAGE_ADDED ON)

  # Common Targets
  add_custom_target(ccov-preprocessing
    COMMAND ${CMAKE_COMMAND}
    -E
    make_directory
    ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}
    DEPENDS ccov-clean)

  if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
      OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
    # Messages
    message(STATUS "Building with llvm Code Coverage Tools")

    if(NOT LLVM_COV_PATH)
      message(FATAL_ERROR "llvm-cov not found! Aborting.")
    else()
      # Version number checking for 'EXCLUDE' compatability
      execute_process(COMMAND ${LLVM_COV_PATH} --version
        OUTPUT_VARIABLE LLVM_COV_VERSION_CALL_OUTPUT)
      string(REGEX MATCH
        "[0-9]+\\.[0-9]+\\.[0-9]+"
        LLVM_COV_VERSION
        ${LLVM_COV_VERSION_CALL_OUTPUT})

      if(LLVM_COV_VERSION VERSION_LESS "7.0.0")
        message(
          WARNING
          "target_code_coverage()/add_code_coverage_all_targets() 'EXCLUDE' option only available on llvm-cov >= 7.0.0"
        )
    endif()
  endif()

  # Targets
  add_custom_target(ccov-clean
    COMMAND rm -f
    ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/binaries.list
    COMMAND rm -f
    ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/profraw.list)

  # Used to get the shared object file list before doing the main all-processing
  add_custom_target(ccov-libs
    COMMAND ;
    COMMENT "libs ready for coverage report.")

elseif(CMAKE_COMPILER_IS_GNUCXX)
  # Messages
  message(STATUS "Building with lcov Code Coverage Tools")

  if(NOT LCOV_PATH)
    message(FATAL_ERROR "lcov not found! Aborting...")
  endif()
  if(NOT GENHTML_PATH)
    message(FATAL_ERROR "genhtml not found! Aborting...")
  endif()

  # Targets
  add_custom_target(ccov-clean
    COMMAND ${LCOV_PATH}
    --directory
    ${CMAKE_BINARY_DIR}
    --zerocounters)

else()
  message(FATAL_ERROR "Code coverage requires Clang or GCC. Aborting.")
endif()
endif()

# Adds code coverage instrumentation to a library, or instrumentation/targets
# for an executable target.
# ~~~
# EXECUTABLE ADDED TARGETS:
# GCOV/LCOV:
# ccov-${TARGET_NAME} : Generates HTML code coverage report for the associated named target.
#
# LLVM-COV:
# ccov-show-${TARGET_NAME} : Prints to command line detailed per-line coverage information.
#
# Required:
# TARGET_NAME - Name of the target to generate code coverage for.
# Optional:
# EXCLUDE <REGEX_PATTERNS> - Excludes files of the patterns provided from coverage. **These do not copy to the 'all' targets.**
# OBJECTS <TARGETS> - For executables ONLY, if the provided targets are shared libraries, adds coverage information to the output
# ~~~
function(target_code_coverage TARGET_NAME)
  # Argument parsing
  set(multi_value_keywords EXCLUDE OBJECTS)
  cmake_parse_arguments(target_code_coverage
    "${options}"
    ""
    "${multi_value_keywords}"
    ${ARGN})

  if(CODE_COVERAGE_ADDED)
    # Targets
    get_target_property(target_type ${TARGET_NAME} TYPE)

    # For executables add targets to run and produce output
    if(target_type STREQUAL "EXECUTABLE")
      if("${CMAKE_C_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang"
          OR "${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")

        # Run the executable, generating raw profile data
        add_custom_target(
          ccov-run-${TARGET_NAME}
          COMMAND LLVM_PROFILE_FILE=${TARGET_NAME}.profraw
          $<TARGET_FILE:${TARGET_NAME}>
          COMMAND echo
          "-object=$<TARGET_FILE:${TARGET_NAME}>"
          >>
          ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/binaries.list
          COMMAND echo
          "${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME}.profraw "
          >>
          ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/profraw.list
          DEPENDS ccov-preprocessing ccov-libs ${TARGET_NAME})

        # Merge the generated profile data so llvm-cov can process it
        add_custom_target(ccov-processing-${TARGET_NAME}
          COMMAND ${LLVM_PROFDATA_PATH}
          merge
          -sparse
          ${TARGET_NAME}.profraw
          -o
          ${TARGET_NAME}.profdata
          DEPENDS ccov-run-${TARGET_NAME})

        # Ignore regex only works on LLVM >= 7
        if(LLVM_COV_VERSION VERSION_GREATER_EQUAL "7.0.0")
          foreach(EXCLUDE_ITEM ${target_code_coverage_EXCLUDE})
            set(EXCLUDE_REGEX ${EXCLUDE_REGEX}
              -ignore-filename-regex='${EXCLUDE_ITEM}')
          endforeach()
        endif()

        # Print out details of the coverage information to the command line
        add_custom_target(ccov-show-${TARGET_NAME}
          COMMAND ${LLVM_COV_PATH}
          show
          $<TARGET_FILE:${TARGET_NAME}>
          ${SO_OBJECTS}
          -instr-profile=${TARGET_NAME}.profdata
          -show-line-counts-or-regions
          ${EXCLUDE_REGEX}
          DEPENDS ccov-processing-${TARGET_NAME})

        # Print out a summary of the coverage information to the command line
        add_custom_target(ccov-report-${TARGET_NAME}
          COMMAND ${LLVM_COV_PATH}
          report
          $<TARGET_FILE:${TARGET_NAME}>
          ${SO_OBJECTS}
          -instr-profile=${TARGET_NAME}.profdata
          ${EXCLUDE_REGEX}
          DEPENDS ccov-processing-${TARGET_NAME})

        # Generates HTML output of the coverage information for perusal
        add_custom_target(
          ccov-${TARGET_NAME}
          COMMAND ${LLVM_COV_PATH}
          show
          $<TARGET_FILE:${TARGET_NAME}>
          ${SO_OBJECTS}
          -instr-profile=${TARGET_NAME}.profdata
          -show-line-counts-or-regions
          -output-dir=${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/${TARGET_NAME}
          -format="html"
          ${EXCLUDE_REGEX}
          DEPENDS ccov-processing-${TARGET_NAME})

      elseif(CMAKE_COMPILER_IS_GNUCXX)
        set(COVERAGE_INFO
          "${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/${TARGET_NAME}.info")

        # Run the executable, generating coverage information
        add_custom_target(ccov-run-${TARGET_NAME}
          COMMAND $<TARGET_FILE:${TARGET_NAME}>
          DEPENDS ccov-preprocessing ${TARGET_NAME})

        # Generate exclusion string for use
        foreach(EXCLUDE_ITEM ${target_code_coverage_EXCLUDE})
          set(EXCLUDE_REGEX
            ${EXCLUDE_REGEX}
            --remove
            ${COVERAGE_INFO}
            '${EXCLUDE_ITEM}')
        endforeach()

        if(EXCLUDE_REGEX)
          set(EXCLUDE_COMMAND
            ${LCOV_PATH}
            ${EXCLUDE_REGEX}
            --ignore-errors unused
            --output-file
            ${COVERAGE_INFO})
        else()
          set(EXCLUDE_COMMAND ;)
        endif()

        set(EXTERNAL_OPTION --no-external)

        # Generates HTML output of the coverage information for perusal
        add_custom_target(
          ccov-${TARGET_NAME}
          COMMAND ${CMAKE_COMMAND}
          -E
          remove
          ${COVERAGE_INFO}
          COMMAND ${LCOV_PATH}
          --directory
          ${CMAKE_BINARY_DIR}
          --zerocounters
          COMMAND $<TARGET_FILE:${TARGET_NAME}>
          COMMAND ${LCOV_PATH}
          --directory
          ${CMAKE_BINARY_DIR}
          --base-directory
          ${CMAKE_SOURCE_DIR}
          --capture
          ${EXTERNAL_OPTION}
          --output-file
          ${COVERAGE_INFO}
          --ignore-errors mismatch
          COMMAND ${EXCLUDE_COMMAND}
          COMMAND ${GENHTML_PATH}
          -o
          ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/${TARGET_NAME}
          ${COVERAGE_INFO}
          DEPENDS ccov-preprocessing ${TARGET_NAME})
      else()
        message(FATAL_ERROR "Compiler must be GCC or Clang")
      endif()

      add_custom_command(
        TARGET ccov-${TARGET_NAME} POST_BUILD
        COMMAND ;
        COMMENT
        "Open ${CMAKE_COVERAGE_OUTPUT_DIRECTORY}/${TARGET_NAME}/index.html in your browser to view the coverage report.")
    else()
      message(FATAL_ERROR "Only executable targets")
    endif()
  else()
    message(FATAL_ERROR "Can't add coverage to targets because initialization wasn't successful. Make sure to only use it on Debug builds")
  endif()
endfunction()
