#ifndef VECTOR_H
#define VECTOR_H
#include <cassert>

// The class interface/declaration must have Doxygen comments – put these in
// Follow the style in modelfile.h
// Template class must have -> assignment operator, copy constructor and destructor

template <class T>
class Vector
{
	public:
	    /** Constructor */
		Vector(int initialCapacity = 1);

	    /** Destructor */
		~Vector();

        /** Add element */
        void append(const T& value);

        /** Get Vector Size */
        int size() const;

        /** Access element */
        const T& operator[](int index) const;

	private:
	    /** Pointer to array stored in heap */
        T* data;
        /** Number of elements stored */
        int vsize;
        /** Allocated slots */
        int capacity;

        /** Helper function */
        void resize(int newCapacity);
};


// --------------------------------------------------------------------------------------------------- //


/** Constructor */
template <class T>
Vector<T>::Vector(int initialCapacity) : data(nullptr), vsize(0), capacity(initialCapacity)
{
    /** @brief Create the array based on the input capacity */
    if (capacity > 0) {
        data = new T[capacity];
    }
}

/** Destructor
* @brief Delete the data in the heap */
template <class T>
Vector<T>::~Vector()
{
    delete[] data;
}

/** Resize Helper Function */
template <class T>
void Vector<T>::resize(int newCapacity)
{
    // create a new temp array as updatedData with a new capacity
    T* updatedData = new T[newCapacity];

    // copy the contents over to the new temp array
    for (int i=0; i < vsize; ++i) {
        updatedData[i] = data[i];
    }

    delete[] data;              // delete the data from the original array
    data = updatedData;         // copy the data from the temp array including the new capacity
    capacity = newCapacity;     // update the vector's new capacity
}

/** Add Element */
template <class T>
void Vector<T>::append(const T& value)
{
    // if the vector no longer have space left
    if (vsize >= capacity) {
        resize(capacity * 2);       // resize the vector
    }

    data[vsize++] = value;          // add the value into the array based on the number of elements, then increase vsize (pre-increment)
}

/** Getter for vsize
* @brief returns current number of elements in the vector */
template <class T>
int Vector<T>::size() const
{
    return vsize;
}

/** Operator Override for []
* @brief const Element access */
template <class T>
const T& Vector<T>::operator[](int index) const
{
    assert(index >= 0 && index < vsize);
    return data[index];
}


#endif
