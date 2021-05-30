#include "worker.hpp"
void Worker::showInfo()
{

}
string Worker::getDepName()
{
    return 0;
}

//员工
Employee::Employee(int id, string name, int dptid)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DptId = dptid;
}
void Employee::showInfo()
{
    cout<<"职工编号："<<this->m_Id
        <<"\t职工姓名："<<this->m_Name
        <<"\t职工所在部门："<<this->getDepName()
        <<"\t岗位职责：完成经理交给的任务"<<endl;
}
string Employee::getDepName()
{
    return string("员工");    
}

//经理
Manager::Manager(int id, string name, int dptid)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DptId = dptid;
}
void Manager::showInfo()
{
    cout<<"职工编号："<<this->m_Id
        <<"\t职工姓名："<<this->m_Name
        <<"\t职工所在部门："<<this->getDepName()
        <<"\t岗位职责：下发任务给员工，完成老板交给的任务"<<endl;
}
string Manager::getDepName()
{
    return string("经理");    
}


//老板
Boss::Boss(int id, string name, int dptid)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DptId = dptid;
}
void Boss::showInfo()
{
    cout<<"职工编号："<<this->m_Id
        <<"\t职工姓名："<<this->m_Name
        <<"\t职工所在部门："<<this->getDepName()
        <<"\t岗位职责：下发任务给经理"<<endl;
}
string Boss::getDepName()
{
    return string("老板");    
}