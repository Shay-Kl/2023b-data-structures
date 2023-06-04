
#include "recordsCompany.h"

RecordsCompany::RecordsCompany(): m_members() {}

RecordsCompany::~RecordsCompany() {}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    //Record related code
    m_members.resetExpenses();
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
    Customer* customer;
    //customer = customers.get(c_id)
    m_members.insert(customer);
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
    if (amount <=0 || c_id1 < 0 || c_id2 < c_id1)
    {
        return StatusType::INVALID_INPUT;
    }
    
    m_members.addPrize(c_id1, c_id2, amount);
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
