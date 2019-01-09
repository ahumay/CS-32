





#include "newSequence.h"

Sequence::Sequence(int max)
{
    m_sequenceArray = new ItemType[max];
    m_arraySize = max;
    m_sequenceSize = 0;
}

Sequence::~Sequence()
{
    delete [] m_sequenceArray;
}
Sequence::Sequence(const Sequence& other)
{
    m_sequenceArray = new ItemType[other.m_arraySize];
    m_arraySize = other.m_arraySize;
    m_sequenceSize = other.m_sequenceSize;
    for (int k = 0; k < m_sequenceSize; k++)
    {
        m_sequenceArray[k] = other.m_sequenceArray[k];
    }
}

Sequence& Sequence::operator=(Sequence other)
{
 	swap(other);
    return *this;
}

bool Sequence::empty() const
{
    if (m_sequenceSize == 0)
        return true;
    else
        return false;
}

int Sequence::size() const
{
    return m_sequenceSize;
}

bool Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0 || pos > m_sequenceSize || m_sequenceSize == m_arraySize)
        return false;
    
    if (pos == m_sequenceSize)
    {
        m_sequenceSize ++;
        m_sequenceArray[pos] = value;
        return true;
    }
    
    
    m_sequenceSize ++;
    ItemType tempReplace = m_sequenceArray[pos];
    m_sequenceArray[pos] = value;
    for (int k = pos+1; k < m_sequenceSize; k++)
    {
        m_sequenceArray[k] = tempReplace;
        if (k == m_sequenceSize-1)
            continue;
        else
            tempReplace = m_sequenceArray[k+1];
    }
    return true;
}

int Sequence::insert(const ItemType& value)
{
    if (m_sequenceSize == m_arraySize)
        return -1;
    
    int p = -1;
    
    for (int k = 0; p == -1 && k < m_sequenceSize; k++)
    {
        if (value <= m_sequenceArray[k])
            p = k;
    }
    
    if (p == -1)
    {
        insert(m_sequenceSize, value);
        return m_sequenceSize;
    }
    
    else
    {
        insert(p, value);
        return p;
    }
}

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos >= m_sequenceSize)
        return false;
    
    for (int k = pos; k < m_sequenceSize - 1; k++)
    {
        m_sequenceArray[k] = m_sequenceArray[k+1];
    }
    m_sequenceSize--;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    for (int k = 0; k < m_sequenceSize; k++)
    {
        if (value == m_sequenceArray[k])
        {
            erase(k);
            k--;
            count++;
        }
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos >= m_sequenceSize)
        return false;
    
    value = m_sequenceArray[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos >= m_sequenceSize)
        return false;
    
    m_sequenceArray[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    int p = -1;
    
    for (int k = 0; k < m_sequenceSize && p == -1; k++)
    {
        if (m_sequenceArray[k] == value)
            p = k;
    }
    
    return p;
}

void Sequence::swap(Sequence& other)
{
    int tempArraySize = m_arraySize;
    m_arraySize = other.m_arraySize;
    other.m_arraySize = tempArraySize;
    
    int tempSequenceSize = other.m_sequenceSize;
    other.m_sequenceSize = m_sequenceSize;
    m_sequenceSize = tempSequenceSize;
    
    ItemType* tempSequenceArray = other.m_sequenceArray;
    other.m_sequenceArray = m_sequenceArray;
    m_sequenceArray = tempSequenceArray;
}
 
 
 
