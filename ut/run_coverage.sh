#!/bin/bash

set -e

cmake .

make

./calculate_test

lcov --capture --directory . --output-file coverage.info
lcov --remove coverage.info '*/usr/*' '*/ut/*' '*/gtest/*' '*/calculate_module.c' --output-file coverage_filtered.info
lcov --list  coverage_filtered.info

genhtml coverage_filtered.info --output-directory coverage_report

echo "Coverage report generated at $(pwd)/coverage_report/index.html"
