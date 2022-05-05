#include <iostream>
#include <algorithm>

using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

//初始链表
bool InitList(LinkList &L)
{
    L = (LNode *)malloc(sizeof(LNode)); //分配一个头结点
    if (!L)
        return false;
    L->next = NULL;
    return true;
}

//链表的长度
int Length(LinkList L)
{
    LNode *p = L;
    int len = 0;
    while (p->next)
    {
        p = p->next;
        len++;
    }
    return len;
}

//按位查找，返回第i个元素
LNode *GetElem(LinkList L, int i)
{
    if (i < 0)
        return NULL;
    int j = 0;
    LNode *p = L;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

//按值查找
LNode *LocateElem(LinkList L, int e)
{
    LNode *p = L->next;
    while (p && p->data != e)
    {
        p = p->next;
    }
    return p;
}

//后插操作，在节点p之后插入元素e
bool InsertNextNode(LNode *p, int e)
{
    if (!p)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (!s)
        return false;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//带头结点的插入操作，在第i个位置插入元素e
bool ListInsert(LinkList &L, int i, int e)
{
    if (i < 1)
        return false;
    LNode *p = GetElem(L, i - 1);
    if (!p)
        return false;
    return InsertNextNode(p, e);
}

//不带头结点的插入操作，在第i个位置插入元素e
bool NoHead_ListInsert(LinkList &L, int i, int e)
{
    if (i < 1)
        return false;
    if (i == 1) //多加一个位置为1的判断
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;
        return true;
    }
    LNode *p;
    p = L;
    int j = 1;
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (!p)
        return false;
    return InsertNextNode(p, e);
}

// 前插操作，在p节点插入元素e
bool InsertPriorNode(LNode *p, int e)
{
    if (!p)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (!s)
        return false;
    s->next = p->next;
    p->next = s;
    s->data = p->data;
    p->data = e;
    return true;
}

//删除位序为i的节点，e是i节点的值
bool ListDelete(LinkList &L, int i, int &e)
{
    if (i < 1)
        return false;
    LNode *p = GetElem(L, i - 1);
    LNode *q = p->next;
    e = q->data;
    p->next = q->next;
    free(q);
    return true;
}

//删除指定的p
bool DeleteNode(LNode *p)
{
    if (p->next == NULL)
        return true;
    //下面代码有but，不能用于删除最后一个节点。
    LNode *q = p->next;
    p->data = q->data;
    p->next = q->next;
    free(q);
    return true;
}

//尾插
LinkList List_TailInsert(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LNode *s, *r = L; // r表示尾指针
    int x;
    while (cin >> x)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        r->next = s;
        r = s;
    }
    r->next = NULL;
    return L;
}

//头插（可以把头结点理解为一个最顶层的东西）
LinkList List_HeadInsert(LinkList &L)
{
    L = (LinkList)malloc(sizeof(LNode));
    L->next = NULL;
    LNode *s;
    int x;
    while (cin >> x)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        s->next = L->next;
        L->next = s;
    }
    return L;
}

void print(LinkList L)
{
    LNode *s = L;
    while (s->next != NULL)
    {
        s = s->next;
        cout << s->data << " ";
    }
    cout << endl;
}

int main()
{
    LinkList L;

    //尾插法
    // List_TailInsert(L);
    // cout << "尾插的结果: ";
    // print(L);

    //头插法
    List_HeadInsert(L);
    cout << "头插的结果: ";
    print(L);

    //获取链表的元素
    cout << "链表的第二个元素: " << GetElem(L, 2)->data << endl;
    cout << "链表的长度" << Length(L) << endl;

    //删除元素
    int e;
    ListDelete(L, 3, e);
    cout << "删除的第三个元素是: " << e << endl;
    cout << "删除后的的链表是: ";
    print(L);

    //插入元素
    ListInsert(L, 3, e);
    cout << "插入的第三个元素是" << e << endl;
    cout << "当前的链表";
    print(L);

    return 0;
}
