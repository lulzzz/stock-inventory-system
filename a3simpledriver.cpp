// File:        a3simpledriver.cpp
// Author:      Geoffrey Tien
// Date:        2016-06-05
// Description: Test driver for RBTree and StockSystem classes
//              Only basic cases for RBTree are tested. You are responsible
//              for adding your own code to thoroughly test your RBTree class.
//              See PDF specification for tips for testing your tree structure using
//              pre-order traversal.

#include <iostream>
#include <cstdlib>
#include <string>

#include "rbtree.h"
#include "stocksystem.h"

using namespace std;

// forward declarations

void PrintMenu();
void RBTreeTest();

// program entry point
int main()
{
  RBTreeTest();

  int choice = 0;
  string inputchoice;
  int asku;
  string inputasku;
  string adesc;
  double aprice;
  string inputaprice;
  int amount;
  string inputamt;
  string ctlg = "";

  StockSystem mystore;

  while (choice != 8)
  {
    PrintMenu();
    // get the menu choice from standard input
    getline(cin, inputchoice);
    choice = atoi(inputchoice.c_str());

    switch (choice)
    {
      case 1: // Print balance
        cout << "Funds: $" << mystore.GetBalance() << endl << endl;
        break;
      case 2: // Print catalogue
        ctlg = mystore.GetCatalogue();
        cout << ctlg << endl;
        break;
      case 3: // Add SKU
        cout << "Enter a numeric SKU (will be converted to 5 digits): ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter item description: ";
        getline(cin, adesc);
        cout << "Enter a retail price: $";
        getline(cin, inputaprice);
        aprice = atof(inputaprice.c_str());
        if (mystore.StockNewItem(StockItem(asku, adesc, aprice)))
          cout << "Successfully added item to catalogue." << endl;
        else
          cout << "Item not added to catalogue." << endl;
        break;
      case 4: // Edit item description
        cout << "Enter a numeric SKU to edit: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter item description: ";
        getline(cin, adesc);
        if (mystore.EditStockItemDescription(asku, adesc))
          cout << "Item successfully updated." << endl;
        else
          cout << "Item not updated." << endl;
        break;
      case 5: // Edit item price
        cout << "Enter a numeric SKU to edit: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter a retail price: $";
        getline(cin, inputaprice);
        aprice = atof(inputaprice.c_str());
        if (mystore.EditStockItemPrice(asku, aprice))
          cout << "Item successfully updated." << endl;
        else
          cout << "Item not updated." << endl;
        break;
      case 6: // Restock an item
        cout << "Enter a numeric SKU to purchase: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter a quantity to purchase: ";
        getline(cin, inputamt);
        amount = atoi(inputamt.c_str());
        cout << "Enter the per-unit purchase price: $";
        getline(cin, inputaprice);
        aprice = atof(inputaprice.c_str());
        if (mystore.Restock(asku, amount, aprice))
          cout << "Item successfully restocked." << endl;
        else
          cout << "Item not restocked." << endl;
        break;
      case 7: // Sell an item
        cout << "Enter the SKU of item to sell: ";
        getline(cin, inputasku);
        asku = atoi(inputasku.c_str());
        cout << "Enter a quantity to sell: ";
        getline(cin, inputamt);
        amount = atoi(inputamt.c_str());
        if (mystore.Sell(asku, amount))
          cout << "Transaction complete. Have a nice day." << endl;
        else
          cout << "Item is out of stock. Sorry!" << endl;
        break;
      case 8: // Quit
        // no need to do anything, will cause while loop to break
        break;
      default:
        cout << "Invalid choice." << endl;
        break;
    }
  }

  return 0;
}

void PrintMenu()
{
  cout << "****************************************************\n"
       << "* Please select an option:                         *\n"
       << "* 1. Print balance             6. Restock an item  *\n"
       << "* 2. Print catalogue           7. Sell an item     *\n"
       << "* 3. Add a new SKU                                 *\n"
       << "* 4. Edit item description                         *\n"
       << "* 5. Edit item price           8. Quit             *\n"
       << "****************************************************\n" << endl;
  cout << "Enter your choice: ";
}

void RBTreeTest()
{
  RBTree<int> tree1;

  tree1.Insert(10);
  tree1.Insert(1);
  tree1.Insert(5); // should cause 2 rotations to occur
  tree1.Insert(4);
  tree1.Insert(3);
  tree1.Insert(8);
  tree1.Insert(2);
  tree1.Insert(6);
  tree1.Insert(7);
  tree1.Insert(9);
  tree1.Insert(11);
  tree1.Insert(12);
  tree1.Insert(13);
  tree1.Insert(14);
  tree1.Insert(15);
  tree1.Insert(16);
  tree1.Insert(17);
  tree1.Insert(18);
  tree1.Insert(19);
  tree1.Insert(20);
  int size = tree1.Size();
  tree1.DumpPreOrder(size);
  cout << "Tree contains " << tree1.Size() << " entries." << endl;
  tree1.Remove(5);
  tree1.Remove(4);
  tree1.Remove(14);
  tree1.Remove(10);
  tree1.Remove(9);
  tree1.Remove(8);
  tree1.Remove(7);
  tree1.Remove(6);
  tree1.Remove(16);
  int size2 = tree1.Size();
  tree1.DumpPreOrder(size2);

  cout << "Tree contains " << tree1.Size() << " entries." << endl;
  cout << "Tree height: " << tree1.Height() << endl;

  RBTree<int> tree2(tree1);
  int copySize = tree2.Size();
  cout << copySize << endl;
  cout << tree2.Height() << endl;
  tree2.DumpPreOrder(copySize);

  tree1.RemoveAll();

  RBTree<int> tree3;
  tree3.Insert(5);
  tree3 = tree2;
  int tree3Size = tree3.Size();
  tree3.DumpPreOrder(tree3Size);
}
