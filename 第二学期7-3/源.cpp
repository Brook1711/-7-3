#include<iostream>
#include<vector>
#include<string>
#include <algorithm>

using namespace std;

template<class T>
class BiNode
{
public:
	T data;
	//	BiNode<T>* parent;
	BiNode<T>* lchild;
	BiNode<T>* rchild;
};

template<class T>
class BiTree
{
private:
	void Create(BiNode<T> * &R, vector<T> &v, int i, int n);
	void Release(BiNode<T> * R);

public:

	BiNode<T> * root;
	BiTree()
	{
		root = NULL;
	}

	BiTree(vector<T>& v, int n);
	void PIBiTree(BiNode<T> *& R, string Pre, string In, bool& Ti);
	void PreOrder(BiNode<T> * R);
	void InOrder(BiNode<T> * R);
	void PostOrder(BiNode<T> * R);
	int GetHight(BiNode<T> * R);
	int GetMinHight(BiNode<T> * R);
	bool JudgeOneNode(BiNode<T> * R);
	bool JudgeEveryNode(BiNode<T> * R);
	//	void SPreOrder(BiNode<T> * R);
	//	void SInOrder(BiNode<T> * R);
	//	void SPostOrder(BiNode<T> * R);
	void LevelOrder(BiNode<T> * R);
	int GetLeafNum(BiNode<T> * R);
	~BiTree();

};
template<class T>
void BiTree<T>::Create(BiNode<T> * &R, vector<T> &v, int i, int n)
{
	if (i <= n && v[i - 1] != '0')
	{
		R = new BiNode<T>;
		R->data = v[i - 1];
		Create(R->lchild, v, 2 * i, n);
		Create(R->rchild, v, 2 * i + 1, n);
	}
	else
		R = NULL;
}

template<class T>
void BiTree<T>::Release(BiNode<T> * R)
{
	if (R != NULL)
	{
		Release(R->lchild);
		Release(R->rchild);
		delete R;
	}
}

template<class T>
BiTree<T>::BiTree(vector<T>& v, int n)
{
	Create(root, v, 1, n);
}

template<class T>
void BiTree<T>::PIBiTree(BiNode<T> *& R, string Pre, string In, bool& Ti)
{
	if (Pre.length() == 0)
	{
		R = NULL;
		return;
	}
	char rootNode = Pre[0];
	int index = In.find(rootNode);
	string lchild_In = In.substr(0, index);
	string rchild_In;
	if ((index + 1) >= Pre.length())
	{
		rchild_In = "";
	}
	else
	{
		rchild_In = In.substr(index + 1);
	}

	int lchildLen = lchild_In.length();
	int rchildLen = rchild_In.length();
	string lchild_Pre = Pre.substr(1, lchildLen);
	string rchild_Pre;
	if ((1 + lchildLen) >= Pre.length())
	{
		rchild_Pre = "";
	}
	else
	{
		rchild_Pre = Pre.substr(1 + lchildLen);
	}
	string tlchild_Pre = lchild_Pre;
	string tlchild_In = lchild_In;
	sort(tlchild_Pre.begin(), tlchild_Pre.end());
	sort(tlchild_In.begin(), tlchild_In.end());
	if (tlchild_Pre.compare(tlchild_In))
	{
		Ti=false;
		R = new BiNode<T>;
		if (R != NULL)
		{
			R->data = rootNode;
			PIBiTree(R->lchild, lchild_Pre, lchild_In, Ti);
			PIBiTree(R->rchild, rchild_Pre, rchild_In, Ti);
		}
	}
	else
	{
		R = new BiNode<T>;
		if (R != NULL)
		{
			R->data = rootNode;
			PIBiTree(R->lchild, lchild_Pre, lchild_In, Ti);
			PIBiTree(R->rchild, rchild_Pre, rchild_In, Ti);
		}

	}
}




template<class T>
void BiTree<T>::PreOrder(BiNode<T> * R)
{
	if (R != NULL)
	{
		cout << R->data;
		PreOrder(R->lchild);
		PreOrder(R->rchild);
	}
}

template<class T>
void BiTree<T>::InOrder(BiNode<T> * R)
{
	if (R != NULL)
	{
		InOrder(R->lchild);
		cout << R->data;
		InOrder(R->rchild);
	}
}

template<class T>
void BiTree<T>::PostOrder(BiNode<T> * R)
{
	if (R != NULL)
	{
		PostOrder(R->lchild);
		PostOrder(R->rchild);
		cout << R->data;
	}
}

template<class T>
bool BiTree<T>::JudgeOneNode(BiNode<T> * R)
{
	int left = GetHight(R->lchild);
	int right = GetHight(R->rchild);
	int m;
	if (left > right)
		m = left - right;
	else
		m = right - left;
	if (m > 1)
		return false;
	else
		return true;
}

template<class T>
bool BiTree<T>::JudgeEveryNode(BiNode<T> * R)
{
	if (R == NULL)
		return true;
	int leftDepth = GetHight(R->lchild);
	int rightDepth = GetHight(R->rchild);
	int diff = leftDepth - rightDepth;
	if (diff > 1 || diff < -1)
		return false;
	return JudgeEveryNode(R->lchild) && JudgeEveryNode(R->rchild);
}

template<class T>
void BiTree<T>::LevelOrder(BiNode<T>* R)
{
	BiNode<T> ** queue = new BiNode<T> *[GetLeafNum(root)];
	int f = 0, r = 0;
	if (R != NULL)
		queue[++r] = R;
	while (f != r)
	{
		BiNode<T> *p = queue[++f];
		cout << p->data;
		if (p->lchild != NULL)
			queue[++r] = p->lchild;
		if (p->rchild != NULL)
			queue[++r] = p->rchild;
	}

}

template<class T>
int BiTree<T>::GetLeafNum(BiNode<T>* R)
{
	if (R == NULL)
		return 0;
	else
		return GetLeafNum(R->lchild) + GetLeafNum(R->rchild) + 1;

}

template<class T>
BiTree<T>::~BiTree()
{
	Release(root);
}

template<class T>
int BiTree<T>::GetHight(BiNode<T> *R)
{
	if (R != NULL)
	{
		int m = GetHight(R->lchild);
		int n = GetHight(R->rchild);
		return (m > n ? m : n) + 1;
	}
	else
		return 0;
}

template<class T>
int BiTree<T>::GetMinHight(BiNode<T> *R)
{
	if (R != NULL)
	{
		int m = GetMinHight(R->lchild);
		int n = GetMinHight(R->rchild);
		return (m < n ? m : n) + 1;
	}
	else
		return 0;
}


int main()
{
	string Pre, In;
	cin >> Pre >> In;
	string tPre = Pre;
	string tIn = In;
	sort(tPre.begin(), tPre.end());
	sort(tIn.begin(), tIn.end());
	if (tPre.compare(tIn))
		cout << "error"<<endl;
	else
	{
		int n = Pre.size();

		BiTree<char> MyTree;
		bool Ti = true;

		MyTree.PIBiTree(MyTree.root, Pre, In, Ti);

		if (Ti)
		{
			MyTree.PostOrder(MyTree.root);
			cout << endl;
			MyTree.LevelOrder(MyTree.root);
		}
		else
			cout << "error";
	}





	system("pause");
	return 0;
}