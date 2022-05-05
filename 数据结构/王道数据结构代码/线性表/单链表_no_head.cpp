#include <iostream>
#include <algorithm>

using namespace std;

typedef struct LNode
{
    int data;
    struct LNode *next;
} LNode, *LinkList;

/*
struct LNode* == LinkList
强调节点 用LNode
强调链表 用LinkList
*/

//初始化单链表
bool InitList(LinkList &L)
{
    L = NULL;
    return true;
}

//头插法(不带头结点)
LinkList List_HeadInsert(LinkList &L)
{
    InitList(L);
    LNode *s;
    int x;
    while (cin >> x)
    {
        s = (LNode *)malloc(sizeof(LNode));
        s->data = x;
        s->next = L;
        L = s;
    }
    return L;
}

//尾插法（不带头结点）
LinkList List_TailInsert(LinkList &L)
{
    InitList(L);
    LNode *s, *r = L; // r表示尾指针
    int x;
    bool is_head = true;
    while (cin >> x)
    {
        s = (LNode *)malloc(sizeof(LNode));
        if (is_head)
        {
            is_head = false;
            s->data = x;
            L = s;
            r = s;
        }
        else
        {
            s->data = x;
            r->next = s;
            r = s;
        }
    }
    r->next = NULL;
    return L;
}

//查（按位），返回第i个元素
LNode *GetElem(LinkList L, int i)
{
    if (i <= 0)
        return NULL;
    int j = 1;
    LNode *p = L;
    while (p && j < i)
    {
        p = p->next;
        j++;
    }
    return p;
}

//查（按值），返回该值所在的位置
int LocateElem(LinkList L, int e)
{
    LNode *p = L;
    int count = 1;
    while (p && p->data != e)
    {
        p = p->next;
        count++;
    }
    if (p && p->data == e)
        return count;
    else
        return -1;
}

//统计链表长度
int Length(LinkList L)
{
    int len = 0;
    LNode *p = L;
    while (p)
    {
        p = p->next;
        len++;
    }
    return len;
}

//后插操作，在节点p之后插入元素e
bool InsertNextNode(LNode *p, int e)
{
    if (!p)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (!s) //为啥要加这个判断？
        return false;
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//后插（不带头结点），在第i个位置插入元素e
bool ListInsert(LinkList &L, int i, int e)
{
    if (i < 1)
        return false;
    if (i == 1)
    {
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data = e;
        s->next = L;
        L = s;
        return true;
    }
    LNode *p;
    p = L;
    int j = i; //当前p指向的是第几个节点，没有头结点，所以从1开始
    while (p && j < i - 1)
    {
        p = p->next;
        j++;
    }
    if (!p)
        return false;
    return InsertNextNode(p, e);
}

//前插操作，在节点p之前插入元素e
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

//前插（不带头结点），在节点P之前节点s
bool InsertPriorNode(LNode *p, LNode *s)
{
    if (!p || !s)
        return false;
    s->next = p->next;
    swap(s->data, p->data);
    return true;
}

//删除节点，e是i节点的值
bool ListDelete(LinkList &L, int i, int &e)
{
    if (L == NULL)
    {
        e = -1;
        return false;
    }
    if (i < 1)
        return false;
    if (i > 1)
    {
        LNode *p = GetElem(L, i - 1);
        if (!p || !(p->next))
            return false;
        LNode *q = p->next;
        e = q->data;
        p->next = q->next;
        free(q);
    }
    else //位置为1，即第一个节点
    {
        if (L->next == NULL)
        {
            e = L->data;
            L = NULL;
        }
        else
        {
            e = L->data;
            L = L->next;
        }
    }
    return true;
}

//删除指定节点p
bool DeleteNode(LNode *p)
{
    if (p->next == NULL)
        return false;
    //下面代码不能删除最后一个节点
    LNode *q = p->next;
    p->data = q->data;
    p->next = q->next;
    free(q);
    return true;
}

//打印
void print(LinkList L)
{
    LNode *s = L;
    while (s != NULL)
    {
        cout << s->data << " ";
        s = s->next;
    }
    cout << endl;
}

int main()
{
    LinkList L;
    //头插
    // List_HeadInsert(L);
    // cout << "头插法的结果" << endl;
    // print(L);

    //尾插
    List_TailInsert(L);
    cout << "尾插法的结果" << endl;
    print(L);

    //链表长度
    cout << "链表长度为: " << Length(L) << endl;

    //按位查值
    cout << "链表的第1个元素: " << GetElem(L, 1)->data << endl;
    //按值查找
    cout << "值为3的元素所在的位置为: " << LocateElem(L, 3) << endl;
    //后插元素
    ListInsert(L, 2, 10);
    cout << "在第二个位置插入10这个元素: ";
    print(L);

    //删除元素
    int e;
    ListDelete(L, 5, e);
    cout << "删除的第5个元素为：" << e << endl;
    cout << "删除后的链表为：";
    print(L);

    return 0;
}