#include <iostream>
using namespace std;

class check {
    int x;
    public:
    int y;
    check function();
} check1;

check check::function() {
    // return check1;
}

int main() {
    check1.y = 1;
    cout << check1.y;
    int * arr;
    int arr1[] = {1,2,3};
    arr = new int[5];
    arr[0] = 1;
    cout << arr[0];
    cout << arr1[2];
    // check1.function();
    return 0;
}
