#include "../User.h"
#include <string>
#include <iostream>

int main(int argc, char** argv) {
    User u;
    u.setName("John");
    std::string name = u.getName();
    if (name == "John")
        return 0;
    else {
        std::cerr << "Expected set name to set the name to 'John' but it set it to " << name << std::endl;
        return -1; // Failed test
    }
}
