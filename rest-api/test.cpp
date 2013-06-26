#include "server.hpp"
#include "client.hpp"

int main(int argc, char** argv) {
    int result;
    runServer(argc, argv, [&]{result = runClient();});
    return result;
}
