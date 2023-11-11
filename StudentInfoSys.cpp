#include "StudentManageSys.h"

// 重载日期类的输出运算符
std::ostream &operator<<(std::ostream &os, Date date){
    os << date.year << '/' << date.month << '/' << date.day;
    return os;
}

// 重载日期类的比较运算符，用于比较学生的出生日期大小
bool operator>(Date date1, Date date2){
    if (date1.year != date2.year){
        return date1.year < date2.year;
    }
    else{
        if (date1.month != date2.month){
            return date1.month < date2.month;
        }
        else{
            return date1.day < date2.day;
        }
    }
}

// 比较器函数，用于按照id进行排序
bool CompareById(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.first < p2.first;
}

// 比较器函数，用于按照姓名进行排序
bool CompareByName(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.first.name < p2.second.first.name;
}

// 比较器函数，用于按照出生日期进行排序
bool CompareByBirthday(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.first.birthday > p2.second.first.birthday;
}

// 比较器函数，用于按照学年进行排序
bool CompareBySchoolYear(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.first.schoolYear < p2.second.first.schoolYear;
}

// 比较器函数，用于按照单项分数进行排序
// 按照C Programming Language
bool CompareByCppScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.second["C Programming Language"].score > p2.second.second["C Programming Language"].score;
}

// 按照Advanced math
bool CompareByMathScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.second["Advanced math"].score > p2.second.second["Advanced math"].score;
}

// 按照College English
bool CompareByEngScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.second["College English"].score > p2.second.second["College English"].score;
}

// 按照Control Theory
bool CompareByConScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.second["Control Theory"].score > p2.second.second["Control Theory"].score;
}

// 按照Python
bool CompareByPyScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    return p1.second.second["Python"].score > p2.second.second["Python"].score;
}

// 比较器函数，用于按照总分数进行排序
bool CompareByTotalScore(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2){
    double totalScore1 = 0;
    for (const auto &course : p1.second.second){
        totalScore1 += course.second.score;
    }
    double totalScore2 = 0;
    for (const auto &course : p2.second.second){
        totalScore2 += course.second.score;
    }
    return totalScore1 > totalScore2;
}

StudentManageSys(std::ifstream &fin1, std::ifstream &fin2){
    // 读取StudentCourse.txt的内容
    std::string line;
    // 读取第一行并忽略
    std::getline(fin1, line);
    while (std::getline(fin1, line)){
        std::size_t pos1 = line.find(' ');
        std::size_t pos2 = line.find(' ', pos1 + 1);
        while (pos2 != std::string::npos && !std::isdigit(line[pos2 + 1])){
            pos2 = line.find(' ', pos2 + 1);
        }
        std::size_t pos3 = line.find(' ', pos2 + 1);

        std::string id_ = line.substr(0, pos1);
        std::string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        CourseData cd{};
        cd.credits = std::stod(line.substr(pos2 + 1, pos3 - pos2 - 1));
        cd.score = std::stod(line.substr(pos3 + 1));

        // 将该课程作为新键加入StuDict[id_]的StudentCourse
        StuDict[id_].second[name] = cd;
    }
    // 读取StudentInfo.txt的内容
    // 读取第一行并忽略
    std::getline(fin2, line);
    while (std::getline(fin2, line)){
        StudentInfo stu;
        std::string id_, birth;
        std::stringstream ss(line);
        ss >> id_ >> stu.name >> stu.sex >> birth >> stu.schoolYear >> stu.birthplace;
        stu.birthday = Date(birth);
        // 将stu更新到StuDict
        StuDict[id_].first = stu;
    }
}

// 按学号打印学生信息
void Print(const std::string &id_){
    std::cout << "学号: " << id_ << std::endl;
    std::cout << "姓名: " << StuDict[id_].first.name << std::endl;
    std::cout << "性别: " << StuDict[id_].first.sex << std::endl;
    std::cout << "出生日期: " << StuDict[id_].first.birthday << std::endl;
    std::cout << "学年: " << StuDict[id_].first.schoolYear << std::endl;
    std::cout << "出生地: " << StuDict[id_].first.birthplace << std::endl;
    double totalcredits = 0;
    for (const auto &c : StuDict[id_].second){
        std::cout << "课程: " << c.first << " / 学分: " << c.second.credits << " / 分数: " << c.second.score << std::endl;
        totalcredits += c.second.score;
    }
    std::cout << "总分为: " << totalcredits << std::endl;
}

// 打印所有学生信息
void PrintAll(){
    for (const auto &i : StuDict){
        Print(i.first);
        std::cout << std::endl;
    }
}

// 按照指定的比较器函数对vector进行排序，使用类模版思想
template <typename Compare>
void Sort(Compare comp){
    std::vector<std::pair<std::string, std::pair<StudentInfo, StudentCourse>>> vec(StuDict.begin(), StuDict.end());
    std::sort(vec.begin(), vec.end(), comp);
    for (const auto &i : vec){
        Print(i.first);
        std::cout << std::endl;
    }
}

// 查询某门课分数在给定范围内的学生信息
void FindStuInfoInRange(const std::string &course, double minScore, double maxScore){
    std::cout << course << " 在 " << minScore << " 到 " << maxScore << " 分数段的人有: " << std::endl;
    for (auto p : StuDict){
        if (p.second.second[course].score >= minScore && p.second.second[course].score <= maxScore){
            std::cout << p.first << " / " << p.second.first.name << " / " << p.second.second[course].score << "分" << std::endl;
        }
    }
    std::cout << std::endl;
}

double AverageScore(const std::string &id_){
    double totalCredits = 0;
    double totalScore = 0;
    for (const auto &c : StuDict[id_].second){
        totalCredits += c.second.credits;
        totalScore += c.second.credits * c.second.score;
    }
    return totalScore / totalCredits;
}

