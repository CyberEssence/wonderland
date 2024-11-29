#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <cmath>
#include <sstream>
#include <climits>
#include <cstring>
#include <bitset>

using namespace std;

#define MAX 1024

// Функция для генерации случайной строки
string genRandomString(int length) {
    const string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, characters.size() - 1);
    
    string result(length, ' ');
    for (int i = 0; i < length; ++i) {
        result[i] = characters[dis(gen)];
    }
    return result;
}

// Функция для генерации хеша
string mutateAndHash(const string& input) {
    vector<char> shuffledInput(input.begin(), input.end());
    shuffle(shuffledInput.begin(), shuffledInput.end(), default_random_engine());
    
    string hashString;
    for (char c : shuffledInput) {
        if (isalnum(c)) {
            hashString += c;
        }
    }
    
    return hashString;
}

int power(int base, int a) {
       int production = 1;
       
       for (int i = 0; i < a; i++) {
              production *= base;
       }
       return production;
}

int root(int input, int n)
{
    return round(pow(input, 1./n));
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Функция для очистки строк от пробелов
string cleanFromSpaces(const string& input) {
    string result;
    bool prevSpace = false;
    
    for (char c : input) {
        if (!isspace(c)) {
            if (!prevSpace) {
                result += c;
            }
            prevSpace = false;
        } else {
            prevSpace = true;
        }
    }
    
    return result;
}

// Функция для генерации хеша из строки
string genHash(const string& input) {
    string cleanedInput = cleanFromSpaces(input);
    string randomString = genRandomString(24);
    string output = cleanedInput + randomString;
    return mutateAndHash(output);
}

// Функция для генерации случайного числа
int generateRandomNumber() {
    random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dis(10000, 99999);
    return dis(gen);
}

// Функция для преобразования строки в массив ASCII-кодов
std::vector<int> stringToASCIIArray(const std::string& str) {
    std::vector<int> asciiArray;
    for (char c : str) {
        asciiArray.push_back(static_cast<int>(c));
    }
    return asciiArray;
}

int concatenateArr(std::vector<int>& arr) {
    // Сначала преобразуем вектор в строку
    stringstream ss; 
    std::string str;
    int num;
    for (int num : arr) {
        str += std::to_string(num);
    }
    ss << str;
    ss >> num;

    //print to the consloe
    cout << num << endl;
    return num;
}

string xorStrings(const std::string& str1, const std::string& str2) {
    int len = std::max(str1.length(), str2.length());
    
    std::string result;
    result.reserve(len);

    for (int i = 0; i < len; ++i) {
        char c1 = (i < str1.length()) ? str1[i] : '0';
        char c2 = (i < str2.length()) ? str2[i] : '0';
        
        result += ((c1 - '0') ^ (c2 - '0')) + '0';
    }

    return result;
}

void printHashString(string hashedSentence) {
    cout << "Хеш: " << hashedSentence << endl;
}

void printAsciiStringOfHash(std::vector<int> asciiArray) {
    std::cout << "ASCII codes of the string: ";
    for (int code : asciiArray) {
        std::cout << code << " ";
    }
    std::cout << std::endl;
}

vector<int> pushBackAndReverse(int temp, vector<int> digits) {
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }
    
    reverse(digits.begin(), digits.end());
    
    return digits;
}

string convertIntsToChars(string result, vector<int> digits) {
    for (int digit : digits) {
        result += char(digit + 97); // Преобразование чисел в символы
    }
    return result;
}

void printResult(string result) {
    cout << "Результат: " << result << endl;
}

void printCharactersSize(string characters) {
    cout << characters.size() << endl;
}

int main() {
    int p;
    int g;
    int x;
    int num;
    int superTetrationResult;
    
    unsigned dataArraySize;

    vector<int> digits;
    
    string sentence;
    cout << "Введите строку: ";
    cin >> sentence; 
    
    cout << "Введите p: ";
    cin >> p;
    
    cout << "Введите g: ";
    cin >> g;
    
    superTetrationResult = power(p, power(x, g));
    
    string hashedSentence = genHash(sentence);
    
    std::vector<int> asciiArray = stringToASCIIArray(hashedSentence);
    
    dataArraySize = sizeof(asciiArray) / sizeof(int);
    
    num = concatenateArr(asciiArray);
    
    pushBackAndReverse(superTetrationResult, digits);
    
    string result;
    convertIntsToChars(result, digits);
    
    string array = mutateAndHash(result);
    
    string characters = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; 
    
    string chars = mutateAndHash(characters).substr(0, array.length());
    
    string new_chars;
    
    string new_string;
    
    string new_second_string;
    
    for (int i = 0; i <= characters.size(); i++) {
        new_chars += mutateAndHash(array + characters);
        new_string = mutateAndHash(new_chars);
    }
    
    for (int j = 0; j <= new_string.size() / characters.size(); j++) {
        new_second_string += characters;
    }
    
    string new_third_string = mutateAndHash(new_second_string.substr(0, new_string.length()));
    
    std::string res = xorStrings(new_third_string, new_second_string);
    cout << mutateAndHash(res) << endl;
    
    return 0;
}

