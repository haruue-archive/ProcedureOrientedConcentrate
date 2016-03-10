#include <cstring>
#include <iostream>
#include "stuList.h"

using namespace std;

/**
 * stu 学生链表
 * 来源于题目要求
 * 请使用 freeStuList() 来释放整个链表所占的内存空间
 * @see freeStuList()
 */
struct stu {
    char name[20] = {'\0'};
    char sex = 0;
    int no = 0;
    int age = 0;
    struct stu *next = NULL;
};

/**
 * 整数链表
 * 主要用于实现存储深度的链表
 * 请使用 freeIntegerLinkList() 来释放整个链表所占据的存储空间
 * @see freeIntegerLinkList()
 */
struct IntegerLinkedList {
    int value = 0;
    IntegerLinkedList *next = NULL;
};

/**
 * 创建一个空的学生链表
 * CREATE TABLE `stu`;
 * 请用 freeStuList() 函数来释放 stu 链表
 * @return 指向创建的学生链表的指针
 * @deprecated 直接用 insertList(NULL, ...) 插入一个值，链表会自动建立
 * @see freeStuList()
 */
stu *createList() {
    return new stu();
}

/**
 * 删除整个学生链表并释放其占用的内存空间
 * DROP TABLE `list`;
 * @param list 指向需要删除的链表的指针
 */
void freeStuList(stu *list) {
    stu *currentStudent = list;
    while (NULL != currentStudent) {
        stu *tmp = currentStudent;
        currentStudent = currentStudent->next;
        delete tmp;
    }
    list = NULL;
}

/**
 * 删除整个整数链表并释放其占用的内存空间
 * DROP TABLE `list`;
 * @param 指向需要删除的链表的指针
 */
void freeIntegerLinkList(IntegerLinkedList *list) {
    IntegerLinkedList *currentInteger = list;
    while (NULL != currentInteger) {
        IntegerLinkedList *tmp = currentInteger;
        currentInteger = currentInteger->next;
        delete tmp;
    }
    list = NULL;
}

/**
 * 删除链表中所有满足条件的学生
 * DELETE FROM `list` WHERE `field` = value;
 * 进行此重载的原因是本次实验限制使用面向过程程序设计，函数模板可能被禁用
 * @param list 需要进行操作的链表
 * @param field 针对的成员属性名称，可以是 "name", "sex", "no", "age"
 * @param value 针对的成员属性值
 * @return 操作完成的链表，如果找不到对应学生则不发生改变
 */
stu *deleteList(stu *list, const char *field, const char value) {
    if (strcmp(field, "sex") == 0) {
        IntegerLinkedList *depthListToDelete = selectListForDepth(list, field, value);
        list = deleteList(list, depthListToDelete);
        if (NULL != depthListToDelete) {
            freeIntegerLinkList(depthListToDelete);
        }
    }
    return list;
}

stu *deleteList(stu *list, const char *field, const int value) {
    if (strcmp(field, "no") == 0) {
        IntegerLinkedList *depthListToDelete = selectListForDepth(list, field, value);
        list = deleteList(list, depthListToDelete);
        if (NULL != depthListToDelete) {
            freeIntegerLinkList(depthListToDelete);
        }
    } else if (strcmp(field, "age") == 0) {
        IntegerLinkedList *depthListToDelete = selectListForDepth(list, field, value);
        list = deleteList(list, depthListToDelete);
        if (NULL != depthListToDelete) {
            freeIntegerLinkList(depthListToDelete);
        }
    }
    return list;
}

stu *deleteList(stu *list, const char *field, const char *value) {
    if (strcmp(field, "name") == 0) {
        IntegerLinkedList *depthListToDelete = selectListForDepth(list, field, value);
        list = deleteList(list, depthListToDelete);
        if (NULL != depthListToDelete) {
            freeIntegerLinkList(depthListToDelete);
        }
    }
    return list;
}

/**
 * 删除链表中指定深度的数据
 * DELETE FROM `list` WHERE `depth` = depth;
 * @param list 需要进行操作的链表
 * @param depth 指定的深度
 * @return 返回操作完成的结果链表，越界则不会发生任何变化
 */
stu *deleteList(stu *list, int depth) {
    stu *head = list;
    stu *previousStudent = NULL;
    stu *currentStudent = list;
    int currentDepth = 0;
    while (NULL != currentStudent) {
        if (currentDepth == depth) {
            if (NULL == previousStudent) {
                head = currentStudent->next;
            } else {
                previousStudent->next = currentStudent->next;
            }
            delete currentStudent;
            break;
        }
        previousStudent = currentStudent;
        currentStudent = currentStudent->next;
        currentDepth++;
    }
    return head;
}

