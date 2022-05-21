#ifndef COURSE_H
#define COURSE_H

#include "Array.h"
#include "Lecture.h"
#include "Exceptions.h"
#include <memory>

class Course
{
private:
        int course_id;
        int lectures_with_zero_time;
        Array<int> lecture_times;
        Array<std::shared_ptr<LinkedListNode<Lecture> > > node_ptrs_array;

public:
        Course(int course_id, int lecutres_in_course);
        Course(int course_id);
        int getCourseID() const;
        void SetCourseID(const int number);
        int getLecturesWithZeroTime() const;
        void DecrementLecturesZeroTime();
        Array<int>& getLectureTimes();
        Array<std::shared_ptr<LinkedListNode<Lecture> > >& getNodePtrsArray();
        bool operator < (const Course& other) const;
};
        bool operator > (const Course& course1, const Course& course2) ;
        bool operator == (const Course& course1, const Course& course2) ;
        bool operator != (const Course& course1, const Course& course2) ;
        


#endif //COURSE_H