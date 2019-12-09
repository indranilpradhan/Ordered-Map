#include <iostream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

template <typename T1,typename T2>
class Node
{
	public:
	T1 key;
	T2 value;
	Node *left = NULL;
	Node *right = NULL;
};

template <typename T1,typename T2>
class orderedmap
{
	Node<T1, T2>* root = NULL;
	public:
//	unorderedmap()
//	{
//		root = NULL;
//	}
	int max(int a, int b)
	{
		return a>b?a:b;	
	}

	int height(Node<T1, T2> *ptr)
	{
	//	cout<<"33"<<endl;
		if(ptr == NULL)
		{
	//		cout<<"36"<<endl;
			return 0;
		}
		if(ptr->left == NULL && ptr->right == NULL)
		{
	//		cout<<"37"<<endl;
			return 1;
		}
		else
		{
		//	cout<<"46"<<endl;
			return max(1+height(ptr->right),1+height(ptr->left));
		}	
	}

	Node<T1, T2>* inordersuc(Node<T1, T2>* ptr)
	{
		Node<T1, T2>* pt = ptr;
		while(pt->left)
		{
			pt = pt->left;
		}
		return pt;
	}
	
	void insert(T1 key,T2 value)
	{
		root = insertintotree(key, value, root);
	}

	Node<T1, T2>* insertintotree(T1 key,T2 value,Node<T1, T2> *ptr)
	{
		if(ptr == NULL)
		{
			ptr = new Node<T1, T2>();
			ptr->key = key;
			ptr->value = value;
			ptr->right = NULL;
			ptr->left = NULL;
//			ptr->rightvalue = 0;
			return ptr;
		}
		
		if(ptr->key == key)
		{
//			cout<<"key "<<key<<endl;
//			cout<<"value "<<value<<endl;
			ptr->value = value;
			return ptr;	
		}
	
		if(key < ptr->key)
		{
			ptr->left = insertintotree(key, value, ptr->left);
		}
	
		if(key > ptr->key)
		{
	//		ptr->rightvalue += 1; 
			ptr->right = insertintotree(key, value,ptr->right);
		}
	//	cout<<"72"<<endl;
		int rheight = height(ptr->right);
	//	cout<<"74"<<endl;
		int lheight = height(ptr->left);
	
//	cout<<"lh"<<lheight<<endl;
//	cout<<"rh"<<rheight<<endl;
	
		if(lheight > 1+rheight)
		{
			int llheight = height(ptr->left->left);
			int lrheight = height(ptr->left->right);
	//		cout<<"llh"<<llheight<<endl;
	//		cout<<"lrh"<<lrheight<<endl;
			if(llheight > lrheight)
			{
				//rightrotate
	//			cout<<"ptr rr"<<ptr->value<<endl;
				Node<T1, T2>* newptr = new Node<T1, T2>();
				newptr = ptr->left;
		//		newptr->rightvalue = ptr->rightvalue + ptr->left->rightvalue;
				ptr->left = newptr->right;
				newptr->right = ptr;
				ptr = newptr;
			}
			else
			{
				//leftrightrotate
				Node<T1, T2>* newptr1 = new Node<T1, T2>();
				Node<T1, T2>* newptr2 = new Node<T1, T2>();
				newptr1 = ptr->left->right;
			//	ptr->left->rightvalue = 0;
				ptr->left->right = newptr1->left;
				newptr1->left = ptr->left;
				ptr->left = newptr1;
				newptr2 = ptr->left;
				ptr->left = newptr2->right;
				newptr2->right = ptr;
				ptr = newptr2;
			}
		}
//	cout<<"95"<<endl;
		if(rheight > 1+lheight)
		{
			int rlheight = height(ptr->right->left);
			int rrheight = height(ptr->right->right);
//			cout<<"rlh"<<rlheight<<endl;
//			cout<<"rrh"<<rrheight<<endl;
			if(rrheight > rlheight)
			{
			//leftrotate
				Node<T1, T2>* newptr = new Node<T1, T2>();
				newptr = ptr->right;
				ptr->right = newptr->left;
				newptr->left=ptr;
				ptr = newptr;
			}
			else
			{
			//rightleftrotate
				Node<T1, T2>* newptr1 = new Node<T1, T2>();
				Node<T1, T2>* newptr2 = new Node<T1, T2>();
				newptr1 = ptr->right->left;
				ptr->right->left = newptr1->right;
				newptr1->right = ptr->right;
				ptr->right = newptr1;
				newptr2 = ptr->right;
				ptr->right = newptr2->left;
				newptr2->left = ptr;
				ptr = newptr2;
			}
		}
		return ptr;	
	}
	
	void erase(T1 key)
	{
		root = deletenode(key, root);
	}

