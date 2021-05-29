#include <string>
#include <vector>
#include <map>
#include <iostream>

using namespace std;

map<string, string> names;

struct Message {
    string uid;
    string suffix;
};

vector<string> mysplit(string text) {
    vector<string> ret;
    string cur = "";
    for (int i = 0; i < text.length(); i++) {
        if (text[i] == ' ') {
            ret.push_back(cur);
            cur = "";
        } else {
            cur += text[i];
        }
    }
    ret.push_back(cur);
    return ret;
}

vector<string> solution(vector<string> record) {
    vector<string> answer;
    vector<Message> messages;

    for (int i = 0; i < record.size(); i++) {
        vector<string> splits = mysplit(record[i]);
        string command = splits[0];
        string uid = splits[1];
        bool checkUpdatename = false;

        if (command.compare("Enter") == 0) {
            struct Message msg;
            msg.suffix = "님이 들어왔습니다.";
            msg.uid = uid;
            messages.push_back(msg);
            checkUpdatename = true;

        } else if (command.compare("Leave") == 0) {
            struct Message msg;
            msg.suffix = "님이 나갔습니다.";
            msg.uid = uid;
            messages.push_back(msg);
            
        } else if (command.compare("Change") == 0) {
            checkUpdatename = true;
        }

        if (checkUpdatename) {
            string name = splits[2];
            map<string, string>::iterator it = names.find(uid);
            if (it == names.end()) {
                names.insert(make_pair(uid, name));
            } else {
                it->second = name;
            }
        }
    }

    for (int i = 0; i < messages.size(); i++) {
        string uid = messages[i].uid;
        string name = names.find(uid)->second;
        answer.push_back(name + messages[i].suffix);
    }

    return answer;
}

int main() {
    vector<string> splits = mysplit("Enter uid1234 Muzi");

    vector<string> record = {"Enter uid1234 Muzi", "Enter uid4567 Prodo","Leave uid1234","Enter uid1234 Prodo","Change uid4567 Ryan"};

    vector<string> ans = solution(record);

    for (int i = 0; i < ans.size(); i++) {
        cout<<ans[i]<<endl;
    }
}