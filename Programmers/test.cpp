#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include <hash_map>
#include <map>

using namespace std;

struct OrderItem {
    vector<string> combinations;
};

OrderItem items[21];

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

            items[i].combinations.push_back(combi);
            orderSet.clear();
        }
    }
    
    vector<string> answer;

    for (int i = 0; i < course.size(); i++) {
        int courseSize = course[i];

        map<string, int> m;
        m.clear();

        for (int j = 0; j < orders.size(); j++) {
            for (int k = 0; k < items[j].combinations.size(); k++) {
                if (items[j].combinations[k].length() == courseSize) {
                    map<string, int>::iterator it = m.find(items[j].combinations[k]);

                    if (it != m.end()) {
                        it->second = it->second + 1;
                    } else {
                        m.insert(make_pair(items[j].combinations[k], 1));
                    }
                }
            }
        }

        int maxCount = 1;
        vector<string> currentAnswer;

        for (map<string, int>::iterator it = m.begin(); it != m.end(); it++) {
            if (it->second > maxCount) {
                maxCount = it->second;
                currentAnswer.clear();
                currentAnswer.push_back(it->first);
            } else if (maxCount != 1 && it->second == maxCount) {
                currentAnswer.push_back(it->first);
            }
        }
        
        for (int i = 0; i < currentAnswer.size(); i++) {
            answer.push_back(currentAnswer[i]);
        }
    }

    sort(answer.begin(), answer.end());

    for (int i = 0; i < answer.size(); i++) {
        cout<<answer[i]<<endl;
    }

    return answer;
}



int main() {
    vector<string> orders = {"ABCDEFGHI", "ABCDEFGHI", "ABCDEFGHI", "ABCDEFGHI"};

    vector<int> course = {2};

    solution(orders, course);
    
    return 0;
}
