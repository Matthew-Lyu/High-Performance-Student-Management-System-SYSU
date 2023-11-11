# Student Management System

This is a  C++ program for managing student information, including personal details and course scores. The program provides functionalities such as sorting, printing, and querying student data based on various criteria.

## Project Background

This documentation outlines the completion of the third assignment for the C++ course design in the School of Intelligent Engineering at Sun Yat-sen University for the academic year 2022. The project aims to develop a comprehensive student management system, providing functionalities for organizing and analyzing student information.

![image-20231111093654972](https://p.ipic.vip/eu8gdn.png)

## Table of Contents

- [Usage](#usage)
- [File Structure](#file-structure)
- [Classes and Functions](#classes-and-functions)
- [Example Usage](#example-usage)

## Usage

The program reads student information from two input files: `StudentCourse.txt` and `StudentInfo.txt`. It performs various operations, including sorting, printing, and querying student data based on different criteria. The results are stored in an output file named `result.txt`.

## File Structure

- `main.cpp`: Contains the main program logic, class definitions, and example usage.
- `StudentCourse.txt`: Input file containing student course information.
- `StudentInfo.txt`: Input file containing student personal information.
- `result.txt`: Output file storing the results of queries and tests.

## Classes and Functions

### `Date` Class

The `Date` class is responsible for representing dates and includes methods for parsing date strings and comparing dates. The class is used for handling student birthdates, allowing for easy comparison and manipulation.

- **Attributes:**
  - `year`: An integer representing the year.
  - `month`: An integer representing the month.
  - `day`: An integer representing the day.

- **Methods:**
  - `Date()`: Default constructor.
  - `explicit Date(const std::string& date_str)`: Constructor that takes a date string (in the format "YYYY/MM/DD") and initializes the `Date` object.
  - `operator<<`: Overloaded output stream operator to facilitate easy printing of `Date` objects.
  - `operator>`: Overloaded greater-than operator for comparing two `Date` objects.

### `StudentInfo` Struct

The `StudentInfo` struct holds personal information about a student, such as name, sex, birthday, school year, and birthplace. This structure is used to organize and store individual student data.

- **Attributes:**
  - `name`: A string representing the student's name.
  - `sex`: A string representing the student's gender.
  - `birthday`: An instance of the `Date` class representing the student's birthdate.
  - `schoolYear`: A string representing the student's school year.
  - `birthplace`: A string representing the student's birthplace.

### `CourseData` Struct

The `CourseData` struct stores information about a student's performance in a particular course, including the number of credits and the score obtained. This structure is utilized for organizing course-specific data.

- **Attributes:**
  - `credits`: A double representing the number of credits for the course.
  - `score`: A double representing the student's score in the course.

### `StudentCourse` Typedef

The `StudentCourse` typedef is an unordered map associating course names with `CourseData` structures. This data structure is used to store a student's performance in various courses.

### `Compare` Functions

Several comparator functions are defined for sorting students based on different criteria. These functions are utilized in the sorting functionality of the `StudentManageSys` class.

- `CompareById`: Compares students based on their ID.
- `CompareByName`: Compares students based on their names.
- `CompareByBirthday`: Compares students based on their birthdates.
- `CompareBySchoolYear`: Compares students based on their school years.
- `CompareByCppScore`, `CompareByMathScore`, `CompareByEngScore`, `CompareByConScore`, `CompareByPyScore`: Compare students based on scores in specific courses.
- `CompareByTotalScore`: Compares students based on their total scores across all courses.

### `StudentManageSys` Class

The `StudentManageSys` class is the main class responsible for managing student information. It includes methods for reading data from files, printing student information, sorting students, and performing various queries.

- **Attributes:**
  - `StuDict`: A map associating student IDs with pairs of `StudentInfo` and `StudentCourse` structures.

- **Methods:**
  - `StudentManageSys(std::ifstream& fin1, std::ifstream& fin2)`: Constructor that initializes the class by reading data from two input files (`StudentCourse.txt` and `StudentInfo.txt`).
  - `Print(const std::string& id_)`: Prints information for a specific student based on their ID.
  - `PrintAll()`: Prints information for all students.
  - `Sort(Compare comp)`: Sorts and prints students based on the specified comparator function.
  - `FindStuInfoInRange(const std::string& course, double minScore, double maxScore)`: Finds and prints students whose scores in a specific course fall within a given range.
  - `AverageScore(const std::string& id_)`: Calculates and returns the average score of a student based on their ID.
  - `FindStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond)`: Finds and prints students based on a given condition using a boolean function pointer.
  - `FindStuInfoByConditions2(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond, std::vector<std::string>& res)`: A specialized version of the above function, which also returns the results.
  - `RemoveStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond)`: Removes students based on a given condition.
  - `Test(std::ofstream& file)`: Performs various tests and writes results to a file.

These classes and functions collectively form a comprehensive student management system with features for data organization, sorting, querying, and testing.

## Example Usage

```cpp
#include "student_management_system.h"

int main() {
    std::ifstream fin1("./StudentCourse.txt");
    std::ifstream fin2("./StudentInfo.txt");
    StudentManageSys sms(fin1, fin2);

    std::ofstream file("./result.txt");
    sms.Test(file);

    // Display sorting functionality
    std::cout << "@————Sorting Features (in logical order)————@" << std::endl;
    sms.Sort(CompareById);
    // ... (similarly, other sorting criteria)

    // Display range query features
    std::cout << "@————Range Query Features (default order by ID if multiple entries)————@" << std::endl;
    sms.FindStuInfoInRange("C Programming Language", 0, 60);
    sms.FindStuInfoInRange("College English", 80, 90);

    // Display multiple condition query and deletion features
    std::cout << "@————Multiple Condition Query and Deletion Features (default order by ID)————@" << std::endl;
    // ... (similarly, other query conditions and deletions)

    return 0;
}
```

Feel free to modify and adapt the program to suit your needs.
