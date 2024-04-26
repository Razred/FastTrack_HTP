#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx_;
int shared_data_ = 0;


void writeThread() {
    for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> lock(mtx_);
        ++shared_data_;
        std::cout << "Writer thread: write " << shared_data_ << std::endl;
    }
}

void readThread() {
    int val;
    for (int i = 0; i < 10; ++i) {
        std::lock_guard<std::mutex> lock(mtx_);
        val = shared_data_;
        std::cout << "Reader thread: read " << shared_data_ << std::endl;
    }
}

int main() {
    std::thread write(writeThread);
    std::thread read(readThread);

    write.join();
    read.join();

    return 0;
}