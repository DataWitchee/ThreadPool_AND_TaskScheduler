#include<iostream>
#include<thread>
#include<mutex>
#include<map>
#include<chrono>
#include<string>

std::map<std::string, std::string> g_pages;
std::mutex g_pages_mutex;

void save_page(const std::string &URL){
    // simulate a long page fetch
    std::this_thread::sleep_for(std::chrono::seconds(2));
    std::string result = "Fake content";

    std::lock_guard<std::mutex> guard(g_pages_mutex);
    g_pages[URL] = result;
}

int main() 
{
    std::thread t1(save_page, "http://foo");
    std::thread t2(save_page, "http://bar");
    t1.join();
    t2.join();
    
    // safe to access g_pages without lock now, as the threads are joined
    for (const auto& [url, page] : g_pages)
        std::cout << url << " => " << page << '\n';

    return 0;
}
