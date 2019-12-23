# CMake generated Testfile for 
# Source directory: /home/student/hw-clfische/hw3/hw3-check/stack_tests
# Build directory: /home/student/hw-clfische/hw3/hw3-check/stack_tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(Stack.MakeStack "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.MakeStack" "--gtest_color=yes")
add_test(Stack.SingleItemStack "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.SingleItemStack" "--gtest_color=yes")
add_test(Stack.OneItemAdd "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.OneItemAdd" "--gtest_color=yes")
add_test(Stack.OneItemAddRemove "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.OneItemAddRemove" "--gtest_color=yes")
add_test(Stack.SingleItemSetRetrieve "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.SingleItemSetRetrieve" "--gtest_color=yes")
add_test(Stack.SingleItemEmpty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.SingleItemEmpty" "--gtest_color=yes")
add_test(Stack.FillEmpty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.FillEmpty" "--gtest_color=yes")
add_test(Stack.FillEmptyFill "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=Stack.FillEmptyFill" "--gtest_color=yes")
add_test(StackStress.TenThousandFillEmpty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=StackStress.TenThousandFillEmpty" "--gtest_color=yes")
add_test(StackStress.FiftyThousandFillEmpty "/usr/bin/valgrind" "--tool=memcheck" "--leak-check=yes" "--error-exitcode=42" "--trace-children=no" "/home/student/hw-clfische/hw3/hw3-check/stack_tests/stack_test" "--gtest_filter=StackStress.FiftyThousandFillEmpty" "--gtest_color=yes")
