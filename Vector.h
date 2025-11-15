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
	    /**
	     * @brief Constructor
	     * Initializes a vector with default capacity 1 and size 0
	     */
		Vector(int initialCapacity = 1);

	    /**
	     * @brief Copy Constructor
	     * @param other The other vector object to copy
	     */
		Vector(const Vector<T>& other);

	    /**
	     * @brief Destructor
	     * Frees the memory in the heap
	     */
		~Vector();

        /**
         * @brief Add element to the vector
         * Resizes if necessary
         * @param value Element of vector to add
         */
        void append(const T& value);

        /**
         * @brief Get Vector Size
         * @return int of the number of elements in the vector
         */
        int size() const;

        /**
         * @brief Access element based on index
         */
        const T& operator[](int index) const;

	private:
	    /**
	     * @brief Pointer to array stored in heap
	     */
        T* data;

        /**
         * @brief Number of elements stored
         */
        int vsize;

        /**
         * @brief Slots available to store elements
         */
        int capacity;

        /**
         * @brief Helper function
         * @param newCapacity Determines the new size of the Vector
         */
        void resize(int newCapacity);
};


// --------------------------------------------------------------------------------------------------- //


/** Constructor */
template <class T>
Vector<T>::Vector(int initialCapacity) : data(nullptr), vsize(0), capacity(initialCapacity)
{
    // Create the array based on the input capacity
    if (capacity > 0) {
        data = new T[capacity];
    }
}

/** Copy Constructor */
template <class T>
Vector<T>::Vector(const Vector<T>& other)
{
    capacity = other.capacity;
    vsize = other.size();
    data = new T[capacity];
    for (int i = 0; i < other.size(); ++i) {
        data[i] = other.data[i];
    }
}

/** Destructor */
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

    data[vsize++] = value;          // add the value into the array based on the number of elements, then increase vsize (post-increment)
}

/** Getter for vsize */
template <class T>
int Vector<T>::size() const
{
    return vsize;
}

/** Operator Override for [] */
template <class T>
const T& Vector<T>::operator[](int index) const
{
    assert(index >= 0 && index < vsize);
    return data[index];
}


#endif
