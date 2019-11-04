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
	cout << "˳���Ĵ洢�ռ�size:" << L.size << ",�ѱ���Ԫ�ظ���length:" << L.length << endl;
	for (int i = 0; i < L.length; i++) {
		cout << L.elems[i] << " ";
	}
	cout << endl;
}

int main(void) {
	SqList list, link, LC;
	int count = 0, i = 0, e = 0;

	if (ListInit(list)) cout << "Ԫ�س�ʼ���ɹ�!" << endl;
	if (ListInit(link)) cout << "Ԫ�س�ʼ���ɹ�!" << endl;
	if (ListInit(LC)) cout << "Ԫ�س�ʼ���ɹ�!" << endl;

	cout << "��������������Ԫ������:";
	cin >> count;

	for (int i = 0; i < count; i++) {
		cout << "��������Ҫ��ӵ�Ԫ��e:";
		cin >> e;
		if (ListAppend(list, e)) {
			cout << "Ԫ����ӳɹ�!" << endl;
		}
		else {
			cout << "Ԫ�����ʧ��!" << endl;
		}
	}

	ListPrint(list);

	for (int i = 0; i < count; i++) {
		cout << "��������Ҫ��ӵ�Ԫ��e:";
		cin >> e;
		if (ListAppend(link, e)) {
			cout << "Ԫ����ӳɹ�!" << endl;
		}
		else {
			cout << "Ԫ�����ʧ��!" << endl;
		}
	}
	ListPrint(link);



	cout << "������Ҫ�����λ�ú� Ҫ���������Ԫ��:";
	cin >> i >> e;

	if (ListInsert(list, i, e)) {
		cout << "����ɹ�" << endl;
	}
	else {
		cout << "����ʧ��" << endl;
	}

	ListPrint(list);

	cout << "������Ҫɾ��Ԫ�ص�λ��:";
	cin >> i;
	if (ListDelete(list, i)) cout << "ɾ���ɹ�!" << endl;
	else cout << "ɾ��ʧ��!" << endl;
	ListPrint(list);

	if (MergeList_Sort(list, link, LC)) ListPrint(LC);
	else cout << "����ϲ�ʧ�ܣ�" << endl;

	ListPrint(list);
	ListPrint(link);

	if (MergeList(list, link)) ListPrint(list);
	else cout << "�ϲ�ʧ��!" << endl;

}
