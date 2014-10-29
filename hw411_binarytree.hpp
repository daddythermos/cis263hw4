//
//  GVBinaryTree.hpp

#ifndef CS263_BinaryTree
#define CS263_BinaryTree
#include <stdexcept>
#include <ostream>
#include <queue>
using namespace std;
namespace gvsu {
    template<typename Z>
    class BinaryTree {
    private:
        class Node;
        /* instance variables */
        Node *root;   /* pointer to the root node */
        /* inner class(es) */
        class Node {
        public:
            Z data;
            Node *left;   /* pointer to the left child */
            Node *right;  /* pointer to the right child */
        };
    public:
        /* member functions */

        BinaryTree () {
            root = nullptr;
        }

        ~BinaryTree() {
            if (root == nullptr)
                return;
            clearAll(root);
        }

        int numberOfNodes() const {
        	return numNodes(root);
            /* in your recursive private function, make sure to avoid duplicate recursive calls */
        }

        /* Definition: a leaf node has no children */
        int numberOfLeaves() const {
        	return numLeaves(root);
            /* in your recursive private function, make sure to avoid duplicate recursive calls */
        }

        /* Definition:  a full node has two children */
        int numberOfFullNodes() const {
            return numFull(root);
            /* in your recursive private function, make sure to avoid duplicate recursive calls */
        }

        /* copy assignment */
        BinaryTree&  operator= (const BinaryTree& rhs) {
            clearAll(root); /* required to avoid mem leak */
            root = duplicate (rhs.root);
            return *this;
        }

        /* move assignment */
        BinaryTree& operator= (BinaryTree&& rhs)
        {
            clearAll(root);
            this->root = rhs.root;
            rhs.root = nullptr;
            return *this;
        }

        bool contains (const Z& key) const
        {
            return is_element_of (root, key);
        }

        bool insert (const Z& key) {
            return insert_into (root, key);
        }

        void remove (const Z& key) {
            remove_from(root, key);
        }

        vector<Z> levelOrder () const {
            vector<Z> output;
            queue<Node*> q;
            if (root != nullptr){
            	q.push (root);
            }
            while(!q.empty()){
            	Node* temp = q.front();
            	output.push_back(temp->data);
            	if(temp->left != nullptr)
            		q.push(temp->left);
            	if(temp->right != nullptr)
            		q.push(temp->right);
            	q.pop();
            }
            return output;
        }

        /* Use the following print for debugging. To call this function,
         * use one of the following invocations from your "main" function:
           (fill in the blank with the name of you tree object)

            ______.print();
            ______.print(std::cout);
            ______.print(your_own_output_stream);
         
            The last example can be used, for instance, to save the output
            to a file (by first creating an ofstream object)

         */
        void print (ostream& os = std::cout) const {
            print_from (root, os, "");
        }

    private:

        int numNodes(const Node* pos) const{
        	if(pos == nullptr)
        		return 0;
        	else{
        		return numNodes(pos->left) + numNodes(pos->right) + 1;
        	}
        }

        int numLeaves (const Node* pos) const{
        	if(pos == nullptr)
        	   return 0;
        	else if (pos->left == nullptr && pos->right == nullptr){
        		return 1;
        	}
        	else{
        		return numLeaves(pos->left) + numLeaves(pos->right);
        	}
        }

        int numFull (const Node* pos) const{
        	if(pos == nullptr)
        	   return 0;
        	else if (pos->left != nullptr && pos->right != nullptr){
        	   return numFull(pos->left) + numFull(pos->right) + 1;
        	}
        	else{
        		return numFull(pos->left) + numFull(pos->right);
        	}
        }

        Node * findMin(Node* pos) const{
        	if (pos != nullptr){
        		while (pos->left != nullptr)
        			pos = pos->left;
        	}
        	return pos;
        }


        Node * duplicate_from (Node *theOtherNode)
        {
            if (theOtherNode == nullptr)
            	return nullptr;
            else
            	return new Node (theOtherNode->data,
            					duplicate_from(theOtherNode->left),
            					duplicate_from(theOtherNode->right));

        	//FAIL("I have to complete duplicate");
            //return nullptr;
        }

        bool is_element_of (Node *pos, const Z& key) const {
        	if(pos == nullptr)
        		return false;
        	else if (key < pos->data)
        		return is_element_of(pos->left, key);
        	else if (pos->data < key)
        		return is_element_of(pos->right, key);
        	else
        		return true;

            //FAIL("I have to complete this recursive function");
            //return false;
        }
        
        bool insert_into (Node*& pos, const Z& key) const {
            if (pos == nullptr){
            	pos = new Node{key, nullptr, nullptr};
            	return true;
            }
            else if (key < pos->data)
            	return insert_into(pos->left,key);
            else if (pos->data < key)
            	return insert_into(pos->right, key);
            else
            	return false;

        	//FAIL("I have to complete this recursive function");
            //return false;
        }
        
        void remove_from (Node*& pos, const Z& key) const {
            if (pos == nullptr)
            	return;
            if (key < pos->data)
            	remove_from (pos->left, key);
            else if (pos->data < key)
            	remove_from(pos->right, key);
            else if(pos->left != nullptr && pos->right != nullptr){
            	pos->data = findMin(pos->right)->data;
            	remove_from(pos->right, pos->data);
            }
            else{
            	Node * oldNode = pos;
            	pos = (pos->left != nullptr) ? pos->left : pos->right;
            	delete oldNode;
            }

        	//FAIL("I have to complete this recursive function");
        }
        
        void clearAll (Node* & pos) // remove all the nodes from this tree
        {
            if (pos != nullptr){
            	clearAll(pos->left);
            	clearAll(pos->right);
            	delete pos;
            }
            pos = nullptr;
        }

        void print_from (Node *pos, ostream& os, const string&& path) const
        {
            if (pos) {
                print_from (pos->left, os, path + "L");
                os << pos->data << " (" << path << ")" << endl;
                print_from (pos->right, os, path + "R");
            }
        }
    };

    template <typename Z>
    ostream& operator<< (ostream& os, const BinaryTree<Z>& t)
    {
        t.print (os);
        return os;
    }

}


#endif
