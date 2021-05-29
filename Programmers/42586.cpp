#include<string>
#include<vector>
#include<iostream>

using namespace std;

vector<int> solution(vector<int> progresses, vector<int> speeds) {
    vector<int> answer;
    vector<int> times;

    for (int i = 0; i < progresses.size(); i++) {
        int remainWork = 100 - progresses[i];

        if (remainWork % speeds[i] == 0) {
            times.push_back(remainWork / speeds[i]);
        } else {
            times.push_back((remainWork / speeds[i]) + 1);
        }
    }

    int cnt = 1;
    int curmax = times[0];

    for (int i = 1; i < times.size(); i++) {
        if (times[i] > curmax) {
            answer.push_back(cnt);
            cnt = 1;
            curmax = times[i];
        } else {
            cnt++;
        }
    }

    answer.push_back(cnt);

    return answer;
}

int main() {
    vector<int> progresses = {95,90,99,99,80,99};
    vector<int> speeds = {1,1,1,1,1,1};

    vector<int> ans = solution(progresses, speeds);

    for (int i = 0; i < ans.size(); i++) {
        cout<<ans[i]<<endl;
    }
}