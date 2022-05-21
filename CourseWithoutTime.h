#ifndef COURSE_WITHOUT_TIME_H
#define COURSE_WITHOUT_TIME_H

#include "LinkedList.h"
#include "Lecture.h"
#include "Exceptions.h"
#include <memory>

class CourseWithoutTime
{
    private:
        int course_id;
        std::shared_ptr<LinkedListNode<Lecture> > last_lecture_node;
        
    public:
        CourseWithoutTime(int id);

        int getCourseID() const;
        void SetCourseID(const int number);
        std::shared_ptr<LinkedListNode<Lecture> > getLastLecture() const;
        void SetLastLecture(const std::shared_ptr<LinkedListNode<Lecture> >& new_last_lecture_node);
        bool operator < (const CourseWithoutTime& other) const;

};
        bool operator > (const CourseWithoutTime& course1, const CourseWithoutTime& course2) ;
        bool operator == (const CourseWithoutTime& course1, const CourseWithoutTime& course2) ;
        bool operator != (const CourseWithoutTime& course1, const CourseWithoutTime& course2) ;
        



#endif //COURSE_WITHOUT_TIME_H