#ifndef __RECORDSPILE_H__
#define __RECORDSPILE_H__


class RecordsPile
{
public:
    //Junk c'tor
    RecordsPile();

    //Big 3
    ~RecordsPile();
    RecordsPile(const RecordsPile& other);
    RecordsPile& operator=(const RecordsPile& other);

    //Real c'tor
    RecordsPile(int* records_stock, int number_of_records);

    //Piles id1's stack on top of id 2's stack
    //O(log*n)
    void pileOnTop(int id1, int id2);

    //Return column of the record
    //O(log*n)
    int getColumn(int id);

    //Return the height of the record
    //O(1) if done right after getColumn
    int getHeight(int id);

    //Returns the current cost of the record (100+bought) and increment cost
    //O(1)
    int purchase(int id);
    class Record;

private:

    //Unionfind union on 2 parameter roots
    //O(1) (when given pointers to roots)
    void Union(Record* root1, Record* root2);

    //Unionfind find
    //Also updates heights of everything when shortening the way
    //O(log* n)
    Record* find(int id);


    Record* m_pile;
    int m_count;
};

struct RootDelta //Struct for return root alongside delta height from getRoot()
{
    RootDelta(int delta, RecordsPile::Record* root): delta(delta), root(root) {}
    int delta;
    RecordsPile::Record* root;
};

class RecordsPile::Record
{
public:

    //Junk C'tor for array initialize
    Record() {};

    //C'tor
    Record(int height, int id);

    //Return the height of the record by adding up the delta height on the path to the root.
    int getRecordHeight();

    //Returns the root of the node's reverse tree
    //Shortens the path of all nodes along the way and updates heights
    RootDelta getRoot();
    

    Record* parent; //Record's parent / next node in reverse tree
    int delta; //Height of the record relative to its parent's height for non root, absolute height for root
    int cost; // cost of the record (starts at 100 and goes up every time a record is bought)

    //All 3 stack fields are only "active" (as in updated and relevant) for root records
    int stack_height; //Stack's total height
    int stack_column; //Stack's column
    int stack_count; //Stack's total record count
};



#endif // __RECORDSPILE_H__

