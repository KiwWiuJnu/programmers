# 📝 [Programmers / Level 3] 디스크 컨트롤러

> **분류**: 힙(Heap), 그리디(Greedy)  
> **문제 링크**: [디스크 컨트롤러](https://school.programmers.co.kr/learn/courses/30/lessons/42627)

## 1. 문제 파악 및 제한 조건
* **핵심 목표**: 디스크가 수행하는 작업들의 요청부터 종료까지 걸린 시간의 평균을 최소화하는 스케줄러 구현.
* **데이터 범위 및 제약 사항**:
  * 작업 개수 $N$: $1 \le N \le 500$
  * `jobs[i]`: `[요청 시점, 소요 시간]`
  * 요청 시점: $0 \le \text{요청 시점} \le 1,000$
  * 소요 시간: $1 \le \text{소요 시간} \le 1,000$
  * 하드디스크 유휴 상태 시 먼저 요청된 작업 우선 처리.
  * 소수점 이하 나눗셈 결과는 버림.

---

## 2. 논리 전개 및 풀이 과정 (Approaches)
### 🚨 1차 시도 (접근 및 한계)
* **초기 설계 (원시적 접근)**:
  * 모든 작업의 순열(Permutation)을 구하여 평균 대기 시간이 최소가 되는 순서를 찾는 브루트 포스 탐색.
  * $N \le 500$이므로 $O(N!)$의 시간 복잡도는 절대 불가능.
* **우선순위 큐 기반 접근 (사용자 풀이)**:
  * 대기 큐(`jpq`)와 실행 대기 큐(`pq`)를 두고 `t`를 1씩 증가시키며 해당 시간 이하에 들어온 요청을 모두 `pq`로 이동.
  * `pq`에서는 소요 시간이 짧은 것을 우선 처리.
* **한계점**:
  * `pair<vector<int>, int>`와 같이 무거운 컨테이너를 값 형태로 우선순위 큐에 담아 복사 및 동적 할당 오버헤드가 발생.
  * 매번 루프에서 시간 `t`를 1씩 증가시켜 유휴 시간이 길 때 낭비 발생.

### ✅ 2차 시도 (최적화 및 최종 통과)
* **개선된 논리**:
  * 입력 `jobs` 벡터를 `std::sort`로 사전 정렬하여 대기 우선순위 큐의 오버헤드를 완전 제거하고 단순 인덱스 탐색으로 대체.
  * `struct Job` 구조체를 정의하여 메모리 복사와 구조 해석 가독성 극대화.
  * 유휴 상태 시 `current_time`을 다음 작업 요청 시간으로 직접 점프하게 하여 루프 횟수 단축.
* **결과**:
  * 불필요한 동적 메모리 할당 제거 및 루프 최적화로 효율성 극대화 및 깔끔한 코드 통과.

---

## ⏱️ 3. 복잡도 분석 및 성능 비교
* **시간 복잡도**: $O(N \log N)$ ➡️ 정렬 $O(N \log N)$, 모든 작업에 대해 우선순위 큐 삽입/삭제 $O(N \log N)$ 수행.
* **공간 복잡도**: $O(N)$ ➡️ 대기 및 우선순위 큐 관리를 위한 추가 공간 $O(N)$.

---

## ⚠️ 4. 엣지 케이스 및 실수 (Mistakes & Edge Cases)
* **유휴 상태 점프**: 현재 시점에서 요청된 작업이 없고 큐도 비어 있을 때 시간 `t`를 1씩만 늘리면 효율성이 낮아지거나 시간 초과 가능. 다음 가장 빠른 요청 시간으로 직접 대입하는 엣지 처리 필요.
* **우선순위 동일성**: 소요 시간이 같으면 요청 시간 순, 요청 시간도 같으면 번호 순 등 명밀한 정렬 순서 준수 필요.

---

## 🧠 5. 핵심 디테일 및 딥다이브 (Key Takeaways)
* **SJF(Shortest Job First)**: 대기 중인 모든 요청 중에서 소요 시간이 가장 작은 작업을 먼저 배치하는 것이 수학적으로 전체 평균 대기 시간을 항상 최소화함.
* **값 타입 복사 방지**: 우선순위 큐에 `vector`나 `string`처럼 동적 할당을 동반하는 구조를 직접 밀어 넣는 것은 성능 하락 요인. 가벼운 `struct` 정의 및 인덱스 활용이 C++ 성능의 정석.

```cpp
#include <bits/stdc++.h>
using namespace std;

struct Job {
    int request_time;
    int duration;
    int id;
};

struct CompareJob {
    bool operator()(const Job& a, const Job& b) const {
        if (a.duration != b.duration) {
            return a.duration > b.duration;
        }
        if (a.request_time != b.request_time) {
            return a.request_time > b.request_time;
        }
        return a.id > b.id;
    }
};

int solution(vector<vector<int>> jobs) {
    int n = jobs.size();
    sort(jobs.begin(), jobs.end());

    priority_queue<Job, vector<Job>, CompareJob> pq;
    int total_turnaround_time = 0;
    int current_time = 0;
    int job_idx = 0;

    while (job_idx < n || !pq.empty()) {
        if (pq.empty() && current_time < jobs[job_idx][0]) {
            current_time = jobs[job_idx][0];
        }

        while (job_idx < n && jobs[job_idx][0] <= current_time) {
            pq.push({jobs[job_idx][0], jobs[job_idx][1], job_idx});
            job_idx++;
        }

        Job current_job = pq.top();
        pq.pop();

        current_time += current_job.duration;
        total_turnaround_time += (current_time - current_job.request_time);
    }

    return total_turnaround_time / n;
}
```
