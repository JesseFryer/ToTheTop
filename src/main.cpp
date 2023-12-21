#include "app/app.h"

int main() {
    App app;
    if (app.init()) {
        app.run();
        app.quit();
    } else {
        return 1;
    }
    return 0;
}
