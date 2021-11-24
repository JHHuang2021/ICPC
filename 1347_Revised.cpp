#include <bits/stdc++.h>

struct LastSubmisson {
    int status = 0;
    int problem = 0;
};

struct Problem {
    int submit_num_of_times = 0;
    int freeze_submit_num_of_times = 0;
    int freeze_accepted = 0;
    int accept_time = 0;
    int ac = 0;
};

struct Team {
    int solved = 0;
    int all_penalty = 0;
    int submit[5][27] = {0};//存放每一道题每一种评测状态的最后一次提交的时间
    int all_status[27] = {0};//存放每一道题最后一次的提交的评测状态
    int all_problem[5] = {0};//存放每一种评测状态下最后一次提交的题目
    LastSubmisson last_submission;//存放最后一次的提交
    Problem problem_status[27];
    std::multiset<int, std::greater<> > ac_time;//从大到小存放所有通过题目的通过时间
    std::set<char> freezed_problem;//从小到大存放所有冻结的题目
};
std::unordered_map<std::string, Team> team_info;//存放所有队伍的信息
const int kN = 31;

struct TeamCmp {//set比较规则
    bool operator()(const std::string &team1, const std::string &team2) const {
        const auto &_iter1 = team_info[team1], &_iter2 = team_info[team2];
        if (_iter1.solved == _iter2.solved) {
            if (_iter1.all_penalty == _iter2.all_penalty) {
                auto iter1 = _iter1.ac_time.begin(), iter2 = _iter2.ac_time.begin();
                for (int i = 1; i <= _iter1.solved; ++i) {
                    if (*iter1 - *iter2 >> kN)
                        return true;
                    if (*iter2 - *iter1 >> kN)
                        return false;
                    ++iter1;
                    ++iter2;
                }
                int tmp = strcmp(team1.c_str(), team2.c_str());
                if (tmp < 0)
                    return true;
                else
                    return false;
            } else
                return _iter1.all_penalty - _iter2.all_penalty >> kN;
        } else
            return _iter2.solved - _iter1.solved >> kN;
    }
};

std::set<std::string, TeamCmp> team_list;//更新排名
std::unordered_map<std::string, int> team_rank;
std::string rank_team[10001];
std::string int_to_status[5] = {"NULL",
                                "Accepted",
                                "Wrong_Answer",
                                "Runtime_Error",
                                "Time_Limit_Exceed"};
int flag_start = 0, flag_freeze = 0, duration_time, problem_count, team_number = 0;

int main() {
    std::ios::sync_with_stdio(false);
    void Addteam();
    void Submit();
    void Start();
    void Flush();
    void Freeze();
    void Scroll();
    void QueryRanking();
    void QuerySubmission();
    void End();
    while (true) {
        std::string op;
        std::cin >> op;
        if (op == "ADDTEAM") {
            Addteam();
            continue;
        }
        if (op == "SUBMIT") {
            Submit();
            continue;
        }
        if (op == "QUERY_RANKING") {
            QueryRanking();
            continue;
        }
        if (op == "QUERY_SUBMISSION") {
            QuerySubmission();
            continue;
        }
        if (op == "FLUSH") {
            Flush();
            continue;
        }
        if (op == "SCROLL") {
            Scroll();
            continue;
        }
        if (op == "FREEZE") {
            Freeze();
            continue;
        }
        if (op == "START") {
            Start();
            continue;
        }
        if (op == "END") {
            End();
            break;
        }
    }
    return 0;
}

void Addteam() {
    std::string team_name;
    std::cin >> team_name;
    if (flag_start) {
        fputs("[Error]Add failed: competition has started.\n", stdout);
        return;
    }
    if (team_info.count(team_name)) {
        fputs("[Error]Add failed: duplicated team name.\n", stdout);
        return;
    }
    Team team_ex;
    team_info[team_name] = team_ex;
    ++team_number;
    team_list.insert(team_name);
    fputs("[Info]Add successfully.\n", stdout);
}

void Start() {
    std::string temp_str;
    if (flag_start) {
        fputs("[Error]Start failed: competition has started.\n", stdout);
        return;
    } else {
        std::cin >> temp_str >> duration_time >> temp_str >> problem_count;
        flag_start = 1;
        int rank = 1;
        for (const auto &set_iter: team_list) {
            team_rank[set_iter] = rank;
            rank_team[rank] = set_iter;
            ++rank;
        }
        fputs("[Info]Competition starts.\n", stdout);
    }
}

