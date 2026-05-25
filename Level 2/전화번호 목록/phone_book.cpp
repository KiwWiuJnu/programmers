#include <bits/stdc++.h>
using namespace std;

bool solution(vector<string> phone_book) {
    bool answer = true;

    sort(phone_book.begin(), phone_book.end());

    for (int i = 0; i < phone_book.size() - 1; i++) {
        if (phone_book[i + 1].find(phone_book[i]) == 0) answer = false;
    }

    return answer;
}

int main() {
    vector<string> phone_book;
    int n;

    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        phone_book.push_back(s);
    }

    if (solution(phone_book))
        cout << "true";
    else
        cout << "false";

    return 0;
}