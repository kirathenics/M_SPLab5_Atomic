#include <iostream>
#include <thread>
#include <atomic>
using namespace std;

int main()
{
    setlocale(0, "");

    atomic<float> resultValue = 0.0;
    float addValue = 0.0;
    cout << "������� ��������� ��������: ";
    cin >> addValue;
    resultValue.store(addValue);

    thread additionThread([&]() {
        cout << "������� ����������� ��������: ";
        cin >> addValue;
        resultValue.store(resultValue.load() + addValue);
        cout << "��������� ��������: " << resultValue << endl;
        });

    thread multiplicationThread([&]() {
        cout << "������� ���������: ";
        cin >> addValue;
        resultValue.store(resultValue.load() * addValue);
        cout << "��������� ���������: " << resultValue << endl;
        });

    thread divisionThread([&]() {
        cout << "������� ��������: ";
        cin >> addValue;
        if (fabs(addValue - 0.0) < FLT_EPSILON)
        {
            cout << "������� �� 0 ����������!" << endl;
            return;
        }
        resultValue.store(resultValue.load() / addValue);
        cout << "��������� �������: " << resultValue << endl;
        });

    additionThread.join();
    multiplicationThread.join();
    divisionThread.join();

    cout << "��������� ����������: " << resultValue.load() << endl;

    return 0;
}