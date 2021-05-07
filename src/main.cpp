#include <iostream>
#include "../include/utils.h"
#include "../include/exercises.h"
#include "../include/algo.h"
#include "../include/ds.h"

#define newline std::cout << std::endl;

int main() {
    /*
    partI::exercise1("../data/agn.us.txt");
    partI::exercise1("../data/ainv.us.txt");
    partI::exercise1("../data/ale.us.txt");
    newline
    newline
    partI::exercise2("../data/agn.us.txt");
    std::cout << std::endl;
    partI::exercise2("../data/ainv.us.txt");
    std::cout << std::endl;
    partI::exercise2("../data/ale.us.txt");
    newline
    partI::exercise3();
    partI::exercise4();
     */
//    utils::stock::StockDayVolume s1 = {"2005-05-05", 10}, s2 = {"2007-01-01", 50}, s3 = {"2003-04-04", 10}, s4 = {"2010-02-02", 90};

    ds::AVLTree<int> tree;
    tree.insert(10);
    tree.printInOrder();
    newline
    tree.insert(20);
    tree.printInOrder();
    newline
    tree.insert(30);
    tree.printInOrder();
    newline
    tree.insert(40);
    tree.printInOrder();
    newline
    tree.insert(50);
    tree.printInOrder();
    newline
    tree.insert(25);
    tree.printInOrder();


    return 0;
}
