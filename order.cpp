 #include "order.h"

using namespace orderInfo;

//Constructor
order::order(int customerID, int orderID) : dropOff(), pickUp(3), _laundry(),  _dryClean(), _alterations() {
    _customerID = customerID;
    _orderID = orderID;
    _total = 0;
    _rackNumber = -1;
    _pickedUp = false;
    _pieceTotal = 0;
    _discountApplied = false;
    _discount = 0.00;
    _discountedCost = 0.00;

    _taxable = false;
    _tax = 0.00;
    _finalTotal = 0.00;

    _deposit = 0.00;
    _voidOrder = false;
}

//Constructor used when loading in orders from orderFile into the program memory
order::order(const Params& params) :
    _customerID(params.customerID),
    _orderID(params.orderID),
    _laundry(params.laundry),
    _dryClean(params.dryClean),
    _alterations(params.alterations),
    _total(params.total),
    _finalTotal(params.finalTotal),
    _rackNumber(params.rack),
    _pickedUp(params.pickedUp),
    _paid(params.paid),
    _pieceTotal(params.pieceTotal),
    _discountApplied(params.discountApplied),
    _discount(params.discount),
    _discountedCost(params.discountedCost),

    _taxable(params.taxable),
    _tax(params.tax),

    _deposit(params.deposit),
    _voidOrder(params.voidOrder)
{

    if(params.orderID != -1) //set -1 to a #defined
        _orderID = params.orderID;
    else
        _orderID = std::nullopt;
}



/*Set Functions*/
int order::setCustomerID(int id){
    this->_customerID = id;
    return 0;
}

float order::calculateSubTotal(void){
    _total = 0;

    _total += _laundry.calculateTotalPrice();
    _total += _dryClean.calculateTotalPrice();
    _total += _alterations.calculateTotalPrice();

    return _total;
}

int order::calculatePieceTotal(){
    _pieceTotal = 0;

    _pieceTotal += _laundry.calculatePieceTotal();
    _pieceTotal += _dryClean.calculatePieceTotal();
    _pieceTotal += _alterations.calculatePieceTotal();

    return _pieceTotal;
}

float order::applyDiscount(){
    if(_discountApplied) // = true;
        _discountedCost = _total - (_total * (_discount/100.0));
    else
        _discountedCost = _total;
    return _discountedCost;
}

void order::voidOrder(){
    _orderID = std::nullopt;
    _customerID = -1;

    _laundry.voidOrder();
    _dryClean.voidOrder();
    _alterations.voidOrder();

    _total = -1;
    _rackNumber = 0;
    _paid = false;
    _pieceTotal = -1;

    _discountApplied = false;
    _discount = -1;
    _discountedCost = -1;
    _deposit = -1;
}

float order::calculateFinalTotal(){

    float tempTotal;

    if(_discountApplied)
        _finalTotal = _total - (_total * (_discount/100.0));
    else
        _finalTotal = _total;

    tempTotal = _finalTotal;

    if(_taxable){
        set_calculateTax();
        _finalTotal = tempTotal + _tax;
    }
    else
        _finalTotal = tempTotal;

    return _finalTotal;
}
