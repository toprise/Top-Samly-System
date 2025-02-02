#include <iostream>
#include <string>
#include <algorithm>
#include "Rand.h"

int Rand(int left, int right) {
    return rand() % right + left;
}

std::string verify_Number(int len, int min_number, int max_number) {
    std::string ans = "";
    for (int i = 1; i <= len; i++) {
        int x = Rand(0, 9);
        ans = ans + char(x + '0');
    }
    return ans;
}