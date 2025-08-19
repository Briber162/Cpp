// Online C++ compiler to run C++ program online
#include <iostream>
#include <queue>
#include <chrono>
#include<vector>

struct Bid{
    double bid_price;
    int bid_id;
   int timestamp;
};

// Overload << for printing Bid
std::ostream& operator<<(std::ostream& os, const Bid& b) {
    os << "{id: " << b.bid_id 
       << ", price: " << b.bid_price 
       << ", ts: " << b.timestamp << "}";
    return os;
}

// struct comparator{
//     bool operator() (Bid& a, Bid& b){
//         std::cout<<a.bid_price <<" "<<b.bid_price<<"\n";
//         if(a.bid_price == b.bid_price){
//             return a.timestamp > b.timestamp;
//         }
//         return a.bid_price < b.bid_price;
//     }
// };

int main() {
    // Write C++ code here
    std::cout << "Try programiz.pro\n";
    
    
    std::priority_queue<int> pq;
    pq.push(1);
    pq.push(25);
    pq.push(31);
    pq.push(19);
    
    std::cout<<pq.top()<<"\n";

    auto cmp = [] (Bid& a, Bid& b) {
        if(a.bid_price == b.bid_price){
            return a.timestamp > b.timestamp;
        }
        return a.bid_price < b.bid_price;
    };
    //min Heap
    Bid b1 = {10.5, 1, 5};
    Bid b2 = {12.5, 2, 5};
    Bid b3 = {9.4, 3,2};
    std::priority_queue<Bid, std::vector<Bid>, decltype(cmp)> minHeap(cmp);
    
    minHeap.push(b1);
    minHeap.push(b2);
    minHeap.push(b3);
    
    std::cout<<minHeap.top()<<"\n";
    minHeap.pop();
    std::cout<<minHeap.top()<<"\n";
     
    return 0;
}
