
#undef NDEBUG
#include "CoursesManager.h"
#include <stdlib.h>
#include <cassert>



void f1(CoursesManager& manager)
{
    int iterations = 2;
    std::cout<< manager.AddCourse(2,2) <<endl;
    std::cout<< manager.AddCourse(3,2) <<endl;
    std::cout<< manager.WatchClass(2,0,10)<<endl;
    std::cout<< manager.WatchClass(2,1,15)<<endl;
    std::cout<< manager.AddCourse(1,3) <<endl;
    std::cout<< manager.WatchClass(1,0,5)<<endl;
    std::cout<< manager.WatchClass(1,2,32)<<endl;
    std::cout<< manager.RemoveCourse(2)<<endl;
    std::cout<< manager.RemoveCourse(1)<<endl;
    int* arr_courses=new int[iterations];
    int* arr_lectures=new int[iterations];
    std::cout<<manager.GetMostViewedClasses(iterations, arr_courses, arr_lectures)<<endl;
    for(int i=0;i<iterations;i++)
    {
        std::cout << "course:"<< arr_courses[i]<<" ,lecture:"<<arr_lectures[i]<<"."<<endl;
    }
    delete[] arr_courses;
    delete[] arr_lectures;
}


void f2(CoursesManager& manager)
{
    int iterations = 3;
    std::cout<< manager.AddCourse(2,4) <<endl;
    std::cout<< manager.AddCourse(3,5) <<endl;
    std::cout<< manager.WatchClass(2,3,1)<<endl;
    std::cout<< manager.WatchClass(2,3,2)<<endl;
    std::cout<< manager.WatchClass(2,3,3)<<endl;
    int* time=new int;
    int* arr_courses = new int[iterations];
    int* arr_lectures = new int[iterations];
    std::cout<< manager.TimeViewed(2,3,time)<<endl;
    std::cout<< "time:" << *time << std::endl;
    std::cout<< manager.WatchClass(2,2,45)<<endl;
    std::cout<<manager.GetMostViewedClasses(iterations, arr_courses, arr_lectures)<<endl;
    for(int i=0;i<iterations;i++)
    {
        std::cout << "course:"<< arr_courses[i]<<" ,lecture:"<<arr_lectures[i]<<"."<<endl;
    }
    std::cout<< manager.WatchClass(2,3,60)<<endl;
    std::cout<<manager.GetMostViewedClasses(iterations, arr_courses, arr_lectures)<<endl;
    for(int i=0;i<iterations;i++)
    {
        std::cout << "course:"<< arr_courses[i]<<" ,lecture:"<<arr_lectures[i]<<"."<<endl;
    }
    delete time;
    delete[] arr_courses;
    delete[] arr_lectures;
}


void f3(CoursesManager& manager)
{
    //addCourse
    cout<< "AddCourse TESTS" << endl;
    assert(manager.AddCourse(2,4)==0);
    assert(manager.AddCourse(0,4) ==-3);
    assert(manager.AddCourse(3,4)==0);
    assert(manager.AddCourse(-2,4)==-3);
    assert(manager.AddCourse(5,0)==-3);
    assert(manager.AddCourse(5,-2)==-3);
    assert(manager.AddCourse(-3,-2) ==-3);
    assert(manager.AddCourse(2,6)==-1);

    //removeCourse
    cout<< "removeCourse TESTS" << endl;
    assert(manager.RemoveCourse(-2)==-3);
    assert(manager.RemoveCourse(0)==-3);
    assert(manager.RemoveCourse(2)==0);
    assert(manager.RemoveCourse(2)==-1);
    assert(manager.RemoveCourse(5)==-1);

    cout<< "watchClass TESTS" << endl;
    //WatchClass
    assert(manager.WatchClass(3,5,2)==-3);
    assert(manager.WatchClass(3,4,2)==-3);
    assert(manager.WatchClass(2,2,1)==-1);
    assert(manager.WatchClass(3,2,0)==-3);
    assert(manager.WatchClass(3,2,-3)==-3);
    assert(manager.WatchClass(3,-2,5)==-3);
    assert(manager.WatchClass(-2,2,1)==-3);
    assert(manager.WatchClass(8,4,2)==-1);
    assert(manager.WatchClass(8,-4,2)==-3);
    assert(manager.WatchClass(8,4,-2)==-3);
    assert(manager.WatchClass(3,3,2)==0);

    cout<< "TimeViewed TESTS" << endl;
    //TimeViewed
    int* time=new int;
    assert(manager.TimeViewed(3,5,time)==-3);
    assert(manager.TimeViewed(3,4,time)==-3);
    assert(manager.TimeViewed(2,2,time)==-1);
    assert(manager.TimeViewed(3,2,time)==0);
    assert(manager.TimeViewed(3,-2,time)==-3);
    assert(manager.TimeViewed(8,4,time)==-1);
    assert(manager.TimeViewed(8,-4,time)==-3);
    assert(manager.TimeViewed(3,3,time)==0);
    delete time;
    
    cout<< "GetMostViewedClasses TESTS" << endl;
    //GetMostViewedClasses
    int* arr_courses = new int[4];
    int* arr_lectures = new int[4];
    assert(manager.GetMostViewedClasses(0,arr_courses,arr_lectures)==-3);
    assert(manager.GetMostViewedClasses(-2,arr_courses,arr_lectures)==-3);
    assert(manager.GetMostViewedClasses(5,arr_courses,arr_lectures)==-1);
    assert(manager.GetMostViewedClasses(4,arr_courses,arr_lectures)==0);
    assert(manager.GetMostViewedClasses(1,arr_courses,arr_lectures)==0);

    delete[] arr_courses;
    delete[] arr_lectures;
}

