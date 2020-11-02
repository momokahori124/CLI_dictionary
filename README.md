# 📖📖📖CLIで実行できる英和辞書プログラム📖📖📖

言語：C++  

## Get Start

```
$ make
```

## Demo
```
Loading...

Please Select MODE
 s : search
 a : add
 u : update
 r : remove
 q : quit
Input MODE : s
Input search word : apple
『リンゴ』;リンゴの木

Please Select MODE
 s : search
 a : add
 u : update
 r : remove
 q : quit
Input MODE : a
Input key and value : apple appleapple
DONE!

Please Select MODE
 s : search
 a : add
 u : update
 r : remove
 q : quit
Input MODE : s
Input search word : apple
『リンゴ』;リンゴの木
appleapple
```

## 機能

1. 検索　意味を出力します、複数個意味がある場合は改行しながら表示します
2. 追加　今まであったvalueとは別に追加されます
3. 更新　今まであったvalueを削除して新しく追加します
4. 削除　
  
完全一致のみ。ハッシュテーブル＋チェイン法(連結リストでつないでいく)で実装しました。  
ハッシュ関数は、アスキーコードの総和、ハッシュテーブルの大きさは素数の401にしました。  


## 考えたこと

#### ハッシュ関数をどう定義するか???

考えたが自分では思い付かなかった。  
キーのアスキーコードの総和にすると良い。  
この方法は辞書や数字のように、満遍なくデータが分布している時に有効。  
偏りがあるものには使えない。  
```
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
```

#### 配列の数、どうして素数だと満遍なく振り分けられるのか？？

興味があるので時間のある時に勉強したい

## こだわりポイント
#### addとupdateをきちんとわけたところ。  
addは今の情報を残したままvalueを追加し、  
updateは上書きする。  
  
#### Makefile
前回の課題でMakefileを作っている人がいてカッコ良かったので真似してみた。

#### 意味の重複
同じキーで複数の意味を持つ場合、まとめてデータとして持てるようにした。
```
Input search word : con
…'を'よく研究する
〈人〉'を'ペテンにかける
=convict
=confidence trick
```

## コメント
最初とりあえず完全一致のみ作ろうとハッシュテーブルで実装したが、  
作り終えてからハッシュテーブルだと前方一致は難しいことに気づく。  
トライ木(prefix tree)で前方一致も作ろうとして断念。。。  
多分木を二分木で表そうとしたが、操作が難しかった。。。><
