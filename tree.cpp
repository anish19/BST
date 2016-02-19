#include "header"

class TreeNode{
	public:
		TreeNode(int);
		~TreeNode();
		int get_val();
		void set_val(int);
		TreeNode* get_left();
		TreeNode* get_right();
		int get_lcount();
		void set_left(TreeNode*);
		void set_right(TreeNode*);
		void set_lcount(int);
		TreeNode *next;

	private:
		TreeNode *left, *right;
		int val;
		int lcount;
};

TreeNode::TreeNode(int val){
	this->val = val;
	left = NULL;
	right = NULL;
	next = NULL;
}

TreeNode::~TreeNode(){
	cout<<"Deleting Node with val: "<<this->val<<endl;
}

int TreeNode::get_val(){
	return this->val;
}

void TreeNode::set_val(int val){
	this->val = val;
}

TreeNode* TreeNode::get_left(){
	return this->left;
}

TreeNode* TreeNode::get_right(){
	return this->right;
}

int TreeNode::get_lcount(){
	return this->lcount;
}

void TreeNode::set_left(TreeNode* node){
	this->left = node;
}

void TreeNode::set_right(TreeNode* node){
	this->right = node;
}

void TreeNode::set_lcount(int val){
	this->lcount = val;
}

class Tree{
	public:
		Tree();
		~Tree();
		TreeNode* insert(int);
		void print();
		int lcount;
//		vector<int> in_order_tr(TreeNode*);
//		int kth_smallest(int);
//		int kth_largest(int);
	private:
		void tree_insert(TreeNode*, TreeNode*);
		TreeNode* head, *tail;
};

Tree::Tree(){
	head = NULL;
	tail = NULL;
	lcount = 0;
}

void Tree::tree_insert(TreeNode* head, TreeNode* node){

	if(head->get_val() > node->get_val()){
		if(head->get_left() == NULL){
			head->set_lcount(head->get_lcount()+1);
			head->set_left(node);
			node->set_left(NULL);
		}
		else{
			head->set_lcount(head->get_lcount()+1);
			tree_insert(head->get_left(), node);
		}
	}
	else{
		if(head->get_right() == NULL){
			head->set_right(node);
			node->set_right(NULL);
		}
		else{
			tree_insert(head->get_right(), node);
		}
	}
}

TreeNode* Tree::insert(int val){
	TreeNode *node = new TreeNode(val);
	node->set_lcount(0);
	if(this->head == NULL){
		this->head = node;
		node->set_left(NULL);
		node->set_right(NULL);
	}
	else{
		tree_insert(this->head, node);
	}
	
	return node;
}

void printTree(TreeNode* node){
	if(node == NULL)
		return;
	else{
		if(node->get_left() != NULL && node->get_right() != NULL){
			cout<<"[{node: "<<node->get_val()<<"}"<<
				"	{l: "<<node->get_left()->get_val()<<
				" r: "<<node->get_right()->get_val()<<"}"<<
				"	{lcount: "<<node->get_lcount()<<"}]"<<endl;
			printTree(node->get_left());
			printTree(node->get_right());
		}
		else if(node->get_left() != NULL){
			cout<<"[{node: "<<node->get_val()<<"}"<<
				"	{l: "<<node->get_left()->get_val()<<
				" r: NULL}"<<"	{lcount:"<<node->get_lcount()<<"}]"<<endl;
			printTree(node->get_left());
		}
		else if(node->get_right() != NULL){
			cout<<"[{node: "<<node->get_val()<<"	{l: NULL"<<
				" r: "<<node->get_right()->get_val()<<"}"<<
				"	{lcount:"<<node->get_lcount()<<"}]"<<endl;
			printTree(node->get_right());
		}
		else 
			cout<<"[{node: "<<node->get_val()<<"}]"<<endl;
	}
}

void Tree::print(){	
	printTree(this->head);
}

int main(int argc, char **argv){
	int t_size, temp;
	cout<<"enter no of elements you want "<<endl;
	cin>>t_size;
	cout<<"no of elements "<<t_size<<endl;
	cout<<"enter elements"<<endl;
	Tree *t = new Tree();
	for(int i = 1 ; i <= t_size; i ++){
		cin>>temp;
		t->insert(temp);
	}
	cout<<"\n\n Tree:"<<endl;
	t->print();
	cout<<"\nFormat:\n [{node}\t{children}\t{left_count}]"<<endl;
//	t.in_order_tr();
	
}