void f4(CoursesManager& manager)
{
    std::cout<< manager.AddCourse(1,1) <<endl;
    std::cout<< manager.AddCourse(2,2) <<endl;
    std::cout<< manager.AddCourse(3,3) <<endl;
    std::cout<< manager.AddCourse(4,4) <<endl;
    std::cout<< manager.AddCourse(5,5) <<endl;
    for (int i=1; i<6; i++)
    {
        std::cout<< manager.WatchClass(i, i-1, i*i) <<endl;
    }
    int* arr_courses = new int[15];
    int* arr_lectures = new int[15];
    cout<< "STARTED GetMostViewedClasses" <<endl;
    std::cout<<manager.GetMostViewedClasses(15, arr_courses, arr_lectures)<<endl;
    for(int i=0;i<15;i++)
    {
        std::cout << "course:"<< arr_courses[i]<<" ,lecture:"<<arr_lectures[i]<<"."<<endl;
    }

    delete[] arr_courses;
    delete[] arr_lectures;
    int* arr_courses1 = new int[10];
    int* arr_lectures1 = new int[10];
    std::cout<<manager.GetMostViewedClasses(10, arr_courses1, arr_lectures1)<<endl;
    for(int i=0;i<10;i++)
    {
        std::cout << "course:"<< arr_courses1[i]<<" ,lecture:"<<arr_lectures1[i]<<"."<<endl;
    }
    delete[] arr_courses1;
    delete[] arr_lectures1;
    
    cout<< "STARTED TimeViewed" << endl;
    int* time=new int;
    for(int i=1;i<6;i++)
    {
        for(int j=0;j<i;j++)
        {
            std::cout<<manager.TimeViewed(i, j, time)<<endl;
            std::cout << "course:"<< i<<" ,lecture:"<<j<<",time:"<<*time<<endl;
        }
    }
    delete time;
    std::cout << manager.RemoveCourse(5) << endl;
    std::cout << manager.RemoveCourse(4) << endl;
    std::cout << manager.RemoveCourse(3) << endl;
    cout<<"STARTED Remove" <<endl;
    int* arr_courses2 = new int[3];
    int* arr_lectures2 = new int[3];
    cout<< manager.GetMostViewedClasses(3, arr_courses2, arr_lectures2)<<endl;
    for(int i=0;i<3;i++)
    {
        std::cout << "course:"<< arr_courses2[i]<<" ,lecture:"<<arr_lectures2[i]<<"."<<endl;
    }
    delete[] arr_courses2;
    delete[] arr_lectures2;
}

void f9000(CoursesManager& manager)
{
    for(int i=0;i<3000;i++)
    {
        int r1= rand() %3000 + (-1000);
        int r2= rand() %500 + (-100);
        if(r1<=0 || r2<=0)
        {
            assert(manager.AddCourse(r1,r2)==-3);
        }
        else
        {
            manager.AddCourse(r1,r2);
        }
    }
    for(int i=0;i<7000;i++)
    {
        int t= rand() %600 + (-200);
        int r1= rand() %3000 + (-1000);
        int r2= rand() %500 + (-100);
        if(r1<=0 || r2<0 || t<=0)
        {
            assert(manager.WatchClass(r1,r2,t)==-3);
        }
        else
        {
            manager.WatchClass(r1,r2,t);
        }
    }
    for(int i=0;i<4000;i++)
    {
        int r1= rand() %3000 + (-1000);
        if(r1<=0)
        {
            assert(manager.RemoveCourse(r1)==-3);
        }
        else
        {
            manager.RemoveCourse(r1);
        }
    }
}

int main()
{

    CoursesManager manager;
    CoursesManager manager1;
    CoursesManager manager2;
    CoursesManager manager3;
    CoursesManager manager4;
    //f1(manager);
    //f2(manager1);
    //f3(manager2);
    f4(manager3);
    //f9000(manager4);
    return 0;
}