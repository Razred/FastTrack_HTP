#include <iostream>
#include <cassert>

using namespace std;

void TEST_string();
void TEST_int();

template<typename PTR>
void invert_bites(PTR* ptr, size_t len, unsigned char mask) {
    for (size_t i = 0; i < len; ++i) {
        ptr[i] ^= mask;
    }
}

int main() {
    TEST_int();
    TEST_string();
}

void TEST_string() {
    unsigned char data[] = "HELLO WORLD";
    unsigned char check_data[] = "hello world";
    unsigned char mask = 0b00100000;
    int len = 6;
    invert_bites(data, len, mask);
    for (int i = 0; i < len - 1; ++i) {
        assert(data[i] == check_data[i]);
    }
}

void TEST_int() {
    int data[] = {0b00001010, 0b00010011, 0b01010101, 0b11100010};
    unsigned char mask = 0b00011111;
    int len = 3;
    invert_bites(data, len, mask);
    assert(data[0] == 0b00010101);
    assert(data[1] == 0b00001100);
    assert(data[2] == 0b01001010);
    assert(data[3] == 0b11100010);
}