void Submit() {
    std::string temp_str, team_name, submit_status;
    char problem_name;
    int submit_time, status_to_int;
    std::cin >> problem_name >> temp_str >> team_name >> temp_str >> submit_status >> temp_str >> submit_time;
    auto &map_iter = team_info[team_name];
    auto &_iter = map_iter.problem_status[problem_name - 'A' + 1];
    if (submit_status == "Accepted")
        status_to_int = 1;
    else if (submit_status == "Wrong_Answer")
        status_to_int = 2;
    else if (submit_status == "Runtime_Error")
        status_to_int = 3;
    else if (submit_status == "Time_Limit_Exceed")
        status_to_int = 4;
    map_iter.submit[status_to_int][problem_name - 'A' + 1] = submit_time;
    map_iter.submit[status_to_int][0] = submit_time;
    map_iter.all_problem[status_to_int] = problem_name - 'A' + 1;
    map_iter.submit[0][problem_name - 'A' + 1] = submit_time;
    map_iter.all_status[problem_name - 'A' + 1] = status_to_int;
    map_iter.submit[0][0] = submit_time;
    map_iter.last_submission.status = status_to_int;
    map_iter.last_submission.problem = problem_name - 'A' + 1;
    //若team_info[team_name].problem_status[problem_name - 'A' + 1].freeze_submit_num_of_times=0，则说明没有被冻结
    if (_iter.ac && !_iter.freeze_submit_num_of_times)
        return;
    if (flag_freeze) {
        map_iter.freezed_problem.insert(problem_name);
        _iter.freeze_submit_num_of_times++;
    }
    if (_iter.ac && _iter.freeze_submit_num_of_times)
        return;
    if (!_iter.ac && !_iter.freeze_submit_num_of_times) {
        if (submit_status == "Accepted") {
            _iter.ac = 1;
            team_list.erase(team_name);
            _iter.accept_time = submit_time;
            ++map_iter.solved;
            map_iter.ac_time.insert(submit_time);
            map_iter.all_penalty += (_iter.submit_num_of_times * 20 + submit_time);
            team_list.insert(team_name);
        }
        (submit_status != "Accepted") && ++_iter.submit_num_of_times;
    }
    if (!_iter.ac && _iter.freeze_submit_num_of_times) {
        (submit_status != "Accepted") ? ++_iter.freeze_accepted : (_iter.accept_time = submit_time, _iter.ac = 1);
    }
}

void Flush() {
    int rank = 1;
    for (const auto &set_iter: team_list) {
        team_rank[set_iter] = rank;
        rank_team[rank] = set_iter;
        ++rank;
    }
    fputs("[Info]Flush scoreboard.\n", stdout);
}

void Freeze() {
    if (flag_freeze) {
        fputs("[Error]Freeze failed: scoreboard has been frozen.\n", stdout);
        return;
    } else {
        fputs("[Info]Freeze scoreboard.\n", stdout);
        flag_freeze = 1;
    }
}

void Scroll() {
    void Print();
    if (!flag_freeze) {
        fputs("[Error]Scroll failed: scoreboard has not been frozen.\n", stdout);
        return;
    } else {
        flag_freeze = 0;
        fputs("[Info]Scroll scoreboard.\n", stdout);
        int rank = 1;
        for (const auto &set_iter: team_list) {
            team_rank[set_iter] = rank;
            rank_team[rank] = set_iter;
            ++rank;
        }
        Print();
        while (true) {
            auto iter = --team_list.end();
            while (team_info[*iter].freezed_problem.empty()) {
                team_list.erase(*iter);
                if (team_list.empty()) {
                    rank = 1;
                    for (const auto &map_iter: team_info)
                        team_list.insert(map_iter.first);
                    for (const auto &set_iter2: team_list) {
                        team_rank[set_iter2] = rank;
                        rank_team[rank] = set_iter2;
                        ++rank;
                    }
                    Print();
                    return;
                }
                iter = --team_list.end();
            }
            auto iter_cmp1 = iter;
            ++iter_cmp1;
            std::string name_cmp1 = *iter_cmp1++;
            std::string name = *iter;
            auto &map_iter = team_info[name];
            const auto &set_iter = map_iter.freezed_problem.begin();
            auto &_iter = map_iter.problem_status[*set_iter - 'A' + 1];
            //若accpet_time不为零，说明已经通过
            if (_iter.accept_time) {
                team_list.erase(name);
                ++map_iter.solved;
                map_iter.ac_time.insert(_iter.accept_time);
                map_iter.all_penalty += ((_iter.submit_num_of_times + _iter.freeze_accepted) * 20 + _iter.accept_time);
                _iter.ac = 1;
                _iter.submit_num_of_times += (_iter.freeze_accepted);
                team_list.insert(name);
            } else
                _iter.submit_num_of_times += (_iter.freeze_submit_num_of_times);
            _iter.freeze_submit_num_of_times = 0;
            _iter.freeze_accepted = 0;
            map_iter.freezed_problem.erase(*set_iter);
            auto iter1 = team_list.find(name);
            auto iter_cmp2 = iter1;
            ++iter_cmp2;
            std::string name_cmp2 = *iter_cmp2;
            if (name_cmp1 != name_cmp2) {
                ++iter1;
                printf("%s %s %d %d\n", name.c_str(), iter1->c_str(), map_iter.solved, map_iter.all_penalty);
            }
        }
    }
}

