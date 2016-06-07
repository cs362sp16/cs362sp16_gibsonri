#!/usr/bin/env python

import subprocess
import os


def tarantula(test_program_names):
    coverages = [get_coverage(prog_name) for prog_name in test_program_names]
    susp_list = suspicousness(coverages)
    print_tarantula(susp_list)


def print_tarantula(line_susp_list):
    dom_file = open("dominion.c", "r")
    dom_lines = dom_file.readlines()
    for (dom_line, susp_val) in zip(dom_lines, line_susp_list):
        print "--  " if susp_val is None else "%.2f" % susp_val,
        print dom_line,
    dom_file.close()


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

    numerator = float(num_failed) / total_failed if total_failed != 0 else 0
    denominator = (
        float(num_passed) / total_passed if total_passed != 0 else 0 +
        (float(num_failed) / total_failed if total_failed != 0 else 0)
    )
    return numerator / denominator if denominator != 0 else 0

devnull = open(os.devnull, "w")


def get_coverage(prog_name):
    subprocess.call(["make", "clean"], stdout=devnull, stderr=devnull)
    subprocess.call(["make", prog_name], stdout=devnull, stderr=devnull)
    test_output = subprocess.check_output(["./" + prog_name])
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
    tarantula(["unittest1", "unittest2", "unittest3", "unittest4",
               "cardtest1", "cardtest2", "cardtest3", "cardtest4", "cardtest5"])
