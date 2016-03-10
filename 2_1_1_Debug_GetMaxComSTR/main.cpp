#include <iostream>
#include <cstring>

using namespace std;

int GetMaxComSTR(const char *s, const char *t, int *length);

int main() {
    char *str1 = "ABDEFGHY";
    char *str2 = "ADEGHY";
    int maxComLength = 0;
    int maxComIndex = GetMaxComSTR(str1, str2, &maxComLength);
    for (int i = 0; i < maxComLength; i++) {
        cout << str1[maxComIndex + i];
    }
    cout << endl;
}

/**
 * 寻找两个字符串的最大公共子串
 * @param s 第一个字符串
 * @param t 第二个字符串
 * @param length 用于存储最大公共字符串长度的变量
 * @return 公共子串在第一个字符串的存储位置
 */
int GetMaxComSTR(const char *s, const char *t, int *length) {
    int i, j, k;
    int tmp_len, condition;

    int index = 0;
    *length = -1;
    i = 0;

    while (i < strlen(s)) {
        j = 0;
        while (j < strlen(t)) {
            if (s[i] == t[j]) {
                k = 0;
                tmp_len = 0;
                condition = 1;

                while (condition == 1) {
                    if (i + k < strlen(s) && j + k < strlen(t) && s[i + k] == t[j + k]) { //[1]
                        tmp_len++;
                        k++;
                    } else {
                        condition = 0; //[2]
                    }
                }

                if (tmp_len >= *length) { //[3]
                    index = i;
                    *length = tmp_len;
                }
            }
            j++; //[4]
        }
        i++; //[5]
    }

    return index;
}