#include "engine.hpp"

int main() {
    Engine* engine = new Engine();
    int result = engine->init();
    if (result != 0){
        return -1;
    }
    engine->loop();
    engine->uninit();
    delete engine;
    return 0;
}