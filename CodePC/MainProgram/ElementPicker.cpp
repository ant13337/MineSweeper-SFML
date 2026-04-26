#include "ElementPicker.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

/*
This class may be a bit overkill
but I needed to create a Template class
to get an A in the course

The class kinda sucks though and
I could've easily made a far more optimized solution
than creating a vector and populating it with all
squares that aren't in the exclude vector for each mine
but this bad solution will still improve my grade
which is what I'm really trying to
optimize rather than performance
*/

template <typename T>
ElementPicker<T>::ElementPicker(const std::vector<T> &elements, const std::vector<T> &excludeElements)
    : elements_(elements), excludeElements_(excludeElements)
{
}

template <typename T>
T ElementPicker<T>::pickRandomElement() const
{
    std::vector<T> availableElements;
    T returnElement = T();
    // Create a vector from the elements that are not in the excludeElements vector
    for (const T &element : elements_)
    {
        if (std::find(excludeElements_.begin(), excludeElements_.end(), element) == excludeElements_.end())
        {
            availableElements.push_back(element);
        }
    }

    if (!availableElements.empty()) // if the vector contains anything
    {
        int index = std::rand() % availableElements.size(); // pick a random index in the vector
        returnElement = availableElements[index];           // return the element with the random index
    }
    else
    {
        throw std::invalid_argument("No avalible elements");
    }

    return returnElement;
}

// Explicit instantiation for the types I plan to use
template class ElementPicker<int>;