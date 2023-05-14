#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

void sendHttpRequest(string url) {
    while(true) {
        string command = "curl -s -o /dev/null -w \"%{http_code}\" " + url;
        system(command.c_str());
    }
}

int main(int argc, char** argv) {
    vector<thread> threads;
    string url = argv[1];
    int numThreads = atoi(argv[2]);

    for(int i = 0; i < numThreads; i++) {
        threads.emplace_back(sendHttpRequest, url);
    }

    for_each(threads.begin(), threads.end(), [](thread &t) {
        t.join();
    });

    return 0;
}
