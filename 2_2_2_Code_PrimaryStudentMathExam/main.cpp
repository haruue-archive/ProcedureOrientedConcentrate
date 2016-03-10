#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

/**
 * 题目结构体
 */
struct Question {
    int num1;
    int num2;
    char op;
    int answer;
};

/**
 * 随机题目生成器
 * @param emptyQuestion 指向用于存储问题的结构体
 * @return 指向生成的随机问题的指针
 */
Question *randQuestion(Question *emptyQuestion) {
    emptyQuestion->answer = -1;
    emptyQuestion->num1 = rand() % 51;
    emptyQuestion->num2 = rand() % 51;
    while (emptyQuestion->answer < 0 || emptyQuestion->answer > 50) {
        emptyQuestion->op = (rand() % 2 == 0) ? '+' : '-';
        switch (emptyQuestion->op) {
            case '+':
                emptyQuestion->answer = emptyQuestion->num1 + emptyQuestion->num2;
                break;
            case '-':
                if (emptyQuestion->num1 < emptyQuestion->num2) {
                    emptyQuestion->num1 ^= emptyQuestion->num2;
                    emptyQuestion->num2 ^= emptyQuestion->num1;
                    emptyQuestion->num1 ^= emptyQuestion->num2;
                }
                emptyQuestion->answer = emptyQuestion->num1 - emptyQuestion->num2;
                break;
            default:
                continue;
        }
    }
    return emptyQuestion;
}

/**
 * 判断正误
 * @param question 问题
 * @param answer 孩子输入的答案
 * @return true正确  false错误
 */
bool condition(Question *question, int answer) {
    return question->answer == answer;
}

int main() {
    int grade = 0;
    for (int i = 0; i < 10; ++i) {
        Question *question = new Question();
        question = randQuestion(question);
        for (int j = 0; j < 3; ++j) {
            cout << question->num1 << " " << question->op << " " << question->num2 << " = ";
            int answer;
            cin >> answer;
            if (condition(question, answer)) {
                if (j == 0) grade += 10;
                if (j == 1) grade += 7;
                if (j == 2) grade += 5;
                break;
            } else {
                cout << "你错了，";
                if (j < 2) {
                    cout << "再试一次吧！" << endl;
                }
                if (j == 2) {
                    cout << "正确答案是: " << question->answer << endl;
                }
            }
        }
        delete question;
        cout << endl;
    }
    if (grade >= 90) {
        cout << "SMART" << endl;
    } else if (grade >= 80) {
        cout << "GOOD" << endl;
    } else if (grade >= 70) {
        cout << "OK";
    } else if (grade >= 60) {
        cout << "PASS" << endl;
    } else {
        cout << "TRY AGAIN" << endl;
    }
}