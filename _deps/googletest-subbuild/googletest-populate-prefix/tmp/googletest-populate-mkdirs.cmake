# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-src"
  "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-build"
  "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-subbuild/googletest-populate-prefix"
  "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-subbuild/googletest-populate-prefix/tmp"
  "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
  "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-subbuild/googletest-populate-prefix/src"
  "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/_deps/googletest-subbuild/googletest-populate-prefix/src/googletest-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
