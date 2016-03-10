#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

//[添加模块][录入模块]0程序启动和1基本资料录入
char first_face(int mode);

//[显示模块]-1 学生成绩的显示，-2 查找时运用此模块对学生总成绩排序，大于 0 时显示特定链表深度的学生成绩
void in_storage(int mode);

//[删除模块]
void out_storage();

//[查找模块]
void select_ele();

//[保存模块]
void save();

//[退出模块]
int exit();

//数据存储结构
struct Student {
    int id;
    char *name = new char[20];
    long studentId;
    char *address = new char[100];
    int gradeAdvancedMathematics;
    int gradeEnglish;
    int gradeComputer;
    int gradeAll;
    Student *next = NULL;
};

//链表操作函数
Student *linkedListSortZA(Student *list);
Student *linkedListDelete(Student *list, int depth);
Student *linkedListAdd(Student *list, Student *newStudent);
Student *linkedListGet(Student *list, int depth);
int linkedListFind(Student *list, int studentId);
void linkedListFree(Student *list);

Student *studentLinkedList = NULL;
int savedFlag = 1;

int main() {
    int status = 1;
    while (status) {
        switch (first_face(0)) {
            case '1':
                first_face(1);
                break;
            case '2':
                in_storage(-1);
                break;
            case '3':
                select_ele();
                break;
            case '4':
                out_storage();
                break;
            case '5':
                in_storage(-2);
                break;
            case '6':
                save();
                break;
            case '7':
                status = exit();
                break;
            default:
                cout << "输入错误，请重试" << endl;
                break;
        }
        cout << endl;
    }
}

/**
 * [添加模块][录入模块]
 */
char first_face(int mode) {
    switch (mode) {
        case 0:
            cout << "1. 添加学生信息" << endl;
            cout << "2. 显示学生信息" << endl;
            cout << "3. 按学号查找" << endl;
            cout << "4. 删除学生信息" << endl;
            cout << "5. 按总分排序" << endl;
            cout << "6. 保存" << endl;
            cout << "7. 退出" << endl;
            cout << "请选择操作(1-7)" << endl;
            char choose;
            cin >> choose;
            return choose;
            break;
        case 1:
            while (true) {
                Student *newStudent = new Student();
                cout << "请依次输入学生的姓名, 学号, 地址, 高数, 英语, 计算机:" << endl;
                cin >> newStudent->name >>
                newStudent->studentId >>
                newStudent->address >>
                newStudent->gradeAdvancedMathematics >>
                newStudent->gradeEnglish >>
                newStudent->gradeComputer;
                newStudent->gradeAll = newStudent->gradeAdvancedMathematics + newStudent->gradeEnglish + newStudent->gradeComputer;
                studentLinkedList = linkedListAdd(studentLinkedList, newStudent);
                cout << "是否继续输入？(Y/N) ";
                char choose;
                cin >> choose;
                if (choose != 'Y' && choose != 'y') {
                    break;
                }
            }
            break;
        default:
            break;
    }
    return 0;
}

/**
 * 链表添加函数
 * @param list 链表头
 * @param newStudent 新的 Student 对象
 * @return 添加后的链表头
 */
Student *linkedListAdd(Student *list, Student *newStudent) {
    savedFlag = 0;
    Student *lastStudent;
    if (list == NULL) {
        list = newStudent;
        list->id = 0;
    } else {
        lastStudent = list;
        //move to the last student
        while(NULL != lastStudent->next) {
            lastStudent = lastStudent->next;
        }
        lastStudent->next = newStudent;
        lastStudent->next->id = lastStudent->id + 1;
    }
    return list;
}

/**
 * [显示模块]-1 学生成绩的显示，-2 查找时运用此模块对学生总成绩排序，大于 0 时显示特定链表深度的学生成绩
 */
void in_storage(int mode) {
    Student *currentStudent = studentLinkedList;
    switch (mode) {
        case -1:
            if (NULL == studentLinkedList) {
                cout << "无记录" << endl;
                return;
            }
            cout << "序号\t姓名\t学号\t地址\t高数\t英语\t计算机\t总分" << endl;
            while (NULL != currentStudent) {
                cout << currentStudent->id << "\t" <<
                        currentStudent->name << "\t" <<
                        currentStudent->studentId << "\t" <<
                        currentStudent->address << "\t" <<
                        currentStudent->gradeAdvancedMathematics << "\t" <<
                        currentStudent->gradeEnglish << "\t" <<
                        currentStudent->gradeComputer << "\t" <<
                        currentStudent->gradeAll << endl;
                currentStudent = currentStudent->next;
            }
            break;
        case -2:
            studentLinkedList = linkedListSortZA(studentLinkedList);
            in_storage(-1);
            break;
        default:
            if (mode >= 0) {
                currentStudent = linkedListGet(studentLinkedList, mode);
                cout << "序号\t姓名\t学号\t地址\t高数\t英语\t计算机\t总分" << endl;
                cout << currentStudent->id << "\t" <<
                currentStudent->name << "\t" <<
                currentStudent->studentId << "\t" <<
                currentStudent->address << "\t" <<
                currentStudent->gradeAdvancedMathematics << "\t" <<
                currentStudent->gradeEnglish << "\t" <<
                currentStudent->gradeComputer << "\t" <<
                currentStudent->gradeAll << endl;
            }
            break;
    }
}

/**
 * 链表降序排序
 * @param list 要排序的链表
 * @return 排序完成的链表
 */
