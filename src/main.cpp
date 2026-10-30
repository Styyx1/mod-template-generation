#include "config.hpp"

int main(int argc, char **argv) {
    if(CONF::IsConfigPresent() && CONF::IsLuaPresent()){
        CONF::GenerateTemp();
    }
    return 0;
}
