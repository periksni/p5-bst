#include "BinarySearchTree.hpp"
#include "unit_test_framework.hpp"


TEST(test_empty_tree) {
    BinarySearchTree<int> tree;
    ASSERT_TRUE(tree.empty());
    ASSERT_EQUAL(tree.height(), 0);
    ASSERT_EQUAL(tree.size(), 0);
    ASSERT_TRUE(tree.begin() == tree.end());
    ASSERT_TRUE(tree.find(5) == tree.end());
    ASSERT_TRUE(tree.min_element() == tree.end());
    ASSERT_TRUE(tree.max_element() == tree.end());
    ASSERT_TRUE(tree.min_greater_than(10) == tree.end());
}

TEST(test_insert_bomboclat) {
    BinarySearchTree<int>christmas;
    christmas.insert(10);
    christmas.insert(5);
    christmas.insert(3);
    christmas.insert(4);

    ASSERT_FALSE(christmas.empty());
    ASSERT_EQUAL(christmas.size(), 4);
    ASSERT_EQUAL(christmas.height(), 4)
    
    ASSERT_TRUE(christmas.find(10) != christmas.end());
    ASSERT_TRUE(christmas.find(5) != christmas.end());
    ASSERT_TRUE(christmas.find(3) != christmas.end());

    ASSERT_EQUAL(*christmas.min_element(), 3);
    ASSERT_EQUAL(*christmas.max_element(), 10);
}

TEST(test_sorting_invariant_when_correct) {
    BinarySearchTree<int> pine;

    pine.insert(20);
    pine.insert(10);
    pine.insert(30);
    pine.insert(5);
    pine.insert(15);

    ASSERT_TRUE(pine.check_sorting_invariant());
}

TEST(test_sorting_invariant_invalid_tree) {
    BinarySearchTree<int> oak;

    oak.insert(10);
    oak.insert(5);
    oak.insert(20);

    *oak.begin() = 11;

    ASSERT_FALSE(oak.check_sorting_invariant());
}

TEST(test_sorting_invariant_sucks) {
    BinarySearchTree<int> maple;
    maple.insert(10);
    maple.insert(5);
    maple.insert(16);
    maple.insert(20);

    auto it = maple.begin();
    ++it;
    ++it;

    *it = 9;

    ASSERT_FALSE(maple.check_sorting_invariant());
}

TEST(test_min_greater_than_edgerallenpoe) {
    BinarySearchTree<int> tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(12);

    auto it_h = tree.min_greater_than(1);
    ASSERT_TRUE(it_h != tree.end());
    ASSERT_EQUAL(*it_h, 5);

    auto it_he = tree.min_greater_than(10);
    ASSERT_TRUE(it_he != tree.end());
    ASSERT_EQUAL(*it_he, 12);

    auto it_hel = tree.min_greater_than(11);
    ASSERT_TRUE(it_hel != tree.end());
    ASSERT_EQUAL(*it_hel, 12);

    auto it_help = tree.min_greater_than(20);
    ASSERT_TRUE(it_help == tree.end());
}

TEST(test_traversals) {
    BinarySearchTree<int> tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(14);
    
    std::ostringstream uss_inorder;
    tree.traverse_inorder(uss_inorder);
    // Should be : 1 3 6 8 10 14 
    ASSERT_EQUAL(uss_inorder.str(), "1 3 6 8 10 14 ");
    
    std::ostringstream uss_preorder;
    tree.traverse_preorder(uss_preorder);
    // Should be : 8 3 1 6 10 14
    ASSERT_EQUAL(uss_preorder.str(), "8 3 1 6 10 14 ");
}

TEST(test_copy_constructor) {
    BinarySearchTree<int> birch; 
    birch.insert(10);
    birch.insert(5);
    birch.insert(15);

    BinarySearchTree<int> copy(birch);

    ASSERT_FALSE(copy.empty());
    ASSERT_EQUAL(copy.size(), 3);
    ASSERT_TRUE(copy.find(10) != copy.end());
    ASSERT_TRUE(copy.find(5) != copy.end());
    ASSERT_TRUE(copy.find(15) != copy.end());

    copy.insert(20);
    copy.insert(3);

    ASSERT_TRUE(copy.find(20) != copy.end());
    ASSERT_TRUE(copy.find(3) != copy.end());

    ASSERT_TRUE(birch.find(20) == birch.end());
    ASSERT_TRUE(birch.find(3) == birch.end());
}

TEST(test_empty_constructor) {
    BinarySearchTree<int> sadtree;
    BinarySearchTree<int> copy(sadtree);

    ASSERT_TRUE(copy.empty());
    ASSERT_EQUAL(copy.size(),0);
    ASSERT_TRUE(copy.begin() == copy.end());

}

TEST(test_copy_constructor_fellow) {
    BinarySearchTree<int> spruce;
    spruce.insert(10);
    spruce.insert(5);
    spruce.insert(15);
    spruce.insert(2);
    spruce.insert(7);

    // Height of this BST is 3 if inserted in this order
    ASSERT_EQUAL(spruce.height(), 3);
    ASSERT_EQUAL(spruce.size(), 5);

    BinarySearchTree<int> copy(spruce);

    // Copy MUST have same size and height
    ASSERT_EQUAL(copy.size(), 5);
    ASSERT_EQUAL(copy.height(), 3);

    // Modify the copy
    copy.insert(20);
    copy.insert(1);

    // Now size must diverge
    ASSERT_EQUAL(copy.size(), 7);
    ASSERT_EQUAL(spruce.size(), 5);

    // And heights also diverge
    ASSERT_TRUE(copy.height() != spruce.height());
}

TEST(test_copy_constructor_right_side) {
    BinarySearchTree<int> tea;

    tea.insert(1);
    tea.insert(2);
    tea.insert(3);
    tea.insert(4);
    tea.insert(5);

    BinarySearchTree<int> copy(tea);

    // Check ALL values appear in copy
    for (int i = 1; i <= 5; ++i) {
        ASSERT_TRUE(copy.find(i) != copy.end());
    }

    // Sizes must match
    ASSERT_EQUAL(tea.size(), copy.size());
}



TEST_MAIN()
