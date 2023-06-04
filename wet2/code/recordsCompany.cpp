
#include "recordsCompany.h"
#include "exceptions.h"

RecordsCompany::RecordsCompany(): m_members() {}

RecordsCompany::~RecordsCompany() {}

StatusType RecordsCompany::newMonth(int *records_stocks, int number_of_records)
{
    if (number_of_records < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        //Initialize records unionfind
        m_members.resetExpenses();
        return StatusType::SUCCESS;
    }
    catch(bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    
}

StatusType RecordsCompany::addCostumer(int c_id, int phone)
{
    if (c_id < 0 || phone < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        //customers.insert(new Customer(c_id, phone));
        return StatusType::SUCCESS;
    }
    catch(KeyAlreadyExists)
    {
        return StatusType::ALREADY_EXISTS;
    }
    catch(bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

Output_t<int> RecordsCompany::getPhone(int c_id)
{
    if(c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        //Customer* customer = customers.get(c_id);
        // return customer.getPhone();
        return 0;
    }
    catch(KeyMissing)
    {
        return StatusType::DOESNT_EXISTS;
    }
}

StatusType RecordsCompany::makeMember(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        Customer* customer;
        //customer = customers.get(c_id);
        m_members.insert(customer);
        customer->makeMember();
        return StatusType::SUCCESS;
    }
    catch(KeyAlreadyExists)
    {
        return StatusType::ALREADY_EXISTS;
    }
    catch(KeyMissing)
    {
        return StatusType::DOESNT_EXISTS;
    }
    catch(bad_alloc)
    {
        return StatusType::ALLOCATION_ERROR;
    }
}

Output_t<bool> RecordsCompany::isMember(int c_id)
{
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        //Customer* customer = customers.get(c_id)
        //return customer.isMember();
        return true;
    }
    catch(KeyMissing)
    {
        return StatusType::DOESNT_EXISTS;
    }
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
    if (c_id < 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        Customer& customer = m_members.get(c_id);
        return customer.getExpenses();
    }
    catch(KeyMissing)
    {
        return StatusType::DOESNT_EXISTS;
    }
}




//Record related, to be implemented

StatusType RecordsCompany::buyRecord(int c_id, int r_id)
{
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::putOnTop(int r_id1, int r_id2)
{
    return StatusType::SUCCESS;
}

StatusType RecordsCompany::getPlace(int r_id, int *column, int *hight)
{
    return StatusType::SUCCESS;
}
