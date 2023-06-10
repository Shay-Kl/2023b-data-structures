#include "RecordsPile.h"
#include "exceptions.h"

RecordsPile::RecordsPile(): m_pile(new Record[1]) {}

RecordsPile::RecordsPile(int* records_stock, int number_of_records): m_pile(new Record[number_of_records]), m_count(number_of_records)
{
    for (int i = 0; i < m_count; i++)
    {
        m_pile[i] = Record(records_stock[i], i);
    }
}

RecordsPile::~RecordsPile()
{
    delete[] m_pile;
}

RecordsPile::RecordsPile(const RecordsPile& other): m_pile(new Record[other.m_count]), m_count(other.m_count)
{
    for(int i = 0; i < m_count; i++)
    {
        m_pile[i] = Record(other.m_pile[i]);
    }
}

RecordsPile& RecordsPile::operator=(const RecordsPile& other) 
{
    delete[] m_pile;
    m_count = other.m_count;
    m_pile = new Record[m_count];
    for(int i = 0; i < m_count; i++)
    {
        m_pile[i] = Record(other.m_pile[i]);
    }
    return *this;
}

void RecordsPile::pileOnTop(int id1, int id2)
{
    Record* root1 = m_pile[id1].getRoot();
    Record* root2 = m_pile[id2].getRoot();
    if (root1==root2)
    {
        throw Failiure();
    }
    

    int stackHeight1 = root1->getStackHeight();
    int stackHeight2 = root2->getStackHeight();

    int ogHeight2 = root2->getRecordCopies();

    root1->setParent(root2);
    root1->increaseHeightDelta(stackHeight2 - ogHeight2);
    root2->increaseHeightTotal(stackHeight1);
}

int RecordsPile::purchase(int id)
{
    return m_pile[id].purchase();
}

int RecordsPile::getColumn(int id)
{
    return m_pile[id].getColumn();
}

int RecordsPile::getHeight(int id)
{
    return m_pile[id].getRecordHeight();
}

RecordsPile::Record::Record(int height, int id): parent(nullptr), bought(0), column(id), copies(height), height_delta(height), height_total(height) {}

int RecordsPile::Record::getRecordHeight() 
{
    
    Record* temp = parent;
    int sum = height_delta - copies;
    while(temp)
    {
        sum+=temp->height_delta;
        temp = temp->parent;
    }
    return sum;
}

int RecordsPile::Record::getStackHeight() 
{
    if (parent)
    {
        return parent->getStackHeight();
    }
    return height_total;
}

int RecordsPile::Record::getRecordCopies()
{
    return copies;
}

int RecordsPile::Record::getColumn()
{
    if (parent)
    {
        return parent->getColumn();
    }
    return column;
}

RecordsPile::Record* RecordsPile::Record::getRoot()
{
    if (parent)
    {
        return parent->getRoot();
    }
    return this;   
}

void RecordsPile::Record::setParent(Record* record)
{
    parent = record;
}

void RecordsPile::Record::increaseHeightDelta(int height)
{
    height_delta+=height;
}

void RecordsPile::Record::increaseHeightTotal(int height)
{
    height_total+=height;
}

int RecordsPile::Record::purchase()
{
    return 100 + bought++;
}
