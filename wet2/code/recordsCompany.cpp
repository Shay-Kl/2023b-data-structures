
#include "recordsCompany.h"

RecordsCompany::RecordsCompany() {}

RecordsCompany::~RecordsCompany() {}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    return StatusType::SUCCESS;
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    return 0;
}

StatusType RecordsCompany::makeMember(int c_id)
{
    return StatusType::SUCCESS;
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    return true;
}

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::addPrize(int c_id1, int c_id2, double  amount)
{
    return StatusType::SUCCESS;
}

Output_t<double> RecordsCompany::getExpenses(int c_id)
{
    return 0.0;
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    return StatusType::SUCCESS;
}
