#include <iostream>

using namespace std;

typedef int ElemType;

typedef struct DNode
{
    ElemType data;
    struct DNode *prior, *next; //前指针，后指针
} DNode, *DLinkList;

//初始化双链表
bool InitDLinkList(DLinkList &L)
{
    L = (DNode *)malloc(sizeof(DNode)); //分配头结点的空间
    if (L == NULL)
        return false;
    L->prior = NULL;
    L->next = NULL;
    return true;
}
//判断双链表是否为空
bool empty(DLinkList L)
{
    if (L->next == NULL)
        return true;
    return false;
}

//按位查找，返回第i个节点
DNode *GetElem(DLinkList L, int i)
{
    if (i < 0)
        return NULL;
    int j = 0;
    DNode *p = L;
    while (p != NULL && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

//按值查找：找到第一个数据域为e的节点
DNode *LocateElem(DLinkList L, ElemType e)
{
    DNode *p = L;
    if (p == NULL)
        return NULL;
    p = p->next;
    while (p != NULL && p->data != e)
    {
        p = p->next;
    }
    return p;
}

//在p节点之后插入s节点
bool InsertNextNode(DNode *p, DNode *s)
{
    if (p == NULL || s == NULL)
    {
        return false;
    }
    s->next = p->next;
    if (p->next != NULL)
    {
        p->next->prior = s;
    }
    s->prior = p;
    p->next = s;
    return true;
}

//在p节点之后插入值是e的节点
bool InsertNextDNode(DNode *p, ElemType e)
{
    if (p == NULL)
        return false;
    DNode *q = (DNode *)malloc(sizeof(DNode));
    if (q == NULL)
        return false;
    q->data = e;
    q->next = NULL;
    q->prior = p;
    if (p->next != NULL)
    {
        p->next->prior = q;
        q->next = p->next;
    }
    p->next = q;
    return true;
}

//在p节点前面插入s节点
bool InsertPriorDnode(DNode *p, DNode *s)
{
    return InsertNextNode(p->prior, s); //相当于在p前面一个节点后插入s节点
}

//在第i个位置插入值为e的节点
bool InsertDLinkList(DLinkList &L, int i, ElemType e)
{
    if (i <= 0)
        return false;
    DNode *p = GetElem(L, i - 1);
    return InsertNextDNode(p, e);
}

//删除p节点的后继节点
bool DeleteNextNode(DNode *p)
{
    if (p == NULL)
        return false;
    DNode *q = p->next;
    if (q == NULL)
        return false;
    p->next = q->next;
    if (q->next != NULL)
        q->next->prior = p;
    free(q);
    return true;
}

//销毁双链表
bool DestoryList(DLinkList &L)
{
    while (L->next != NULL)
    {
        DeleteNextNode(L);
    }
    free(L);
    L = NULL;
    return true;
}

//尾插法
DLinkList List_TailInset(DLinkList &L)
{
    InitDLinkList(L);
    DNode *p = L;
    ElemType x;
    while (cin >> x)
    {
        InsertNextDNode(p, x);
        p = p->next;
    }
    return L;
}

//头插法
DLinkList List_HeadInsert(DLinkList &L)
{
    InitDLinkList(L);
    ElemType x;
    while (cin >> x)
    {
        InsertNextDNode(L, x);
    }
    return L;
}

int Length(DLinkList L)
{
    DNode *p = L;
    int len = 0;
    while (p->next != NULL)
    {
        len++;
        p = p->next;
    }
    return len;
}

//删除指定节点s
bool DeleteNode(DNode *s)
{
    DNode *p;
    p = s->prior;
    p->next = s->next;
    if (s->next != NULL)
    {
        s->next->prior = p;
    }
    free(s);
    return true;
}

//删除位序i的节点，e是i节点的值
bool ListDelete(DLinkList &L, int i, ElemType &e)
{
    if (i <= 0 || i > Length(L))
        return false;
    DNode *s;
    s = GetElem(L, i);
    if (s == NULL)
        return false;
    e = s->data;
    return DeleteNode(s);
}

void print(DLinkList L)
{
    DNode *p = L->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

int main()
{
    DLinkList L;

    //头插法
    // cout << "头插法：" << endl;
    // List_HeadInsert(L);
    // print(L);

    //尾插法
    cout << "尾插法：" << endl;
    List_TailInset(L);
    print(L);

    cout << "长度：" << Length(L) << endl;
    cout << "第1个元素为" << GetElem(L, 1)->data << endl;
    cout << "在第一个位置插入元素0" << endl;
    InsertDLinkList(L, 1, 0);
    print(L);
    cout << "在最后一个位置插入元素6" << endl;
    InsertDLinkList(L, Length(L) + 1, 6);
    print(L);

    int e;
    ListDelete(L, 1, e);
    cout << "删除第一个节点：" << e << endl;
    cout << "当前链表为：" << endl;
    print(L);

    DestoryList(L);

    return 0;
}