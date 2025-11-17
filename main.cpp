#include <windows.h>
#include "AppController.h"

int main()
{
    std::cout << "[DEBUG] Entering main()\n";
    // UTF-8 console setting for printing superscript
    SetConsoleOutputCP(CP_UTF8);

    AppController app;
    std::cout << "[DEBUG] Before app.run()\n";
    app.run();
    std::cout << "[DEBUG] After app.run()\n";
    return 0;
}
