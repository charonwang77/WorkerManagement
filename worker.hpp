#include <iostream>
#include <string>
using namespace std;

//父类
class Worker
{
public:
    virtual void showInfo();  //显示个人信息
    virtual string getDepName(); //获取岗位名称

    int m_Id;
    string m_Name;
    int m_DptId;
};

//员工
class Employee : public Worker
{
public:
    Employee(int id, string name, int dptid);
    virtual void showInfo();
    virtual string getDepName();
};

//经理
class Manager : public Worker
{
public:
    Manager(int id, string name, int dptid);   
    virtual void showInfo();
    virtual string getDepName();
};

//老板
class Boss : public Worker
{
public:
    Boss(int id, string name, int dptid);
    virtual void showInfo();
    virtual string getDepName();
};