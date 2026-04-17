#ifndef ORDER_H
#define ORDER_H

#include "main.h"
#include "date.h"
#include "pieces.h"
#include "service.h"
#include <optional>


namespace orderInfo{
    class order{
        public:
            struct Params{
                std::optional<int> orderID;
                int customerID;

                services::serviceOrder laundry;
                services::serviceOrder dryClean;
                services::serviceOrder alterations;

                float total;
                int rack;
                bool pickedUp;
                bool paid;
                int pieceTotal;
                bool discountApplied;
                float discount;
                float discountedCost;

                bool taxable;
                float tax;
                float finalTotal;

                float deposit;
                bool voidOrder;

                date::Date dropOff;
                date::Date pickUp;

            };

            //Constructor
            //Order created in drop off page
            order(int customerID, int orderID);

            order(std::optional<int> orderID); //creating a null order


            //Loads orders at the start of program
            order(const Params& params);

            order(int orderID, int customerID, float cost, int rack, bool pickedUp, bool paid, int pieceTotal, bool discountApplied, float discount, float discountedCost, bool taxable, float tax, float deposit, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, int, float>>> laundry, std::vector<std::vector<std::tuple<std::string, int, float>>> dryClean, std::vector<std::vector<std::tuple<std::string, int, float>>> alterations);
            order(int orderID, int customerID, float cost, int rack, bool pickedUp, bool paid, int pieceTotal, bool discountApplied, float discount, float discountedCost, bool taxable, float tax, float deposit, int dropOffDay, int dropOffMonth, int dropOffYear, int dropOffHour, int dropOffMin, std::string dropOffAm_Pm, int pickUpDay, int pickUpMonth, int pickUpYear, int pickUpHour, int pickUpMin, std::string pickUpAm_Pm, std::vector<std::vector<std::tuple<std::string, std::string, int, float>>> laundry, std::vector<std::vector<std::tuple<std::string, std::string, int, float>>> dryClean, std::vector<std::vector<std::tuple<std::string, std::string, int, float>>> alterations);

            //~order();

            //Get functions, set to const to insure that data isn't being changed
            int getCustomerID() const {return _customerID;}
            std::optional<int> getOrderID() const {return _orderID;}

            services::serviceOrder getLaundry() const {return _laundry;}
            services::serviceOrder getDryClean() const {return _dryClean;}
            services::serviceOrder getAlterations() const {return _alterations;}

            float getCost() const {return _total;}
            int getRack() const {return _rackNumber;}
            bool getPickUp() const {return _pickedUp;}
            bool getPaid() const {return _paid;}
            int getPieceTotal() const {return _pieceTotal;}
            bool getDiscountApplied() const {return _discountApplied;}
            float getDiscount() const {return _discount;}
            float getDiscountedCost() {return applyDiscount();}
            bool getTaxable() const {return _taxable;}
            float getTax() const {return _tax;}
            float getDeposit() const {return _deposit;}

            //Set functions
            int setCustomerID(int id);

            void setLaundry(services::serviceOrder laundry) {_laundry = laundry;}
            void addLaundryPiece(std::string typeName, int typeID, pieces::piece piece, int pieceCount) {_laundry.addPiece(typeName, typeID, piece, pieceCount); calculatePieceTotal();}

            void setDryClean(services::serviceOrder dryClean) {_dryClean = dryClean;}
            void addDryCleanPiece(std::string typeName, int typeID, pieces::piece piece, int pieceCount) {_dryClean.addPiece(typeName, typeID, piece, pieceCount); calculatePieceTotal();}

            void setAlterations(services::serviceOrder alterations) {_alterations = alterations;}
            void addAlterationsPiece(std::string typeName, int typeID, pieces::piece piece, int pieceCount) {_alterations.addPiece(typeName, typeID, piece, pieceCount); calculatePieceTotal();}

            void setTotal(float total) {_total = total;}
            void setRack(int rack) {_rackNumber = rack;}
            void setPickUp(bool pickUp) {_pickedUp = pickUp;}
            void setPaid(bool paid) {_paid = paid;}
            void setPieceTotal(int pieceTotal) {_pieceTotal = pieceTotal;}
            void setDiscountApplied(bool applied) {_discountApplied = applied;}
            void setDiscount(float disc) {_discount = disc;}
            void setDiscountedCost(float discountedCost) {_discountedCost = discountedCost;}
            void setTaxable(bool taxable) {_taxable = taxable;}
            void setTax(bool tax) {_tax = tax;}
            void setDeposit(float deposit) {_deposit = deposit;}

            //Helper functions
            float calculateSubTotal(); //Add tax information to this
            int calculatePieceTotal(); //Add tax information to this
            float applyDiscount();
            bool verifyOrderIDs();
            float calculateFinalTotal();
            void set_calculateTax(){if(_taxable) _tax = (_total * .09375);}
            void taxReset();
            void voidOrder();

            //order& operator=(const order& other);

            //Dates
            date::Date dropOff;
            date::Date pickUp;

        private:
            int _customerID;
            std::optional<int> _orderID;

            services::serviceOrder _laundry;
            services::serviceOrder _dryClean;
            services::serviceOrder _alterations;

            float _total; //Cost
            float _finalTotal;
            int _rackNumber;
            bool _pickedUp;
            bool _paid;
            int _pieceTotal;

            bool _discountApplied;
            float _discount;

            float _discountedCost;

            bool _taxable;
            float _tax;

            float _deposit;
    };
}

#endif
