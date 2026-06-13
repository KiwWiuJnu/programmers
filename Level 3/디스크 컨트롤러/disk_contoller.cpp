#include <bits/stdc++.h>
using namespace std;

#define vi vector<int>
#define pvii pair<vi, int>

int solution(vector<vector<int>> jobs) {
    int ans = 0;
    int t = 0;
    bool flag = false;

    // jobs[i].second -> jobs[i].first -> i

    priority_queue<pvii, vector<pvii>, greater<pvii>> jpq;
    priority_queue<pvii, vector<pvii>, greater<pvii>> pq;

    for (int i = 0; i < jobs.size(); i++) {
        jpq.push({jobs[i], i});
    }

    while (true) {
        flag = false;
        if (jpq.empty() && pq.empty()) break;

        while (!jpq.empty() && jpq.top().first.front() <= t) {
            flag = true;
            pq.push(
                {{jpq.top().first[1], jpq.top().first[0]}, jpq.top().second});
            jpq.pop();
        }

        if (flag || !pq.empty()) {
            t += pq.top().first[0];
            ans += t - pq.top().first[1];

            pq.pop();
        } else
            t++;
    }

    return ans / jobs.size();
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (!(cin >> n)) return 0;
    vector<vector<int>> jobs(n, vector<int>(2));
    for (int i = 0; i < n; ++i) {
        cin >> jobs[i][0] >> jobs[i][1];
    }
    cout << solution(jobs) << "\n";
    return 0;
}
