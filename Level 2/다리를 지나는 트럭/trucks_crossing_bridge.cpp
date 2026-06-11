#include <bits/stdc++.h>
using namespace std;

int solution(int bridge_length, int weight, vector<int> truck_weights) {
    int answer = 0;
    int cnt = 0;
    queue<int> q;
    int len = truck_weights.size();

    for (int i = 0; i < bridge_length; i++) {
        q.push(0);
    }

    int i = 0;

    while (i < len) {
        answer++;

        weight += q.front();
        if (q.front() > 0) cnt--;
        q.pop();

        if (weight >= truck_weights[i] && bridge_length > cnt) {
            q.push(truck_weights[i]);
            weight -= truck_weights[i];
            cnt++;
            i++;
        } else {
            q.push(0);
        }
    }

    answer += bridge_length;

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int bridge_length, weight, n;
    if (cin >> bridge_length >> weight >> n) {
        vector<int> truck_weights(n);
        for (int i = 0; i < n; i++) {
            cin >> truck_weights[i];
        }
        cout << solution(bridge_length, weight, truck_weights) << "\n";
    }
    return 0;
}