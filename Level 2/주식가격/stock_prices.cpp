#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<int> prices) {
    vector<int> answer(prices.size());
    stack<pair<int, int>> st;

    for (int i = 0; i < prices.size(); i++) {
        while (!st.empty() && st.top().second > prices[i]) {
            answer[st.top().first] = i - st.top().first;
            st.pop();
        }
        st.push({i, prices[i]});
    }

    while (!st.empty()) {
        answer[st.top().first] = (prices.size() - 1) - st.top().first;
        st.pop();
    }

    return answer;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    if (cin >> n) {
        vector<int> prices(n);
        for (int i = 0; i < n; ++i) {
            cin >> prices[i];
        }
        vector<int> answer = solution(prices);
        for (int i = 0; i < answer.size(); ++i) {
            cout << answer[i] << (i == (int)answer.size() - 1 ? "" : " ");
        }
        cout << "\n";
    }
    return 0;
}
