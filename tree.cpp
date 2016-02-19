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
		void print_node();
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

void TreeNode::print_node(){
	if(this->get_left() != NULL && this->get_right() != NULL){
		cout<<"[{node: "<<this->get_val()<<"}"<<
			"	{l: "<<this->get_left()->get_val()<<
			" r: "<<this->get_right()->get_val()<<"}"<<
			"	{lcount: "<<this->get_lcount()<<"}]"<<endl;
	}
	else if(this->get_left() != NULL){
			cout<<"[{node: "<<this->get_val()<<"}"<<
				"	{l: "<<this->get_left()->get_val()<<
				" r: NULL}"<<
				"	{lcount: "<<this->get_lcount()<<"}]"<<endl;
	
	}
	else if (this->get_right() != NULL){
			cout<<"[{node: "<<this->get_val()<<"}"<<
				"	{l: NULL"<<
				" r: "<<this->get_right()->get_val()<<"}"<<
				"	{lcount: "<<this->get_lcount()<<"}]"<<endl;
	
	
	}
	else{
		cout<<"[{node: "<<this->get_val()<<"}]"<<endl;	
	}
}

class Tree{
	public:
		Tree();
		~Tree();
		TreeNode* insert(int);
		void print();
		int node_count;
//		vector<int> in_order_tr(TreeNode*);
		TreeNode* kth_smallest(int);
//		int kth_largest(int);
	private:
		void tree_insert(TreeNode*, TreeNode*);
		TreeNode* find_k_sm(TreeNode*, int);
		TreeNode* head, *tail;
};

Tree::Tree(){
	this->head = NULL;
	this->tail = NULL;
	this->node_count = 0;
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
	this->node_count++;
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

TreeNode* Tree::find_k_sm(TreeNode* node, int k){
	if(node->get_lcount() == k)
		return node;
	else if (node->get_lcount() > k){
		cout<<node->get_val()<<endl;
		return find_k_sm(node->get_left(), k);
	}
	else
		return find_k_sm(node->get_right(), k - node->get_lcount() -1);
}

TreeNode* Tree::kth_smallest(int k){
	return find_k_sm(this->head, k);
}

int main(int argc, char **argv){
	int t_size, temp, k;
	cout<<"enter no of elements you want: "<<endl;
	cin>>t_size;
	cout<<"no of elements is "<<t_size<<endl;
	cout<<"enter elements: (e.g. 3 21 4 83 0 -2 1)"<<endl;
	Tree *t = new Tree();
	for(int i = 1 ; i <= t_size; i ++){
		cin>>temp;
		t->insert(temp);
	}
	cout<<"\n\n Tree:"<<endl;
	t->print();
	cout<<"\nFormat:\n [{node}\t{children}\t{left_count}]"<<endl;
	cout<<"\n\nEnter k to get the kth smallest element: ";
	cin>>k;
	while(k > t->node_count || k < 1){
		cout<<"Tree only has "<< t->node_count<<
		" elements.\nEnter a positive value less than or equal to "<<
		t->node_count<<endl<<endl;
		cin>>k;
	}
	cout<<"\n"<<k<<" smallest element is: ";
	t->kth_smallest(k-1)->print_node();
	cout<<endl;
//	t.in_order_tr();
	
}





