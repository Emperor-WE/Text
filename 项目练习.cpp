#include <iostream>

#define MAX_SIZE 100


using namespace std;

typedef struct {
	int* elems;
	int length;
	int size;
}SqList;

bool ListInit(SqList& L) {
	L.elems = new int[MAX_SIZE];
	if (!L.elems) return false;

	L.length = 0;
	L.size = MAX_SIZE;
	return true;
}

bool ListAppend(SqList& L, int e) {
	if (L.length == MAX_SIZE) return false;
	L.elems[L.length] = e;
	L.length++;
	return true;
}

bool ListInsert(SqList& L, int i, int e) {
	if (i < 0 || i >MAX_SIZE) return false;
	if (L.length == MAX_SIZE) return false;

	for (int j = L.length - 1; j >= i - 1; j--) {
		L.elems[j + 1] = L.elems[j];
	}
	L.elems[i - 1] = e;
	L.length++;
	return true;
}

bool GetElems(SqList L, int i, int& e) {
	if (i < 0 || i >MAX_SIZE) return false;

	e = L.elems[i - 1];
	return true;
}

bool LocateElem(SqList L, int e) {
	for (int i = 0; i < L.length; i++)
		if (e == L.elems[i]) return true;
	return false;
}

bool ListDelete(SqList& L, int i) {
	if (i < 0 || i >MAX_SIZE) return false;

	if (i == L.length) {
		L.length--;
		return true;
	}

	for (int j = i; j <= L.length - 1; j++) {
		L.elems[j - 1] = L.elems[j];
	}
	L.length--;
	return true;
}

void DestoryList(SqList& L) {
	if (L.elems) delete[] L.elems;
	L.length = 0;
	L.size = 0;
}

void SortList(SqList& L) {
	for (int i = 0; i < L.length; i++) {
		for (int j = 0; j < L.length - i - 1; j++) {
			if (L.elems[j] > L.elems[j + 1]) {
				int k = L.elems[j];
				L.elems[j] = L.elems[j + 1];
				L.elems[j + 1] = k;
			}
		}
	}
}

bool MergeList(SqList& LA, SqList LB) {
	int e = 0;
	for (int i = 1; i <= LB.length; i++) {
		if (GetElems(LB, i, e)) {
			int j = LA.length;
			if (!LocateElem(LA, e)) ListInsert(LA, ++j, e);
		}
	}
	return true;
}

bool MergeList_Sort(SqList LA, SqList LB, SqList& LC) {
	SortList(LA);
	SortList(LB);

	LC.length = LA.length + LB.length;
	LC.elems = new int[LC.length];

	int* pc = LC.elems;
	int* pa = LA.elems, * pb = LB.elems;
	int* pa_last = LA.elems + LA.length - 1;
	int* pb_last = LB.elems + LB.length - 1;

	while ((pa <= pa_last) && (pb <= pb_last)) {
		if (*pa <= *pb)* pc++ = *pa++;
		else *pc++ = *pb++;
	}
	while (pa <= pa_last)* pc++ = *pa++;
	while (pb <= pb_last)* pc++ = *pb++;

	return true;
}

void ListPrint(SqList& L) {
	cout << "顺序表的存储空间size:" << L.size << ",已保存元素个数length:" << L.length << endl;
	for (int i = 0; i < L.length; i++) {
		cout << L.elems[i] << " ";
	}
	cout << endl;
}

int main(void) {
	SqList list, link, LC;
	int count = 0, i = 0, e = 0;

	if (ListInit(list)) cout << "元素初始化成功!" << endl;
	if (ListInit(link)) cout << "元素初始化成功!" << endl;
	if (ListInit(LC)) cout << "元素初始化成功!" << endl;

	cout << "请输入你想插入的元素数量:";
	cin >> count;

	for (int i = 0; i < count; i++) {
		cout << "请输入想要添加的元素e:";
		cin >> e;
		if (ListAppend(list, e)) {
			cout << "元素添加成功!" << endl;
		}
		else {
			cout << "元素添加失败!" << endl;
		}
	}

	ListPrint(list);

	for (int i = 0; i < count; i++) {
		cout << "请输入想要添加的元素e:";
		cin >> e;
		if (ListAppend(link, e)) {
			cout << "元素添加成功!" << endl;
		}
		else {
			cout << "元素添加失败!" << endl;
		}
	}
	ListPrint(link);



	cout << "请输入要插入的位置和 要插入的数据元素:";
	cin >> i >> e;

	if (ListInsert(list, i, e)) {
		cout << "插入成功" << endl;
	}
	else {
		cout << "插入失败" << endl;
	}

	ListPrint(list);

	cout << "请输入要删除元素的位置:";
	cin >> i;
	if (ListDelete(list, i)) cout << "删除成功!" << endl;
	else cout << "删除失败!" << endl;
	ListPrint(list);

	if (MergeList_Sort(list, link, LC)) ListPrint(LC);
	else cout << "有序合并失败！" << endl;

	ListPrint(list);
	ListPrint(link);

	if (MergeList(list, link)) ListPrint(list);
	else cout << "合并失败!" << endl;

}
