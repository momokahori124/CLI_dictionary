#include "hash_table.hpp"

//ハッシュ関数
int Hash(char *key)
{
    int ret=0;
	int i=0;

	while (key[i])
	{
		ret += key[i];
		i++;
	}
    return ret % HASHSIZE;
}

class LinkedList
{
	protected:
		struct ListNode
		{
			char *key;
			char *value;
			ListNode *next;
		};
		//ListNode *head;//先頭ノードへのポインタ
		ListNode *HashTable[HASHSIZE];

	public:
		LinkedList();
		~LinkedList();

		//連結リストの機能
		void removeValue(char *key);
		void setValue(char *key,char *value);
		char *search(char *key);//keyからvalueを検索
		void display_list();//リストを全部列挙
		void updateValue(char *key,char *value);
		void list_count();//それぞれのハッシュテーブルに何個入っているか？
};

LinkedList::LinkedList(){
	//ハッシュテーブルを初期化！！
	for (int i=0;i<HASHSIZE;i++)
		HashTable[i]=NULL;
}
LinkedList::~LinkedList(){
	//nothing
}

/**********************************************
	setValue : リストの最後にノードを追加する
***********************************************/

void LinkedList::setValue(char *k, char *v){
	ListNode *new_node;//今追加したい新しいノード
	ListNode *node_tmp;//リスト移動用のノード

	new_node = new ListNode;
	new_node->key = k;
	new_node->value = v;
	new_node->next = NULL;

	//Hash(key)番目のハッシュテーブルにくっつけていく
	node_tmp = HashTable[Hash(k)];

	if (node_tmp==NULL){
		HashTable[Hash(k)] = new_node;
	}
	else
	{
		while (node_tmp->next){
			if (strcmp(node_tmp->key,k)==0)//もしすでに同じkeyが入ってたら横に追加する
			{
				char *n = (char *)malloc(sizeof(char)*(10000));//多めに確保
				strcat(n,node_tmp->value);
				strcat(n, "\n");
				strcat(n, v);
				node_tmp->value = n;
				delete new_node;//作っちゃったノードは消しておく
				return;
			}
			node_tmp = node_tmp->next;
		}
		node_tmp->next = new_node;//最後まで行ってもkeyがなかったら新しく追加
	}
}

/**********************************************
	updateValue : リストを更新する
***********************************************/

void LinkedList::updateValue(char *k, char *v){
	ListNode *new_node;//今追加したい新しいノード
	ListNode *node_tmp;//リスト移動用のノード

	//Hash(key)番目のハッシュテーブルを検索する
	node_tmp = HashTable[Hash(k)];

	if (node_tmp==NULL){

	}
	else
	{
		while (node_tmp->next){
			if (strcmp(node_tmp->key,k)==0)//もしすでに同じkeyが入ってたら更新する
			{
				node_tmp->value = v;
				return;
			}
			node_tmp = node_tmp->next;
		}
	}
	//updateしたいkeyを探したが見つからなかった場合
	cout<<"Sorry, Key don't exist."<<endl;
	return;
}

/***********************************************
	search : keyからvalueを検索して出力する
***********************************************/

char *LinkedList::search(char *k)
{
	int hash = Hash(k);//ハッシュ値
	ListNode *node_tmp;//リスト移動用のノード

	node_tmp = HashTable[hash];//先頭アドレスをセット

	if (node_tmp==NULL){
		ERROR
		return (NULL);
	}
	while (node_tmp){
		if (strcmp(k, node_tmp->key)==0){
			cout<<node_tmp->value<<endl;
			return (node_tmp->value);
		}
		node_tmp = node_tmp->next;
	}
	ERROR
	return (NULL);
}


/**********************************************
	removeValue : 与えられたkeyのdataを削除する
***********************************************/

void LinkedList::removeValue(char *k){
	ListNode *node_tmp;//リスト移動用のノード
	ListNode *node_save;//リスト保存用のノード

	node_tmp = HashTable[Hash(k)];
	if (node_tmp == NULL)
	{
		cout<<"Error : Can't remove. Key is wrong.\n"<<endl;
		return;
	}

	if (strcmp(node_tmp->key,k)==0){
		node_save = HashTable[Hash(k)];
		HashTable[Hash(k)] = node_tmp->next;
		delete node_save;
		cout<<"Done!!!\n"<<endl;
		return;
	}

	while (node_tmp->next){
		if (strcmp((node_tmp->next)->key,k)==0){
			node_save=node_tmp->next;
			node_tmp->next= (node_tmp->next)->next;
			delete node_save;
			cout<<"Done!!!\n"<<endl;
			return;
		}
		node_tmp = node_tmp->next;
	}
	cout<<"Error : Can't remove. Key is wrong.\n"<<endl;
	return;
}

/**********************************************
	list_count : リストの要素をカウントする
***********************************************/

void LinkedList::list_count()
{
	ListNode *node_tmp;//リスト保存用のノード

	for (int i=0;i<HASHSIZE;i++)
	{
		node_tmp = HashTable[i];
		if (node_tmp==NULL)
			cout<<"HashTable["<<i<<"]="<<0<<endl;
		else{
		int count= 1;
		while (node_tmp->next){
			count++;
			node_tmp = node_tmp->next;
		}
		cout<<"HashTable["<<i<<"]="<<count<<endl;
		}
	}
}