#include <gtest/gtest.h>
#include <fstream>
#include <cstdio>
#include "serializer.h"
#include "array.h"
#include "ForwardList.h"
#include "DoubleList.h"
#include "stack.h"
#include "queue.h"
#include "tree.h"
#include "HashTable.h"
#include "database.h"

// 1. Тесты DynamicArray
TEST(DynamicArrayTest, FullOperationsAndExceptions) {
    DynamicArray arr(2);
    arr.setName("m1");
    EXPECT_STREQ(arr.getName(), "m1");
    EXPECT_EQ(arr.getLength(), 0);

    arr.addToEnd("apple");
    arr.addToEnd("banana");
    arr.addToEnd("cherry"); // вызов resizeIfNeeded
    EXPECT_EQ(arr.getLength(), 3);
    EXPECT_EQ(arr.getElement(1), "banana");

    arr.addAtIndex(1, "orange");
    EXPECT_EQ(arr.getElement(1), "orange");
    arr.setElement(1, "grape");
    EXPECT_EQ(arr.getElement(1), "grape");

    arr.removeAtIndex(1);
    EXPECT_EQ(arr.getLength(), 3);
    arr.print();

    // Проверка исключений при выходе за границы
    EXPECT_THROW(arr.getElement(-1), std::out_of_range);
    EXPECT_THROW(arr.getElement(10), std::out_of_range);
    EXPECT_THROW(arr.setElement(-1, "x"), std::out_of_range);
    EXPECT_THROW(arr.addAtIndex(10, "x"), std::out_of_range);
    EXPECT_THROW(arr.removeAtIndex(10), std::out_of_range);

    // Сохранение и загрузка
    std::ofstream out("test_arr.txt");
    arr.save(out);
    out.close();

    DynamicArray arrLoaded;
    std::ifstream in("test_arr.txt");
    arrLoaded.load(in);
    in.close();
    EXPECT_EQ(arrLoaded.getLength(), 3);
    EXPECT_EQ(arrLoaded.getElement(0), "apple");
    std::remove("test_arr.txt");
}

// 2. Тесты ForwardList
TEST(ForwardListTest, FullOperations) {
    ForwardList fl;
    fl.setName("f1");
    EXPECT_STREQ(fl.getName(), "f1");
    EXPECT_EQ(fl.getFirst(), nullptr);

    // Пустой список
    fl.deleteHead();
    fl.deleteTail();
    EXPECT_FALSE(fl.deleteByValue("none"));

    fl.addToEnd("b");
    fl.addToBeginning("a");
    fl.addToEnd("d");
    Node* nodeB = fl.findNodeByValue("b");
    ASSERT_NE(nodeB, nullptr);
    EXPECT_EQ(fl.findNodeByValue("missing"), nullptr);

    fl.addNode(nodeB, "c");
    fl.addBeforeNode(nodeB, "a2");
    fl.addBeforeNode(fl.getFirst(), "first");
    fl.print();

    fl.deleteHead();
    fl.deleteTail();
    fl.deleteAfterNode(nodeB);
    fl.deleteBeforeNode(nodeB);
    EXPECT_TRUE(fl.deleteByValue("b"));
    EXPECT_FALSE(fl.deleteByValue("b"));

    // Сохранение и загрузка
    std::ofstream out("test_fl.txt");
    fl.save(out);
    out.close();

    ForwardList flLoaded;
    std::ifstream in("test_fl.txt");
    flLoaded.load(in);
    in.close();
    EXPECT_NE(flLoaded.getFirst(), nullptr);
    std::remove("test_fl.txt");

    fl.create("single");
    fl.deleteTail();
    EXPECT_EQ(fl.getFirst(), nullptr);
}

// 3. Тесты DoubleList
TEST(DoubleListTest, FullOperations) {
    DoubleList dl;
    dl.setName("d1");
    EXPECT_STREQ(dl.getName(), "d1");
    EXPECT_EQ(dl.getFirst(), nullptr);

    dl.deleteHead();
    dl.deleteTail();
    EXPECT_FALSE(dl.deleteByValue("none"));

    dl.addToEnd("b");
    dl.addToBeginning("a");
    dl.addToEnd("d");
    DNode* nodeB = dl.findNodeByValue("b");
    ASSERT_NE(nodeB, nullptr);
    EXPECT_EQ(dl.findNodeByValue("missing"), nullptr);

    dl.addAfterNode(nodeB, "c");
    dl.addBeforeNode(nodeB, "a2");
    dl.addBeforeNode(dl.getFirst(), "first");
    dl.print();

    dl.deleteHead();
    dl.deleteTail();
    dl.deleteAfterNode(nodeB);
    dl.deleteBeforeNode(nodeB);
    EXPECT_TRUE(dl.deleteByValue("b"));
    EXPECT_FALSE(dl.deleteByValue("b"));

    std::ofstream out("test_dl.txt");
    dl.save(out);
    out.close();

    DoubleList dlLoaded;
    std::ifstream in("test_dl.txt");
    dlLoaded.load(in);
    in.close();
    EXPECT_NE(dlLoaded.getFirst(), nullptr);
    std::remove("test_dl.txt");

    dl.create("single");
    dl.deleteTail();
    EXPECT_EQ(dl.getFirst(), nullptr);
}

