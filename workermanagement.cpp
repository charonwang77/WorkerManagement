#include "workermanagement.hpp"

WorkerManagement::WorkerManagement()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);
    //文件不存在
    if (!ifs.is_open())
    {
        cout<<"文件不存在"<<endl;
        this->m_EmpNum = 0;  //初始化
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    //文件存在，记录为空
    char ch;
    ifs>>ch;
    if (ifs.eof())
    {
        cout<<"文件为空"<<endl;
        this->m_EmpNum = 0; 
        this->m_EmpArray = NULL;
        this->m_FileIsEmpty = true;
        ifs.close();
        return;
    }
    int num = this->getFileEmpNum();
    //cout<<"职工人数为："<<num<<endl;
    this->m_EmpNum  = num; 
    this->m_EmpArray = new Worker*[this->m_EmpNum];
    initEmp();
    /*
    cout<<"现有员工："<<endl;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        cout<<"职工号："<<this->m_EmpArray[i]->m_Id
            <<"\t姓名："<<this->m_EmpArray[i]->m_Name
            <<"\t部门编号："<<this->m_EmpArray[i]->m_DptId<<endl;
    }
    */
    
    
}
void WorkerManagement::showMenu()
{
    cout<<"*********************************************************"<<endl;
    cout<<"*******************欢迎使用职工管理系统*********************"<<endl;
    cout<<"********************* 0.退出管理程序 **********************"<<endl;
    cout<<"********************* 1.增加职工信息 **********************"<<endl;
    cout<<"********************* 2.显示职工信息 **********************"<<endl;
    cout<<"********************* 3.删除离职职工 **********************"<<endl;
    cout<<"********************* 4.修改职工信息 **********************"<<endl;
    cout<<"********************* 5.查找职工信息 **********************"<<endl;
    cout<<"********************* 6.进行职工排序 **********************"<<endl;
    cout<<"********************* 7.清空所有文档 **********************"<<endl;
    cout<<"*********************************************************"<<endl;
}

void WorkerManagement::exieMenu()
{
    cout<<"欢迎下次使用"<<endl;
    system("pause");
    exit(0);
}

void WorkerManagement::addEmp()
{
    cout<<"请输入新增员工的数量："<<endl;
    int addNum;
    cin>>addNum;
    if (addNum>0)
    {
        // 计算新空间大小并开辟
        int newSize = this->m_EmpNum+addNum;
        Worker** newSpace = new Worker*[newSize]; //这里的*为什么放Worker后面？
        //将原空间下的内容存储到新空间下
        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
            }
            
        }
        //输入新数据
        for (int i = 0; i < addNum; i++)
        {
            int id;
            string name;
            int depid;

            cout<<"请输入第"<<i+1<<"个员工的编号："<<endl;
            cin>>id;
            
            cout<<"请输入第"<<i+1<<"个员工的姓名"<<endl;
            cin>>name;

            cout<<"请输入第"<<i+1<<"个员工的部门编号"<<endl;
            cout<<"1.普通员工"<<endl;
            cout<<"2.经理"<<endl;
            cout<<"3.老板"<<endl;
            cin>>depid;

            Worker *worker = NULL;
            switch (depid)
            {
            case 1:
                worker = new Employee(id,name,depid);
                break;
            case 2:
                worker = new Manager(id,name,depid);
                break;
            case 3:
                worker = new Boss(id,name,depid);
                break;
            default:
                break;
            }
            newSpace[this->m_EmpNum+i] = worker;

        }
        //释放原有空间 更新指向和个数
        delete[] this->m_EmpArray;  //释放
        this->m_EmpArray = newSpace;  //更新
        this->m_EmpNum = newSize;
        
        this->save(); //save(); 用this指针的意义？
        this->m_FileIsEmpty = false;
        cout<<"成功添加"<<addNum<<"个新员工"<<endl;

    }
    else
    {
        cout<<"输入有误"<<endl;
    }
    
}

void WorkerManagement::showEmp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"员工记录为空"<<endl;
    }
    else
    {
        for (int i = 0; i < this->m_EmpNum; i++)
        {
            this->m_EmpArray[i]->showInfo();
        }    
    }
    system("pause");
    system("cls");
}

void WorkerManagement::deletEmp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或为空"<<endl;
    }
    else
    {
        cout<<"输入您要删除的员工编号："<<endl;
        int id;
        cin>>id;
        int num = isExist(id);
        if (num != -1)
        {
            for (int i = num; i < this->m_EmpNum; i++)
            {
                this->m_EmpArray[i] = this->m_EmpArray[i+1]; 
            }
            this->m_EmpNum--;
            this->save();
            cout<<"删除成功"<<endl;
            
        }
        else
        {
            cout<<" 编号不存在"<<endl;
        }  
    }     
}

void WorkerManagement::modEmp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或为空"<<endl;
    }
    else
    {
        cout<<"输入您要修改的员工编号："<<endl;
        int id;
        cin>>id;
        int num = isExist(id);
        if (num != -1)
        {
            delete this->m_EmpArray[num];

            int newid;
            string newname;
            int select;
            cout<<"请输入员工编号："<<endl;
            cin>>newid;
            cout<<"请输入员工姓名："<<endl;
            cin>>newname;
            cout<<"请输入员工的类型："<<endl;
            cout<<"1.员工"<<"\n"<<"2.经理"<<"\n"<<"3.老板"<<endl;
            cin>>select;

            Worker *worker = NULL;
            switch (select)
            {
            case 1:
                worker = new Employee(newid, newname, select);
                break;
            case 2:
                worker = new Manager(newid, newname, select);
            case 3:
                worker = new Boss(newid,newname, select);
            default:
                break;
            }
            this->m_EmpArray[num] = worker;
            this->save();
            cout<<"更改成功"<<endl;
        }
        else
        {
            cout<<"员工不存在"<<endl;
        }
    }  
    system("pause");
    system("cls");

}

