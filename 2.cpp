#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <curl/curl.h>

using namespace std;

// function to send HTTP requests
void send_request(string url) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
}

int main() {
    vector<thread> threads;
    string url = "http://example.com";
    int num_threads = 500;

    for (int i = 0; i < num_threads; i++) {
        threads.push_back(thread(send_request, url));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return 0;
}
