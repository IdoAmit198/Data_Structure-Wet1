#include "CoursesManager.h"

    StatusType CoursesManager::AddCourse(const int courseID,const int numOfClasses)//3log(n)+m
    {
        if (courseID <= 0 || numOfClasses <= 0)
        {
            return INVALID_INPUT;
        }
        Course new_course(courseID, numOfClasses);
        AvlNode<Course>* course_ptr = courses_tree.insert(new_course);//logn
        if(course_ptr==NULL)
            return FAILURE;
        CourseWithoutTime course_zero_time(courseID);
        AvlNode<CourseWithoutTime>* course_zero_time_ptr = time_zero_tree.insert(course_zero_time);//logn
        AvlNode<CourseWithoutTime>* previous_ptr = time_zero_tree.findPreviousInOrder(course_zero_time);//logn
        std::shared_ptr<LinkedListNode<Lecture> > previous_node_in_list;
        if(previous_ptr==NULL)
        {
            previous_node_in_list=lecture_zero_time_list.insertAtStart(Lecture(courseID, 0));//1
        }
        else
        {
            previous_node_in_list=lecture_zero_time_list.insertAfterNode((previous_ptr->data).getLastLecture(),
                                                                        Lecture(courseID, 0));//1
        }
        Array<std::shared_ptr<LinkedListNode<Lecture> > >& node_array=((course_ptr->data).getNodePtrsArray()); //1
        node_array[0] = previous_node_in_list;
        Array<std::shared_ptr<LinkedListNode<Lecture> > >::iterator it=node_array.begin();
        it++;
        //WE START FROM SECOND LECTURE, BECAUSE WE ALREADY POINTED THE FIRST ABOVE.
        for(int i=1; it != node_array.end(); it++, i++)//m
        {
            previous_node_in_list=lecture_zero_time_list.insertAfterNode(previous_node_in_list,
                                                                        Lecture(courseID, i));//1
            *it=previous_node_in_list;
        }
        (course_zero_time_ptr->data).SetLastLecture(previous_node_in_list); //1
        assert(courses_tree.CheckIfBalanced() && time_zero_tree.CheckIfBalanced() && time_not_zero_tree.CheckIfBalanced());//NEED TO DELETE!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        return SUCCESS;
    }

    StatusType CoursesManager::RemoveCourse(const int courseID)//3log(n)+mlog(m)
    {
        if (courseID <= 0)
        {
            return INVALID_INPUT;
        }
        AvlNode<Course>* course_ptr=courses_tree.find(Course(courseID)); //logn
        if (course_ptr==NULL)
        {
            return FAILURE;
        } 
        Array<std::shared_ptr<LinkedListNode<Lecture> > >& node_array=((course_ptr->data).getNodePtrsArray());//1
        Array<int>& time_array=((course_ptr->data).getLectureTimes());//1
        Array<int>::iterator it_time=time_array.begin();//1
        int lecture_num=0;
        for(Array<std::shared_ptr<LinkedListNode<Lecture> > >::iterator it_ptr=node_array.begin();
            it_ptr != node_array.end() && it_time!=time_array.end(); it_ptr++, it_time++,lecture_num++)//m*logM
        {
            if((*it_time)==0)
            {
                lecture_zero_time_list.remove(*(*it_ptr));//1
            }
            else
            {
                time_not_zero_tree.remove(Lecture(courseID,lecture_num,*it_time));//logM
                lectures_not_zero_list.remove(*(*it_ptr));//1
            }
            *it_ptr=nullptr;
        }
        AvlNode<CourseWithoutTime>* found_course_no_time = time_zero_tree.find(CourseWithoutTime(courseID));//logn
        if(found_course_no_time!=NULL)
        {
            (found_course_no_time->data).SetLastLecture(nullptr);//1
            time_zero_tree.remove(CourseWithoutTime(courseID));//logn
        }
        courses_tree.remove(Course(courseID));//logn
        assert(courses_tree.CheckIfBalanced() && time_zero_tree.CheckIfBalanced() && time_not_zero_tree.CheckIfBalanced());//NEED TO DELETE!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        return SUCCESS;
    }
        
    StatusType CoursesManager::WatchClass(const int courseID,const int classID,const int time)//2LogM+4logn
    {
        if (time<=0 || classID<0 || courseID<=0)
        {
            return INVALID_INPUT;
        }
        AvlNode<Course>* course_ptr=NULL;
        course_ptr=courses_tree.find(Course(courseID));//logn
        if (course_ptr==NULL)
        {
            return FAILURE;
        }
        Array<std::shared_ptr<LinkedListNode<Lecture> > >& node_array=((course_ptr->data).getNodePtrsArray());//1
        if (classID+1 > node_array.getSize())
        {
            return INVALID_INPUT;
        }
        Array<int>& time_array=((course_ptr->data).getLectureTimes());//1
        if(time_array[classID]==0)
        {
            (course_ptr->data).DecrementLecturesZeroTime();//1
            CourseWithoutTime this_course_without_time(courseID);
            //WE FIND THE COURSE IN THE TREE OF TIME=0.
            AvlNode<CourseWithoutTime>* course_without_time_ptr = time_zero_tree.find(this_course_without_time);//logn
            if((node_array[classID])==(course_without_time_ptr->data).getLastLecture()) //1
            {
                (course_without_time_ptr->data).SetLastLecture(lecture_zero_time_list.remove(*(node_array[classID])));//1
                if((course_ptr->data).getLecturesWithZeroTime()==0)
                {
                    (course_without_time_ptr->data).SetLastLecture(nullptr);//1
                    time_zero_tree.remove(this_course_without_time);//logn
                }
            }
            else
            {
                lecture_zero_time_list.remove(*(node_array[classID])); //1
            }
        }
        else
        {
            lectures_not_zero_list.remove(*(node_array[classID])); //REMOVE FROM LIST OF TIME!=0 //1
            time_not_zero_tree.remove(Lecture(courseID,classID,time_array[classID]));//REMOVE FROM TREE TIME!=0 //logM
        }
        time_array[classID]+=time;
        Lecture new_lecture(courseID,classID,time_array[classID]);
        time_not_zero_tree.insert(new_lecture);//logM
        AvlNode<Lecture>* prev_lecture_tree_ptr=time_not_zero_tree.findPreviousInOrder(new_lecture);//FIND LECTURE BEFORE THE NEW LECTURE //logM
        if (prev_lecture_tree_ptr==NULL)
        {
            //IF THE LECTURE SHOULD BE FIRST IN THE LIST
            node_array[classID]=lectures_not_zero_list.insertAtStart(new_lecture); //1
        }
        else
        {
            //WE FIND THE COURSE IN COURSES_TREE AND GET POINTER TO IT.
            AvlNode<Course>* prev_course_ptr=courses_tree.find(Course(prev_lecture_tree_ptr->data.getCourseID()));//logn
            //WE FIND THE NUMBER OF THE LECTURE BEFORE OUR LECTURE IN THE LIST OF TIME!=0.
            int prev_lecture_num= (prev_lecture_tree_ptr->data).getLectureID();//1
            //WE FIND THE PREVIOUS NODE IN THE LIST FROM THE LECTURES POINTERS ARRAY
            std::shared_ptr<LinkedListNode<Lecture> > prev_node_list=(prev_course_ptr->data).getNodePtrsArray()[prev_lecture_num];//1
            //WE INSERT THE LECTURE AFTER THE FOUND NODE AND UPDATE THE LECTURES POINTERS ARRAY
            node_array[classID]=lectures_not_zero_list.insertAfterNode(prev_node_list,new_lecture);//1
        }
        assert(courses_tree.CheckIfBalanced() && time_zero_tree.CheckIfBalanced() && time_not_zero_tree.CheckIfBalanced());//NEED TO DELETE!@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        return SUCCESS;
    }

    StatusType CoursesManager::TimeViewed(const int courseID,const int classID, int * timeViewed) const//logn
    {
        if ( classID<0 || courseID<=0)
        {
            return INVALID_INPUT;
        }
        AvlNode<Course>* course_ptr=NULL;
        course_ptr=courses_tree.find(Course(courseID));//logn
        if (course_ptr==NULL)
        {
            return FAILURE;
        }
        Array<int>& time_array = ((course_ptr->data).getLectureTimes());//1
        if (classID+1 > time_array.getSize())//1
        {
            return INVALID_INPUT;
        }
        *timeViewed = time_array[classID];//1
        return SUCCESS;
    }

    StatusType CoursesManager::GetMostViewedClasses(const int numOfClasses,
                                                    int * courses, int * classes) const
    {
        if (numOfClasses <= 0)
        {
            return INVALID_INPUT;
        }
        int counter = 0;
        for (LinkedList<Lecture>::const_iterator it = lectures_not_zero_list.begin();
            it != lectures_not_zero_list.end() && counter<numOfClasses; it++, counter++)
            {
                courses[counter]=(*it).getCourseID();
                classes[counter]=(*it).getLectureID();
            }
        for (LinkedList<Lecture>::const_iterator it = lecture_zero_time_list.begin();
            it != lecture_zero_time_list.end() && counter<numOfClasses; it++, counter++)
            {
                courses[counter]=(*it).getCourseID();
                classes[counter]=(*it).getLectureID();
            }
        if(counter<numOfClasses)
        {
            return FAILURE;
        }
        return SUCCESS;
    }