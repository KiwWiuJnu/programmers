#include <bits/stdc++.h>

using namespace std;

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;

    // 장르별로 정렬
    // 장르별로 정렬해서 제일 높은 순으로 곡 많이 재생된거 2개씩 앨범에 수록하기

    unordered_map<string, int> um;

    for (int i = 0; i < genres.size(); i++) {
        um[genres[i]] += plays[i];
    }

    // 장르별로 정렬
    priority_queue<pair<int, string>> pq;

    for (const auto& [k, v] : um) {
        pq.push({v, k});
    }

    unordered_map<string, vector<pair<int, int>>> umg;

    for (int i = 0; i < genres.size(); i++) {
        umg[genres[i]].push_back({plays[i], i * (-1)});
    }

    while (!pq.empty()) {
        auto v = umg[pq.top().second];
        sort(v.begin(), v.end());

        for (int i = 0; i < 2; i++) {
            if (!v.empty()) {
                answer.push_back(v.back().second * (-1));
                v.pop_back();
            }
        }

        pq.pop();
    }

    return answer;
}

int main() {
    vector<string> genres;
    vector<int> plays;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        int p;
        cin >> s >> p;
        genres.push_back(s);
        plays.push_back(p);
    }

    vector<int> result = solution(genres, plays);

    for (int i : result) {
        cout << i << ' ';
    }

    return 0;
}