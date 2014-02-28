#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include "args/CommandArgs.h"
#include "ROM.h"

using namespace std;
using namespace avrel;

void usage()
{
    cerr << "Usage: ./avrel <ROM file>" << endl;
}

int main(int argc, char *argv[])
{
    CommandArgs args(argc, argv);
    vector<string> parts = args.getParts();

    if (parts.size() != 1 || args.hasFlag("?") || args.hasFlag("help")) {
        usage();
        return EXIT_FAILURE;
    } else {
        string romFile = parts[0];
        cout << "Loading ROM " << romFile << "..." << endl;
        ROM rom(romFile);

        printf("%04x\n", rom.readUWord());
    }
}
