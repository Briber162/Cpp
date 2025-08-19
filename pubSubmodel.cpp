#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>
#include <vector>
#include <queue>
#include <chrono>

class Broker {
private:
    struct TopicData {
        std::queue<std::string> messages;
        std::mutex mtx;
        std::condition_variable cv;
    };
    // Map topic → TopicData
    std::unordered_map<std::string, TopicData> topics;
public:
    // Publish message to a topic
    void publish(const std::string& topic, const std::string& msg) {
        auto& t = topics[topic];
        {
            std::lock_guard<std::mutex> lock(t.mtx);
            t.messages.push(msg);
        }
        t.cv.notify_all();
    }
    // Subscribe to a topic and block until a message arrives
    std::string subscribe(const std::string& topic) {
        auto& t = topics[topic];
        std::unique_lock<std::mutex> lock(t.mtx);
        t.cv.wait(lock, [&]{ return !t.messages.empty(); });
        std::string msg = t.messages.front();
        t.messages.pop();
        return msg;
    }
};
// Subscriber worker
void subscriberWorker(Broker& broker, const std::string& topic, int id) {
    while (true) {
        std::string msg = broker.subscribe(topic);
        std::cout << "[Subscriber " << id << " | Topic: " << topic 
                  << "] received: " << msg << std::endl;
    }
}
// Publisher worker
void publisherWorker(Broker& broker, const std::string& topic) {
    int count = 1;
    while (true) {
        std::string msg = topic + " update " + std::to_string(count++);
        broker.publish(topic, msg);
        std::cout << "[Publisher | Topic: " << topic 
                  << "] sent: " << msg << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    Broker broker;

    // Subscribers
    std::thread sub1(subscriberWorker, std::ref(broker), "news", 1);
    std::thread sub2(subscriberWorker, std::ref(broker), "stocks", 2);
    std::thread sub3(subscriberWorker, std::ref(broker), "news", 3);

    // Publishers
    std::thread pub1(publisherWorker, std::ref(broker), "news");
    std::thread pub2(publisherWorker, std::ref(broker), "stocks");

    pub1.join();
    pub2.join();
    sub1.join();
    sub2.join();
    sub3.join();

    return 0;
}
