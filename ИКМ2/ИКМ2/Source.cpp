#include "Header.h"

//������ �����
void Tree::ReadFile(string Filename) {                  //������������ ����
    fstream file(Filename);
    if (!file.is_open()) {
        throw "���� �� ��������";
        exit(0);
    }


    vector<int> Letter;
    string a;
    Veify verify;
    getline(file, a);                                   //��������� ������ ����� ����� (���������� ����� ��� �����)
    if (!verify.Number(a)) {
        cin.ignore();
        cout << "������. �� ���� ��������� ���-�� �� ��";
        exit(0);
    }

    int Count = stoi(a);

    for (int i = 0; i < Count; i++) {                   //���� �� ���� �������
        string b, c;
        file >> b;                                      //��������� ������ ����� ������ ������ (���������� ������� � ����� ������)
        if (!verify.Number(b)) {
            cout << "������. �� ���� ��������� ���-�� �� ��";
            exit(0);
        }
        int NeighborCount = stoi(b);

        file >> c;                                      //��������� ������ ����� ������ ������ (���������� ����� � ��� ������)
        if (!verify.Number(c)) {
            cout << "������. �� ���� ��������� ���-�� �� ��";
            exit(0);
        }
        int Letters = stoi(c);
        Letter.push_back(Letters);
        vector<int> Neighbors(NeighborCount);

        for (int j = 0; j < NeighborCount; j++) {
            string d;
            file >> d;                                  //��������� ���� ������� (������� �� ���������� ��� ������ ����� � ������)
            if (!verify.Number(d)) {
                cout << "������. �� ���� ��������� ���-�� �� ��";
                exit(0);
            }

            int Neighbor = stoi(d);
            Neighbors[j] = Neighbor;                    //������� � ������ Neighbours
        }

        //���� ��������� ������:
        //1. ��������� ������� 1 ��� ������ � �������� �������, ������ ������� � ������� (Childrens), � ����� ��������� ���������� ����� (Letters)
        //2. ������� ���������� ��� 2 � ����������� ������

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

//����� ������ ���� (� ������ �������)
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

//�������� ������� � ������
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

//�������� ����� � ������� ���������
int Tree::Deliver(vector<int>& Letters) {
    int apologies = 0;
    for (int i = 0; i < Letters.size(); i++) {
        if (Letters[i] > 0) {
            TreeNode* node = FindNode(i + 1, root);

            if (node) {
                //���� ������� �� ����� �������� �� �����
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

//����� ���������� � ����
void Tree::PrintInFile(int k, string outputFile) {
    ofstream file(outputFile);

    file << k;
}

//�������� �� �����
bool Veify::Number(string& x) {
    if (x.empty()) {
        throw "������ ������ �� ����";
        return false;
    }

    for (char c : x) {
        if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}