/**
 * 删除链表中指定深度的数据
 * DELETE FROM `list` WHERE `depth` = depth;
 * @param list 需要进行操作的链表
 * @param depth 存储指定深度的链表，假设删除过程中深度不发生改变
 * @return 返回操作完成的结果链表，越界则不会发生任何变化
 */
stu *deleteList(stu *list, IntegerLinkedList *depthList) {
    IntegerLinkedList *currentDepth = depthList;
    //realDepthList 用来存储“真正操作时需要删除的深度”，由于进行删除操作时深度会改变，因此必须把传入的，假设深度不改变时的 depthList 转换过来，除了这种转换的方法，还可以对 depthList 进行由大到小排序并除重，也可以达到目的 -- Haruue Icymoon <haruue@caoyue.com.cn> Mar 10,2016 2:10
    IntegerLinkedList *realDepthList = NULL;
    IntegerLinkedList *currentRealDepthList = NULL;
    int i = 0;
    while (NULL != currentDepth) {
        int j = 0;
        int lessCount = 0;
        IntegerLinkedList *currentDepth2 = depthList;
        while (j < i) {
            if (currentDepth2->value < currentDepth->value) {
                lessCount++;
            } else if (currentDepth2->value == currentDepth->value) {
                //此处使用 goto 是为了 continue 外层循环，如果发现 depthList 中有重复的值，则不把它加入到 realDepthList 中，但是 C++ 不支持 continue 指定循环，所以我暂时没有想出其他方法 -- Haruue Icymoon <haruue@caoyue.com.cn> Mar 10,2016 2:05
                goto continue2;
            }
            currentDepth2 = currentDepth2->next;
            j++;
        }
        if (realDepthList == NULL) {
            realDepthList = new IntegerLinkedList();
            currentRealDepthList = realDepthList;
        } else {
            currentRealDepthList->next = new IntegerLinkedList();
            currentRealDepthList = currentRealDepthList->next;
        }
        currentRealDepthList->value = currentDepth->value - lessCount;
        continue2:
        currentDepth = currentDepth->next;
        i++;
    }
    currentDepth = realDepthList;
    while (NULL != currentDepth) {
        list = deleteList(list, currentDepth->value);
        currentDepth = currentDepth->next;
    }
    if (NULL != realDepthList) {
        freeIntegerLinkList(realDepthList);
    }
    return list;
}

/**
 * 获得链表中指定深度的数据
 * SELECT * FROM `list` WHERE `depth` = depth;
 * @param list 需要查询的链表
 * @param depth 指定的深度
 * @return 获取的值，失败返回 NULL
 */
stu *findListByDepth(stu *list, int depth) {
    stu *currentStudent = list;
    int currentDepth = 0;
    while (NULL != currentStudent) {
        if (currentDepth == depth) {
            return currentStudent;
        }
        currentStudent = currentStudent->next;
        currentDepth++;
    }
    return NULL;
}

/**
 * 获得链表中指定深度的值
 * SELECT * FROM `list` WHERE `depth` = depth;
 * @param list 需要查询的链表
 * @param depthList 存储指定深度的整数链表
 * @return 只包含有结果的链表，注意里面的节点和原列表内的节点是不同的，需要单独进行释放
 */
stu *findListByDepth(stu *list, IntegerLinkedList *depthList) {
    stu *resultList = NULL;
    IntegerLinkedList *currentDepth = depthList;
    while (NULL != currentDepth) {
        resultList = combineList(resultList, copyNode(findListByDepth(list, currentDepth->value)));
        currentDepth = currentDepth->next;
    }
    return resultList;
}

/**
 * 寻找链表中所有符合条件的值的深度
 * SELECT `depth` FROM `list` WHERE `field` = value;
 * 进行此重载的原因是本次实验限制使用面向过程程序设计，函数模板可能被禁用
 * 请使用 freeIntegerLinkedList() 来释放返回的整形链表
 * @param list 需要进行操作的链表
 * @param field 针对的成员属性名称，可以是 "name", "sex", "no", "age"
 * @param value 针对的成员属性值
 * @return 一个存储所有符合要求深度的值的链表，如果没有找到则返回 NULL
 * @see freeIntegerLinkList()
 */
