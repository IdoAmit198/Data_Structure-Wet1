#ifndef EXCEPTIONS
#define EXCEPTIONS

#include <cassert>
#include <string>

    class Exceptions : public std::exception
    {
        protected:
            std::string to_print;
        public:
            Exceptions(std::string error) : to_print(error) {}
            virtual ~Exceptions() {}
            virtual const char* what() const noexcept
            {
                return to_print.c_str();
            }
    };


//ARRAY EXCEPTIONS
    class ArrayExceptions : public Exceptions 
    {
        public:
            ArrayExceptions(std::string error) : Exceptions(error) {}
            virtual ~ArrayExceptions() {}
    };

    class AccessIllegalElementArray :  public ArrayExceptions
    {
        public:
            AccessIllegalElementArray() :
            ArrayExceptions("An Array related error has occurred: AccessIllegalElementArray") {}
    };
//


//AVL EXCEPTIONS
    class AvlExceptions : public Exceptions 
    {
        public:
            AvlExceptions(std::string error) : Exceptions(error) {}
            virtual ~AvlExceptions() {}
    };
//


//LIST EXCEPTIONS
    class LinkedListExceptions : public Exceptions 
    {
        public:
            LinkedListExceptions(std::string error) : Exceptions(error) {}
            virtual ~LinkedListExceptions() {}
    };

    class IllegalAccessPtr :  public LinkedListExceptions
    {
        public:
            IllegalAccessPtr() :
            LinkedListExceptions("A Linked List related error has occurred: IllegalAccessPtr") {}
    };
//


//COURSESMANAGER EXCEPTIONS
    class CoursesManagerExceptions : public Exceptions
    {
    public:
            CoursesManagerExceptions(std::string error) : Exceptions(error) {}
            virtual ~CoursesManagerExceptions() {}
    };
    class InvalidInput :  public CoursesManagerExceptions
    {
        public:
            InvalidInput() :
            CoursesManagerExceptions("A course manager related error has occurred: InvalidInput") {}
    };
#endif //EXCEPTIONS