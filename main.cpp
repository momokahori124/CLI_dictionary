#include "HashTable/hash_table.hpp"

LinkedList *HashTable=0;

void program_HashTable()
{
	char ans[5]="";
	char key[512]="";
	char value[10000]="";

	while (strcmp(ans,"q")!=0)
	{
		cout<<"input word: "<<ans[0]<<endl;
		SELECT_MODE
		cin>>ans;
		if (strcmp(ans,"s")==0){
			SEARCH
			cin>>key;
			HashTable->search(key);
			cout<<endl;
		}else if (strcmp(ans,"a")==0){
			ADD
			cin>>key>>value;
			HashTable->setValue(key,value);
			DONE
		}else if ((strcmp(ans,"r")==0)){
			REMOVE
			cin>>key;
			HashTable->removeValue(key);
		}else if ((strcmp(ans,"u")==0)){
			UPDATE
			cin>>key>>value;
			HashTable->updateValue(key,value);
			DONE
		}
	}
	return;
}

void input(string line)
{
		//keyに格納
		int k=0;
		while (line[k]!= '\t') k++;
		char *key = (char *)malloc(sizeof(char)*(k+1));
		int i=0;
		while (i<k){
			key[i]=line[i];
			i++;
		}
		key[i]='\0';

		//valueに格納
		int l=0;
		while (line[k+l+1]!='\0') l++;
		char *value = (char *)malloc(sizeof(char)*(l+1));
		i=0;
		while (i<l){
			value[i]=line[k+i+1];
			i++;
		}
		value[i]='\0';
		HashTable->setValue(key,value);//HashTableにセット
}

int main(){

	INIT_MESSAGE

	HashTable = new LinkedList();//インスタンス生成

	string filename = "dataset/words.txt";
	ifstream ifs(filename, ios::in);
	//ファイルを開くのに失敗したときの処理
	if(!ifs){
		cerr << "Error: file not opened." << endl;
		return (0);
	}

	string line;
	while(getline(ifs, line))
		input(line);// ここで読み込んだlineをデータに格納する
	program_HashTable();

	// ファイルを閉じる
	ifs.close();

	delete HashTable;//インスタンス削除
	return (0);
}