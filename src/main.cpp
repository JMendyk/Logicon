//
// Created by rufus on 12.12.17.
//

#include <logger.h>
#include "app.h"

void run_shell();

int main(int argc, char *argv[]) {

    if (argc == 2 && std::string(argv[1]) == "shell")
        Logicon::App::getInstance().run(true);
    else
        Logicon::App::getInstance().run(false);

    return 0;
}