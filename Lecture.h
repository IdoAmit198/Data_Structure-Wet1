#ifndef LECTURE_H
#define LECTURE_H

#include "LinkedList.h"
#include "Lecture.h"
#include <memory>

class Lecture
{
    private:
        int course_id;
        int lecture_id;
        int time;

    public:
        Lecture() = default;
        Lecture(const int course_id,const int lecture_id,const int time=0);

        int getCourseID() const;
        void SetCourseID(const int number);
        int getLectureID() const;
        void SetLectureID(const int number);
        int getTime() const;
        void SetTime(const int time);
        bool operator < (const Lecture& other) const;

};
        bool operator > (const Lecture& lecture1, const Lecture& lecture2) ;
        bool operator == (const Lecture& lecture1, const Lecture& lecture2) ;
        bool operator != (const Lecture& lecture1, const Lecture& lecture2) ;
        



#endif //LECTURE_H