#include <stdlib.h>
#include <stdio.h>
#include "../../include/errors/errors.h"

void Assert(int expression, const char *message, ...) {
    if (!expression) {
        ErrorExit(message);
    }
}