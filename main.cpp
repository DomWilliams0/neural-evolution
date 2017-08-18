#include "simulator/simulator.h"
#include "renderer/renderer.h"

int main() {
    Simulator sim;
    Renderer renderer((unsigned int) Config::WORLD_WIDTH, (unsigned int) Config::WORLD_HEIGHT, sim);

    renderer.run();

    return 0;
}