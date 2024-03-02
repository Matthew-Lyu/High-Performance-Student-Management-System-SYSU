# Student Management System

This is a  C++ program for managing student information, including personal details and course scores. The program provides functionalities such as sorting, printing, and querying student data based on various criteria.

## Project Background

This documentation outlines the completion of the third assignment for the C++ course design in the School of Intelligent Engineering at Sun Yat-sen University for the academic year 2022. The project aims to develop a comprehensive student management system, providing functionalities for organizing and analyzing student information

![image-20231111093654972](https://p.ipic.vip/eu8gdn.png)

## Table of Contents

- [Usage](#usage)
- [File Structure](#file-structure)
- [Classes and Functions](#classes-and-functions)
- [Implemented Functionalities and Functions](#implemented-functionalities-and-functions)
- [Example Usage](#example-usage)
- [Project Highlights](#project-highlights)

## Usage

The program reads student information from two input files: `StudentCourse.txt` and `StudentInfo.txt`. It performs various operations, including sorting, printing, and querying student data based on different criteria. The results are stored in an output file named `result.txt`.

## File Structure

The project consists of two files:

- `StudentManageSys.h`: Header file containing class declarations, structure definitions, and function prototypes.
- `StudentManageSys.cpp`: Implementation file containing the actual implementation of the functions declared in the header file.

## Classes and Functions

### 1. `StudentManageSys.h`

#### Contents:

- **Date Class**: Represents the date of birth, providing functionality to parse a date string.
  
```cpp
class Date {
    // ...
};
```

- **StudentInfo Structure**: Contains personal information about a student.

```cpp
struct StudentInfo {
    std::string name;
    std::string sex;
    Date birthday{};
    std::string schoolYear;
    std::string birthplace;
};
```

- **CourseData Structure**: Stores information about a student's course.

```cpp
struct CourseData {
    double credits;
    double score;
};
```

- **StudentCourse Type**: An unordered map representing a student's course information.

```cpp
typedef std::unordered_map<std::string, CourseData> StudentCourse;
```

- **StudentManageSys Class**: The main class representing the student management system.

```cpp
class StudentManageSys {
    // ...
};
```

- **Comparator Functions**: Various comparator functions for sorting students based on different criteria.

```cpp
bool CompareById(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>& p2);
// ... Other comparator functions
```

### 2. `StudentManageSys.cpp`

#### Contents:

- **Implementation of Date Class Overloads**: Overloaded operators for date comparison.

```cpp
std::ostream &operator<<(std::ostream &os, Date date);
bool operator>(Date date1, Date date2);
```

- **Comparator Function Implementations**: Implementations of comparator functions for sorting students.

```cpp
bool CompareById(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p1, const std::pair<std::string, std::pair<StudentInfo, StudentCourse>> &p2) {
    return p1.first < p2.first;
}
// ... Other comparator function implementations
```

- **StudentManageSys Class Implementation**: Methods for printing, sorting, finding students, calculating average scores, and more.

```cpp
void StudentManageSys::Sort(Compare comp) {
    // ...
}

void StudentManageSys::FindStuInfoInRange(const std::string &course, double minScore, double maxScore) {
    // ...
}

double StudentManageSys::AverageScore(const std::string &id_) {
    // ...
}

// ... Other method implementations
```

- **Main Function**: A main function demonstrating the usage of implemented functionalities.

```cpp
int main() {
    // ...
}
```

## Implemented Functionalities and Functions

### 1. **File Input and Initialization**

- **Function:**
  ```cpp
  StudentManageSys::StudentManageSys(std::ifstream& fin1, std::ifstream& fin2);
  ```
- **Description:**
  Reads data from two input files (`StudentCourse.txt` and `StudentInfo.txt`) to initialize the Student Management System. The data includes information about students' courses and personal details.

### 2. **Print Student Information**

- **Function:**
  ```cpp
  void StudentManageSys::Print(const std::string& id_);
  ```
- **Description:**
  Prints detailed information about a student identified by their student ID.

### 3. **Print All Student Information**

- **Function:**
  ```cpp
  void StudentManageSys::PrintAll();
  ```
- **Description:**
  Prints detailed information about all students in the system.

### 4. **Sort Students Based on Various Criteria**

- **Function:**
  ```cpp
  template<typename Compare>
  void StudentManageSys::Sort(Compare comp);
  ```
- **Description:**
  Sorts and prints students based on different criteria specified by the comparator function provided as a template argument. Criteria include sorting by ID, name, birthday, school year, individual course scores, and total scores.

### 5. **Find Students with Scores in a Given Range**

- **Function:**
  ```cpp
  void StudentManageSys::FindStuInfoInRange(const std::string& course, double minScore, double maxScore);
  ```
- **Description:**
  Searches for and prints students who achieved scores in a specified range for a particular course.

### 6. **Calculate Average Score for a Student**

- **Function:**
  ```cpp
  double StudentManageSys::AverageScore(const std::string& id_);
  ```
- **Description:**
  Calculates and returns the average score of a student across all courses.

### 7. **Query Students Based on Custom Conditions**

- **Functions:**
  ```cpp
  void StudentManageSys::FindStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond);
  void StudentManageSys::FindStuInfoByConditions2(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond, std::vector<std::string>& res);
  ```
- **Description:**
  - `FindStuInfoByConditions`: Searches for and prints students based on custom conditions specified by a boolean function pointer.
  - `FindStuInfoByConditions2`: Similar to the above, but additionally stores student IDs in a vector for further processing.

### 8. **Remove Students Based on Custom Conditions**

- **Function:**
  ```cpp
  void StudentManageSys::RemoveStuInfoByConditions(const std::function<bool(const std::pair<std::string, std::pair<StudentInfo, StudentCourse>>&)>& cond);
  ```
- **Description:**
  Removes students from the system based on custom conditions specified by a boolean function pointer.

### 9. **Testing Functionality**

- **Function:**
  ```cpp
  void StudentManageSys::Test(std::ofstream& file);
  ```
- **Description:**
  Executes a set of predefined tests and writes the results to an output file (`result.txt`). Test cases include finding students with specific criteria and checking if students meet credit requirements.

### 10. **Main Function for Demonstration**

- **Function:**
  ```cpp
  int main();
  ```
- **Description:**
  Demonstrates the usage of various functionalities, including initialization, testing, sorting, and querying, in the main function.

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

## Project Highlights

- **Data Storage:**
  - Utilizes `std::map` to store student information efficiently.
  - Uses `std::unordered_map` to store course information for quick access.

- **Flexible Sorting:**
  - Employs template-based sorting, allowing users to define custom comparison functions.
  - Supports sorting based on various criteria such as ID, name, scores, and total scores.

- **Dynamic Querying:**
  - Enables users to query students based on custom conditions using function pointers.

- **Comprehensive Testing:**
  - Includes a testing function to demonstrate the system's capabilities with predefined scenarios.

Feel free to modify and adapt the program to suit your needs.

Contact with me if you have any questions.😎
