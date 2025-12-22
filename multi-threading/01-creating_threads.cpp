#include<iostream>
#include <string>
#include<thread>
using namespace std;

void counter(int n, string t_name){
    for(int i=0; i<=n; i++){
        cout<<"\n"<<            i<<"th iteration from "<<t_name<<" \n";
    }
    cout<<"\nThread id : "<<this_thread::get_id()<<"\n";
    cout<<"\nFunction from "<<t_name<<" ended\n";
}

int main(){
    std::thread t1(counter, 10, "thread 1");
    std::thread t2(counter , 10, "thread 2");
    std::thread t3(counter, 100, "thread 3");

    t1.join();
    t2.join();
    t3.detach();

    cout<<"\nMain thread ended\n";
    return 0;
}