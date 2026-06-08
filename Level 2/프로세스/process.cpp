#include <bits/stdc++.h>

using namespace std;

int solution(vector<int> priorities, int location) {
    int answer = 0;
    map<int, int, greater<int>> m;
    queue<int> q;

    priorities[location] *= (-1);

    for (auto x : priorities) {
        if (x < 0) {
            m[x * (-1)]++;
        } else {
            m[x]++;
        }
        q.push(x);
    }

    int pr = priorities[location];

    for (auto [k, v] : m) {
        while (v) {
            if (q.front() == pr && pr * (-1) == k)
                return ++answer;
            else if (q.front() == k) {
                q.pop();
                answer++;
                v--;
            } else {
                q.push(q.front());
                q.pop();
            }
        }
    }

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> priorities(n);
    for (int i = 0; i < n; i++) {
        cin >> priorities[i];
    }

    int location;
    cin >> location;

    cout << solution(priorities, location) << "\n";

    return 0;
}