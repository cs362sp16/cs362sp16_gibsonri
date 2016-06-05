#!/usr/bin/env python

import subprocess
import os

# what will I do?
# -- run a random test (not a differential test)
# -- record which lines are covered
# -- after running many tests, finally come out with a score for each line
# -- put out a "tarantula coverage" file with the code and the score for each line


def tarantula():
    coverages = [get_coverage(i) for i in range(8720, 8740)]
    return suspicousness(coverages)


def suspicousness(coverages):
    # (failed(e) / totalfailed) / (passed(e) / totalpassed + failed(e) / totalfailed)
    total_passed = len(filter(lambda (success, _): success, coverages))
    total_failed = len(filter(lambda (success, _): not success, coverages))
    _, lines = coverages[0]
    num_lines = len(lines)
    line_suspiciousnesses = [line_suspiciousness(n, coverages,
                                                 total_passed, total_failed)
                             for n in range(num_lines)]
    return line_suspiciousnesses


def line_suspiciousness(line_no, coverages, total_passed, total_failed):
    num_passed = 0
    num_failed = 0
    for success, lines in coverages:
        if lines[line_no] is None:
            return None

        if lines[line_no] > 0:
            if success:
                num_passed += 1
            else:
                num_failed += 1

    numerator = num_failed // total_failed if total_failed != 0 else 0
    denominator = (
        num_passed // total_passed if total_passed != 0 else 0 +
        (num_failed // total_failed if total_failed != 0 else 0)
    )
    return numerator // denominator if denominator != 0 else 0

devnull = open(os.devnull, "w")
def get_coverage(random_seed):
    subprocess.call(["make", "clean"], stdout=devnull, stderr=devnull)
    subprocess.call(["make", "randomtestcard2"], stdout=devnull, stderr=devnull)
    test_output = subprocess.check_output(["./randomtestcard2", str(random_seed)])
    succeeded = not "FAILED" in test_output
    subprocess.call(["gcov", "dominion.c"], stdout=devnull, stderr=devnull)
    fi = open("dominion.c.gcov", "r")
    lines = [get_line_coverage(line) for line in fi.readlines() if not is_header_line(line)]
    fi.close()
    return succeeded, lines


def is_header_line(line):
    parts = line.split(":")
    line_number = parts[1]
    return int(line_number) == 0


def get_line_coverage(line):
    parts = line.split(":")
    coverage_string = parts[0]
    if "-" in coverage_string:
        return None
    if "#" in coverage_string:
        return 0
    return int(coverage_string)


if __name__ == "__main__":
    tarantula()
