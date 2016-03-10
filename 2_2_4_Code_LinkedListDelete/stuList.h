#ifndef INC_2_2_4_LINKEDLISTDELETE_STULIST_H
#define INC_2_2_4_LINKEDLISTDELETE_STULIST_H

struct stu;
struct IntegerLinkedList;

stu *createList();

void freeStuList(stu *list);
void freeIntegerLinkList(IntegerLinkedList *list);

stu *deleteList(stu *list, const char *field, const char value);
stu *deleteList(stu *list, const char *field, const int value);
stu *deleteList(stu *list, const char *field, const char *value);

stu *deleteList(stu *list, int depth);
stu *deleteList(stu *list, IntegerLinkedList *depthList);

stu *findListByDepth(stu* list, int depth);
stu *findListByDepth(stu *list, IntegerLinkedList *depthList);

IntegerLinkedList *selectListForDepth(stu *list, const char *field, const char value);
IntegerLinkedList *selectListForDepth(stu *list, const char *field, const int value);
IntegerLinkedList *selectListForDepth(stu *list, const char *field, const char *value);

stu *selectList(stu *list, const char *field, const char value);
stu *selectList(stu *list, const char *field, const int value);
stu *selectList(stu *list, const char *field, const char *value);

void display(stu *list, bool isHeader);
void displayByDepth(stu *list, int depth, bool isHeader);
void displayByDepth(stu *list, IntegerLinkedList *depthList, bool isHeader);
void displayNode(stu *node, bool isHeader);

stu *insertList(stu *list, const char *name, const char sex, const int no, const int age);
stu *insertList(stu *list, stu *node);

stu *combineList(stu *list1, stu *list2);

stu *copyNode(stu *node);

#endif //INC_2_2_4_LINKEDLISTDELETE_STULIST_H
