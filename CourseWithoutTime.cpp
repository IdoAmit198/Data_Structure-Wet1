#include "CourseWithoutTime.h"

    CourseWithoutTime::CourseWithoutTime(int id) : course_id(id)
    {
        if (id<=0)
        {
            throw InvalidInput();
        }
    }

    int CourseWithoutTime::getCourseID() const
    {
        return course_id;
    }

    void CourseWithoutTime::SetCourseID(const int number)
    {
        this->course_id=number;
    }
    
    std::shared_ptr<LinkedListNode<Lecture> > CourseWithoutTime::getLastLecture() const
    {
        return last_lecture_node;
    }

    void CourseWithoutTime::SetLastLecture(const std::shared_ptr<LinkedListNode<Lecture> >&
                                            new_last_lecture_node)
    {
        this->last_lecture_node = new_last_lecture_node;                                       
    }

    bool CourseWithoutTime::operator < (const CourseWithoutTime& other) const
    {
        return (course_id<other.course_id);
    }
    bool operator > (const CourseWithoutTime& course1, const CourseWithoutTime& course2)
    {
        return course2<course1;
    }

    bool operator == (const CourseWithoutTime& course1, const CourseWithoutTime& course2) 
    {
        return !(course1>course2) && !(course1<course2);
    }
    
    bool operator != (const CourseWithoutTime& course1, const CourseWithoutTime& course2) 
    {
        return !(course1==course2);
    }


