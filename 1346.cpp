#include <bits/stdc++.h>

struct Students {
    char gender;
    int int_class;
    std::vector<int> score;
    int average = 0;
};
std::unordered_map<std::string, Students> students_info;//所有学生的信息
std::unordered_map<std::string, int> students_rank;//存放rank
std::unordered_map<int, std::string> rank_students;

struct StudentsComp {
    bool operator()(const std::string &_student1, const std::string &_student2) const {
        if (students_info[_student1].average == students_info[_student2].average) {
            for (int i = 0; i < 9; i++) {
                if (students_info[_student1].score[i] > students_info[_student2].score[i])
                    return true;
                if (students_info[_student1].score[i] < students_info[_student2].score[i])
                    return false;
            }
            int tmp = strcmp(_student1.c_str(), _student2.c_str());
            if (tmp < 0)
                return true;
            else
                return false;
        } else
            return students_info[_student1].average > students_info[_student2].average;
    }
};

std::set<std::string, StudentsComp> students_list;
int flag_start = 0, students_num = 0;

int main() {
    std::string str;
    while (std::cin >> str, str != "END") {
        if (str == "UPDATE") {
            std::string name;
            std::cin >> name;
            if (!students_info.count(name)) {
                printf("[Error]Update failed.\n");
                continue;
            }
            int code, temp;
            scanf("%d %d", &code, &temp);
            students_list.erase(name);
            students_info[name].score[9] += (temp - students_info[name].score[code]);
            students_info[name].average = students_info[name].score[9] / 9;
            students_info[name].score[code] = temp;
            students_list.insert(name);
        } else if (str == "QUERY") {
            char name[25];
            scanf("%s", name);
            if (students_rank.count(name))
                printf("STUDENT %s NOW AT RANKING %d\n", name, students_rank[name]);
            else
                printf("[Error]Query failed.\n");
        } else if (str == "ADD") {
            int sum = 0;
            std::string name;
            std::cin >> name;
            Students student_ex;
            if (flag_start) {
                printf("[Error]Cannot add student now.\n");
                continue;
            }
            if (students_info.count(name)) {
                printf("[Error]Add failed.\n");
                continue;
            }
            std::cin >> student_ex.gender >> student_ex.int_class;
            for (int i = 0; i < 9; i++) {
                int num;
                scanf("%d", &num);
                sum += num;
                student_ex.score.push_back(num);
            }
            student_ex.score.push_back(sum);
            student_ex.average = sum / 9;
            students_info[name] = student_ex;
            students_num++;
        } else if (str == "FLUSH") {
            int rank = 1;
            for (const auto &set_iter: students_list) {
                rank_students[rank] = set_iter;
                students_rank[set_iter] = rank;
                rank++;
            }
        } else if (str == "PRINTLIST") {
            for (int i = 1; i <= students_num; i++) {
                std::string name = rank_students[i];
                std::string gender;
                if (students_info[name].gender == 'M')
                    gender = "male";
                else
                    gender = "female";
                printf("%d %s %s %d %d\n", i, name.c_str(), gender.c_str(), students_info[name].int_class,
                       students_info[name].average);
            }
        } else if (str == "START") {
            flag_start = 1;
            for (const auto &map_iter: students_info)
                students_list.insert(map_iter.first);
            int rank = 1;
            for (const auto &set_iter: students_list) {
                rank_students[rank] = set_iter;
                students_rank[set_iter] = rank;
                rank++;
            }
        }
    }
    return 0;
}