void QueryRanking() {
    std::string team_name;
    std::cin >> team_name;
    if (!team_info.count(team_name)) {
        fputs("[Error]Query ranking failed: cannot find the team.\n", stdout);
        return;
    }
    fputs("[Info]Complete query ranking.\n", stdout);
    (flag_freeze) && fputs("[Warning]Scoreboard is frozen. The ranking may be inaccurate until it were scrolled.\n", stdout);;
    printf("%s NOW AT RANKING %d\n", team_name.c_str(), team_rank[team_name]);
}

void Print() {
    for (int i = 1; i <= team_number; ++i) {
        std::string name = rank_team[i];
        const auto &map_iter = team_info[name];
        printf("%s %d %d %d ", name.c_str(), i, map_iter.solved, map_iter.all_penalty);
        for (int j = 1; j <= problem_count; ++j) {
            const auto &iter = map_iter.problem_status[j];
            if (iter.freeze_submit_num_of_times)
                (!iter.submit_num_of_times) ? printf("0/%d ", iter.freeze_submit_num_of_times) : printf("-%d/%d ",
                                                                                                        iter.submit_num_of_times,
                                                                                                        iter.freeze_submit_num_of_times);
            else {
                if (iter.ac)
                    (!iter.submit_num_of_times) ? printf("+ ") : printf("+%d ", iter.submit_num_of_times);
                else
                    (!iter.submit_num_of_times) ? printf(". ") : printf("-%d ", iter.submit_num_of_times);
            }
        }
        printf("\n");
    }
}

void QuerySubmission() {
    int status_to_int;
    std::string temp, team_name, problem_name, status;
    std::cin >> team_name >> temp >> problem_name >> temp >> status;
    if (!team_info.count(team_name)) {
        fputs("[Error]Query submission failed: cannot find the team.\n", stdout);
        return;
    }
    fputs("[Info]Complete query submission.\n", stdout);
    problem_name = problem_name.substr(8, problem_name.length() - 8);
    status = status.substr(7, status.length() - 7);
    const auto &iter = team_info[team_name];
    if (status != "ALL")
        if (status == "Accepted")
            status_to_int = 1;
        else if (status == "Wrong_Answer")
            status_to_int = 2;
        else if (status == "Runtime_Error")
            status_to_int = 3;
        else if (status == "Time_Limit_Exceed")
            status_to_int = 4;
    if (problem_name == "ALL")
        if (status == "ALL")
            (!iter.submit[0][0]) ? printf("Cannot find any submission.\n") : printf("%s %c %s %d\n", team_name.c_str(),
                                                                                    'A' + iter.last_submission.problem - 1,
                                                                                    int_to_status[iter.last_submission.status].c_str(),
                                                                                    iter.submit[0][0]);
        else
            (!iter.submit[status_to_int][0]) ? printf("Cannot find any submission.\n") : printf("%s %c %s %d\n",
                                                                                                team_name.c_str(),
                                                                                                iter.all_problem[status_to_int] +
                                                                                                'A' - 1, status.c_str(),
                                                                                                iter.submit[status_to_int][0]);
    else if (status == "ALL")
        (!iter.submit[0][problem_name[0] - 'A' + 1]) ? printf("Cannot find any submission.\n") : printf("%s %c %s %d\n",
                                                                                                        team_name.c_str(),
                                                                                                        problem_name[0],
                                                                                                        int_to_status[iter.all_status[
                                                                                                                problem_name[0] -
                                                                                                                'A' + 1]].c_str(),
                                                                                                        iter.submit[0][
                                                                                                                problem_name[0] -
                                                                                                                'A' + 1]);
    else
        (!iter.submit[status_to_int][problem_name[0] - 'A' + 1]) ? printf("Cannot find any submission.\n") : printf(
                "%s %c %s %d\n", team_name.c_str(), problem_name[0], status.c_str(),
                iter.submit[status_to_int][problem_name[0] - 'A' + 1]);
}

void End() {
    fputs("[Info]Competition ends.\n", stdout);
}