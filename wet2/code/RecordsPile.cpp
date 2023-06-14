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
    if (id1 >= m_count || id2 >= m_count)
    {
        throw KeyMissing();
    }
    
    Record* root1 = m_pile[id1].getRoot().root;
    Record* root2 = m_pile[id2].getRoot().root;
    if (root1==root2)
    {
        throw Failiure();
    }
    

    //if(root1->stack_count < root2->stack_count)
    {
        root2->stack_count+=root1->stack_count;
        root1->height_delta+= root2->height_total-root2->copies;
        root2->height_total+=root1->height_total;
        root1->setParent(root2);
    }
    /*
    else
    {
        root1->column = root2->column;
        root1->stack_count+=root2->stack_count;
        root1->height_total+=root2->height_total;
        root2->setParent(root1);
        root1->height_delta+= root2->height_total;
        root2->height_delta-=root1->height_delta;
    }
    */
}

int RecordsPile::purchase(int id)
{
    if (id >= m_count)
    {
        throw KeyMissing();
    }
    return m_pile[id].purchase();
}

int RecordsPile::getColumn(int id)
{
    if (id >= m_count)
    {
        throw KeyMissing();
    }
    return m_pile[id].getRoot().root->column;
}

int RecordsPile::getHeight(int id)
{
    if (id >= m_count)
    {
        throw KeyMissing();
    }
    
    return m_pile[id].getRecordHeight();
}

RecordsPile::Record::Record(int height, int id): parent(nullptr), cost(100), copies(height), height_delta(height), height_total(height), column(id), stack_count(1) {}

int RecordsPile::Record::getRecordHeight() 
{
    
    Record* temp = parent;
    int height = height_delta-copies;
    while(temp)
    {
        height+=temp->height_delta;
        temp = temp->parent;
    }
    return height;
}

RootDelta RecordsPile::Record::getRoot(){
    if (parent)
    {
        RootDelta rd = parent->getRoot();
        parent = rd.root;
        height_delta+=rd.delta;
        return RootDelta(height_delta, rd.root);
    }
    return RootDelta(0, this);
}

void RecordsPile::Record::setParent(Record* record)
{
    parent = record;
}

int RecordsPile::Record::purchase()
{
    return cost++;
}
