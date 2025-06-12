#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class Tree {
private:
    struct TreeNode {
        int Number;                         //����� ������
        vector<TreeNode*> Childrens;        //"������" ������� ����� ������
        TreeNode* Parent;                   //��������
        int Letters;                        //���������� ����� � ������
        bool Visited;                       //���� (�������� �� ������)

        TreeNode(int num, TreeNode* parent = nullptr) : Number(num), Parent(parent), Letters(0), Visited(false) {}
    };

    TreeNode* root;

public:
    void ReadFile(string Filename);                                 //������ �����
    void AddNode(int Parent, int Children, int Letters);            //�������� ������� � ������
    TreeNode* FindNode(int Number, TreeNode* node);                 //����� ������ ���� (� ������ �������)

    int Deliver(vector<int>& letters);                              //�������� ����� � ������� ���������

    void PrintInFile(int k, string outputFile);                     //����� ���������� � ����
};

class Veify {
public:
    Veify() {}

    bool Number(string& x);                                         //�������� �� �����
 };