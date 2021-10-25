#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <cstdio>
#include <cstring>


class QUEUE {
    int* const  elems;	//elems申请内存用于存放队列的元素
    const  int  max;	//elems申请的最大元素个数为max
    int   head, tail;	 	//队列头head和尾tail，队空head=tail;初始head=tail=0
public:
    QUEUE(int m);		//初始化队列：最多申请m个元素
    QUEUE(const QUEUE& q); 			//用q深拷贝初始化队列
    QUEUE(QUEUE&& q)noexcept;		//用q移动初始化队列
    virtual operator int() const noexcept;	//返回队列的实际元素个数
    virtual int size() const noexcept;		//返回队列申请的最大元素个数max
    virtual QUEUE& operator<<(int e);  	//将e入队列尾部，并返回当前队列
    virtual QUEUE& operator>>(int& e); 	//从队首出元素到e，并返回当前队列
    virtual QUEUE& operator=(const QUEUE& q);//深拷贝赋值并返回被赋值队列
    virtual QUEUE& operator=(QUEUE&& q)noexcept;//移动赋值并返回被赋值队列
    virtual char* print(char* s) const noexcept;//打印队列至s并返回s
    virtual ~QUEUE();	 					//销毁当前队列
};


/// <summary>
/// 初始化队列：最多申请m个元素
/// </summary>
/// <param name="m">元素个数</param>
QUEUE::QUEUE(int m) :elems(new int[m]), max(m), head(0), tail(0) {}


/// <summary>
/// 用q深拷贝初始化队列
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

/// <summary>
/// 用q移动初始化队列
/// </summary>
/// <param name="q"></param>
/// <returns>对象</returns>
QUEUE::QUEUE(QUEUE&& q) noexcept :elems(q.elems), max(q.max)        //用q移动初始化队列
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


/// <summary>
/// 返回队列的实际元素个数
/// </summary>
/// <returns>队列的实际元素个数</returns>
QUEUE::operator int() const noexcept
{
    return max == 0 ? 0 : (tail + max - head) % max;
}


/// <summary>
/// 返回队列申请的最大元素个数max
/// </summary>
/// <returns></returns>
int QUEUE::size() const noexcept
{
    return this->max;
}


/// <summary>
/// 将e入队列尾部，并返回当前队列
/// </summary>
/// <param name="e">待操作元素</param>
/// <returns>当前队列</returns>
QUEUE& QUEUE::operator<<(int e)
{
    if ((tail + 1) % max == head) {
        throw "QUEUE is full!";
        return *this;
    }
    this->elems[tail] = e;
    this->tail = (tail + 1) % max;
    return *this;
}


/// <summary>
/// 从队首出元素到e
/// </summary>
/// <param name="e">元素</param>
/// <returns>当前队列</returns>
QUEUE& QUEUE::operator>>(int& e)
{
    if (this->tail == this->head) {
        throw "QUEUE is empty!";
        return *this;
    }
    e = this->elems[head];
    head = (head + 1) % max;
    return *this;
}


/// <summary>
/// 深拷贝赋值并返回被赋值队列
/// </summary>
/// <param name="q">赋值</param>
/// <returns>被赋值队列</returns>
QUEUE& QUEUE::operator=(const QUEUE& q)
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


/// <summary>
/// 移动赋值并返回被赋值队列
/// </summary>
/// <param name="q">赋值</param>
/// <returns>队列</returns>
QUEUE& QUEUE::operator=(QUEUE&& q) noexcept
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


/// <summary>
/// 打印至s
/// </summary>
/// <param name="s">待打印的临时字符串</param>
/// <returns>打印的临时字符串</returns>
char* QUEUE::print(char* s) const noexcept
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


/// <summary>
/// 析构
/// </summary>
QUEUE::~QUEUE()
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