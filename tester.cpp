#include <iostream>
using namespace std;

int main() {
    cout << "Type your first name here and press enter : ";
    string s;
    cin >> s;

    cout << endl;
    for (int i{0}; i<s.size() - 1; i++) {
        cout << (int) s[i] << "::";
    }
    cout << (int) s.back();
    cout << endl << endl;
}