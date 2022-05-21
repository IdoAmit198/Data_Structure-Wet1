#include "Course.h"

    Course::Course(int course_id, int lecutres_in_course): course_id(course_id),
                        lectures_with_zero_time(lecutres_in_course), lecture_times(lecutres_in_course,0),
                        node_ptrs_array(lecutres_in_course,nullptr)
    {
        if (course_id<=0 || lecutres_in_course<=0)
        {
            throw InvalidInput();
        }
    }
    Course::Course(int course_id): course_id(course_id), lectures_with_zero_time(1),
                        lecture_times(),node_ptrs_array()
    {
        if (course_id<=0)
        {
            throw InvalidInput();
        }
    }

    int Course::getCourseID() const
    {
        return course_id;
    }
    void Course::SetCourseID(const int number)
    {
        this->course_id=number;
    }
    int Course::getLecturesWithZeroTime() const
    {
        return lectures_with_zero_time;
    }
    
    void Course::DecrementLecturesZeroTime()
    {
        (this->lectures_with_zero_time)--;
    }

    Array<int>& Course::getLectureTimes() 
    {
        return lecture_times;
    }

    Array<std::shared_ptr<LinkedListNode<Lecture> > >& Course::getNodePtrsArray() 
    {
        return node_ptrs_array;
    }
    
    
    bool Course::operator < (const Course& other) const
    {
        return course_id<other.course_id;
    }

    bool operator > (const Course& course1, const Course& course2)
    {
        return course2<course1;
    }
    
    bool operator == (const Course& course1, const Course& course2)
    {
        return !(course1>course2) && !(course1<course2);
    }

    bool operator != (const Course& course1, const Course& course2)
    {
        return !(course1==course2);
    }