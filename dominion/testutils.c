//
// Created by Rikki Gibson on 5/13/16.
//
#include <stdio.h>

int failed = 0;

void myassert(int b, char* msg)  {
    if (b == 0) {
        printf("FAILED ASSERTION: %s\n",msg);
        failed = 1;
    }
}

void checkasserts() {
    if (!failed) {
        printf ("TEST SUCCESSFULLY COMPLETED.\n");
    }
}
