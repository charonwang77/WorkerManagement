#include <iostream>
#include <fstream>
using namespace std;
#include "worker.hpp"

#define FILENAME "empFILE.txt"
class WorkerManagement
{
public:
    WorkerManagement();

    int isExist(int id);
    void save();
    int getFileEmpNum();
    void initEmp();

    void showMenu();
    void exieMenu();
    void addEmp();
    void showEmp();
    void deletEmp();
    void modEmp();
    void findEmp();
    void sortEmp();
    void clearEmp();


    
    ~WorkerManagement();

    int m_EmpNum;
    Worker ** m_EmpArray;  //指向指针的指针
    bool m_FileIsEmpty;
};