#include <ctime>
#include <iostream>
#include <set>
#include <string>
#include <vector>
#include <windows.h>
using namespace std;

// ANSI Цвета
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string CYAN = "\033[36m";
const string RESET = "\033[0m";

// Генерація секретних номерів
vector<int> generateSecret() {
    vector<int> secret(4);
    for (int i = 0; i < 4; i++) {
        int d;
        bool ok;
        do {
            d = rand() % 10;
            ok = true;
            for (int j = 0; j < i; j++)
                if (secret[j] == d)
                    ok = false;
        } while (!ok);
        secret[i] = d;
    }
    return secret;
}

// Підрахунок биків та корів
pair<int, int> getBullsCows(const vector<int>& secret, const string& guess) {
    int bulls = 0, cows = 0;
    for (int i = 0; i < 4; i++) {
        int g = guess[i] - '0';
        if (secret[i] == g)
            bulls++;
        else {
            for (int j = 0; j < 4; j++)
                if (secret[j] == g)
                    cows++;
        }
    }
    return { bulls, cows };
}

int main() {
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    srand((unsigned int)time(nullptr));

    cout << BLUE << "=Гра=Бики=та=Корови=\n" << RESET;
    cout << "Комп'ютер загадав 4 унікальні цифри.\n\n";

    vector<int> secret = generateSecret();

    while (true) {
        string guess;
        cout << CYAN << "Ваш Варіант (4 цифри): " << RESET;
        cin >> guess;

        if (guess.size() != 4) {
            cout << RED << "Помилка: введіть рівно 4 цифри!\n\n" << RESET;
            continue;
        }

        bool valid = true;
        for (char c : guess)
            if (!isdigit(c))
                valid = false;

        if (!valid) {
            cout << RED << "Помилка: тільки цифри!\n\n" << RESET;
            continue;
        }

        set<char> uniqueChars(guess.begin(), guess.end());
        if (uniqueChars.size() != 4) {
            cout << RED << "Помилка: цифри повинні бути унікальними!\n\n" << RESET;
            continue;
        }

        auto [bulls, cows] = getBullsCows(secret, guess);

        cout << "Результат: ";
        for (int i = 0; i < 4; i++) {
            int g = guess[i] - '0';
            if (secret[i] == g) {
                cout << GREEN << g << RESET;
            }
            else {
                bool found = false;
                for (int j = 0; j < 4; j++)
                    if (secret[j] == g)
                        found = true;
                if (found)
                    cout << YELLOW << g << RESET;
                else
                    cout << RED << g << RESET;
            }
        }

        cout << "\n";
        cout << GREEN << "Бики: " << bulls << RESET << " | "
            << YELLOW << "Корови: " << cows << RESET << "\n\n";

        if (bulls == 4) {
            cout << GREEN << "Вітаємо! Ви вгадали число!\n" << RESET;
            break;
        }
    }

    cout << BLUE << "\nСекретне число було: " << RESET;
    for (int d : secret)
        cout << d;
    cout << "\n";

    return 0;
}