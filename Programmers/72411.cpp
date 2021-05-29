#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <hash_map>
#include <map>

using namespace std;

map<string, int> combinations;

vector<string> solution(vector<string> orders, vector<int> course) {
    for (int i = 0; i < orders.size(); i++) {

        int totalCombnation = (1 << (orders[i].length())) - 1;
        for (int bit = 1; bit <= totalCombnation; bit++) {
            vector<char> orderSet;
            string combi = "";
        
            for (int position = 0; (1 << position) <= bit; position++) {
                if (bit & (1 << position)) {
                    orderSet.push_back((char) orders[i][position]);
                }
            }

            sort(orderSet.begin(), orderSet.end());

            for (int i = 0; i < orderSet.size(); i++) {
                combi += orderSet[i];
            }

            map<string, int>::iterator it = combinations.find(combi);

            if (it == combinations.end()) {
                combinations.insert(make_pair(combi, 1));
            } else {
                it->second++;
            }
        }
    }

    vector<string> answer;

    for (int i = 0; i < course.size(); i++) {
        int courseSize = course[i];
        int maxCount = 1;

        vector<string> currentAnswer;

        for (map<string, int>::iterator it = combinations.begin(); it != combinations.end(); it++) {
            if (it->first.length() == courseSize) {
                if (it->second > maxCount) {
                    maxCount = it->second;
                    currentAnswer.clear();
                    currentAnswer.push_back(it->first);
                } else if (maxCount != 1 && it->second == maxCount) {
                    currentAnswer.push_back(it->first);
                }
            }
        }
        
        for (int i = 0; i < currentAnswer.size(); i++) {
            answer.push_back(currentAnswer[i]);
        }
    }

    sort(answer.begin(), answer.end());

    return answer;
}

int main() {
    vector<string> orders = {"ABCDEFGHI", "ABCDEFGHI", "ABCDEFGHI", "ABCDEFGHI"};

    vector<int> course = {2};

    solution(orders, course);
    
    return 0;
}
