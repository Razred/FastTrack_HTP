#include <iostream>
#include <string>
#include <map>
#include <mutex>
#include <memory>
#include <cassert>

struct Student {
    int id_;
    std::string name_;
    int age_;
};

class StudentDatabase {
public:
    void addStudent(int id, const std::string& name, int age) {
        if (students_.find(id) != students_.end())
            throw std::logic_error("This ID already exists: " + id);
        std::lock_guard<std::mutex> lock(mtx_);
        auto student = std::make_shared<Student>(Student{id, name, age});
        students_[id] = student;
    }

    void removeStudent(int id) {
        if (students_.find(id) == students_.end())
            throw std::logic_error("This ID does not exist: " + id);
        std::lock_guard<std::mutex> lock(mtx_);
        students_.erase(id);
    }

    std::shared_ptr<Student> getStudent(int id) {
        auto it = students_.find(id);
        if (it != students_.end()) {
            return it->second;
        }
        return nullptr;
    }

private:
    std::map<int, std::shared_ptr<Student>> students_;
    std::mutex mtx_;
};

void TEST() {
    StudentDatabase db;

    db.addStudent(0, "Nikita", 20);
    db.addStudent(1, "Navid", 35);
    db.addStudent(2, "Ivan", 22);

    try {
        db.addStudent(0, "Check", 12);
    } catch (...) {
        std::cout << "Error" << std::endl;
    }

    assert(db.getStudent(0)->name_ == "Nikita");
    db.removeStudent(0);
    assert(db.getStudent(0) == nullptr);
}

int main() {
    TEST();
    return 0;
}