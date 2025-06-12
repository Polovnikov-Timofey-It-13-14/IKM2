#include "Header.h"

//Чтение файла
void Tree::ReadFile(string Filename) {                  //Обрабатываем файл
    fstream file(Filename);
    if (!file.is_open()) {
        throw "Ôàéë íå îòêðûëñÿ";
        exit(0);
    }


    vector<int> Letter;
    string a;
    Veify verify;
    getline(file, a);                                   //Считываем первое число файла (Количество строк или гнезд)
    if (!verify.Number(a)) {
        cin.ignore();
        cout << "Îøèáêà. Íà ââîä ïîñòóïèëî ÷òî-òî íå òî";
        exit(0);
    }

    int Count = stoi(a);

    for (int i = 0; i < Count; i++) {                   //Идем по всем строкам
        string b, c;
        file >> b;                                      //Считываем первое число каждой строки (Количество соседей у этого гнезда)
        if (!verify.Number(b)) {
            cout << "Îøèáêà. Íà ââîä ïîñòóïèëî ÷òî-òî íå òî";
            exit(0);
        }
        int NeighborCount = stoi(b);

        file >> c;                                      //Считываем второе число каждой строки (Количество писем в это гнездо)
        if (!verify.Number(c)) {
            cout << "Îøèáêà. Íà ââîä ïîñòóïèëî ÷òî-òî íå òî";
            exit(0);
        }
        int Letters = stoi(c);
        Letter.push_back(Letters);
        vector<int> Neighbors(NeighborCount);

        for (int j = 0; j < NeighborCount; j++) {
            string d;
            file >> d;                                  //Считываем всех соседей (Считали их количество как первое число в строке)
            if (!verify.Number(d)) {
                cout << "Îøèáêà. Íà ââîä ïîñòóïèëî ÷òî-òî íå òî";
                exit(0);
            }

            int Neighbor = stoi(d);
            Neighbors[j] = Neighbor;                    //Заносим в массив Neighbours
        }

        //Надо построить дерево:
        //1. Поставить вершину 1 как корень и добавить соседей, номера которых в массиве (Childrens), а также присвоить количество писем (Letters)
        //2. Сделать аналогично для 2 и последующих вершин

        if (i == 0) {
            root = new TreeNode(1);
            root->Letters = Letters;
        }

        TreeNode* NewNode = FindNode(i + 1, root);
        if (NewNode) {
            for (int a : Neighbors)
                AddNode(i + 1, a, 0);
            NewNode->Letters = Letters;
        }
    }
    file.close();
}

//Найти нужный узел (С нужным номером)
Tree::TreeNode* Tree::FindNode(int Number, TreeNode* node) {
    if (!Number)
        return nullptr;

    if (node->Number == Number)
        return node;

    for (TreeNode* child : node->Childrens) {
        TreeNode* Newnode = FindNode(Number, child);
        if (Newnode)
            return Newnode;
    }
    return nullptr;
}

//Добавить элемент в дерево
void Tree::AddNode(int Parent, int Children, int Letters) {
    TreeNode* parent = FindNode(Parent, root);

    if (!parent)
        return;

    for (TreeNode* Newnode : parent->Childrens)
        if (Newnode->Number == Children)
            return;

    TreeNode* NewNode = new TreeNode(Children, parent);
    NewNode->Letters = Letters;
    parent->Childrens.push_back(NewNode);
}

//Доставка почты и подсчет извинений
int Tree::Deliver(vector<int>& Letters) {
    int apologies = 0;
    for (int i = 0; i < Letters.size(); i++) {
        if (Letters[i] > 0) {
            TreeNode* node = FindNode(i + 1, root);

            if (node) {
                for (TreeNode* current = node; current != nullptr; current = current->Parent) {
                    if (current->Letters == 0 && !current->Visited) {
                        apologies++;
                        current->Visited = true;
                    }
                }
                node->Letters = 0;
                Letters[i] = 0;
            }
        }
    }
    return apologies;
}

//Вывод результата в файл
void Tree::PrintInFile(int k, string outputFile) {
    ofstream file(outputFile);

    file << k;
}

//Проверка на число
bool Veify::Number(string& x) {
    if (x.empty()) {
        throw "Ïóñòàÿ ñòðîêà íà ââîä";
        return false;
    }

    for (char c : x) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
