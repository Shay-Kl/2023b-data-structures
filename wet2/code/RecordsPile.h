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
    void pileOnTop(int id1, int id2);

    //Return the height of the record
    int getHeight(int id);

    //Return column of the record
    int getColumn(int id);

    //Returns the current cost of the record (100+bought) and increment bought
    int purchase(int id);

private:
    class Record;
    Record* m_pile;
    int m_count;
};


class RecordsPile::Record
{
public:

    //Junk C'tor for array initialize
    Record() {};

    //C'tor
    Record(int height, int id);

    //Return the height of the record
    int getRecordHeight();

    //Returns the total height of the record's stack
    int getStackHeight();

    //Returns the number of copies of the record
    int getRecordCopies();

    //Returns the record's column
    int getColumn();

    //Returns the root of the node's reverse tree
    Record* getRoot();

    //Increase the record's height delta by a given amount
    void increaseHeightDelta(int height);

    //Increase the record's height delta by a given amount
    void increaseHeightTotal(int height);
    
    //Returns the current cost of the record (100+bought) and increment bought
    int purchase();

    //Sets the node's parent to a given record
    void setParent(Record* record);

private:
    Record* parent; //Record's parent / next node in reverse tree
    int bought; // Number of copies of record bought (only relevant for price calculation)
    
    int copies; //The number of copies of the record, dictates how high the record is.
    int height_delta; //Height of the record relative to its parent's height

    int height_total; //Height of the record's stack, only active for root records
    int column; //Node's column, only active for root records
};
#endif // __RECORDSPILE_H__