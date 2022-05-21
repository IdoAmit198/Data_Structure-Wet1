#ifndef COURSESMANAGER_H
#define COURSESMANAGER_H

#include "AVL.h"
#include "LinkedList.h"
#include "Array.h"
#include "Course.h"
#include "Lecture.h"
#include "CourseWithoutTime.h"
#include "Exceptions.h"
#include "library.h"



class CoursesManager
{
    private:
        AvlTree<Course> courses_tree;
        AvlTree<CourseWithoutTime> time_zero_tree;
        AvlTree<Lecture> time_not_zero_tree;
        LinkedList<Lecture> lecture_zero_time_list;
        LinkedList<Lecture> lectures_not_zero_list;
    
    public:
        CoursesManager() = default;

        StatusType AddCourse(const int courseID,const int numOfClasses);

        StatusType RemoveCourse(const int courseID);
        
        StatusType WatchClass(const int courseID,const int classID,const int time);

        StatusType TimeViewed(const int courseID,const int classID, int * timeViewed) const;

        StatusType GetMostViewedClasses(const int numOfClasses, int * courses, int * classes) const;
};

#endif //COURSESMANAGER_H