// 根据给定条件查询学生信息
// 由于C++不支持条件表达式直接作为参数，所以我使用了一个布尔型函数指针作为参数，
// 函数指针cond指向一个接受一个学生信息并返回布尔值的函数。
void FindStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &)> &cond){
    bool flag = false;
    for (const auto &p : StuDict){
        if (cond(p)){
            flag = true;
            Print(p.first);
            std::cout << std::endl;
        }
    }
    if (!flag)
        std::cout << "没有符合该条件的学生" << std::endl;
}

// 这个函数是上面函数的特例版本，注意到这里使用了两个参数，res时查找到的学生的容器，用来写进txt文件
void FindStuInfoByConditions2(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &)> &cond, std::vector<std::string> &res){
    for (const auto &p : StuDict){
        if (cond(p)){
            res.emplace_back(p.first);
        }
    }
}

// 根据给定条件删除学生信息
void RemoveStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &)> &cond){
    std::vector<std::string> toDelete;
    for (const auto &p : StuDict){
        if (cond(p)){
            toDelete.push_back(p.first);
        }
    }
    for (const auto &id : toDelete){
        StuDict.erase(id);
    }
}

void Test(std::ofstream &file){
    // res1, res2, 用来存放 a) b) 查找到学生的学号
    std::vector<std::string> res1, res2;

    // 选修 C Program Course且成绩小于 60 分的学生
    FindStuInfoByConditions2([](std::pair<std::string, std::pair<StudentInfo, StudentCourse>> p)
                             { return p.second.first.schoolYear == "2020" && p.second.second.count("C Programming Language") > 0 && p.second.second["C Programming Language"].score < 60; },
                             res1);
    file << "a) 选修 C Program Course且成绩小于 60 分的学生" << std::endl;
    for (const auto &p : res1){
        file << p << " " << StuDict[p].first.name << " " << StuDict[p].first.schoolYear << "级 " << StuDict[p].second["C Programming Language"].score << "分" << std::endl;
    }

    // 课程平均分大于 80 的学生
    FindStuInfoByConditions2([this](const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p)
                             { return AverageScore(p.first) > 80; },
                             res2);
    file << "b) 课程平均分大于 80 的学生" << std::endl;
    for (const auto &p : res2){
        file << p << " " << StuDict[p].first.name << " 平均分" << AverageScore(p) << std::endl;
    }

    // 查询每个学生是否修满 20 学分
    file << "c) 查询每个学生是否修满 20 学分" << std::endl;
    for (const auto &p : StuDict){
        double totalCredits = 0;
        for (const auto &c : p.second.second){
            totalCredits += c.second.credits;
        }
        file << p.first << " " << p.second.first.name << " " << (totalCredits >= 20 ? "Yes" : "No") << std::endl;
    }
}

int main(){
    std::ifstream fin1("./StudentCourse.txt");
    std::ifstream fin2("./StudentInfo.txt");
    StudentManageSys sms(fin1, fin2);

    std::ofstream file("./result.txt");
    sms.Test(file);

    std::cout << "@————展示排序功能(按照逻辑上的先后关系)————@" << std::endl;
    std::cout << "1. 按照id顺序排序:" << std::endl;
    sms.Sort(CompareById);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "2. 按照姓名排序:" << std::endl;
    sms.Sort(CompareByName);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "3. 按照出生日期排序:" << std::endl;
    sms.Sort(CompareByBirthday);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "4. 按照入学年份排序:" << std::endl;
    sms.Sort(CompareBySchoolYear);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "5. 按照C Programming Language排序:" << std::endl;
    sms.Sort(CompareByCppScore);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "6. 按照Advanced math:" << std::endl;
    sms.Sort(CompareByMathScore);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "7. 按照College English排序:" << std::endl;
    sms.Sort(CompareByEngScore);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "8. 按照Control Theory排序:" << std::endl;
    sms.Sort(CompareByConScore);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "9. 按照Python排序:" << std::endl;
    sms.Sort(CompareByPyScore);
    std::cout << "—————————————————————————————— " << std::endl;
    std::cout << "10. 按照总分排序:" << std::endl;
    sms.Sort(CompareByTotalScore);
    std::cout << "—————————————————————————————— " << std::endl;

    std::cout << "@————展示范围查询功能（如果有多个条目，默认按照 id 排序）————@" << std::endl;
    sms.FindStuInfoInRange("C Programming Language", 0, 60);
    sms.FindStuInfoInRange("College English", 80, 90);

    std::cout << "@————展示多条件查询和删除功能（如果有多个条目，默认按照 id 排序）————@" << std::endl;
    std::cout << "----测试样例(1): 查询性别为男且出生在2000年及之后的学生---- " << std::endl;
    sms.FindStuInfoByConditions([](const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p)
                                { return p.second.first.sex == "Male" && p.second.first.birthday.year >= 2000; });

    std::cout << "----测试样例(2): 查询性别为女且C++或大学英语成绩不低于90分的学生---- " << std::endl;
    sms.FindStuInfoByConditions([](std::pair<std::string, std::pair<StudentInfo, StudentCourse>> p)
                                { return p.second.first.sex == "Female" && (p.second.second["C Programming Language"].score >= 90 || p.second.second["College English"].score >= 90); });

    std::cout << "----测试样例(3): 删除所有女生和出生在2月的男生, 并调用PrintAll()查看删除情况---- " << std::endl;
    sms.RemoveStuInfoByConditions([](const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p)
                                  { return p.second.first.sex == "Female" || (p.second.first.sex == "Male" && p.second.first.birthday.month == 2); });
    sms.PrintAll();

    return 0;
}