// Online C++ compiler to run C++ program online
#include <iostream>
#include<mutex>
#include<thread>

std::mutex mtx;
class Logger{
  
  private:
    Logger() {
        std::cout<<"Ctor called\n";
    }
    
    Logger(const Logger& other) = delete;
    
    Logger& operator=(const Logger& other) = delete;
    
public:

    static Logger* getLoggerInstance(){
        if(logObject != NULL){
            return logObject;
        }
        
        std::lock_guard<std::mutex> lock(mtx);
        if(logObject == NULL){
            Logger* obj = new Logger();
            logObject = obj;
        }
        return logObject;
        
    }
    
    void printLogsHandler(){
        while(true){
            printLogs();
        }
    }
    
    void printLogs(){
        std::lock_guard<std::mutex> lock(mtx);
        std::cout<<"Thread ID: "<<std::this_thread::get_id()<<"\n";
    }

    static Logger* logObject;
};

Logger* Logger::logObject = NULL;

int main() {
    
    Logger* log1 = Logger::getLoggerInstance();
    
    Logger* log2 = Logger::getLoggerInstance();
    
    if(log1 == log2){
        std::cout<<"Both are same instance\n";
    } else{
        std::cout<<"Both are diff instance\n";
    }
    
    
    std::thread t1(&Logger::printLogsHandler,log1);
    std::thread t2(&Logger::printLogsHandler,log1);
    
    t1.join();
    t2.join();


    return 0;
}
