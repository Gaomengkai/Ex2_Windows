#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <cstdio>
#include <cstring>


class QUEUE {
    int* const  elems;	//elems�����ڴ����ڴ�Ŷ��е�Ԫ��
    const  int  max;	//elems��������Ԫ�ظ���Ϊmax
    int   head, tail;	 	//����ͷhead��βtail���ӿ�head=tail;��ʼhead=tail=0
public:
    QUEUE(int m);		//��ʼ�����У��������m��Ԫ��
    QUEUE(const QUEUE& q); 			//��q�����ʼ������
    QUEUE(QUEUE&& q)noexcept;		//��q�ƶ���ʼ������
    virtual operator int() const noexcept;	//���ض��е�ʵ��Ԫ�ظ���
    virtual int size() const noexcept;		//���ض�����������Ԫ�ظ���max
    virtual QUEUE& operator<<(int e);  	//��e�����β���������ص�ǰ����
    virtual QUEUE& operator>>(int& e); 	//�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
    virtual QUEUE& operator=(const QUEUE& q);//�����ֵ�����ر���ֵ����
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//�ƶ���ֵ�����ر���ֵ����
    virtual char* print(char* s) const noexcept;//��ӡ������s������s
    virtual ~QUEUE();	 					//���ٵ�ǰ����
};


/// <summary>
/// ��ʼ�����У��������m��Ԫ��
/// </summary>
/// <param name="m">Ԫ�ظ���</param>
QUEUE::QUEUE(int m) :elems(new int[m]), max(m), head(0), tail(0) {}


/// <summary>
/// ��q�����ʼ������
/// </summary>
/// <param name="q"></param>
QUEUE::QUEUE(const QUEUE& q) : elems(new int[q.max]), max(q.max)
{
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i != q.tail; i = (i + 1) % max)
    {
        this->elems[i] = q.elems[i];
    }
}

QUEUE::QUEUE(QUEUE&& q) noexcept :elems(q.elems), max(q.max)        //��q�ƶ���ʼ������
{
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i != q.tail; i = (i + 1) % max)
    {
        this->elems[i] = q.elems[i];
    }
    q.head = 0;
    q.tail = 0;
    *(int**)&(q.elems) = nullptr;
    *(int*)&(q.max) = 0;
}

QUEUE::operator int() const noexcept         //���ض��е�ʵ��Ԫ�ظ���
{
    return max == 0 ? 0 : (tail + max - head) % max;
}

int QUEUE::size() const noexcept            //���ض�����������Ԫ�ظ���max
{
    return this->max;
}

QUEUE& QUEUE::operator<<(int e)               //��e�����β���������ص�ǰ����
{
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";
        return *this;
    }
    this->elems[tail] = e;
    this->tail = (tail + 1) % max;
    return *this;
}

QUEUE& QUEUE::operator>>(int& e)              //�Ӷ��׳�Ԫ�ص�e�������ص�ǰ����
{
    if (this->tail == this->head) {
        throw "QUEUE is empty!";
        return *this;
    }
    e = this->elems[head];
    head = (head + 1) % max;
    return *this;
}

QUEUE& QUEUE::operator=(const QUEUE& q)            //�����ֵ�����ر���ֵ����
{
    if (this->elems == q.elems) return *this;
    if (this->elems != NULL) {
        delete this->elems;
    }
    *(int**)&(this->elems) = new int[q.max];
    *(int*)&(this->max) = q.max;
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i <= q.tail; i++) {
        this->elems[i % q.max] = q.elems[i % q.max];
    }
    return *this;
}

QUEUE& QUEUE::operator=(QUEUE&& q) noexcept           //�ƶ���ֵ�����ر���ֵ����
{
    if (this->elems == q.elems) return *this;
    if (this->elems != nullptr) {
        delete this->elems;
    }
    *(int**)&(this->elems) = q.elems;
    this->head = q.head; this->tail = q.tail;
    for (int i = q.head; i <= q.tail; i++) {
        this->elems[i % q.max] = q.elems[i % q.max];
    }
    q.head = 0;
    q.tail = 0;
    *(int**)&(q.elems) = nullptr;
    *(int*)&(q.max) = 0;
    return *this;
}

char* QUEUE::print(char* s) const noexcept           //��ӡ������s������s
{
    char a[10];
    int i; s[0] = 0;
    for (i = this->head; i != tail; i = (i + 1) % max)
    {
        sprintf_s(a, "%d,", this->elems[i]);
        strcat(s, a);
    }
    return s;
}

QUEUE::~QUEUE()                        //���ٵ�ǰ����
{
    if (this->elems != NULL)
    {
        delete this->elems;
        this->head = 0;
        this->tail = 0;
        *(int**)&(this->elems) = NULL;
        *(int*)&(this->max) = 0;
    }
}