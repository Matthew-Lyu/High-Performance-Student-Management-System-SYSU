#ifndef STUDENT_MANAGE_SYS_H
#define STUDENT_MANAGE_SYS_H

#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <functional>

// Date类，用于解析学生出生日期，多条件交并查找学生时使用
class Date {
public:
    int year;
    int month;
    int day;
    Date() = default;
    explicit Date(const std::string& date_str) {
        std::stringstream ss(date_str);
        std::string year_str, month_str, day_str;
        std::getline(ss, year_str, '/');
        std::getline(ss, month_str, '/');
        std::getline(ss, day_str);
        year = std::stoi(year_str);
        month = std::stoi(month_str);
        day = std::stoi(day_str);
    }
};

// 学生个人信息的结构体
struct StudentInfo {
    std::string name;
    std::string sex;
    Date birthday{};
    std::string schoolYear;
    std::string birthplace;
};

// 学生课程分数的结构体
struct CourseData {
    double credits;
    double score;
};

// 使用unordered_map存储学生的课程信息，键为课程名称，键值为课程分数结构体
// unordered_map是一种关联式容器，它存储了关键字/值对。
// 与unordered_map不同，unordered_map底层使用的是哈希表而不是红黑树，因此其元素的顺序是无序的。
// 由于使用了哈希表，unordered_map的查找速度要快得多，但是在插入、删除和遍历元素时略逊于map。
typedef std::unordered_map<std::string, CourseData> StudentCourse;

// 比较器函数，用于按照id进行排序
bool CompareById(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 比较器函数，用于按照姓名进行排序
bool CompareByName(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 比较器函数，用于按照出生日期进行排序
bool CompareByBirthday(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 比较器函数，用于按照学年进行排序
bool CompareBySchoolYear(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 比较器函数，用于按照单项分数进行排序
// 按照C Programming Language
bool CompareByCppScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 按照Advanced math
bool CompareByMathScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 按照College English
bool CompareByEngScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 按照Control Theory
bool CompareByConScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 按照Python
bool CompareByPyScore(std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 比较器函数，用于按照总分数进行排序
bool CompareByTotalScore(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);

// 学生管理系统类
class StudentManageSys {
public:
    // 构造函数
    StudentManageSys(std::ifstream& fin1, std::ifstream& fin2);

    // 按学号打印学生信息
    void Print(const std::string& id_);

    // 打印所有学生信息
    void PrintAll();

    // 按照指定的比较器函数对vector进行排序，使用类模版思想
    template<typename Compare>
    void Sort(Compare comp);

    // 查询某门课分数在给定范围内的学生信息
    void FindStuInfoInRange(const std::string& course, double minScore, double maxScore);

    double AverageScore(const std::string& id_);

    // 根据给定条件查询学生信息
    // 由于C++不支持条件表达式直接作为参数，所以我使用了一个布尔型函数指针作为参数，
    // 函数指针cond指向一个接受一个学生信息并返回布尔值的函数。
    void FindStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond);

    // 这个函数是上面函数的特例版本，注意到这里使用了两个参数，res时查找到的学生的容器，用来写进txt文件
    void FindStuInfoByConditions2(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond, std::vector<std::string>& res);


    // 根据给定条件删除学生信息
    void RemoveStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond);

    void Test(std::ofstream& file);

private:
    // 使用map存储学生的信息，键为学号，键值为pair形式，pair的first存储个人信息，second存储课程信息
    using id = std::string;
    std::map<id, std::pair<StudentInfo, StudentCourse>> StuDict;
};


#endif // STUDENT_MANAGE_SYS_H