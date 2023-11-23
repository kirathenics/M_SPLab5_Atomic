#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

int main()
{
    setlocale(0, "");

    atomic<float> resultValue = 0.0;
    float addValue = 0.0;
    cout << "Введите начальное значение: ";
    cin >> addValue;
    resultValue.store(addValue);

    thread additionThread([&]() {
        cout << "Введите прибавлямое значение: ";
        cin >> addValue;
        resultValue.store(resultValue.load() + addValue);
        cout << "Результат сложения: " << resultValue << endl;
        });

    thread multiplicationThread([&]() {
        cout << "Введите множитель: ";
        cin >> addValue;
        resultValue.store(resultValue.load() * addValue);
        cout << "Результат умножения: " << resultValue << endl;
        });

    thread divisionThread([&]() {
        cout << "Введите делитель: ";
        cin >> addValue;
        if (fabs(addValue - 0.0) < FLT_EPSILON)
        {
            cout << "Деление на 0 невозможно!" << endl;
            return;
        }
        resultValue.store(resultValue.load() / addValue);
        cout << "Результат деления: " << resultValue << endl;
        });

    additionThread.join();
    multiplicationThread.join();
    divisionThread.join();

    cout << "Результат вычислений: " << resultValue.load() << endl;

    return 0;
}