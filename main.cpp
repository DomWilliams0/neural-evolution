#include "simulator/simulator.h"
#include "renderer/renderer.h"

int main() {
    Simulator sim;
    Renderer renderer(600, 600, sim);

    renderer.run();

    return 0;
}