IntegerLinkedList *selectListForDepth(stu *list, const char *field, const char value) {
    stu *currentStudent = list;
    IntegerLinkedList *resultList = NULL;
    IntegerLinkedList *currentResult = NULL;
    int currentDepth = 0;
    if (strcmp(field, "sex") == 0) {
        while (NULL != currentStudent) {
            if (currentStudent->sex == value) {
                if (NULL == resultList) {
                    resultList = new IntegerLinkedList();
                    resultList->value = currentDepth;
                    currentResult = resultList;
                } else {
                    currentResult->next = new IntegerLinkedList();
                    currentResult = currentResult->next;
                    currentResult->value = currentDepth;
                }
            }
            currentDepth++;
            currentStudent = currentStudent->next;
        }
    }
    return resultList;
}

IntegerLinkedList *selectListForDepth(stu *list, const char *field, const int value) {
    stu *currentStudent = list;
    IntegerLinkedList *resultList = NULL;
    IntegerLinkedList *currentResult = NULL;
    int currentDepth = 0;
    if (strcmp(field, "no") == 0) {
        while (NULL != currentStudent) {
            if (currentStudent->no == value) {
                if (NULL == resultList) {
                    resultList = new IntegerLinkedList();
                    resultList->value = currentDepth;
                    currentResult = resultList;
                } else {
                    currentResult->next = new IntegerLinkedList();
                    currentResult = currentResult->next;
                    currentResult->value = currentDepth;
                }
            }
            currentDepth++;
            currentStudent = currentStudent->next;
        }
    } else if (strcmp(field, "age") == 0) {
        while (NULL != currentStudent) {
            if (currentStudent->age == value) {
                if (NULL == resultList) {
                    resultList = new IntegerLinkedList();
                    resultList->value = currentDepth;
                    currentResult = resultList;
                } else {
                    currentResult->next = new IntegerLinkedList();
                    currentResult = currentResult->next;
                    currentResult->value = currentDepth;
                }
            }
            currentDepth++;
            currentStudent = currentStudent->next;
        }
    }
    return resultList;
}

IntegerLinkedList *selectListForDepth(stu *list, const char *field, const char *value) {
    stu *currentStudent = list;
    IntegerLinkedList *resultList = NULL;
    IntegerLinkedList *currentResult = NULL;
    int currentDepth = 0;
    if (strcmp(field, "name") == 0) {
        while (NULL != currentStudent) {
            if (strcmp(currentStudent->name, value) == 0) {
                if (NULL == resultList) {
                    resultList = new IntegerLinkedList();
                    resultList->value = currentDepth;
                    currentResult = resultList;
                } else {
                    currentResult->next = new IntegerLinkedList();
                    currentResult = currentResult->next;
                    currentResult->value = currentDepth;
                }
            }
            currentDepth++;
            currentStudent = currentStudent->next;
        }
    }
    return resultList;
}

/**
 * 寻找链表中所有符合条件的值
 * SELECT * FROM `list` WHERE `field` = value;
 * 进行此重载的原因是本次实验限制使用面向过程程序设计，函数模板可能被禁用
 * @param list 需要进行操作的链表
 * @param field 针对的成员属性名称，可以是 "name", "sex", "no", "age"
 * @param value 针对的成员属性值
 * @return 一个存储所有符合要求的值的链表，如果没有找到则返回 NULL，注意里面的节点和原列表内的节点是不同的，需要单独进行释放
 */
stu *selectList(stu *list, const char *field, const char value) {
    IntegerLinkedList *depthList = selectListForDepth(list, field, value);
    stu *resultList = findListByDepth(list, depthList);
    if (depthList != NULL) {
        freeIntegerLinkList(depthList);
    }
    return resultList;
}

stu *selectList(stu *list, const char *field, const int value) {
    IntegerLinkedList *depthList = selectListForDepth(list, field, value);
    stu *resultList = findListByDepth(list, depthList);
    if (depthList != NULL) {
        freeIntegerLinkList(depthList);
    }
    return resultList;
}

stu *selectList(stu *list, const char *field, const char *value) {
    IntegerLinkedList *depthList = selectListForDepth(list, field, value);
    stu *resultList = findListByDepth(list, depthList);
    if (depthList != NULL) {
        freeIntegerLinkList(depthList);
    }
    return resultList;
}


/**
 * 查看记录，遍历输出整个链表数据
 * @param list 需要输出的链表
 * @param isHeader 是否输出表头
 */
