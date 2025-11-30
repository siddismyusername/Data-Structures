// Online C++ compiler to run C++ program online
#include <iostream>

using namespace std;

void sayHi(){
    cout<<"Hii";
}

int main() {
    // sayHi* fp = *sayHi(); 
    void (*fp)() = sayHi; 
    fp();
    // sayHi();
    return 0;
}