//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     FILIP JANUSKA <xjanus11@stud.fit.vutbr.cz>
// $Date:       $2020-17-02
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author FILIP JANUSKA
 * 
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"


//Testovaci trida prazdneho stromu
class EmptyTree : public ::testing::Test
{
	protected:
		BinaryTree Empty;

};

//Testovaci trida naplneneho stromu
class NonEmptyTree : public ::testing::Test
{
	protected:
		BinaryTree NonEmpty;
		void SetUp()
		{
			
			for (int i = -10; i <= 10; ++i)
			{
				NonEmpty.InsertNode(i);
			}
		}
};


//Testovaci trida pro axiomy
class TreeAxioms : public ::testing::Test
{
	protected:
		BinaryTree AxiomTree;
		void SetUp()
		{
			for (int i = -100; i <= 100; ++i)
			{
				AxiomTree.InsertNode(i);
			}
		}
};

//Testy prazdneho stromu

TEST_F(EmptyTree, InsertNode)
{
		
	//kontrola vlozeni prvku
	std::pair<bool, BinaryTree::Node_t *> insert_e = Empty.InsertNode(1);
	BinaryTree::Node_t *node1 = insert_e.second;
	ASSERT_FALSE(node1 == NULL);
	EXPECT_TRUE(insert_e.first);
	EXPECT_EQ(Empty.GetRoot(), node1);
	EXPECT_EQ(1, node1->key);
	EXPECT_EQ(BLACK, node1->color);
	EXPECT_FALSE(node1->pLeft == NULL);
	EXPECT_FALSE(node1->pRight == NULL);
	
	//kontrola leveho potomka
	BinaryTree::Node_t *left1 = node1->pLeft;
	ASSERT_FALSE(left1 == NULL);
	EXPECT_TRUE(left1->pLeft == NULL);
	EXPECT_TRUE(left1->pRight == NULL);
	EXPECT_EQ(BLACK, left1->color);
	EXPECT_TRUE(left1->pParent == node1);

	//kontrola praveho potomka
	BinaryTree::Node_t *right1 = node1->pRight;
	ASSERT_FALSE(right1 == NULL);
	EXPECT_TRUE(right1->pLeft == NULL);
	EXPECT_TRUE(right1->pRight == NULL);
	EXPECT_EQ(BLACK, right1->color);
	EXPECT_TRUE(right1->pParent == node1);
}


TEST_F(EmptyTree, DeleteNode)
{
	for (int i = -100; i <= 100; ++i)
	{
		EXPECT_FALSE(Empty.DeleteNode(i));
	}
	
}

TEST_F(EmptyTree, FindNode)
{
	for (int i = -100; i <= 100; ++i)
	{
		EXPECT_TRUE(Empty.FindNode(i) == NULL);
	}
}

//Testy pro ne-prazdny strom


TEST_F(NonEmptyTree, InsertNode)
{
	//Vlozeni existujiciho prvku
	std::pair<bool, BinaryTree::Node_t *> insert_1 = NonEmpty.InsertNode(10);
	EXPECT_FALSE(insert_1.first);
	ASSERT_FALSE(insert_1.second == NULL);
	EXPECT_EQ(10, insert_1.second->key);

	std::pair<bool, BinaryTree::Node_t *> insert_2 = NonEmpty.InsertNode(-10);
	EXPECT_FALSE(insert_2.first);
	ASSERT_FALSE(insert_2.second == NULL);
	EXPECT_EQ(-10, insert_2.second->key);
	
	//Vlozeni noveho prvku
	std::pair<bool, BinaryTree::Node_t *> insert_3 = NonEmpty.InsertNode(25);
	BinaryTree::Node_t *new_node = insert_3.second;
	EXPECT_TRUE(insert_3.first);
	ASSERT_TRUE(new_node != NULL);
	EXPECT_TRUE(new_node->key == 25);
	EXPECT_TRUE(new_node->pLeft != NULL);
	EXPECT_TRUE(new_node->pRight != NULL);
	
	//Kontrola potomku noveho prvku
	BinaryTree::Node_t * left = new_node->pLeft;
	ASSERT_TRUE(left != NULL);
	EXPECT_TRUE(left->pParent == new_node);

	BinaryTree::Node_t * right = new_node->pRight;
	ASSERT_TRUE(right != NULL);
	EXPECT_TRUE(right->pParent == new_node);
} 


TEST_F(NonEmptyTree, DeleteNode)
{
	//Vymazani neexistujiciho prvku
	EXPECT_FALSE(NonEmpty.DeleteNode(42));
	EXPECT_TRUE(NonEmpty.FindNode(42) == NULL);

	//Vymazani existujiciho prvku
	EXPECT_TRUE(NonEmpty.DeleteNode(5));
	EXPECT_TRUE(NonEmpty.FindNode(5) == NULL);
}

TEST_F(NonEmptyTree, FindNode)
{
	//Vyhledani neexistujiciho prvku
	EXPECT_TRUE(NonEmpty.FindNode(42) == NULL);

	//Vyhledani existujiciho prvku
	EXPECT_TRUE(NonEmpty.FindNode(5) != NULL);
	EXPECT_TRUE(NonEmpty.FindNode(-9) != NULL);
}



//Testy axiomu 
TEST_F(TreeAxioms, Axiom1)
{	
	//Vsechny listy jsou cerne	
	std::vector<BinaryTree::Node_t *> leaf_nodes;
	AxiomTree.GetLeafNodes(leaf_nodes);
	for (int i = 0; i < leaf_nodes.size() ; ++i)
	{
		ASSERT_TRUE(leaf_nodes[i]->pLeft == NULL);
		ASSERT_TRUE(leaf_nodes[i]->pRight == NULL);
		EXPECT_EQ(BLACK, leaf_nodes[i]->color);
	}

}

TEST_F(TreeAxioms, Axiom2)
{
	//Cervene uzly maji cerne potomky
	std::vector<BinaryTree::Node_t *> nodes;
	AxiomTree.GetNonLeafNodes(nodes);
	for (int i = 0; i < nodes.size(); ++i)
	
	{
		if (nodes[i]->color == RED)
		{
			EXPECT_EQ(BLACK, nodes[i]->pLeft->color);
			EXPECT_EQ(BLACK, nodes[i]->pRight->color);
		}

	}

}

TEST_F(TreeAxioms, Axiom3)
{
	//Stejny pocet cernych uzlu od korenu po list
	
	std::vector<BinaryTree::Node_t *> leaf_nodes;
	AxiomTree.GetLeafNodes(leaf_nodes);
	BinaryTree::Node_t *root = AxiomTree.GetRoot();
	
	int counter = 0;
	int previous = 0;

	for (int i = 0; i < leaf_nodes.size(); i++)
	{
		counter = 0;
		BinaryTree::Node_t *node = leaf_nodes[i]->pParent;
		while(node != root)
		{
			if (node->color == BLACK)
			{
				counter++;
			}
			node = node->pParent;
		}
		if (i == 0)
		{
			previous = counter;
		}
		else
		{
			EXPECT_EQ(previous, counter);
			previous = counter;
		}
	}
}





//===========================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
