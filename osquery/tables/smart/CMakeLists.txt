# Copyright (c) 2014-present, The osquery authors
#
# This source code is licensed as defined by the LICENSE file found in the
# root directory of this source tree.
#
# SPDX-License-Identifier: (Apache-2.0 OR GPL-2.0-only)

function(osqueryTablesSmartMain)
  if(OSQUERY_BUILD_TESTS)
    add_subdirectory("tests")
  endif()

  generateOsqueryTablesSmart()
endfunction()

function(generateOsqueryTablesSmart)
  # We want to remove support for smartmontools, so skip support for M1
  if(DEFINED PLATFORM_WINDOWS OR (DEFINED PLATFORM_MACOS AND "${TARGET_PROCESSOR}" STREQUAL "aarch64"))
    add_osquery_library(osquery_tables_smart INTERFACE)
  else()
    set(source_files
      smart_drives.cpp
    )
    add_osquery_library(osquery_tables_smart EXCLUDE_FROM_ALL
      "${source_files}"
    )

    target_link_libraries(osquery_tables_smart PUBLIC
      osquery_cxx_settings
      osquery_logger
      osquery_sql
      thirdparty_smartmontools
    )

    if(DEFINED PLATFORM_LINUX OR DEFINED PLATFORM_MACOS)
      set(public_header_files
        smart_drives.h
      )

      generateIncludeNamespace(osquery_tables_smart "osquery/tables/smart" "FILE_ONLY" ${public_header_files})
    endif()

    if(DEFINED PLATFORM_POSIX)
      add_test(NAME osquery_tables_smart_tests_smartdrivestests-test COMMAND osquery_tables_smart_tests_smartdrivestests-test)
    endif()
  endif()
endfunction()

osqueryTablesSmartMain()
