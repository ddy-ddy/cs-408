#include <stdlib.h>
#include <stdio.h>
#include <iostream>

using namespace std;

#define InitSize 10 //表长度的初始定义

//静态分配
// typedef struct
// {
//     int data[InitSize];
//     int length;
// } SeqList;

//动态分配
typedef struct
{
    int *data;
    int length;  //当前长度
    int MaxSize; //最大长度
} SeqList;

//初始化顺序表
void InitList(SeqList &L)
{
    L.data = (int *)malloc(InitSize * sizeof(int));
    L.length = 0;
    L.MaxSize = InitSize;
}

//插入元素
bool ListInsert(SeqList &L, int i, int e)
{
    if (i < 1 || i > L.length + 1) // i的范围是否有效
        return false;
    if (L.length >= L.MaxSize) //当前的存储空间已满，不能插入
        return false;

    for (int j = L.length; j >= i; j--)
        L.data[j] = L.data[j - 1];
    L.data[i - 1] = e;
    L.length++;
    return true;
}

//删除元素,删除位序为i个位置上的元素，e是删除的元素
bool ListDelete(SeqList &L, int i, int &e)
{
    if (i < 1 || i > L.length)
        return false;
    e = L.data[i - 1];
    for (int j = i; j < L.length; j++)
    {
        L.data[j - 1] = L.data[j];
    }
    L.length--;
    return true;
}

//查找元素，按位置查找
int GetElem(SeqList L, int i)
{
    if (i < 1 || i > L.length)
        return -1;
    return L.data[i - 1];
}

//查找元素，按值查找
int LocalElem(SeqList L, int e)
{
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] == e)
            return i + 1;
    }
    return -1;
}

//删除值位于s和t之间的数
bool Delete_s_t(SeqList &L, int s, int t)
{
    if (L.length == 0 || s >= t)
        return false;
    int k = 0;
    for (int i = 0; i < L.length; i++)
    {
        if (L.data[i] < s || L.data[i] > t)
        {
            L.data[k++] = L.data[i];
        }
    }
    L.length = k;
    return true;
}

//打印顺序表
void printList(SeqList &L)
{
    for (int i = 0; i < L.length; i++)
    {
        cout << L.data[i] << " ";
    }
    cout << endl;
}

int main()
{
    SeqList L;   //定义一个顺序表L
    InitList(L); //初始化L

    //测试插入元素
    ListInsert(L, 1, 1);
    ListInsert(L, 2, 6);
    ListInsert(L, 3, 3);
    ListInsert(L, 4, 8);
    ListInsert(L, 5, 2);
    printList(L);

    //测试按位置删除元素
    int e;
    ListDelete(L, 2, e); //删除第二个元素，即值为6
    cout << "删除位序为2的值为：" << e << endl;
    printList(L);

    //测试按位置查找元素
    cout << "位序为2的数据的值为：" << GetElem(L, 2) << endl;

    //测试按值查找元素
    cout << "值为3的数据的位序为：" << LocalElem(L, 3) << endl;

    //测试删除2，8之间的值
    Delete_s_t(L, 4, 8);
    cout << "删除4~8之间的值" << endl;
    printList(L);

    return 0;
}