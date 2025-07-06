#include <readline/history.h>
#include <string.h>
#include "history.h"

void add_to_history(const char *input) {
    if (input && strlen(input) > 0) {
        add_history(input);
    }
}
