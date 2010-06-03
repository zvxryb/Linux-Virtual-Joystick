#include "vjoy.h"

int main(int argc, char **argv) {
    assert(vjoy_initialize() == 0);
    for (int i=1; i<argc; i++) {
        if (vjoy_load_module(argv[i]) < 0) {
            printf("Failed to load module: %s\n", argv[i]);
	}
    }
    sleep(36000);
    return 0;
}
