#include <bits/stdc++.h>

using namespace std;

struct Activity {
    string name;
    int avg;
    int level;

    bool operator<(const Activity example) const {
        if (this->avg == example.avg) {
            if (this->level == example.level) {
                int tmp = strcmp(this->name.c_str(), example.name.c_str());
                if (tmp < 0)
                    return true;
                else
                    return false;
            }
            return this->level < example.level;
        }
        return this->avg > example.avg;
    }
};

map<string, vector<int>> first_part;
set<Activity> second_part;

int main() {
    string str;
    while (cin >> str, str != "end") {
        if (str == "map") {
            cin >> str;
            if (str == "insert") {
                string name;
                int times, num;
                cin >> name;
                cin >> times;
                if (first_part.count(name)) {
                    cout << "Error" << endl;
                    continue;
                }
                for (int i = 0; i < times; i++) {
                    cin >> num;
                    first_part[name].push_back(num);
                }
            } else if (str == "size")
                cout << first_part.size() << endl;
            else if (str == "erase") {
                string name;
                cin >> name;
                if (!first_part.count(name)) {
                    cout << "Error" << endl;
                    continue;
                }
                first_part.erase(name);
            } else if (str == "count") {
                string name;
                cin >> name;
                cout << first_part.count(name) << endl;
            } else if (str == "traverse") {
                for (auto map_iter = first_part.begin(); map_iter != first_part.end(); map_iter++) {
                    cout << map_iter->first << " ";
                    for (auto vector_iter = map_iter->second.begin();
                         vector_iter != map_iter->second.end(); vector_iter++)
                        cout << *vector_iter << " ";
                    cout << endl;
                }
            } else if (str == "visitVec") {
                string name;
                int index;
                cin >> name >> index;
                if (!first_part.count(name) || first_part[name].begin() + index >= first_part[name].end() ||
                    index < 0) {
                    cout << "Error" << endl;
                    continue;
                }
                cout << first_part[name][index] << endl;
            } else if (str == "visit") {
                string name;
                cin >> name;
                if (!first_part.count(name)) {
                    cout << "Error" << endl;
                    continue;
                }
                cout << first_part[name].size() << " ";
                for (auto vector_iter = first_part[name].begin(); vector_iter != first_part[name].end(); vector_iter++)
                    cout << *vector_iter << " ";
                cout << endl;
            } else if (str == "append") {
                string name;
                int new_arg;
                cin >> name >> new_arg;
                if (!first_part.count(name)) {
                    cout << "Error" << endl;
                    continue;
                }
                first_part[name].push_back(new_arg);
            } else
                cout << "Error" << endl;
        } else if (str == "set") {
            cin >> str;
            if (str == "size")
                cout << second_part.size() << endl;
            else if (str == "insert") {
                Activity new_activity;
                cin >> new_activity.avg >> new_activity.level >> new_activity.name;
                int flag = 0;
                for (auto set_iter = second_part.begin(); set_iter != second_part.end(); set_iter++)
                    if (set_iter->name == new_activity.name && set_iter->level == new_activity.level &&
                        set_iter->avg == new_activity.avg) {
                        flag = 1;
                        break;
                    }
                if (flag) {
                    cout << "Error" << endl;
                    continue;
                }
                second_part.insert(new_activity);
            } else if (str == "erase") {
                Activity erase_activity;
                cin >> erase_activity.avg >> erase_activity.level >> erase_activity.name;
                int flag = 0;
                for (auto set_iter = second_part.begin(); set_iter != second_part.end(); set_iter++)
                    if (set_iter->name == erase_activity.name && set_iter->avg == erase_activity.avg &&
                        set_iter->level == erase_activity.level) {
                        flag = 1;
                        break;
                    }
                if (!flag) {
                    cout << "Error" << endl;
                    continue;
                }
                second_part.erase(erase_activity);
            } else if (str == "count") {
                Activity cnt_activity;
                cin >> cnt_activity.avg >> cnt_activity.level >> cnt_activity.name;
                cout << second_part.count(cnt_activity) << endl;
            } else if (str == "traverse")
                for (auto set_iter = second_part.begin(); set_iter != second_part.end(); set_iter++)
                    cout << set_iter->avg << " " << set_iter->level << " " << set_iter->name << endl;
            else cout << "Error" << endl;
        } else
            cout << "Error" << endl;
    }
    return 0;
}