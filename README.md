# AI-powered code coverage test generator for Linux Kernel Module

This repository contains a Linux kernel module that performs basic arithmetic operations and calculates the Greatest Common Divisor (GCD) of two numbers. It utilizes [`cover-agent`](https://github.com/Codium-ai/cover-agent) to generate unit tests for GoogleTest and create a code coverage reports.

## **Overview**

The aim of the project is to show POC of AI test generation for Google Test framework using `cover-agent`.
This project demonstrates how to generate a set of tests that could be ran in userspace with kernel-specific functions mocked.

## **Features**

- Kernel module that accepts parameters for two numbers and an operation.
- Supports operations: `add`, `subtract`, `multiply`, `divide`, `power`, and `gcd`.
- Unit tests using GoogleTest, created with cover-agent.
- Code coverage reports generated with `lcov` and `genhtml`.

## **File Structure**
```
calc_example_mod
├── calculate.c
├── calculate_module.c
├── calculate_module.h
├── gcd.c
├── Makefile
└── ut
    ├── calculate_test.cpp
    ├── CMakeLists.txt
    ├── mock
    │   └── calculate_module_mocks.h
    └── run_coverage.sh
```


## **Prerequisites**

- **Linux Kernel Headers**: Ensure you have the Linux kernel headers installed for your current kernel version.
- **Build Tools**: `make`, `gcc`, `g++`, and `cmake`.
- **GoogleTest**: Install GoogleTest for unit testing.
- **Code Coverage Tools** (optional): `lcov`, `genhtml`.

## **Building the Kernel Module**
```bash
cd calc_example_mod
make clean
make
```
## **Running the Kernel Module**
1. Insert the module
```bash
sudo insmod my_calculate_module.ko number1=48 number2=18 operation=gcd
```
2. Check Kernel Logs
```bash
sudo dmesg | tail
```
You should see output similar to:
```
[xxxx.xxxxxx] Module loaded with arguments: number1=48, number2=18, operation=gcd
[xxxx.xxxxxx] Result: 6
```
## **Building and Running Unit Tests**
1. Navigate to the Test Directory
```bash
cd calc_example_mod/ut
```
2. Export OpenAI API key
```bash
export OPENAI_API_KEY=sk-proj...
```
3. Run cover-agent
```bash
cover-agent \
  --source-file-path "../calculate.c" \
  --test-file-path "calculate_test.cpp" \
  --code-coverage-report-path "coverage_filtered.info" \
  --test-command "bash ./run_coverage.sh" \
  --test-command-dir "/home/e_kondrashyn/testmodule2/ut" \
  --coverage-type "lcov" \
  --desired-coverage 65 \
  --max-iterations 3 \
  --included-files "../calculate_module.c"
  --included-files "../gcd.c"
```

## **Here is an example of generated tests**
```
$ diff -ruN calculate_test.cpp.orig calculate_test.cpp
--- calculate_test.cpp.orig     2024-09-24 02:22:28.423755194 +0000
+++ calculate_test.cpp  2024-09-24 02:24:50.135742159 +0000
@@ -11,6 +11,41 @@
     EXPECT_EQ(calculate(-5, 3, (char *)"add"), -2);
 }
 
+TEST(CalculateTest, InvalidOperation) {
+    EXPECT_EQ(calculate(5, 3, (char *)"invalid_op"), 0);
+}
+
+
+TEST(CalculateTest, GCD) {
+    EXPECT_EQ(calculate(48, 18, (char *)"gcd"), 6);
+    EXPECT_EQ(calculate(101, 103, (char *)"gcd"), 1); // Co-prime numbers
+}
+
+
+TEST(CalculateTest, Power) {
+    EXPECT_EQ(calculate(2, 3, (char *)"power"), 8);
+    EXPECT_EQ(calculate(2, -3, (char *)"power"), 0); // Negative exponent
+}
+
+
+TEST(CalculateTest, Division) {
+    EXPECT_EQ(calculate(6, 3, (char *)"divide"), 2);
+    EXPECT_EQ(calculate(5, 0, (char *)"divide"), 0); // Division by zero
+}
+
+
+TEST(CalculateTest, Multiplication) {
+    EXPECT_EQ(calculate(5, 3, (char *)"multiply"), 15);
+    EXPECT_EQ(calculate(-5, 3, (char *)"multiply"), -15);
+}
+
+
+TEST(CalculateTest, Subtraction) {
+    EXPECT_EQ(calculate(5, 3, (char *)"subtract"), 2);
+    EXPECT_EQ(calculate(-5, 3, (char *)"subtract"), -8);
+}
+
+
 int main(int argc, char **argv) {
     ::testing::InitGoogleTest(&argc, argv);
     return RUN_ALL_TESTS();
```
