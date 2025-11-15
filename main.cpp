#include <windows.h>
#include "AppController.h"

int main()
{
    // keep your UTF-8 console setting
    SetConsoleOutputCP(CP_UTF8);

    AppController app;
    app.run();

    return 0;
}