void display(stu *list, bool isHeader) {
    stu *currentStudent = list;
    if (isHeader) {
        cout << "姓名\t性别\t学号\t年龄" << endl;
    }
    while (currentStudent != NULL) {
        cout << currentStudent->name << "\t" << currentStudent->sex << "\t" << currentStudent->no << "\t" << currentStudent->age << endl;
        currentStudent = currentStudent->next;
    }
}

/**
 * 查看指定深度的记录
 * @param list 需要输出的链表
 * @param depth 指定的深度
 * @param isHeader 是否输出表头
 */
void displayByDepth(stu *list, int depth, bool isHeader) {
    if (isHeader) {
        cout << "姓名\t性别\t学号\t年龄" << endl;
    }
    displayNode(findListByDepth(list, depth), false);
}

/**
 * 查看指定深度的记录
 * @param list 需要输出的链表
 * @param depthList 存储指定深度的链表
 * @param isHeader 是否输出表头
 */
void displayByDepth(stu *list, IntegerLinkedList *depthList, bool isHeader) {
    if (isHeader) {
        cout << "姓名\t性别\t学号\t年龄" << endl;
    }
    IntegerLinkedList *currentDepth = depthList;
    while (NULL != currentDepth) {
        displayByDepth(list, currentDepth->value, false);
        currentDepth = currentDepth->next;
    }
}

/**
 * 查看节点
 * @param node 需要输出的节点
 * @param isHeader 是否输出表头
 */
void displayNode(stu *node, bool isHeader) {
    if (isHeader) {
        cout << "姓名\t性别\t学号\t年龄" << endl;
    }
    if (node != NULL) {
        cout << node->name << "\t" << node-> sex << "\t" << node->no << "\t" << node->age << endl;
    }
}

/**
 * 在链表尾插入新数据
 * INSERT INTO `list` (`name`, `sex`, `no`, `age`) VALUES (name, sex, no, age);
 * @param list 需要进行操作的链表
 * @param name 姓名
 * @param sex 性别
 * @param no 学号
 * @param age 年龄
 * @return 操作完成的链表
 */
stu *insertList(stu *list, const char *name, const char sex, const int no, const int age) {
    stu *newNode = new stu();
    strcpy(newNode->name, name);
    newNode->sex = sex;
    newNode->no = no;
    newNode->age = age;
    newNode->next = NULL;
    list = insertList(list, newNode);
    return list;
}

/**
 * 在链表尾插入新数据，只插入一个节点
 * INSERT INTO `list1` (`name`, `sex`, `no`, `age`) SELECT `name`, `sex`, `no`, `age` FROM `node`
 * 与 combineList 不同的是，此方法将会把 node 复制之后再插入到 list 里，并将复制之后的 node->next 设置为 NULL ，因此只会插入一个节点
 * @param list 需要操作的链表
 * @param node 要插入的节点
 * @return 插入完成后的链表
 */
stu *insertList(stu *list, stu *node) {
    stu *currentStudent = list;
    stu *newNode = new stu();
    strcpy(newNode->name, node->name);
    newNode->sex = node->sex;
    newNode->no = node->no;
    newNode->age = node->age;
    newNode->next = NULL;
    if (list == NULL) {
        list = newNode;
    } else {
        while (NULL != currentStudent->next) {
            currentStudent = currentStudent->next;
        }
        currentStudent->next = newNode;
    }
    return list;
}

/**
 * 合并两张表
 * INSERT INTO `list1` (`name`, `sex`, `no`, `age`) SELECT `name`, `sex`, `no`, `age` FROM `list2`
 * 将 list2 接到 list1 后面
 * @param list1 前链表
 * @param list2 后链表
 * @return 合并完成的链表
 */
stu *combineList(stu *list1, stu *list2) {
    stu *currentStudent = list1;
    if (currentStudent == NULL) {
        list1 = list2;
    } else {
        while (NULL != currentStudent->next) {
            currentStudent = currentStudent->next;
        }
        currentStudent->next = list2;
    }
    return list1;
}

/**
 * 复制一个节点
 * 只复制一个节点，指向下一个节点的 next 会被赋值成 NULL
 * @param node 被复制的节点
 * @result 复制节点
 */
stu *copyNode(stu *node) {
    stu *newNode = new stu();
    strcpy(newNode->name, node->name);
    newNode->sex = node->sex;
    newNode->no = node->no;
    newNode->age = node->age;
    newNode->next = NULL;
    return newNode;
}