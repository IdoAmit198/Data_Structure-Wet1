#ifndef Array_H
#define Array_H
#include "Exceptions.h"

template < class T>
class Array
{
    private:
        int size;
        T* data;
        
        /**
         * verifyIndex: private method, check for attempt to access illegal element in the array.
         *              throws "AccessIllegalElement" exception in case of illegal attempt.
         * 
         * @param:
         *      index - the index of the required element in array we attempt to access.
         */
        void verifyIndex(const int& index) const
        {
            if (index < 0 || index >= size)
            {
                throw AccessIllegalElementArray();
            }
        }

    public:
        /**
         * Default c'tor for Array object.
         */
        Array()=default;

        /**
         * c'tor.
         * 
         * @param:
         *      size - Number of members required in the array object.
         *      initial data - Required field to fill in each member of array upon creating.
         *                     Default parameter is the default c'tor of the type T.
         */
        Array(const int size, const T& inital_data= T()): size(size)
        {
            data = new T[size];
            try{
                for(int i=0;i<size;i++)
                {
                    data[i]=inital_data;
                }
            }
            catch(...)
            {
                delete[] data;
                throw;
            }
        } 
        
        /**
         * copy c'tor for Array object.
         * 
         * @param:
         *      other - Reference for another array object, from whom to initialize new array fields.
         */
        Array(const Array& other): size(other.size)
        {
            this->data = new T[size];
            try
            {
                for(int i=0; i<size; i++)
                {
                    this->data[i]=other.data[i];
                }
            }
            catch(...)
            {
                delete[] data;
                throw;
            }
        } 
        
        /**
         * operator= for Array object.
         * 
         * @param:
         *      other - Reference for another array object, from whom to copy its fields to new array.
         */
        Array& operator= (const Array& other)
        {
            if (this == &other)
            {
                return *this;
            }
            T* temp_data = new T[other.size];
            try
            {
                for(int i=0; i<size; i++)
                {
                    temp_data[i]=other.data[i];
                }
            }
            catch(...)
            {
                delete[] temp_data;
                throw;
            }
            delete[] this->data;
            this->data=temp_data;
            size=other.size;
            return *this;
        }

        /**
         * d'tor for Array. deallocate data of Array.
         */
        ~Array()
        {
            delete[] data;
        }
        
        /**
         * operator[] for Array. For example: arr[index] = value.
         * 
         * @paaram:
         *      index - required index to access in the array.
         * 
         * return: T object filled in the required index in array.
         */
        T& operator[] (const int index)
        {
            verifyIndex(index);
            return data[index];
        }

        /**
         * const operator[] for Array. For example: value = arr[index].
         * in use only for reading data and not to write data in array.
         * 
         * @paaram:
         *      index - required index to read from in the array.
         * 
         * return: T object filled in the required index in array.
         */
        const T& operator[] (const int index) const
        {
            verifyIndex(index);
            return data[index];
        }

        /**
         * return size of array, i.e. number of members in it.
         */
        int getSize() const
        {
            return size;
        }

        /* START OF ITERATOR */
        /**
         * iterator for Array class. In use for iteration over Array members, read and write over it.
         */
        class iterator
            {
                private:
                    const Array<T>* array;
                    int index;

                    /**
                    * iterator c'tor
                    * 
                    * @param:
                    *       array - pointer to an Array object.
                    *       input_index - the element index which pointed by the iterator.
                    * 
                    * return: an iterator for the given index in array ot type T
                    */
                    iterator(const Array<T>* array, int input_index) : array(array), index(input_index) {}
                    friend class Array;
                    
                public:                   
                    /**
                    * operator== (iterator)
                    * 
                    * @param:
                    *       it - reference for an iterator object for Array.
                    * 
                    * return: true/false if the this, it iterator are equal 
                    *         (pointing on the same index in the same Array)
                    */
                    bool operator==(const iterator& it) const
                    {
                        assert(array == it.array);
                        return index == it.index;
                    }

