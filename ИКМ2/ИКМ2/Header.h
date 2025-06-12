#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Tree {
private:
    struct TreeNode {
        int Number;                         //Номер гнезда
        vector<TreeNode*> Childrens;        //"Прямые" потомки этого гнезда
        TreeNode* Parent;                   //Родитель
        int Letters;                        //Количество писем в гнезде
        bool Visited;                       //Флаг (Посещано ли гнездо)

        TreeNode(int num, TreeNode* parent = nullptr) : Number(num), Parent(parent), Letters(0), Visited(false) {}
    };

    TreeNode* root;

public:
    void ReadFile(string Filename);                                 //Чтение файла
    void AddNode(int Parent, int Children, int Letters);            //Добавить элемент в список
    TreeNode* FindNode(int Number, TreeNode* node);                 //Найти нужный узел (С нужным номером)

    int Deliver(vector<int>& letters);                              //Доставка почты и подсчет извинений

    void PrintInFile(int k, string outputFile);                     //Вывод результата в файл
};

class Veify {
public:
    Veify() {}

    bool Number(string& x);                                         //Проверка на число
 };