	Node<T1, T2>* deletenode(T1 key, Node<T1, T2>* ptr)
	{
		if(ptr == NULL)
		{
			return ptr;
		}
	
		if(key < ptr->key)
		{
			ptr->left = deletenode(key, ptr->left);
		}	
		else if(key > ptr->key)
		{ 
			ptr->right = deletenode(key,ptr->right);
		}
		else
		{
			if(ptr->left == NULL && ptr->right == NULL)
			{
				ptr = NULL;
			}
			else if(ptr->left != NULL && ptr->right == NULL)
			{
				Node<T1, T2>* temp = ptr->left;
				*ptr = *temp;
				free(temp);
			}
			else if(ptr->left == NULL && ptr->right != NULL)
			{
				Node<T1, T2>* temp = ptr->right;
				*ptr = *temp;
				free(temp);
			}
			else
			{
				Node<T1, T2>* temp = inordersuc(ptr->right);
				ptr->key = temp->key;
				ptr->value = temp->value;
				ptr->right = deletenode(temp->key,ptr->right);
			}
		}
	
		if(ptr == NULL)
			return ptr;
		
		if(ptr->left == NULL && ptr->right == NULL)
			return ptr;
	
	//	cout<<"72"<<endl;
		int rheight = height(ptr->right);
//	cout<<"74"<<endl;
		int lheight = height(ptr->left);
	
//	cout<<"lh"<<lheight<<endl;
//	cout<<"rh"<<rheight<<endl;
	
		if(lheight > 1+rheight)
		{
			int llheight = height(ptr->left->left);
			int lrheight = height(ptr->left->right);
//			cout<<"llh"<<llheight<<endl;
//		cout<<"lrh"<<lrheight<<endl;
			if(llheight > lrheight)
			{
			//rightrotate
	//			cout<<"ptr rr"<<ptr->value<<endl;
				Node<T1, T2>* newptr = new Node<T1, T2>();
				newptr = ptr->left;
		//		newptr->rightvalue = ptr->rightvalue + ptr->left->rightvalue;
				ptr->left = newptr->right;
				newptr->right = ptr;
				ptr = newptr;
			}
			else
			{
			//leftrightrotate
				Node<T1, T2>* newptr1 = new Node<T1, T2>();
				Node<T1, T2>* newptr2 = new Node<T1, T2>();
				newptr1 = ptr->left->right;
			//	ptr->left->rightvalue = 0;
				ptr->left->right = newptr1->left;
				newptr1->left = ptr->left;
				ptr->left = newptr1;
				newptr2 = ptr->left;
				ptr->left = newptr2->right;
				newptr2->right = ptr;
				ptr = newptr2;
			}
		}
//	cout<<"95"<<endl;
		if(rheight > 1+lheight)
		{
			int rlheight = height(ptr->right->left);
			int rrheight = height(ptr->right->right);
	//		cout<<"rlh"<<rlheight<<endl;
	//		cout<<"rrh"<<rrheight<<endl;
			if(rrheight > rlheight)
			{
			//leftrotate
				Node<T1, T2>* newptr = new Node<T1, T2>();
				newptr = ptr->right;
				ptr->right = newptr->left;
				newptr->left=ptr;
				ptr = newptr;
			}
			else
			{
				//rightleftrotate
				Node<T1, T2>* newptr1 = new Node<T1, T2>();
				Node<T1, T2>* newptr2 = new Node<T1, T2>();
				newptr1 = ptr->right->left;
				ptr->right->left = newptr1->right;
				newptr1->right = ptr->right;
				ptr->right = newptr1;
				newptr2 = ptr->right;
				ptr->right = newptr2->left;
				newptr2->left = ptr;
				ptr = newptr2;
			}
		}
		return ptr;
	}
	
	bool find(T1 key)
	{
		bool isthere = ispresent(key, root);
		return isthere;
	}
	
	bool ispresent(T1 key, Node<T1, T2>* ptr)
	{
		if(ptr == NULL)
			return false;
		if(key < ptr->key)
			return ispresent(key, ptr->left);
		else if(key > ptr->key)
			return ispresent(key, ptr->right);
		else
			return true;
	}
	
	bool end()
	{
		return false;
	}
	
	T2 retvalue(T1 key, Node<T1, T2>* ptr)
	{
	//	cout<<"key "<<key<<endl;
		if(ptr == NULL)
		{
		//	cout<<"here"<<endl;
			static T2 value;
			return value;
		}
		if(key < ptr->key)
			return retvalue(key, ptr->left);
		else if(key > ptr->key)
			return retvalue(key, ptr->right);
		else
		{
	//		cout<<" ptr key "<<ptr->key<<endl;
	//		cout<<" ptr "<<ptr->value<<endl;
			return ptr->value;
		}
	}
	
	T2 operator[](T1 key)
	{
		T2 value = retvalue(key, root);
		return value;
	}
	
	void display()
	{
		 
    	stack<Node<T1, T2>*> st; 
    	Node<T1, T2>* curr = root; 
  
    	while (curr != NULL || st.empty() == false) 
    	{
        	while (curr !=  NULL) 
        	{ 
            	st.push(curr); 
            	curr = curr->left; 
        	} 
        	curr = st.top(); 
        	st.pop();
        	cout << curr->key<<" --> "<<curr->value<<endl; 
        	curr = curr->right;
   		}
	}
};

int main()
{
	orderedmap<string,int> ump;
	ump.insert("fdg",4);
	ump.insert("dfgfgb",3);
	ump.insert("poiper",1);
	ump.insert("poiyirt",2);
	ump.insert("qwewr",5);
	ump.erase("poiper");
	if(ump.find("poiper") == ump.end())
		cout<<"deleted"<<endl;
	cout<<ump["dfgfgb"]<<endl;
	ump.display();
	return 0;
}
