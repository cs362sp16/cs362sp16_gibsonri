#!/usr/bin/env python

import sys
import subprocess
import os


def diff_dominion(ref_path, test_path, random_seed):
    subprocess.call(["make", "testdominion"], cwd=ref_path)
    subprocess.call(["make", "testdominion"], cwd=test_path)

    ref_out = open(".ref_out", "w")
    test_out = open(".test_out", "w")

    subprocess.call([ref_path + "/testdominion", random_seed], stdout=ref_out)
    subprocess.call([test_path + "/testdominion", random_seed], stdout=test_out)

    ref_out.close()
    test_out.close()

    diff_proc = subprocess.Popen(["diff", ".ref_out", ".test_out"], stdout=subprocess.PIPE)
    diff, err = diff_proc.communicate()

    os.remove(".ref_out")
    os.remove(".test_out")

    if len(diff) == 0:
        print("TEST PASSED")
    else:
        print("TEST FAILED")
        print(diff)


if __name__ == "__main__":
    if len(sys.argv) != 4:
        print("Usage: diffdominion <ref_path> <test_path> <random_seed>")
        print("<ref_path> and <test_path> should be directories where make testdominion can be invoked.")
        exit()
    diff_dominion(sys.argv[1], sys.argv[2], sys.argv[3])
