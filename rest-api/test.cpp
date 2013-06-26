#include "server.hpp"
#include "client.hpp"

int main(int argc, char** argv) {
    runServer(argc, argv, runClient);
}