// 4. Тесты Stack и Queue
TEST(StackQueueTest, OperationsAndErrors) {
    Stack st;
    st.setName("s1");
    EXPECT_STREQ(st.getName(), "s1");
    EXPECT_THROW(st.pop(), std::runtime_error);
    EXPECT_THROW(st.peek(), std::runtime_error);

    st.push("first");
    st.push("second");
    EXPECT_EQ(st.peek(), "second");
    st.print();

    std::ofstream outSt("test_st.txt");
    st.save(outSt);
    outSt.close();

    Stack stLoaded;
    std::ifstream inSt("test_st.txt");
    stLoaded.load(inSt);
    inSt.close();
    EXPECT_EQ(stLoaded.pop(), "second");
    EXPECT_EQ(stLoaded.pop(), "first");
    std::remove("test_st.txt");

    Queue q;
    q.setName("q1");
    EXPECT_STREQ(q.getName(), "q1");
    EXPECT_THROW(q.dequeue(), std::runtime_error);
    EXPECT_THROW(q.peek(), std::runtime_error);

    q.enqueue("one");
    q.enqueue("two");
    EXPECT_EQ(q.peek(), "one");
    q.print();

    std::ofstream outQ("test_q.txt");
    q.save(outQ);
    outQ.close();

    Queue qLoaded;
    std::ifstream inQ("test_q.txt");
    qLoaded.load(inQ);
    inQ.close();
    EXPECT_EQ(qLoaded.dequeue(), "one");
    EXPECT_EQ(qLoaded.dequeue(), "two");
    std::remove("test_q.txt");
}

// 5. Тесты AVLTree (все 4 поворота, поиск, удаление, сохранение)
TEST(AVLTreeTest, RotationsSearchRemoveAndPersistence) {
    AVLTree tree;
    tree.setName("t1");
    EXPECT_STREQ(tree.getName(), "t1");
    EXPECT_EQ(tree.getRoot(), nullptr);
    EXPECT_FALSE(tree.remove(10));

    // LL поворот
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    EXPECT_EQ(tree.getRoot()->key, 20);
    tree.create();

    // RR поворот
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    EXPECT_EQ(tree.getRoot()->key, 20);
    tree.create();

    // LR поворот
    tree.insert(30);
    tree.insert(10);
    tree.insert(20);
    EXPECT_EQ(tree.getRoot()->key, 20);
    tree.create();

    // RL поворот
    tree.insert(10);
    tree.insert(30);
    tree.insert(20);
    EXPECT_EQ(tree.getRoot()->key, 20);

    // Сложное дерево и удаление узлов (лист, 1 потомок, 2 потомка)
    int keys[] = {50, 25, 75, 15, 35, 65, 85, 5, 45};
    for (int k : keys) tree.insert(k);
    tree.insert(50); // дубликат
    tree.print();

    EXPECT_TRUE(tree.search(65));
    EXPECT_FALSE(tree.search(999));

    EXPECT_TRUE(tree.remove(5));  // лист
    EXPECT_TRUE(tree.remove(15)); // 1 потомок
    EXPECT_TRUE(tree.remove(50)); // 2 потомка
    EXPECT_FALSE(tree.remove(999));

    std::ofstream out("test_avl.txt");
    tree.save(out);
    out.close();

    AVLTree treeLoaded;
    std::ifstream in("test_avl.txt");
    treeLoaded.load(in);
    in.close();
    EXPECT_TRUE(treeLoaded.search(65));
    EXPECT_EQ(treeLoaded.getCount(), tree.getCount());
    std::remove("test_avl.txt");
}

