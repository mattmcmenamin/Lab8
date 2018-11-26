#pragma once

#ifndef _BIN_TREE_H

#define _BIN_TREE_H

#include "RandomUtilities.h"

#include<iostream>

#include<string>

#include<vector>

#include<queue>

//***Binary Tree class ***//

class BinaryTree

{

protected:

	class BinaryNode

	{

	public:

		short entry_;

		BinaryNode * left_;

		BinaryNode *right_;

		BinaryNode(short entry = 0, BinaryNode * left = NULL, BinaryNode * right = NULL )

			: entry_(entry), left_(left), right_(right)

		{}

		BinaryNode()

		{}

	private:

		BinaryNode(const BinaryNode&);

		const BinaryNode & operator=(const BinaryNode&);

	};

public:

	BinaryTree();

	~BinaryTree();

	void build(long size);

	void display(std::ostream& outfile) const;

	long size() const;

	long height() const;

	long leaves() const;

	short leftmost() const;

	std::vector<short> preorder() const;

	std::vector<short> postorder() const;

private:

	BinaryNode * tree_;

	static int btEntry_;

	BinaryTree& operator=(BinaryTree&);

	BinaryTree(const BinaryTree &);

	static void destroy(BinaryNode* &subtree);

	static void buildRandom(long size, BinaryNode* & subtree);

	static void displayLeft(std::ostream &outfile, BinaryNode *subtree, std::string prefix);

	static void displayRight(std::ostream &outfile, BinaryNode *subtree, std::string prefix);

	static long size(const BinaryNode*subtree);

	static long height(const BinaryNode*subtree);

	static long leaves(const BinaryNode*subtree);

	static short leftmost(const BinaryNode*subtree);

	static void preorder(std::vector<short> & traversal, const BinaryNode*subtree);

	static void postorder(std::vector<short> & traversal, const BinaryNode*subtree);

};

int BinaryTree::btEntry_ = 1;

BinaryTree::BinaryTree() : tree_(NULL)

{}

BinaryTree::~BinaryTree()

{

	destroy(tree_);

}

void BinaryTree::build(long size)

{

	destroy(tree_);

	buildRandom(size, tree_);

}

inline void BinaryTree::display(std::ostream & outfile) const

{

	std::string prefix;

	if (tree_ == NULL)

	{

		outfile << "-" << std::endl;

	}

	else

	{

		displayLeft(outfile, tree_->left_, " ");

		outfile << "---" << tree_->entry_ << std::endl;

		displayRight(outfile, tree_->right_, " ");

	}

}

long BinaryTree::size() const

{

	return size(tree_);

}

long BinaryTree::height() const

{

	return height(tree_);

}

long BinaryTree::leaves() const

{

	return leaves(tree_);

}

short BinaryTree::leftmost() const

{

	return leftmost(tree_);

}

std::vector<short> BinaryTree::preorder() const

{

	std::vector<short> traversal;

	preorder(traversal, tree_);

	return traversal;

}

std::vector<short> BinaryTree::postorder() const

{

	std::vector<short> traversal;

	postorder(traversal, tree_);

	return traversal;

}

inline BinaryTree & BinaryTree::operator=(BinaryTree &)

{

	// TODO: insert return statement here

}

void BinaryTree::destroy(BinaryNode* & subtree)

{

	if (subtree != NULL)

	{

		destroy(subtree->left_);

		destroy(subtree->right_);

		delete subtree;

		subtree = NULL;

	}

}

inline void BinaryTree::buildRandom(long size, BinaryNode *& subtree)

{

	if (size == 0)

	{

		subtree = NULL;

	}

	else

	{

		subtree = new BinaryNode(btEntry_);

		btEntry_++;

		long leftSize = randInt(0, size);

		buildRandom(leftSize, subtree->left_);

		long rightSize = size - 1 - leftSize;

		buildRandom(rightSize, subtree->right_);

	}

}

inline void BinaryTree::displayLeft(std::ostream & outfile, BinaryNode * subtree, std::string prefix)

{

	if (subtree == NULL)

	{

		outfile << prefix + "/" << std::endl;

	}

	else

	{

		displayLeft(outfile, subtree->left_, prefix + " ");

		outfile << prefix + "/---" << subtree->entry_ << std::endl;

		displayRight(outfile, subtree->right_, prefix + "| ");

	}

}

void BinaryTree::displayRight(std::ostream & outfile, BinaryNode * subtree, std::string prefix)

{

	if (subtree == NULL)

	{

		outfile << prefix + "\\" << std::endl;

	}

	else

	{

		displayLeft(outfile, subtree->left_, prefix + "| ");

		outfile << prefix + "\\---" << subtree->entry_ << std::endl;

		displayRight(outfile, subtree->right_, prefix + " ");

	}

}

long BinaryTree::size(const BinaryNode * subtree)

{

	if (subtree == NULL)

		return 0;

	else

		return (size(subtree->left_) + 1 + size(subtree->right_));

}

inline long BinaryTree::height(const BinaryNode * subtree)

{

	if (subtree == NULL)

		return 0;

	else

	{

		/* compute the depth of each subtree */

		int lHeight = height(subtree->left_);

		int rlHeight = height(subtree->right_);

		/* use the larger one */

		if (lHeight > rlHeight)

			return(lHeight + 1);

		else return(rlHeight + 1);

	}

}

inline long BinaryTree::leaves(const BinaryNode * subtree)

{

	if (subtree == NULL)

		return 0;

	else if (subtree->left_ == NULL && subtree->right_ == NULL)

		return 1;

	else

	{

		return leaves(subtree->left_) + leaves(subtree->right_);

	}

}

short BinaryTree::leftmost(const BinaryNode * subtree)

{

	const BinaryNode* current = subtree;

	while (current->left_ != NULL)

	{

		current = current->left_;

	}

	return (current->entry_);

}

void BinaryTree::preorder(std::vector<short>& traversal, const BinaryNode * subtree)

{

	if (subtree != NULL)

	{

		traversal.push_back(subtree->entry_);

		preorder(traversal, subtree->left_);

		preorder(traversal, subtree->right_);

	}

}



void BinaryTree::postorder(std::vector<short>& traversal, const BinaryNode * subtree)

{

	if (subtree != NULL)

	{

		

		postorder(traversal, subtree->left_);

		postorder(traversal, subtree->right_);

		traversal.push_back(subtree->entry_);
	}

}

#endif