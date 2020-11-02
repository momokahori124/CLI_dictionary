#include "tree.hpp"

class Tree
{
	protected:
		struct Node
		{
			char c;//ノードの文字
			char *value;//もし文字の最後なら意味を追加しておく
			//bool isWord;//これ必要かな？コード短くなるなら欲しい
			Node *next;//同じ深さの次の文字へのポインタ
			Node *child;//子供へのポインタ
		};
		Node *head;

	public:
		Tree();
		~Tree();

		//Treeの機能
		// void removeValue(char *key);
		void setValue(char *key,char *value);
		void setNode(char *k, char *v, int depth, Node *(&now),int flag);
		char *search(char *key);//keyからvalueを検索
		void rec(Node *now);
		void display_list();//リストを全部列挙
		// void updateValue(char *key,char *value);
		// void list_count();//それぞれのハッシュテーブルに何個入っているか？
};

Tree::Tree(){
	head = NULL;
}
Tree::~Tree(){
	//nothing
}

/**********************************************
	setNode : 途中まで追加されているTreeにワードの最後までノードを生やす
***********************************************/

void Tree::setNode(char *k, char *v, int depth, Node *(&now),int flag)
{
	//depth番目から最後までどんどん新しいノードを作って繋げていく
	//now->childに一致するものがない
	//now->nextに一致するものがないところまで移動しておく

	Node *save;
	save = now;
	for (int i=depth;i<strlen(k);i++)
	{
		//new_node 作成
		Node *new_node;
		new_node = new Node;
		new_node->c = k[i];
		if (i == strlen(k)-1){
			new_node->value = v;//文字列の最後になったらワードの意味を追加
		}
		else new_node->value = NULL;
		new_node->next = NULL;
		new_node->child = NULL;

		//追加
		if (now==NULL)
		{
			now = new_node;
			save = now;
		}
		else
		{
			if (i==depth && flag == 0){
				save->next = new_node;
				//cout<<i<<" "<<new_node->c<<endl;
				save = save->next;
			}
			else{
				save->child = new_node;
				save = save->child;
			}
		}
	}
	cout<<k<<" done"<<endl;
}

/**********************************************
	setValue : リストの最後にノードを追加する
	(1)与えられたワードと一致するノードを辿りながら
		次の文字が登録されていないところまで移動する！
	(2)そこに最後までsetNodeでノードを追加する
***********************************************/

void Tree::setValue(char *k, char *v){
	Node *now;//移動用のノード
	Node *save;//保存用のノード
	int depth=0;

	now = head;
	save = head;

	cout<<k<<endl;

	if (head==NULL)
	{
		setNode(k, v, 0, now,0);
		head = now;
		return;
	}

	while (now)
	{
		save = now;
		while (save)
		{
			if (save->c == k[depth])
			{
				now = save;
				break;
			}
			if (save->next == NULL)
			{
				setNode(k,v,depth+1,save,0);//nextにつけて欲しい
				return;
			}
			save = save->next;
		}
		if (now->child==NULL)
		{
			setNode(k,v,depth+1,now,1);//childにつけて欲しい
			return;
		}
		now = now->child;
		depth++;
	}
}


// /**********************************************
// 	updateValue : リストを更新する
// ***********************************************/

// void Tree::updateValue(char *k, char *v){
// 	ListNode *new_node;//今追加したい新しいノード
// 	ListNode *node_tmp;//リスト移動用のノード

// 	//Hash(key)番目のハッシュテーブルを検索する
// 	node_tmp = HashTable[Hash(k)];

// 	if (node_tmp==NULL){

// 	}
// 	else
// 	{
// 		while (node_tmp->next){
// 			if (strcmp(node_tmp->key,k)==0)//もしすでに同じkeyが入ってたら更新する
// 			{
// 				node_tmp->value = v;
// 				return;
// 			}
// 			node_tmp = node_tmp->next;
// 		}
// 	}
// 	//updateしたいkeyを探したが見つからなかった場合
// 	cout<<"Sorry, Key don't exist."<<endl;
// 	return;
// }

/***********************************************
	search : keyからvalueを検索して出力する
***********************************************/

char *Tree::search(char *k)
{
	Node *now;//リスト移動用のノード
	Node *save;
	int depth=0;

	now = head;

	if (now==NULL){
		ERROR
		return (NULL);
	}
	while (now->child)
	{
		save = now;
		while (save->next)
		{
			if (k[depth]==save->c){//depth番目の文字が一致したら次の深さへ
				now = save;//saveに移動
				break;
			}
			save = save->next;
		}
		// if (save->next == NULL)//もしdepth文字目でどれも一致するものがなければ追加する
		// {
		// 	setNode(k, v, depth, save);
		// }
		if (depth==strlen(k)-1)
		{
			cout<<now->value<<endl;
			return(now->value);
		}
		now = now->child;//次の文字に移動
		depth++;
	}
	ERROR
	return (NULL);
}


// /**********************************************
// 	removeValue : 与えられたkeyのdataを削除する
// ***********************************************/

// void Tree::removeValue(char *k){
// 	ListNode *node_tmp;//リスト移動用のノード
// 	ListNode *node_save;//リスト保存用のノード

// 	node_tmp = HashTable[Hash(k)];
// 	if (node_tmp == NULL)
// 	{
// 		cout<<"Error : Can't remove. Key is wrong.\n"<<endl;
// 		return;
// 	}

// 	if (strcmp(node_tmp->key,k)==0){
// 		node_save = HashTable[Hash(k)];
// 		HashTable[Hash(k)] = node_tmp->next;
// 		delete node_save;
// 		cout<<"Done!!!\n"<<endl;
// 		return;
// 	}

// 	while (node_tmp->next){
// 		if (strcmp((node_tmp->next)->key,k)==0){
// 			node_save=node_tmp->next;
// 			node_tmp->next= (node_tmp->next)->next;
// 			delete node_save;
// 			cout<<"Done!!!\n"<<endl;
// 			return;
// 		}
// 		node_tmp = node_tmp->next;
// 	}
// 	cout<<"Error : Can't remove. Key is wrong.\n"<<endl;
// 	return;
// }

/**********************************************
	display_list :  リストの全要素を表示
***********************************************/

void Tree::display_list()
{
	Node *now;
	now = head;
	cout<<"display_list!!!!!!!!!"<<endl;

	now = now->next;
	cout<<now->c<<endl;

	while (now)
	{
		cout<<now->c<<endl;
		if (now->value!=NULL) cout<<" "<<now->value<<endl;
		now = now->child;
	}
}

// void Tree::rec(Node *now)
// {
// 	Node *save = now;
// 	while (now)
// 	{
// 		save = now;
// 		while (save)
// 		{
// 			if (save->value)
// 				cout<<save->value<<endl;
// 			save = save->next;
// 			rec(save);
// 		}
// 		now = now->child;
// 	}
// }

// void Tree::display_list()
// {
// 	Node *now;
// 	Node *save;

// 	now = head;

// 	cout<<"display_list================"<<endl;

// 	if (head==NULL)
// 	{
// 		cout<<"No elements"<<endl;
// 		return;
// 	}

// 	rec(now);
// }
