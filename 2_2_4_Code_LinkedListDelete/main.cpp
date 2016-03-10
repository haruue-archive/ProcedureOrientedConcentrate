#include <iostream>
#include <cstring>
#include "stuList.h"

using namespace std;

char getChoose();
char showMenuModule();
stu *insertModule(stu *list);
void showModule(stu *list);
void queryModule(stu *list);
stu *deleteModule(stu *list);
char *getField(char *field);

int main() {
    char choose = '\0';
    stu *studentLinkedList = NULL;
    while (choose != '5') {
        choose = showMenuModule();
        switch (choose) {
            case '1':
                studentLinkedList = insertModule(studentLinkedList);
                break;
            case '2':
                showModule(studentLinkedList);
                break;
            case '3':
                queryModule(studentLinkedList);
                break;
            case '4':
                studentLinkedList = deleteModule(studentLinkedList);
                break;
            case '5':
                break;
            default:
                cout << "输入错误，请重试！" << endl;
        }
    }
    if (NULL != studentLinkedList) {
        freeStuList(studentLinkedList);
    }
}

char showMenuModule() {
    cout << "1. 插入学生信息" << endl;
    cout << "2. 显示学生信息" << endl;
    cout << "3. 查询学生信息" << endl;
    cout << "4. 删除学生信息" << endl;
    cout << "5. 退出程序" << endl;
    cout << "请选择: ";
    return getChoose();
}

stu *insertModule(stu *list) {
    while (true) {
        cout << "请依次输入 姓名, 性别(M/F), 学号, 年龄: " << endl;
        char name[20] = {'\0'};
        char sex = 0;
        int no = 0;
        int age = 0;
        cin >> name >> sex >> no >> age;
        list = insertList(list, name, sex, no, age);
        cout << "是否继续添加？(Y/N)";
        char choose = getChoose();
        if (choose != 'Y' && choose != 'y') {
            break;
        }
    }
    return list;
}

char getChoose() {
    char choose;
    cin >> choose;
    return choose;
}

void showModule(stu *list) {
    if (list == NULL) {
        cout << "链表为空" << endl;
    } else {
        display(list, true);
    }
}

void queryModule(stu *list) {
    cout << "查询字段" << endl;
    char *field = new char[5];
    getField(field);
    stu *queryResult = NULL;
    if (strcmp(field, "name") == 0) {
        cout << "请输入一个字符串查询值: ";
        char name[20];
        cin >> name;
        queryResult = selectList(list, field, name);
    } else if (strcmp(field, "sex") == 0) {
        cout << "请输入一个字符查询值(M/F): ";
        char sex;
        cin >> sex;
        queryResult = selectList(list, field, sex);
    } else if (strcmp(field, "no") == 0 || strcmp(field, "age") == 0) {
        cout << "请输入一个整型查询值(M/F): ";
        int value;
        cin >> value;
        queryResult = selectList(list, field, value);
    }
    if (queryResult == NULL) {
        cout << "未找到符合条件的信息" << endl;
    } else {
        display(queryResult, true);
        freeStuList(queryResult);
    }
    delete field;
}

char *getField(char *field) {
    bool hasGetField = false;
    while (!hasGetField) {
        cout << "1. 姓名\t2. 性别\n3. 学号\t4. 年龄" << endl;
        cout << "请选择: ";
        switch (getChoose()) {
            case '1':
                hasGetField = true;
                strcpy(field, "name");
                break;
            case '2':
                hasGetField = true;
                strcpy(field, "sex");
                break;
            case '3':
                hasGetField = true;
                strcpy(field, "no");
                break;
            case '4':
                hasGetField = true;
                strcpy(field, "age");
                break;
            default:
                hasGetField = false;
                break;
        }
    }
    return field;
}

stu *deleteModule(stu *list) {
    cout << "查询字段" << endl;
    char *field = new char[5];
    getField(field);
    IntegerLinkedList *queryResultDepth = NULL;
    if (strcmp(field, "name") == 0) {
        cout << "请输入一个字符串查询值: ";
        char name[20];
        cin >> name;
        queryResultDepth = selectListForDepth(list, field, name);
    } else if (strcmp(field, "sex") == 0) {
        cout << "请输入一个字符查询值(M/F): ";
        char sex;
        cin >> sex;
        queryResultDepth = selectListForDepth(list, field, sex);
    } else if (strcmp(field, "no") == 0 || strcmp(field, "age") == 0) {
        cout << "请输入一个整型查询值(M/F): ";
        int value;
        cin >> value;
        queryResultDepth = selectListForDepth(list, field, value);
    }
    if (queryResultDepth == NULL) {
        cout << "未找到符合条件的信息" << endl;
    } else {
        displayByDepth(list, queryResultDepth, true);
        cout << "确定要删除它们吗？(Y/N) ";
        char choose = getChoose();
        if (choose == 'Y' || choose == 'y') {
            list = deleteList(list, queryResultDepth);
        }
        freeIntegerLinkList(queryResultDepth);
    }
    delete field;
    return list;
}