// 6. Тесты HashTable (цепочки и открытая адресация)
TEST(HashTableTest, ChainAndOpenHashTables) {
    ChainHashTable cht(4);
    cht.setName("cht1");
    EXPECT_STREQ(cht.getName(), "cht1");
    cht.insert("apple");
    cht.insert("banana");
    cht.insert("cherry");
    cht.insert("date");
    cht.insert("apple"); // дубликат
    EXPECT_TRUE(cht.contains("banana"));
    EXPECT_FALSE(cht.contains("fig"));
    cht.print();

    std::ofstream outC("test_cht.txt");
    cht.save(outC);
    outC.close();

    ChainHashTable chtLoaded(4);
    std::ifstream inC("test_cht.txt");
    chtLoaded.load(inC);
    inC.close();
    EXPECT_TRUE(chtLoaded.contains("cherry"));
    std::remove("test_cht.txt");

    EXPECT_TRUE(cht.remove("banana"));
    EXPECT_FALSE(cht.remove("banana"));

    OpenHashTable oht(4);
    oht.setName("oht1");
    EXPECT_STREQ(oht.getName(), "oht1");
    oht.insert("k1");
    oht.insert("k2");
    oht.insert("k3");
    EXPECT_TRUE(oht.contains("k2"));
    EXPECT_FALSE(oht.contains("k9"));
    oht.print();

    std::ofstream outO("test_oht.txt");
    oht.save(outO);
    outO.close();

    OpenHashTable ohtLoaded(4);
    std::ifstream inO("test_oht.txt");
    ohtLoaded.load(inO);
    inO.close();
    EXPECT_TRUE(ohtLoaded.contains("k3"));
    std::remove("test_oht.txt");

    EXPECT_TRUE(oht.remove("k2"));
    EXPECT_FALSE(oht.remove("k2"));
}

// 7. Тесты Database (CLI команды)
TEST(DatabaseTest, CommandsAndFilePersistence) {
    Database db;
    db.processCommand("MPUSHTOEND arr1 val1");
    db.processCommand("FPUSH fl1 val1");
    db.processCommand("LPUSH dl1 val1");
    db.processCommand("SPUSH st1 val1");
    db.processCommand("QPUSH q1 val1");
    db.processCommand("TINSERT tr1 42");
    db.processCommand("TINSERT tr1 20");
    db.processCommand("TDEL tr1 20");
    db.processCommand("HINSERT ht1 key1");
    db.processCommand("PRINT arr1");
    db.processCommand("PRINT tr1");
    db.processCommand("UNKNOWN_CMD test");

    db.saveToFile("test_db_full.txt");
    Database db2;
    db2.loadFromFile("test_db_full.txt");
    db2.processCommand("PRINT ht1");
    std::remove("test_db_full.txt");
}
// 8. Тесты Serializer (текстовый и бинарный форматы)
TEST(SerializerTest, TextAndBinarySerialization) {
    DynamicArray arr;
    arr.setName("arr_ser");
    arr.addToEnd("alpha");
    arr.addToEnd("beta");

    Serializer::saveArrayText(arr, "arr_test.txt");
    DynamicArray arrTxt;
    Serializer::loadArrayText(arrTxt, "arr_test.txt");
    EXPECT_EQ(arrTxt.getLength(), 2);
    EXPECT_EQ(arrTxt.getElement(1), "beta");
    std::remove("arr_test.txt");

    Serializer::saveArrayBinary(arr, "arr_test.bin");
    DynamicArray arrBin;
    Serializer::loadArrayBinary(arrBin, "arr_test.bin");
    EXPECT_EQ(arrBin.getLength(), 2);
    EXPECT_EQ(arrBin.getElement(0), "alpha");
    std::remove("arr_test.bin");

    AVLTree tree;
    tree.setName("tree_ser");
    tree.insert(40);
    tree.insert(20);
    tree.insert(60);

    Serializer::saveTreeText(tree, "tree_test.txt");
    AVLTree treeTxt;
    Serializer::loadTreeText(treeTxt, "tree_test.txt");
    EXPECT_TRUE(treeTxt.search(20));
    std::remove("tree_test.txt");

    Serializer::saveTreeBinary(tree, "tree_test.bin");
    AVLTree treeBin;
    Serializer::loadTreeBinary(treeBin, "tree_test.bin");
    EXPECT_TRUE(treeBin.search(60));
    EXPECT_EQ(treeBin.getCount(), 3);
    std::remove("tree_test.bin");

    ChainHashTable cht(8);
    cht.setName("ht_ser");
    cht.insert("token1");
    cht.insert("token2");
    Serializer::saveHashBinary(cht, "ht_test.bin");
    ChainHashTable chtBin(8);
    Serializer::loadHashBinary(chtBin, "ht_test.bin");
    EXPECT_TRUE(chtBin.contains("token1"));
    EXPECT_TRUE(chtBin.contains("token2"));
    std::remove("ht_test.bin");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