                    /**
                    * operator!= (iterator)
                    * 
                    * @param:
                    *       it - reference for an iterator object for Array.
                    * 
                    * return: true/false if the this, it iterator aren't equal 
                    *         (pointing on the same index in the same Array)
                    */ 
                    bool operator!=(const iterator& it) const
                    {
                        return !(*this == it);
                    }

                    /**
                    * operator* (iterator)
                    * 
                    * return: return a refrence to the value the iterator points at
                    */

                    T& operator*()
                    {
                        array->verifyIndex(index);
                        return array->data[index];
                    }

                    /**
                    * operator++ (iterator)
                    * 
                    * return: promote and return the new value the iterator points at.
                    */

                    iterator& operator++() 
                    {
                        index++;
                        return *this;
                    }

                    /**
                    * operator++ (iterator)
                    * 
                    * return: return the value the iterator points at and promote it to the next member.
                    */
                    iterator operator++(int)
                    {
                        iterator result=*this;
                        ++*this;
                        return result;
                    }

                    /**
                     * default copy c'tor for iterator of Array object.
                     */
                    iterator(const iterator&) = default;

                    /**
                     * default operator= for iterator of Array object.
                     */
                    iterator& operator=(const iterator&) = default;               
            };

            /**
             * const_iterator for Array objects.
             */
            class const_iterator
            {
                private:
                    const Array<T>* const array;
                    int index;

                    /**
                    * const_iterator c'tor
                    * 
                    * @param:
                    *       array - pointer to a Array object.
                    *       input_index - the element index which pointed by the iterator.
                    * 
                    * return: an iterator for the given index in array of type T
                    */
                    const_iterator(const Array<T>* const array, int input_index) :  array(array), 
                                                                                    index(input_index)  {}
                    friend class Array;
                public:
                    /**
                    * operator* (const_iterator)
                    * 
                    * return: return a const reference the iterator points at
                    */
                    const T& operator*() const
                    {
                        array->verifyIndex(index);
                        return array->data[index];
                    }

                    /**
                    * operator== (const_iterator)
                    * 
                    * @param:
                    *       it - reference for an iterator object of Array. 
                    * 
                    * return: true/false wether this, it iterator are equal 
                    *         (pointing on the same index in the same const Array)
                    */       
                    bool operator==(const const_iterator& it) const
                    {
                        assert(array == it.array);
                        return index == it.index;
                    }

                    /**
                    * operator!= (const_iterator)
                    * 
                    * @param:
                    *       it - reference for an iterator object for Array.
                    * 
                    * return: true/false if the this, it iterator aren't equal 
                    *         (pointing on the same index in the same  const Array)
                    */  
                    bool operator!=(const const_iterator& it) const
                    {
                        assert(array == it.array);
                        return index != it.index;
                    }

                    /**
                    * prefix operator++ (const_iterator)
                    * 
                    * return: promote the iterator index and return the iterator after the promotion.
                    */
                    const_iterator& operator++()
                    {
                        index++;
                        return *this;
                    }

                    /**
                    * postfix operator++ (const_iterator)
                    * 
                    * return: return the value the const_iterator points at and promomte it to the next
                    */
                    const_iterator operator++(int)
                    {
                        const_iterator result=*this;
                        ++*this;
                        return result;
                    }

                    /**
                     * copy c'tor for const_iterator of Array object.
                     */
                    const_iterator(const const_iterator&) = default;

                    /**
                     * operator= for const_iterator of Array object.
                     */
                    const_iterator& operator=(const const_iterator&) = default;
            };

            /**
             * method to create and return an iterator points to the first element in Array.
             */
            iterator begin()
            {
                return iterator(this, 0);
            }

            /**
             * method to create and return an iterator points right after the last element in Array.
             */
            iterator end()
            {
                int index = this->getSize();
                return iterator(this, index);
            }

            /**
             * method to create and return a const_iterator points right after the last element in Array.
             */
            const_iterator end() const
            {
                int index = this->getSize();
                return const_iterator(this, index);
            } 

            /**
             * method to create and return a const_iterator points to the first element in Array.
             */
            const_iterator begin() const
            {
                return const_iterator(this, 0);
            }


        /* END OF ITERATOR */
    
};


#endif //ARRAY_H