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
    
    Record* root1 = find(id1);
    Record* root2 = find(id2);
    if (root1==root2)
    {
        throw Failiure();
    }
    
    Union(root1, root2);

    if(root1->stack_count < root2->stack_count)
    {
        root1->delta+= root2->stack_height - root2->delta;
        root2->stack_height+= root1->stack_height;
    }
    else
    {
        root1->delta += root2->stack_height; //increase the height of root 1's stack appropriately
        root2->delta -= root1->delta; //Without increasing the height of root 2's stack
        root1->stack_column = root2->stack_column;
        root1->stack_height+=root2->stack_height;
    }
}

int RecordsPile::purchase(int id)
{
    if (id >= m_count)
    {
        throw KeyMissing();
    }
    return m_pile[id].cost++;
}

int RecordsPile::getColumn(int id)
{
    if (id >= m_count)
    {
        throw KeyMissing();
    }
    return m_pile[id].getRoot().root->stack_column;
}

int RecordsPile::getHeight(int id)
{
    if (id >= m_count)
    {
        throw KeyMissing();
    }
    
    return m_pile[id].getRecordHeight();
}
void RecordsPile::Union(Record* root1, Record* root2)
{
    if(root1->stack_count < root2->stack_count)
    {
        Record* temp = root1;
        root1 = root2;
        root2 = temp;
    }

    root1->parent = root2;
    root2->stack_count+=root1->stack_count;
    root1->parent = root2;
}

RecordsPile::Record* RecordsPile::find(int id)
{
    return m_pile[id].getRoot().root;
}

RecordsPile::Record::Record(int height, int id):  parent(nullptr), delta(0), cost(100), stack_height(height), stack_column(id), stack_count(1){}

int RecordsPile::Record::getRecordHeight() 
{
    if (parent)
    {
        return delta + parent->getRecordHeight();
    }
    return delta;
}

RootDelta RecordsPile::Record::getRoot(){
    if (parent)
    {
        RootDelta rd = parent->getRoot();
        parent = rd.root;
        delta+=rd.delta;
        return RootDelta(delta, rd.root);
    }
    return RootDelta(0, this);
}
