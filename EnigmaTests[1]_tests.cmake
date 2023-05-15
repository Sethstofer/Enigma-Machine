add_test([=[ExampleTests.TestPlugboard]=]  [==[/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153/EnigmaTests]==] [==[--gtest_filter=ExampleTests.TestPlugboard]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[ExampleTests.TestPlugboard]=]  PROPERTIES WORKING_DIRECTORY [==[/Users/sethsjo/Documents/myCode/ECS 153 - Hao Chen/Enigma-Machine-ECS153]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  EnigmaTests_TESTS ExampleTests.TestPlugboard)