void WorkerManagement::findEmp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或者为空"<<endl;
    }
    else
    {
        cout<<"请输入查找方式："<<endl;
        cout<<"1.按编号查找"<<"\n"<<"2.按姓名查找"<<endl;

        int select = 0;
        int id;
        string name;
        cin>>select;
        if (select == 1)
        {
            cout<<"请输入要查找员工的编号："<<endl;
            cin>>id;
            int index = isExist(id);
            if (index != -1)
            {
                this->m_EmpArray[index]->showInfo();
            }
            else
            {
                cout<<"员工不存在"<<endl;
            }   
        }
        else if (select == 2)
        {
            cout<<"请输入员工姓名："<<endl;
            cin>>name;
            bool flag = false;
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if (this->m_EmpArray[i]->m_Name == name)
                {
                    cout<<"员工信息如下："<<endl;
                    this->m_EmpArray[i]->showInfo();
                    flag = true;
                }   
            }
            if (flag == false)
            {
                cout<<"该员工不存在"<<endl;
            }
        }
        else
        {
            cout<<"输入有误"<<endl;
        }
        

    }
    
}

void WorkerManagement::sortEmp()
{
    if (this->m_FileIsEmpty)
    {
        cout<<"文件不存在或为空"<<endl;
    }
    else
    {
        int select;
        cout<<"请选择排序方式："<<"\n"<<"1.升序"<<"\n"<<"2.降序"<<endl;
        cin>>select;


        for (int i = 0; i < this->m_EmpNum; i++)
        {
            int MaxorMin = i;
            for (int j = i+1; j < this->m_EmpNum; j++)
            {
                if (select == 1)
                {
                    if (this->m_EmpArray[MaxorMin]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        MaxorMin = j;
                    }
                    
                }
                else
                {
                    if (this->m_EmpArray[MaxorMin]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        MaxorMin = j;
                    }    
                }    
            }
            if (MaxorMin != i)
            {
                Worker *temp = this->m_EmpArray[i];
                this->m_EmpArray[i] = this->m_EmpArray[MaxorMin];
                this->m_EmpArray[MaxorMin] = temp;
            }    
        }

        this->save();
        cout<<"排序后的结果为："<<endl;
        this->showEmp();   
    }
    
}

void WorkerManagement::clearEmp()
{
    cout<<"确认清空？"<<"\n"<<"1.确认"<<"\n"<<"2.返回"<<endl;
    int select;
    cin>>select;
    if (select==1)
    {
        ofstream ofs(FILENAME, ios::trunc);  //如果存在则删除并重建
        ofs.close();

        if (this->m_EmpArray != NULL)
        {
            for (int i = 0; i < this->m_EmpNum; i++)
            {
                if(this->m_EmpArray[i] != NULL)
                {
                    delete this->m_EmpArray[i];  //delete 释放内存
                }
            }  
            this->m_EmpNum = 0;
            delete[] this->m_EmpArray; //释放内存，但是指针指向没变 所以需要让指针指向NULL，否则指针会成为野指针
            this->m_EmpArray = NULL;   //
            this->m_FileIsEmpty = true; 
        }
        cout<<"清空成功"<<endl;
    }
    
}

int WorkerManagement::isExist(int id)
{
    int index = -1 ;
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        if(id == this->m_EmpArray[i]->m_Id)
        {
            index = i;
            break;
        }
    }
    return index;
}

void WorkerManagement::save()
{
    ofstream ofs;
    ofs.open(FILENAME, ios::out);
    for (int i = 0; i < this->m_EmpNum; i++)
    {
        ofs<<this->m_EmpArray[i]->m_Id<<"\t"
           <<this->m_EmpArray[i]->m_Name<<"\t"
           <<this->m_EmpArray[i]->m_DptId<<endl;
    }
    ofs.close();

}

int WorkerManagement::getFileEmpNum()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::out);
    
    int id = 0;
    string name = "";
    int depid = 0;

    int num = 0;
    while (ifs>>id && ifs>>name && ifs>>depid)
    {
        //记录人数
        num++;
    }

    ifs.close();
    return num;
    
}

void WorkerManagement::initEmp()
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);

    int id;
    string name;
    int depid;

    int index = 0;
    while (ifs>>id && ifs>>name && ifs>>depid)
    {
        Worker *worker = NULL;
        if (depid == 1)
        {
            worker = new Employee(id,name,depid);
        }
        else if (depid  == 2)
        {
            worker = new Manager(id,name,depid);
        }
        else
        {
            worker = new Boss(id,name,depid);
        }
        this->m_EmpArray[index] = worker;
        index++;    
    }
    ifs.close();
}

WorkerManagement::~WorkerManagement()
{
    if (this->m_EmpArray != NULL)
    {
        delete[] this->m_EmpArray;  //释放
    }
    
}
