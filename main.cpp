#include "simulator/simulator.h"

int main() {
    Simulator s;
    while (true)
        s.tick(0.1);
    return 0;
}