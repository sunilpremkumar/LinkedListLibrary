#pragma once
#include <vector>
#include <iostream>

template <class data>
struct sNode
{
    data value;
    sNode *next;

    // constructor
    sNode(data iVal = 0, sNode *iNext = nullptr);
};

template <class data>
struct LinkedList
{
    sNode<data> *head;
    sNode<data> *tail;
    size_t sz;

    LinkedList();
    LinkedList(int iSize);
    LinkedList(std::vector<data> iInput);
    LinkedList(const LinkedList &iObj);
    LinkedList &operator=(const LinkedList &iObj);
    ~LinkedList();

    bool append(data iVal);
    bool append(sNode<data> &iVal);

    int find(data iVal);
    bool insert(data iVal, int index);
    bool erase(data iVal);
    bool clear();
    int size();

    void print();

    data operator[](size_t index)
    {
        int inx = 0;
        sNode<data> *tmp = head;
        while (tmp)
        {
            inx++;
            if (inx == index)
                return tmp->value;
            tmp = tmp->next;
        }
    }

private:
    bool addNode(data iVal);
    bool addNode(sNode<data> &iVal);
};

//--------------------------------------------------------------
// sNode
//--------------------------------------------------------------
// Constructor
template <class data>
sNode<data>::sNode(data iVal, sNode *iNext) : value(iVal), next(iNext)
{
}

//--------------------------------------------------------------
// Linked List
//--------------------------------------------------------------
// constructor
template <class data>
LinkedList<data>::LinkedList() : head(nullptr), tail(nullptr), sz(0) {}

template <class data>
LinkedList<data>::LinkedList(int iSize) : head(nullptr), tail(nullptr), sz(0)
{
    if (!iSize)
        return;
    sz = iSize - 1;
    for (int i = 0; i < iSize; i++)
        addNode(0);
}

template <class data>
LinkedList<data>::LinkedList(std::vector<data> iInput) : head(nullptr), tail(nullptr), sz(0)
{
    if (iInput.empty())
        return;
    sz = iInput.size();
    for (int i = 0; i < iInput.size(); i++)
        addNode(iInput[i]);
}

// copy constructor
template <class data>
LinkedList<data>::LinkedList(const LinkedList &iObj) : head(nullptr), tail(nullptr), sz(0)
{

    sNode<data> *temp = iObj.head;
    while (temp)
    {
        addNode(temp->value);
        temp = temp->next;
    }
    sz = iObj.sz;
}

// assignment operator
template <class data>
LinkedList<data> &LinkedList<data>::operator=(const LinkedList &iObj)
{
    if (iObj != this)
    {
        clear();
        sNode<data> *temp = iObj.head;
        while (temp)
        {
            addNode(temp->value);
            temp = temp->next;
        }
        sz = iObj.sz;
    }
    return this;
}

// destructor
template <class data>
LinkedList<data>::~LinkedList()
{
    clear();
}

// other supporting methods
template <class data>
bool LinkedList<data>::addNode(data iVal)
{
    if (head && tail)
    {
        sNode<data> *temp = new sNode<data>(iVal);
        tail->next = temp;
        tail = temp;
    }
    else
    {
        head = new sNode<data>(iVal);
        tail = head;
    }
    return true;
}

template <class data>
bool LinkedList<data>::addNode(sNode<data> &iVal)
{
    if (head && tail)
    {
        tail->next = &iVal;
        tail = &iVal;
    }
    else
    {
        head = &iVal;
        tail = head;
    }
    return true;
}
template <class data>
bool LinkedList<data>::append(data iVal)
{
    sz++;
    return addNode(iVal);
}
template <class data>
bool LinkedList<data>::append(sNode<data> &iVal)
{
    sz++;
    return addNode(&iVal);
}

template <class data>
int LinkedList<data>::find(data iVal)
{
    int index = -1;
    sNode<data> *temp = head;
    while (temp)
    {
        index++;
        if (temp->value == iVal)
            return index;
        temp = temp->value;
    }
    return -1;
}

template <class data>
bool LinkedList<data>::insert(data iVal, int index)
{
    int inx = 1;
    sNode<data> *temp = head;
    if (inx == index)
    {
        sNode<data> *tempNode = new sNode<data>(iVal);
        tempNode->next = head;
        head = tempNode;
        return true;
    }
    while (temp)
    {
        inx++;
        if (inx == index)
        {
            sNode<data> *tempNode = new sNode<data>(iVal);
            tempNode->next = temp->next;
            temp->next = tempNode;
            return true;
        }
        temp = temp->next;
    }
    return false;
}

template <class data>
bool LinkedList<data>::erase(data iVal)
{
    sNode<data> *temp = head;
    if (iVal == temp->value)
    {
        sNode<data> *tempNode = temp->next;
        delete (head);
        head = tempNode;
        sz--;
        return true;
    }
    while (temp)
    {
        sNode<data> *tempNode = temp->next;
        if (tempNode && iVal == tempNode->value)
        {
            temp->next = tempNode->next;
            delete tempNode;
            sz--;
            return true;
        }
        temp = temp->next;
    }
    return false;
}
template <class data>
bool LinkedList<data>::clear()
{
    sNode<data> *current = head;
    sNode<data> *temp = nullptr;
    while (current)
    {
        temp = current;
        current = current->next;
        sz--;
        delete temp;
    }
    return true;
}

template <class data>
int LinkedList<data>::size()
{
    return sz;
}
template <class data>
void LinkedList<data>::print()
{
    sNode<data> *temp = head;
    while (temp)
    {
        cout << temp->value << endl;
        temp = temp->next;
    }
}
