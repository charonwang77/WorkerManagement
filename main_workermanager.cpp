#include <iostream>
using namespace std;
#include "workermanagement.hpp"
void test()
{
    Worker *worker = NULL;
    worker = new Employee(1,"赵赵",1);
    worker->showInfo();
    delete worker;  //delete 没有删除指针吗？那什么时候删除指针，需不需要删除指针

    worker = new Manager(2,"钱钱",2);
    worker->showInfo();
    delete worker;

    worker = new Boss(3,"孙孙",3);
    worker->showInfo();
    delete worker;

}
int main()
{
    // test();
    WorkerManagement wm;
    int select = 0;
    while (true)
    {
        wm.showMenu();
        cout<<"请输入您的选择："<<endl;
        cin>>select;   
        switch (select)
        {
        case 0: //退出
            wm.exieMenu();
            break;
        case 1: //添加
            wm.addEmp();
            break;
        case 2: //显示
            wm.showEmp();
            break;
        case 3: //删除
            wm.deletEmp();
            break;
        case 4: //修改
            wm.modEmp();
            break;
        case 5: //查找
            wm.findEmp();
            break;
        case 6: //排序
            wm.sortEmp();
            break;
        case 7: //清空
            wm.clearEmp();
            break;
        default:
            system("cls");
            break;
        }
    }   
    system("pause");
    return 0;
}