#include <bits/stdc++.h>

using namespace std;

int solution(vector<vector<string>> clothes) {
    int answer = 1;
    unordered_map<string, int> um;

    // cout << clothes.size() << '\n';

    for (int i = 0; i < clothes.size(); i++) {
        um[clothes[i][1]]++;

        // cout << clothes[i][1] << '\n';
    }

    for (auto& pair : um) {
        answer *= pair.second + 1;

        // cout << answer << '\n';
    }

    answer--;

    return answer;
}

int main() {
    vector<vector<string>> clothes;

    // 예시 입력 1
    clothes.push_back({"yellow_hat", "headgear"});
    clothes.push_back({"blue_sunglasses", "eyewear"});
    clothes.push_back({"green_turban", "headgear"});

    cout << solution(clothes);

    return 0;
}