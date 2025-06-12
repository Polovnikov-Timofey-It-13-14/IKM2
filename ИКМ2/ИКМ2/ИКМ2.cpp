#include "Header.h"

int main() {
    setlocale(LC_ALL, "ru");
    //Инициализация объектов
    Tree tree;
    Veify verify;
    string input = "input.txt";
    string output = "output.txt";
    cout << "Исходный файл: " << input << endl;

    //Чтение и построение дерева
    tree.ReadFile(input);

    //Подготовка данных о письмах
    ifstream file(input);

    string count;
    file >> count;
    if (!verify.Number(count)) {
        cout << "Ошибка. На ввод поступило что-то не то";
        exit(0);
    }
    int Count = stoi(count);

    vector<int> Letters(Count);
    for (int i = 0; i < Count; i++) {
        string Neighbour, Letter;
        file >> Neighbour;
        if (!verify.Number(Neighbour)) {
            cin.ignore();
            cout << "Ошибка. На ввод поступило что-то не то";
            exit(0);
        }
        int Neighbours = stoi(Neighbour);

        file >> Letter;
        if (!verify.Number(Letter)) {
            cin.ignore();
            cout << "Ошибка. На ввод поступило что-то не то";
            exit(0);
        }
        Letters[i] = stoi(Letter);

        for (int j = 0; j < Neighbours; j++) {
            string neighbours;
            file >> neighbours;
            if (!verify.Number(neighbours)) {
                cin.ignore();
                cout << "Ошибка. На ввод поступило что-то не то";
                exit(0);
            }
        }
    }
    file.close();

    //Доставка писем и подсчет извинений
    int Apologies = tree.Deliver(Letters);

    //Вывод результатов
    tree.PrintInFile(Apologies, output);

    //Дополнительный вывод в консоль
    cout << "Общее количество извинений: " << Apologies << endl;
    cout << "Результат записан в файл: " << output;
    exit(0);
}
