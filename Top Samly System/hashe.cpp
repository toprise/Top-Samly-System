#include <iostream>
#include "hashe.h"

std::string hashe(std::string Str) {
    unsigned long long ans = 0;
    for (int i = 0; i < Str.size(); i++) {
       ans = (ans * 131) + (unsigned long long)(Str[i]);
    }
    std::string ansp = "";
    unsigned long long u = ans;
    while (u) {
        ansp = char(u % 10 + '0') + ansp;
        u /= 10;
    }
    return ansp;
}

std::string int_to_string(int x) {
    std::string ans = "";
    int u = x;
    while (u) {
        ans = char(u % 10 + '0') + ans;
        u /= 10;
    }
    return ans;
}