#ifdef _STOCKSYSTEM_H_
#include "stocksystem.h"
#include <iostream>

using namespace std;

StockSystem::StockSystem() {
	balance = 100000;
}

double StockSystem::GetBalance() {
	return balance;
}

bool StockSystem::StockNewItem(StockItem item) {
	if (item.GetPrice() < 0) {
		return false;
	}

	if (records.Insert(item)) {
		return true;
	}

	else {
		return false;
	}
	
}

bool StockSystem::EditStockItemDescription(int itemsku, string desc) {
	StockItem* item = new StockItem(itemsku, "", 0.0);
	StockItem* retrieval = records.Retrieve(*item);

	if (retrieval != NULL) {
		retrieval->SetDescription(desc);
		return true;
	}

	else {
		return false;
	}
}

bool StockSystem::EditStockItemPrice(int itemsku, double retailprice) {
	StockItem* item = new StockItem(itemsku, "", 0.0);
	StockItem* retrieval = records.Retrieve(*item);

	if (retrieval != NULL) {
		if (retailprice < 0) {
			return false;
		}

		else {
			retrieval->SetPrice(retailprice);
			return true;
		}
	}

	else {
		return false;
	}
}

bool StockSystem::Restock(int itemsku, int quantity, double unitprice) {
	cout << "Entering..." << endl;
	StockItem* item = new StockItem(itemsku, "", 0.0);
	StockItem* retrieval = records.Retrieve(*item);
	int totalCost = quantity * unitprice;
	

	if (retrieval != NULL) {
		int stock = retrieval->GetStock();
		if (balance >= totalCost) {
			if (stock + quantity <= 1000) {
				retrieval->SetStock(stock + quantity);
				balance -= totalCost;
				return true;
			}

			else {
				retrieval->SetStock(1000);
				balance -= (1000 - stock) * unitprice;
				return true;
			}
	}
}

	if (totalCost < 0) {
		return false;
	}


	else {
		cout << "No retrieval!" << endl;
		return false;
	}

	return false;
}

bool StockSystem::Sell(int itemsku, int quantity) {
	StockItem* item = new StockItem(itemsku, "", 0.0);
	StockItem* retrieval = records.Retrieve(*item);

	if (retrieval != NULL) {
		int stock = retrieval->GetStock();
		double price = retrieval->GetPrice();
		if (stock > 0 && quantity >= 0) {
			if (quantity > stock) {
				retrieval->SetStock(0);
				balance += stock * price;
				return true;
			}

			else {
				int newQuantity = stock - quantity;
				retrieval->SetStock(newQuantity);
				balance += quantity * price;
				return true;
			}
		}
	}

	return false;
}

#endif