Student *linkedListSortZA(Student *list) {
    savedFlag = 0;
    if (NULL == list) {
        return list;
    }
    if (NULL == list->next) {
        return list;
    }
    int sortFlag = 0;
    Student *head = list;
    while (!sortFlag) {
        sortFlag = 1;
        Student *previousStudent = NULL;
        Student *currentStudent = head;
        while (NULL != currentStudent->next) {
            Student* nextStudent = currentStudent->next;
            if (currentStudent->gradeAll < nextStudent->gradeAll) {
                sortFlag = 0;
                if (head == currentStudent) {
                    head = nextStudent;
                } else {
                    previousStudent->next = nextStudent;
                }
                currentStudent->next = nextStudent->next;
                nextStudent->next = currentStudent;
                previousStudent = nextStudent;
            } else {
                previousStudent = currentStudent;
                currentStudent = currentStudent->next;
            }
        }
    }
    return head;
}

/**
 * 链表查找函数
 * @param list 指定查询的链表
 * @param studentId 要查询的学号
 * @return 查询结果，在链表中的深度，头节点深度为 0，未找到则返回 -1
 */
int linkedListFind(Student *list, int studentId) {
    int depth = 0;
    Student *currentStudent = list;
    while (NULL != currentStudent) {
        if (currentStudent->studentId == studentId) {
            return depth;
        }
        currentStudent = currentStudent->next;
        depth++;
    }
    return -1;
}

/**
 * 链表元素删除函数
 * @param list 指定删除的链表
 * @param depth 指定删除的深度
 * @return 删除了指定元素的链表，如果没有指定的元素则不会有任何改变
 */
Student *linkedListDelete(Student *list, int depth) {
    savedFlag = 0;
    int currentDepth = 0;
    Student *head = list;
    Student *previousStudent = NULL;
    Student *currentStudent = list;
    while (currentDepth < depth && NULL != currentStudent) {
        previousStudent = currentStudent;
        currentStudent = currentStudent->next;
        currentDepth++;
    }
    if (NULL == currentStudent) {
        return list;
    }
    if (currentStudent == head || NULL == previousStudent) {
        head = currentStudent->next;
    } else {
        previousStudent->next = currentStudent->next;
    }
    delete currentStudent->name;
    delete currentStudent->address;
    delete currentStudent;
    return head;
}

/**
 * 获取链表中指定深度的元素
 * @param list 指定的链表
 * @param depth 指定的深度
 * @return 指向该元素的指针
 */
Student *linkedListGet(Student *list, int depth) {
    Student *currentStudent = list;
    for (int i = 0; i < depth; i++) {
        currentStudent = currentStudent->next;
    }
    return currentStudent;
}

/**
 * 释放链表函数
 * @param list 需要释放内存资源的链表根节点
 */
void linkedListFree(Student *list) {
    while (list != NULL) {
        Student *next = list->next;
        delete list->name;
        delete list->address;
        delete list;
        list = next;
    }
}

/**
 * [查找模块]
 */
void select_ele() {
    cout << "请输入您要查找的学号: ";
    int studentIdToFind = 0;
    cin >> studentIdToFind;
    int depth = linkedListFind(studentLinkedList, studentIdToFind);
    if (depth < 0) {
        cout << "未找到此学号的学生" << endl;
        return;
    }
    in_storage(depth);
}

/**
 * [删除模块]
 */
void out_storage() {
    cout << "请输入您要删除的学号: ";
    int studentIdToDelete = 0;
    cin >> studentIdToDelete;
    int depth = linkedListFind(studentLinkedList, studentIdToDelete);
    if (depth < 0) {
        cout << "未找到此学号的学生" << endl;
        return;
    }
    in_storage(depth);
    cout << "确定要删除该学生的记录吗？(Y/N) ";
    char choose;
    cin >> choose;
    switch (choose) {
        case 'Y':
        case 'y':
            studentLinkedList = linkedListDelete(studentLinkedList, depth);
            break;
        default:
            cout << "操作已取消" << endl;
    }
}

/**
 * 保存模块
 */
void save() {
    cout << "请输入文件名: ";
    char *filename = new char[100];
    cin >> filename;
    cout << "将使用 " << filename << " 作为文件名，如果此文件存在，那么它将会被覆盖，是否确定？(Y/N)";
    char choose;
    cin >> choose;
    if (choose != 'Y' && choose != 'y') {
        cout << "操作已取消" << endl;
    }
    fstream f(filename, ios::out);
    if (NULL == studentLinkedList) {
        cout << "无记录，文件写入为空" << endl;
        return;
    }
    Student *currentStudent = studentLinkedList;
    f << "序号\t姓名\t学号\t地址\t高数\t英语\t计算机\t总分" << endl;
    while (NULL != currentStudent) {
        f << currentStudent->id << "\t" <<
        currentStudent->name << "\t" <<
        currentStudent->studentId << "\t" <<
        currentStudent->address << "\t" <<
        currentStudent->gradeAdvancedMathematics << "\t" <<
        currentStudent->gradeEnglish << "\t" <<
        currentStudent->gradeComputer << "\t" <<
        currentStudent->gradeAll << endl;
        currentStudent = currentStudent->next;
    }
    f.close();
    cout << "文件写入完成！" << endl;
    savedFlag = 1;
    delete filename;
}

/**
 * [退出模块]
 * @return 0确实要退出 1不要退出
 */
int exit() {
    if (!savedFlag) {
        cout << "您作出的更改还未保存，是否退出？(Y/N) ";
        char choose;
        cin >> choose;
        if (choose != 'Y' && choose != 'y') {
            cout << "操作已取消";
            return 1;
        }
    }
    linkedListFree(studentLinkedList);
    return 0;
}