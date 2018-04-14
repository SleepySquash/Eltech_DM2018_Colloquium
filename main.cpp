#include <iostream>
#include <stdio.h>
#include <locale.h>
#ifndef __APPLE__
#include <conio.h>
#endif
#include <string>
#ifndef __APPLE__
#include <malloc.h>
#endif

using namespace std;

int __getch()
{
#ifdef __APPLE__
	return getchar();
#else
	return _getch();
#endif
}

template<typename... Args> int _scanf(Args... TArgs)
{
#ifdef __APPLE__
	return scanf(TArgs...);
#else
	return scanf_s(TArgs...);
#endif
}

//                                         ���� ����                                                     \\
// ������ �������� �� ����� �/�++ � ����� Microsoft Visual Studio 2013 ���������� ����� 7301, 7305 � 7307.
//
// _getch() ������ �������� ������ � ���������� ��� ������ ��� �� ����� �������.
// ���� ��� _getch():
// 72 - ������� �����.
// 80 - ������� ����.
// 13 - Enter.
// 27 - Esc.
// ���� ��� ��������� ������ ����� �������� �� ��������� ��� ���������� ����������� _getch() ���������� ���� int, � ����� ������� ���� ����� ����������.
//
// ����������, ������������ ���� � ����:
// index - �������-����� ������.
// tmp - ��������� ����������, �������� � ���� �������� ������.
// module - ������� � ���������� �������� (��� ������ ������� ���� ������).
// prevIndex - �������-�����, ������� ��������� ��������� �������.
//
// ����� ������� (����� >) �� ���� �������� ������������ � ������� ����������� ������������� _getch() � ������ � ����������� �������.
// �������� ��� �� ���� ������������: ���� ����� _getch() ����� ���� ������ ������� �����, �� ���������� �������, ���������� ��� ������� ����.
// ����� ���������� ��������, ��� ������� �� ������ �� ������� �������� module.
//
// ���������� ��������� �������� �� ����: �������, �������� � ���� �������, ������ �� ������� � ���� ������ �������, �������, � ���� �������, ����� ������ � ���� �������.
//
// ������ ����� ������ ��������� ���� � ���� ����� (� �� �����) ���������, ������� ����������� ������ � �������� (� ����� ���������) ���� ���������.
// �� ���� ������ ����� ��������� �� ����� �������� ���������� � ���������������� ������� ������ ����������.
// ������ ����� ������ ���������� ���������� ���, ������� ��� ��� ��� ������� ������.
// ������ ����� ������ ���������� ���������� ���, ����� ��� � ��������� ���� ���� ������� ������������ ������� ���������.
// ������ ����� ������ ���������� ���������� ���, ����� ��� � ��������� ���� ���� ������� ������������ ����� ���������.
// ��������� � ������ ������ ����� ���������� � ������ ���� I ������ ��� ��������� "������".
//
// ������ ������� ����� ������� �� ������ - http://pozdnkov.vm2-leti.spb.ru/ucebnye-gruppy-1/plany-lekcij/kollokvium-po-dm/kollokvium-po-dm-2
// ������ ������������� ������� �� ������� ���������� - https://docs.google.com/spreadsheets/d/1X-aLv9Yl9oKm5RbzMNQT9eqwkyXjf6FtmMNYhdbeCRA/edit#gid=0
//
// �� ������ ������� ����:
// I ������� - ������� ����
// II ������� - ������
// III ������� - �������

bool inputSymbol(int &tmp, int &sign)
// ������� �������, 7305
{
	bool result;
	if ((tmp >= 48) && (tmp <= 57))
		result = true;
	else if ((tmp == 45) && (sign != -1))
	{
		sign = 1;
		result = true;
	}
	else
		result = false;

	return result;
}

void inputDig(int &digit)
// ������� �������, 7305
{
	bool flag = false;
	int tmp;
	digit = -1;
	do
	{
		tmp = __getch();
		if ((tmp >= 48) && (tmp <= 57) && (digit == -1))
		{
			digit = tmp - 48;
			cout << (char)tmp;
		}
		else if ((tmp == 13) && (digit != -1))
			flag = true;
	} while (!flag);
	cout << "\n";
}

void inputNumber(int &sign, int &size, int * &number)
// ������� �������, 7305
{
	bool isMinusWritten = false, flag = false, isNotZeroInside = false;
	int tmp, result = 0;
	size = 0;
	number = NULL;

	if (sign != -1)
		sign = 0;

	do
	{
		tmp = __getch();
		if (inputSymbol(tmp, sign))
		{
			if ((tmp == 45) && (!isMinusWritten) && (sign != -1))
			{
				isMinusWritten = true;
				cout << (char)tmp;
			}
			else if ((tmp != 45) && (((tmp == 48) && (isNotZeroInside)) || (tmp != 48)))
			{
				if (tmp != 48)
					isNotZeroInside = true;

				cout << (char)tmp;
				number = (int*)realloc(number, (size + 1) * sizeof(int));
				*(number + size) = tmp - 48;
				size++;
			}

			else if ((tmp == 48) && (!isNotZeroInside))
			{
				cout << (char)tmp;
				number = (int*)realloc(number, 1 * sizeof(int));
				*(number) = 0;
				size++;
				break;
			}
		}

		if (tmp == 13 || tmp == '\n')
		{
			if (size > 0)
				flag = true;
			else
				puts("������� �����!");
		}

	} while (!flag);
	cout << "\n";
}

void notZero(int &sign, int &size, int * &number)
// ������� �������, 7305
{
	size = 0;
	number = NULL;
	inputNumber(sign, size, number);

	do
	{
		if (*(number) == 0)
		{
			cout << "������� �����, �������� �� ����: ";
			inputNumber(sign, size, number);
		}
	} while (*(number) == 0);
}

int COM_NN_D(int n1, int n2, int *A1, int *A2)
// ��������� ����� 2- ���� ������ ������ �������, 1 - ���� ������ ������ �������, 0 - ���� ����� �����.
// ����� �����, ������ 7307
{
	int D = 0, i;

	if (n1 > n2)
		D = 2;
	else if (n1 < n2)
		D = 1;
	else if (n1 == n2)
		for (i = 0; i < n1; i++)
			if (A1[i] > A2[i])
			{
				D = 2;
				break;
			}
			else if (A1[i] < A2[i])
			{
				D = 1;
				break;
			}

	return D;
}

void MUL_Nk_N(int n, int *A1, int k, int **A10, int *n10)
///��������� ����� �� 10 � ������� k
// ����� �����, ������ 7307
{
	int i, m, *A2 = NULL;
	m = n + k;
	A2 = (int*)malloc(sizeof(int)*m);
	for (i = 0; i<n; i++) ///���������� ������� ��������� ������� ������� �������
		A2[i] = A1[i];

	for (; n<m; n++) ///���������� ������� ������ ����� �������� ���� (���������� ���������� � �������)
		A2[n] = 0;
	(*n10) = m;
	(*A10) = (int*)malloc(sizeof(int)*m);
	for (i = 0; i < m; i++) {
		(*A10)[i] = A2[i];
	}

	free(A2);
}

int *ABS_Z_N(int &b, int n, int *A)
// ���� �������, ������ 7301
{
	b = 0;
	return A;
}

int NZER_N_B(int n1, int * &A1)
//������� �������, ������ 7307
{
	int i, flag = 0, k = 0;
	for (i = 0; i<n1; i++)
	{
		if (A1[i] != 0)
		{
			flag = 1;
			break;
		}
	}

	return flag;
}

void MUL_ND_N(int n1, int dig, int *A1, int *n3, int **answer)
///��������� ������������ ����� �� �����
// ������� �������, ������ 7307
{
	int r = 0, p, q, i, k, z, *help_arr;
	help_arr = (int*)malloc((n1 + 1) * sizeof(int));
	for (i = n1 - 1; i >= 0; i--)
	{
		z = A1[i];
		q = z*dig + r;
		p = q % 10;
		help_arr[i + 1] = p;
		r = q / 10;
	}
	*n3 = n1;
	k = *n3;
	if (r != 0)
	{
		help_arr[0] = r;
		*n3 = n1 + 1;
		k = *n3;
	}
	else
	{
		for (i = 0; i<n1; i++)
		{
			help_arr[i] = help_arr[i + 1];
		}
	}

	(*answer) = (int*)malloc(sizeof(int)*(*n3));

	for (i = 0; i<k; i++)
	{
		(*answer)[i] = help_arr[i];
	}
	free(help_arr);

}

double LED_P_Q(int m, int *C)
// m � ������� ���������� � ������ C �������������
// ������� ����������� ���������� (������� ����������� - ����������� ��� ���������� ������� ������������)
// �������� ����������  �������� ���������� �� �������� �������� � ���� ����������.
// �������� �������, ������ 7307
{
	printf("\n�����: %lf", C[0]);
	puts("");
	return C[0]; //������� ������ ���������� ��� �������� ��� ������ ��� ���������� � ���������?
}

void TRANS_Q_Z(int b, int n, int *A, int n1, int *A1)
// ������ ������, ������ 7307
{
	int i;
	if ((n1 == 0) && (A1[0] == 1))    //�������: �������� �� ����������� ��������?
	{
		printf("����� ���������� � �����: ");
		if (b == 1)               //������ ������� ����� ���� ������� �� ����� ���������, ��� �� ������ :)
			printf("-");       //���� �� ������ ������ �������� � ���� ������ ��� �����, ������ �� ������ �����������
		for (i = n; i >= 0; i--)
			printf("%d", A[i]);
	}
	else
		printf("���������� ������� � ����� ��� ��� ����������� �� ����� 1");//���� �����������  - �� �������
	printf("\n");
}

void SUB_NN_N(int n1, int n2, int *A1, int *A2, int D, int *n6, int **A6)
// ����� �����, ������ 7307
///"��������� �� ������� �������� ������������ ����� ������� �������� ��� �������"
// ������� ������ - ��������
{
	int i, j, *A4;
	(*n6) = 0;

	A4 = (int*)malloc(n1 * sizeof(int));
	for (i = 0; i < n1; i++) { A4[i] = 0; }

	switch (D)
	{
		///������ ����� ������ �������
	case 2:
		for (i = n1 - 1; i >= 0; i--)
		{
			j = i - (n1 - n2);
			if (j >= 0) {
				A4[i] += A1[i] - A2[j];
				if (A4[i]<0) ///��������� ���������
				{
					A4[i] += 10;
					A4[i - 1] -= 1;
				}
			}
			else {
				A4[i] += A1[i];
				if (A4[i] < 0) { A4[i] += 10; A4[i - 1]--; }
			}
			(*n6)++;
		}

		while (A4[0] == 0 && (*n6) != 0) ///������������ ��������� ������� � ����� ������ 0 ����� ���������� �����������
		{
			for (i = 0; i < (*n6 - 1); i++)
			{
				A4[i] = A4[i + 1];
			}
			*n6 = *n6 - 1;
		}

		(*A6) = (int*)malloc(sizeof(int) * (*n6));
		for (i = 0; i < (*n6); i++) ///���������� ������� �������
		{
			*((*A6) + i) = A4[i];
		}
		break;
		///����� �����
	case 0:
		(*A6) = (int*)malloc(sizeof(int) * 1);
		(*A6)[0] = 0;

		break;
		///������ ������ �������
	case 1:
		printf("\n������! ������������ ����!\n");
		(*n6) = 0;
		break;

	}

}

void SUB_NDN_N(int *answer, int *A1, int n1, int n4, int D, int **A5, int *n5)
// ������� �������, ������ 7307
///��������� �� ������������ ������� ������������, ����������� �� ����� ��� ������ � ��������������� �����������.
{
	int *A6 = NULL, n6 = 1, i;
	if ((D == 2) || (D == 0))
	{
		SUB_NN_N(n1, n4, A1, answer, D, &n6, &A6);
		(*n5) = n6;
		(*A5) = (int*)malloc(sizeof(int)*(*n5));
		for (i = 0; i<n6; i++)
			(*A5)[i] = A6[i];
	}
	else
	{
		printf("������!");
		(*n5) = -1;
	}

	free(A6);
}

int POZ_Z_D(int sign, int sum, int *arr) {
	// ����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)
	// sign - ����, sum = ����� ������� �������, arr - ������ ���� �����
	// ��������� ��������, ������ 7301
	if (sign == 1) {//���� ���������� �������� ����� ����� ������� �� ����� ������������� - ���������� 1(����� �������������)
		return 1;
	}
	else {
		if (arr[0] == 0) {//���� ���������� �������� ����� �� ����� ������� �� ����� ������������� ��� ����� 0, ���� ������ ����� � ������� ����� 0  - ���������� 0(����� ����� 0)
			return 0;
		}
		else {            //���� ������ ����� � ������� �� ����� 0  - ���������� 2(����� �������������)
			return 2;
		}
	}
}

void MUL_ZM_Z(int *sign, int sum, int *arr)
// ��������� ��������, ������ 7301
//� ������� ����������� ������ ���� ����� ����� ���������, ����������� ���� � ����� ����� 1, �������� �� ���� �����(0 - ������������� ��� ����, 1 - ������������)
{
	if (*sign == 1) {//���� ���������� �������� ����� ����� ������� �� ����� ������������� � ��� ��������� �������� ������������� �����
		cout << "����� ��������� �� (-1) ����� ��������: ";
		for (int i = 0; i <= sum; i++) {
			cout << arr[i];
		}
		*sign = 0;
		cout << "\n";
	}
	else {
		if (arr[0] == 0) {//���� ���������� �������� ����� �� ����� ������� �� ����� g����������� ��� ����� 0, ���� ������ ����� � ������� ����� 0  - ����� ����� 0 � ��� ��������� �� (-1) �������� 0
			cout << "����� ��������� �� (-1) ��������: ";
			for (int i = 0; i < sum; i++) {
				cout << arr[i];
			}
			cout << "\n";
		}
		else {            //���� ������ ����� � ������� �� ����� 0  - ����� ������������� � ��� ��������� �� (-1) �������� ������������� �����
			cout << "����� ��������� �� (-1) ��������: -";
			for (int i = 0; i <= sum; i++) {
				cout << arr[i];
			}
			*sign = 1;
			cout << "\n";
		}
	}
}

int TRANS_N_Z(int b, int n, int *A) {
	//���� �������, ������ 7301
	if ((b != 0) || (A[0] == 0)) {
		return 2;
	}
	else return b;
}

int TRANS_Z_N(int b, int n, int *A) {
	//���� �������, ������ 7301
	if (b == 1)
		return -1;
	else if (A[0] == 0)
		return -2;
	else
		return *A;
}

int ADD_1N_N(int m, int * &A)
// ������� ��������, ������ 7307
// ���������� ����� ������� ������� (������_�������-1)
// !��� ������� ����� �������� ������ ������� (��������� � ������� �������)
{
	if (A == NULL)
	{
		A = (int*)malloc(sizeof(int));
		A[0] = 1;

		return 1;
	}

	if (m - 1 == 0)
		A[0]++;

	for (int i = m - 1; i > 0; i--) //��� ������ ����� � ����� ���� ���� �� ���� �� 9
	{
		if (A[i]<9)
		{
			A[i]++; //����������� �������
			i = -1;   //����� �� �����
		}
		else
		{
			A[i - 1]++;
			A[i] = 0;
			if (A[i - 1] != 10) { i = -1; }
		}
	}
	if (A[0] == 10) //������, ����� ���� ������� ��������, ��������� ������ �� �������
	{
		A = (int*)realloc(A, (m + 2) * sizeof(int));
		if (!A)  //�������� �� ��������� ������
		{
			printf("Allocation error.");
			exit(1);
		}
		A[0] = 1; //������ ������� �������, ���������-����
		for (int i = 1; i<m + 2; i++) //���������� ��������� ��������� ������
		{
			A[i] = 0;
		}
		m++;
	}
	return m;
}

void DIV_NN_Dk(int n1, int n2, int *A1, int *A2, int D, int **A11, int *n11)
///"���������� ������ ����� ������� �������� ������������ �� �������, ����������� �� 10^k, ��� k - ����� ������� ���� ����� (����� ��������� � ����)"
// ����� �����, ������ 7307
{
	int *A6 = NULL, n6 = 1, i, k = 0, m = 0, *A10 = NULL, n10 = 1, F, *A3 = NULL, n3 = 1;
	A3 = (int*)malloc(n1 * sizeof(int));
	for (i = 0; i<n1; i++)
		A3[i] = A1[i];
	n3 = n1;
	if (D == 2)
	{
		F = COM_NN_D(n2, n2, A1, A2); ///��������� ���� �� ����� 2 �����

		if ((F == 2) || (F == 0)) ///����� ������� �����
			k = n3 - n2;
		else
			k = n3 - n2 - 1;

		MUL_Nk_N(n2, A2, k, &A10, &n10); ///��������� ����� �� 10^k

		F = COM_NN_D(n3, n10, A3, A10);


		while (F != 1) ///���� �� ��������� ������� �����
		{
			SUB_NN_N(n3, n10, A3, A10, F, &n6, &A6);
			m++;
			F = COM_NN_D(n6, n10, A6, A10);

			n3 = n6; ///����������� ����������� ��������, ����� ������� ��������� �������� � �����
			A3 = (int*)realloc(A3, n3 * sizeof(int));
			for (i = 0; i<n3; i++)
				A3[i] = A6[i];
			n6 = 1;
			A6 = (int*)realloc(A6, n6 * sizeof(int));
			A6[0] = 0;
		}
		(*n11) = 1;
		(*A11) = (int*)malloc(sizeof(int)*(*n11));
		(*A11)[0] = m;
	}
	else
	{
		printf("\n������!");

	}
	free(A10);
	free(A6);
	free(A3);
}

void ADD_NN_N(int n1, int n2, int &resultN, int *first, int *second, int * &result)
// ����� �����, ������ 7307
{
	int sum, i;
	bool extraNum = false;

	if (n1 > n2)
		resultN = n1;
	else
		resultN = n2;

	n2--; // ��� ����
	n1--;
	result = NULL;

	result = (int*)realloc(result, (resultN + 1) * sizeof(int));



	if (n1 > n2) // ���������� ������ � ���������� �������
	{
		for (int i = 0; i < (n1 - n2); i++)
			*(result + i) = *(first + i);

		for (int i = (n1 - n2); i <= n1; i++)
			*(result + i) = 0;
	}
	else
	{
		for (int i = 0; i < (n2 - n1); i++)
			*(result + i) = *(second + i);


		for (int i = (n2 - n1); i <= n2; i++)
			*(result + i) = 0;

	}

	if (n1 > n2) // ��� �������
	{
		for (i = n1; i >= (n1 - n2); i--)
		{
			if (extraNum)
			{
				sum = 1;
				extraNum = false;
			}
			else
				sum = 0;

			sum += *(first + i) + *(second + i - (n1 - n2));
			if (sum > 9)
			{
				sum %= 10;
				extraNum = true;
			}

			*(result + i) = *(result + i) + sum;
		}
		if (extraNum && (i == -1))
		{
			for (int i = resultN; i >= 1; i--)
				*(result + i) = *(result + (i - 1));
			resultN++;
			*(result) = 1;
		}
		else if (extraNum)
		{
			*(result + i) = *(result + i) + 1;
		}
	}
	else
	{
		for (i = n2; i >= (n2 - n1); i--)
		{
			if (extraNum)
			{
				sum = 1;
				extraNum = false;
			}
			else
				sum = 0;

			sum += *(second + i) + *(first + i - (n2 - n1));
			if (sum > 9)
			{
				sum %= 10;
				extraNum = true;
			}

			*(result + i) = *(result + i) + sum;
		}
		if (extraNum && (i == -1))
		{
			for (int i = resultN; i >= 1; i--)
				*(result + i) = *(result + (i - 1));
			resultN++;
			*(result) = 1;
		}
		else if (extraNum)
		{
			*(result + i) = *(result + i) + 1;
		}
	}
}

int INT_Q_B(int b, int n, int *A, int n1, int *A1)
// ������ ������, ������ 7307
{
	int first = 0, second = 0;
	for (int i = 0; i < n; i++)
	{
		first *= 10;
		first += *(A + i);
	}
	for (int i = 0; i < n1; i++)
	{
		second *= 10;
		second += *(A1 + i);
	}

	if (first % second == 0)
		return 1;
	else
		return 0;
}

int TRANS_Z_Q(int b, int n, int *A, int n1, int *A1)
//���� �������, ������ 7301
{
	A1[0] = 1;//����������� ���������� ������ �������
	n1 = 1;
	return *A1;
}

void MUL_NN_N(int n0, int n1, int *A0, int *A1, int &nresult, int * &result)
//������ �������, ������ 7301
//�������������: MUL_NN_N(n0, n1, A0, A1, &nresult, &result)
//               n1 - ���������� ���� � ������ �����
//               n2 - ���������� ���� �� ������ �����
//               A0 - ������ ���� ������� ����� (��� ������� ������� - ��� ������ ������)
//               �1 - ������ ���� ������� ����� (��� ������� ������� - ��� ������ ������)
//               nresult - ���� ����� �������� ���������� ���� �����-����������
//               result - ��� ����� ������ ���� �����-���������� (��� ������� ������� - ��� ������ �������)
//���������� �������� nresult �������, � result ������ ����� �������� NULL ��� nullptr �� ��������� ������� � ������� ������.
{
	int i, j;
	int *tmp = NULL, ntmp = 0;
	int *add = NULL, nadd = 0;
	int ntemp = 1, *temp;
	int ntmpresult = 0, *tmpresult = NULL;

	temp = (int*)malloc(sizeof(int));
	temp[ntemp] = 0;

	for (i = 0; i<n1; i++)
	{
		MUL_ND_N(n0, A1[i], A0, &ntmp, &tmp);
		MUL_Nk_N(ntmp, tmp, n1 - i, &add, &nadd);
		ADD_NN_N(ntemp, nadd, ntmpresult, temp, add, tmpresult);
		ntemp = ntmpresult;
		temp = (int*)realloc(temp, (ntemp) * sizeof(int));
		for (j = 0; j<ntemp; j++)
			temp[j] = tmpresult[j];

		tmpresult = NULL; ntmpresult = 0;
		add = NULL; nadd = 0;
		ntmp = 0; tmp = NULL;
	}

	ntemp--;
	while ((*(temp) == 0) && (ntemp > 1))
	{
		*(temp) = *(temp + 1);
		ntemp--;
	}

	nresult = ntemp;
	result = (int*)malloc(sizeof(int)*(ntemp));
	for (i = 0; i < ntemp; i++)
		(result[i]) = temp[i];

	free(tmp);
	free(add);
	free(tmpresult);
}

void MUL_ZZ_Z(int sizeFirst, int sizeSecond, int *first, int *second, int markFirst, int markSecond, int &sizeResult, int * &result, int &markResult)
// ������ �������, ������ 7301
{
	int isPositiveFirst, isPositiveSecond;
	markResult = 1;
	MUL_NN_N(sizeFirst, sizeSecond, first, second, sizeResult, result);

	isPositiveFirst = POZ_Z_D(markFirst, sizeFirst, first);
	isPositiveSecond = POZ_Z_D(markSecond, sizeSecond, second);

	if (isPositiveFirst == isPositiveSecond)
		ABS_Z_N(markResult, sizeResult, result);
}

void DER_PP_P(int m, int *C)
{
	int i, j = 0;
	for (i = 0; i <= 2 * m + 1; i = i + 2)
	{
		printf("���������: %d, �����������: %d", C[i] * j, C[i + 1]);
		j++;
	}
}

void ADD_ZZ_Z(int *sum1, int *arr1, int *sign1, int *sum2, int *arr2, int *sign2, int *sum3, int *&arr3, int *sign3) {
	int D = 2;
	if (*sign1 == *sign2) {//���� ����� � ����� ���������� - ���������� ������ ����� � ������ ���� ����� ����� ������ ������ ���������
		ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
		*sign3 = *sign1;
		*sum3 = *sum3;
	}
	else {
		if (POZ_Z_D(*sign1, *sum1, arr1) == 2 || POZ_Z_D(*sign1, *sum1, arr1) == 0) {//���� ����� �� �����, �� �� ���������� ����� �� ����� �� ������ ������, ������������� ��� �������������, ���� ������������� ������ �� �� �������� �� �������������� ������������� �� ������ � ����������� ����� ����� ���� �����
			if (COM_NN_D((*sum1), (*sum2), arr1, arr2) == 2 || COM_NN_D(*sum1, *sum2, arr1, arr2) == 0) {//���� ������������� ������ �� �������� �� �������������� ������������� � ����������� ����� ����� ���� ����
				*sign3 = 0;
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);

			}
			else {
				*sign3 = 1;
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
			}

		}
		if (POZ_Z_D(*sign2, *sum2, arr2) == 2 || POZ_Z_D(*sign2, *sum2, arr2) == 0) {
			if (COM_NN_D((*sum2), (*sum1), arr2, arr1) == 2 || COM_NN_D(*sum2, *sum1, arr2, arr1) == 0) {
				*sign3 = 0;
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);

			}
			else {
				*sign3 = 1;
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
			}

		}
	}
}

void SUB_ZZ_Z(int *sum1, int *arr1, int *sign1, int *sum2, int *arr2, int *sign2, int *sum3, int *&arr3, int *sign3) {
	int D = 2;
	//if (COM_NN_D(*sum1, *sum2, arr1, arr2) == 2 || COM_NN_D(*sum1, *sum2, arr1, arr2) == 0) {//�������� ����� ������ ������� ��� ����� ��� ����� ����� � �������� �������������� ���
	//    *sum3 = *sum1;
	//}
	//else {
	//    *sum3 = *sum2;
	//}
	//int *arr3 = new int[*sum3 + 2];//������� ������
	if (*sign1 != *sign2) {//���� ����� � ����� ������ - ���������� ������ ����� � ������ ���� ����� ����� ������ ����� �������
		if (*sign2 == 1) {
			ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
			*sign3 = 0;
		}
		else {
			ADD_NN_N((*sum1), (*sum2), (*sum3), arr1, arr2, *&arr3);
			*sign3 = 1;

		}
		//ADD_NN_N( (*sum1), (*sum2), (*sum3), arr1,  arr2, *&arr3);
		//*sign3 = *sign1;
	}
	else {
		if (POZ_Z_D(*sign1, *sum1, arr1) == 2 || POZ_Z_D(*sign1, *sum1, arr1) == 0) {//���� ����� ����� �� ���������� ������ ����� �����, ����� �������� ����� �� ��� �� ������ ������
			if (COM_NN_D((*sum1), (*sum2), arr1, arr2) == 2 || COM_NN_D((*sum1), (*sum2), arr1, arr2) == 0) {//� � ����������� �� ����� ���������� ��� �������� ������ ����� � ������ ������ ����
				*sign3 = 0;
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
				//������ ������ ���� ��� ����� 0, ������ ������ ����
			}                                                    //������ ������ - �������� �� ������� ������ � ������ ���� +
			else {                                                //� �������� ������ ������ ������� - �������� �� ������� ������ � ���� -
				*sign3 = 1;
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
			}

		}
		if (POZ_Z_D(*sign2, *sum2, arr2) == 1) {
			if (COM_NN_D((*sum2), (*sum1), arr2, arr1) == 2 || COM_NN_D((*sum2), (*sum1), arr2, arr1) == 0) {
				*sign3 = 0;
				SUB_NN_N((*sum2), (*sum1), arr2, arr1, D, sum3, &arr3);
			}                                                    //������ � ������ ������ ����
			else {                                                //������ ������ - �������� �� ������� ������ � ������ ���� -
				*sign3 = 1;                                        //� �������� ������ ������ ������� - �������� �� ������� ������ � ���� +
				SUB_NN_N((*sum1), (*sum2), arr1, arr2, D, sum3, &arr3);
			}

		}
	}
}

void MUL_QQ_Q(int b, int n0, int n1, int *A0, int *A1, int b_1, int n0_1, int n1_1, int *A0_1, int *A1_1, int &b_result, int &n0_result, int &n1_result, int *&A0_result, int *&A1_result)
///��������� ������� ����, ��.7307
//��������� ������
// ������ �����: n0 -������ ���������, n1 - ������ �����������, A0 - ������ ���������, A1 - ������ �����������;
//���������� n0_1 � �.�. ��� ������ �����
//(_result) - ���������� - ���������
{
	MUL_ZZ_Z(n0, n0_1, A0, A0_1, b, b_1, n0_result, A0_result, b_result);
	MUL_NN_N(n1, n1_1, A1, A1_1, n1_result, A1_result); //���������� ��� �������, ��� ��� ����������� - ����������� �����
														//����� �������� ������� ���������� �����
}

void DIV_QQ_Q(int b, int n0, int n1, int *A0, int *A1, int b_1, int n0_1, int n1_1, int *A0_1, int *A1_1, int &b0_result, int &b1_result, int &n0_result, int &n1_result, int * &A0_result, int * &A1_result)
///��������� ������� ����, ��.7307
//��������� ������
// ������ �����: n0 -������ ���������, n1 - ������ �����������, A0 - ������ ���������, A1 - ������ �����������;
//���������� n0_1 � �.�. ��� ������ �����
//(_result) - ���������� - ���������
{
	MUL_ZZ_Z(n0, n1_1, A0, A1_1, b, 0, n0_result, A0_result, b0_result);
	MUL_ZZ_Z(n1, n0_1, A1, A0_1, 0, b_1, n1_result, A1_result, b1_result);//���������� ��� �������, ��� ��� ����������� - ����������� �����
																		  //����� �������� ������� ���������� �����
}

void DIV_NN_N(int n1, int *A1, int n2, int *A2, int &nRes, int * &ARes)
//������� ������ 7305
{
	nRes = 0;
	ARes = NULL;
	int nFirst, nSecond, *AFirst, *ASecond;
	if (COM_NN_D(n1, n2, A1, A2) != 1)
	{
		nFirst = n1;
		AFirst = A1;

		nSecond = n2;
		ASecond = A2;
	}
	else
	{
		nFirst = n2;
		AFirst = A2;

		nSecond = n1;
		ASecond = A1;
	}

	nRes = 0;
	int nTemp = 0; int *ATemp = NULL;
	while (COM_NN_D(nFirst, nSecond, AFirst, ASecond) != 1)
	{
		SUB_NN_N(nFirst, nSecond, AFirst, ASecond, COM_NN_D(nFirst, nSecond, AFirst, ASecond), &nTemp, &ATemp);
		if (nRes != 0) { free(AFirst); } nFirst = nTemp; AFirst = ATemp;

		nRes = ADD_1N_N(nRes, ARes);
	}
}

void MOD_NN_N(int n1, int *A1, int n2, int *A2, int &nRes, int * &ARes)
//������� ������ 7305
{
	nRes = 0;
	ARes = NULL;
	int nFirst, nSecond, *AFirst, *ASecond;
	if (COM_NN_D(n1, n2, A1, A2) != 1)
	{
		nFirst = n1;
		AFirst = A1;

		nSecond = n2;
		ASecond = A2;
	}
	else
	{
		nFirst = n2;
		AFirst = A2;

		nSecond = n1;
		ASecond = A1;
	}

	nRes = 0;
	int nTemp = 0; int *ATemp = NULL; bool First = true;
	while (COM_NN_D(nFirst, nSecond, AFirst, ASecond) != 1)
	{
		SUB_NN_N(nFirst, nSecond, AFirst, ASecond, COM_NN_D(nFirst, nSecond, AFirst, ASecond), &nTemp, &ATemp);
		if (!First) { free(AFirst); }
		else { First = false; }
		nFirst = nTemp; AFirst = ATemp;
	}
	nRes = nFirst; ARes = (int*)malloc(sizeof(int)*nFirst);
	for (int i = 0; i < nFirst; i++)
		ARes[i] = AFirst[i];
}

void GCF_NN_N(int sizeFirst, int sizeSecond, int * first, int * second, int & nResult, int * &result)
// ������� �������, ������ 7305
{
	while ((NZER_N_B(sizeFirst, first) != 0) && (NZER_N_B(sizeSecond, second) != 0))
	{
		if (COM_NN_D(sizeFirst, sizeSecond, first, second) == 2)
		{
			nResult = 0;
			result = NULL;

			MOD_NN_N(sizeFirst, first, sizeSecond, second, nResult, result);

			first = NULL;
			first = (int*)malloc((nResult) * sizeof(int));
			sizeFirst = nResult;

			for (int i = 0; i < nResult; i++)
				*(first + i) = *(result + i);

		}
		else
		{
			nResult = 0;
			result = NULL;

			MOD_NN_N(sizeSecond, second, sizeFirst, first, nResult, result);

			second = NULL;
			second = (int*)malloc((nResult) * sizeof(int));
			sizeSecond = nResult;

			for (int i = 0; i < nResult; i++)
				*(second + i) = *(result + i);
		}
	}

	nResult = sizeSecond;
	result = NULL;
	result = (int*)malloc((nResult) * sizeof(int));
	for (int i = 0; i < nResult; i++)
		*(result + i) = *(second + i);
}

void LCM_NN_N(int sizeFirst, int sizeSecond, int * first, int * second, int & nResult, int * &result)
// ������� �������, ������ 7305
{
	int _nResult1, *_result1 = NULL,
		_nResult2, *_result2 = NULL;
	nResult = 0;
	result = NULL;
	GCF_NN_N(sizeFirst, sizeSecond, first, second, _nResult1, _result1);
	MUL_NN_N(sizeFirst, sizeSecond, first, second, _nResult2, _result2);
	DIV_NN_N(_nResult2, _result2, _nResult1, _result1, nResult, result);
}

void DIV_ZZ_Z(int markFirst, int markSecond, int sizeFirst, int sizeSecond, int * first, int * second, int & markResult, int & sizeResult, int * &result)
// ������� �������, ������ 7305
{
	if (POZ_Z_D(markFirst, sizeFirst, first) == POZ_Z_D(markSecond, sizeSecond, second))
		markResult = 0;
	else
		markResult = 1;

	sizeResult = 0;
	result = NULL;

	DIV_NN_N(sizeFirst, first, sizeSecond, second, sizeResult, result);
}

void MOD_ZZ_Z(int markFirst, int markSecond, int sizeFirst, int sizeSecond, int * first, int * second, int & markResult, int & sizeResult, int * &result)
// ������� �������, ������ 7305
{
	sizeResult = 0;
	result = NULL;

	int nFirst, nSecond, *AFirst, *ASecond,
		nTemp = 0, markSkip = 0;
	int *ATemp = NULL;
	bool First = true;
	markResult = 0;

	if (COM_NN_D(sizeFirst, sizeSecond, first, second) != 1)
	{
		nFirst = sizeFirst;
		AFirst = first;

		nSecond = sizeSecond;
		ASecond = second;
	}
	else
	{
		nFirst = sizeSecond;
		AFirst = second;

		nSecond = sizeFirst;
		ASecond = first;
	}

	while (COM_NN_D(nFirst, nSecond, AFirst, ASecond) != 1)
	{
		SUB_ZZ_Z(&nFirst, AFirst, &markSkip, &nSecond, ASecond, &markSkip, &nTemp, ATemp, &markResult);
		if (!First) { free(AFirst); }
		else { First = false; }
		nFirst = nTemp; AFirst = ATemp;
	}

	if (markFirst == 1)
		ADD_ZZ_Z(&nFirst, AFirst, &markFirst, &sizeSecond, second, &markSecond, &sizeResult, result, &markResult);
	else
	{
		if (nFirst == 0)
		{
			sizeResult = 1;
			result = (int*)malloc(sizeof(int)*nFirst);
			*(result) = 0;
		}
		else
		{
			sizeResult = nFirst;
			result = (int*)malloc(sizeof(int)*nFirst);
			for (int i = 0; i < nFirst; i++)
				result[i] = AFirst[i];
		}
	}
}

void RED_QQ_Q(int markFirst, int markSecond, int sizeNumer, int sizeDeno, int * numer, int * deno, int & markResult, int & sizeResultNumer, int & sizeResultDeno, int * & numerResult, int * &denoResult)
// ������� �������, ������ 7305
{
	sizeResultDeno = 0;
	sizeResultNumer = 0;
	numerResult = NULL;
	denoResult = NULL;

	if (markFirst == markSecond)
		markResult = 0;
	else
		markResult = 1;

	int *tmpResult = NULL, sizeTmpResult = 0, markSkip = 0;
	GCF_NN_N(sizeNumer, sizeDeno, numer, deno, sizeTmpResult, tmpResult);
	DIV_ZZ_Z(markSkip, markSkip, sizeNumer, sizeTmpResult, numer, tmpResult, markResult, sizeResultNumer, numerResult);
	DIV_ZZ_Z(markSkip, markSkip, sizeDeno, sizeTmpResult, deno, tmpResult, markResult, sizeResultDeno, denoResult);

	if (markFirst == markSecond)
		markResult = 0;
	else
		markResult = 1;
}

void ADD_QQ_Q(int markFirst, int markSecond, int sizeNumer1, int sizeDeno1, int * numer1, int * deno1, int sizeNumer2, int sizeDeno2, int * numer2, int * deno2,
	int & markResult, int & sizeResultNumer, int & sizeResultDeno, int * & numerResult, int * &denoResult)
	// ������� �������, ������ 7305
{
	sizeResultDeno = 0;
	sizeResultNumer = 0;
	numerResult = NULL;
	denoResult = NULL;

	if (markFirst == markSecond)
		markResult = 0;
	else
		markResult = 1;

	int * tmpFirst = NULL, sizeTmpFirst = 0,
		*tmpSecond = NULL, sizeTmpSecond = 0,
		markSkip = 0,

		sizeMultip1 = 0, sizeMultip2 = 0,
		*multip1 = NULL, *multip2 = NULL;

	LCM_NN_N(sizeDeno1, sizeDeno2, deno1, deno2, sizeResultDeno, denoResult);
	DIV_ZZ_Z(markSkip, markSkip, sizeResultDeno, sizeDeno1, denoResult, deno1, markResult, sizeMultip1, multip1);
	DIV_ZZ_Z(markSkip, markSkip, sizeResultDeno, sizeDeno2, denoResult, deno2, markResult, sizeMultip2, multip2);

	MUL_ZZ_Z(sizeNumer1, sizeMultip1, numer1, multip1, markSkip, markSkip, sizeTmpFirst, tmpFirst, markFirst);

	for (int i = 0; i < sizeTmpFirst; i++)
		cout << *(tmpFirst + i);
	puts("\n----------");

	MUL_ZZ_Z(sizeNumer2, sizeMultip2, numer2, multip2, markSkip, markSkip, sizeTmpSecond, tmpSecond, markSecond);
	for (int i = 0; i < sizeTmpSecond; i++)
		cout << *(tmpSecond + i);
	puts("\n----------");


	ADD_ZZ_Z(&sizeTmpFirst, tmpFirst, &markFirst, &sizeTmpSecond, tmpSecond, &markSecond, &sizeResultNumer, numerResult, &markResult);

	if (markFirst == markSecond)
		markResult = 0;
	else
		markResult = 1;
}


void naturalNum() // ������, � ������� ���� �������� � ������������ �������
{
	string module[14] = { "1. ��������� ����������� ����� ",
		"2. �������� �� ����",
		"3. ���������� 1",
		"4. �������� ����������� �����",
		"5. ��������� �� ������� �������� ������������...",
		"6. ��������� ������������ ����� �� �����",
		"7. ��������� ������������ ����� �� 10^k",
		"8. ��������� ����������� �����",
		"9. ��������� �� ������������ ������� ������������...",
		"10. ���������� ������ ����� ������� ��������...",
		"11. ������� �� ������� �������� ������������ �����...",
		"12. ������� �� ������� �������� ������������ �����...",
		"13. ��� ����������� �����",
		"14. ��� ����������� �����" };

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� ������
	int n0, n1, n2, n4, n5, n6, n10, n11, k, D, dig, m, nresult, sign = -1,
		*A = NULL,
		*A0 = NULL,
		*A1 = NULL,
		*A2 = NULL,
		*A3 = NULL,
		*A5 = NULL,
		*A6 = NULL,
		*A10 = NULL,
		*A11 = NULL,
		*answer = NULL,
		*result = NULL,
		n3 = 0;

	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������! ��������� ��������, ��� ������ ����� ������� �� ����������.\n"
				"��� ��������� ������� ������ �������� ��������������� ����� ����.\n"
				"�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 14; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}

		tmp = __getch();
		switch (tmp)
		{
		case 72:
			if (index > 0)
				index--;
			break;

		case 80:
			if (index < 13)
				index++;
			break;

#ifdef __APPLE__
		case 49:
			index = 0;
			break;
		case 50:
			index = 1;
			break;
		case 51:
			index = 2;
			break;
		case 52:
			index = 3;
			break;
		case 53:
			index = 4;
			break;
		case 54:
			index = 5;
			break;
		case 55:
			index = 6;
			break;
		case 56:
			index = 7;
			break;
		case 57:
			index = 8;
			break;
		case 65:
			index = 9;
			break;
		case 66:
			index = 10;
			break;
		case 67:
			index = 11;
			break;
		case 68:
			index = 12;
			break;
		case 69:
			index = 13;
			break;
		case 'f':
#endif
		case 13:
			prevIndex = -1;

			system("cls");
			switch (index)
			{
			case 0:
				// ����� �����, ������ 7307
				//���� ���������� ���� � ������
				puts("��������� ����������� �����: 2 - ���� ������ ������ �������, 0, ���� �����, 1 �����.");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				inputNumber(sign, n2, A2);

				D = COM_NN_D(n1, n2, A1, A2);
				printf("\n��������� ��������� = %d\n", D);
				system("pause");
				break;

			case 1:
				// ������� �������, ������ 7307
				//���� ���������� ���� � ������
				puts("�������� �� ����: ���� ����� �� ����� ����, �� ��� ����� ����");

				printf("������� �����: ");
				inputNumber(sign, n1, A1);

				D = NZER_N_B(n1, A1);

				if (D)
					cout << "���������: ����� �� ����� ����";
				else
					cout << "���������: ����� ����� ����";

				puts("");
				system("pause");
				break;

			case 2:
				// ������� ��������, ������ 7301
				// m - ����� ������� ������� (������_�������)
				// *A - ��������� �� ������ ������� ����
				// i -���������� ��� �����
				puts("���������� 1 � ������������ �����");

				printf("������� �����: ");
				inputNumber(sign, m, A);

				m = ADD_1N_N(m, A);

				printf("���������� �����: ");
				for (int i = 0; i < m; i++)
				{
					printf("%d", A[i]);
				}
				printf("\n");

				puts("");
				system("pause");
				break;

			case 3:
				// ����� �����, ������ 7307
				//���� ���������� ���� � ������
				puts("�������� ����������� �����");

				n5 = 1;

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				inputNumber(sign, n2, A2);

				ADD_NN_N(n1, n2, n5, A1, A2, A5);

				printf("\n�����: ");
				for (int i = 0; i<n5; i++)
					printf("%d", A5[i]);

				free(A1);
				free(A2);
				free(A5);

				puts("");
				system("pause");
				break;

			case 4:
				// ����� �����, ������ 7307
				// ���� ���������� ���� � ������
				n3 = 1;
				puts("��������� �� ������� �������� ������������ ����� ������� �������� ��� �������");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				inputNumber(sign, n2, A2);

				D = COM_NN_D(n1, n2, A1, A2);
				//  printf("Comparison result= %d\n", D);
				SUB_NN_N(n1, n2, A1, A2, D, &n3, &A3);
				printf("\n�����: ");
				for (int i = 0; i<n3; i++)
				{
					printf("%d", A3[i]);
					// printf("%d\n",n3);
				}
				puts("");
				free(A1);
				free(A2);
				free(A3);
				system("pause");
				break;

			case 5:
				// ������� �������, ������ 7307
				//���� ���������� ���� � ������
				puts("��������� ������������ ����� �� �����");

				printf("������� �����: ");
				inputNumber(sign, n1, A1);

				printf("������� �����: ");
				_scanf("%d", &dig);

				MUL_ND_N(n1, dig, A1, &n3, &answer);
				printf("�����: ");
				for (int i = 0; i<n3; i++)
					printf("%d", answer[i]);
				puts("");
				free(A1);
				free(answer);
				system("pause");
				break;

			case 6:
				// ����� �����, ������ 7307
				//���� ���������� ���� � ������
				puts("��������� ������������ ����� �� 10^k");

				printf("������� �����: ");
				inputNumber(sign, n1, A1);

				cout << "������� ������� k: ";
				inputDig(k);

				n10 = 1;
				MUL_Nk_N(n1, A1, k, &A10, &n10);
				puts("");
				cout << "�����: ";
				for (int i = 0; i < n10; i++)
					cout << *(A10 + i);

				puts("");
				system("pause");
				break;

			case 7:
				// ������ �������, ������ 7301
				puts("��������� ����������� �����");

				printf("������� ������ �����: ");
				inputNumber(sign, n0, A0);
				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);

				MUL_NN_N(n0, n1, A0, A1, nresult, result);

				cout << "�����: ";
				for (int i = 0; i < nresult; i++)
					cout << *(result + i);

				puts("");
				system("pause");
				break;

			case 8:
				// ������� �������, ������ 7307
				//���� ���������� ���� � ������
				n3 = 1;
				n4 = 0;
				n5 = 1;
				puts("��������� �� ������������ ������� ������������, ����������� �� ����� ��� ������ � ��������������� �����������");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				inputNumber(sign, n2, A2);

				printf("������� �����: ");
				inputDig(dig);

				D = COM_NN_D(n1, n2, A1, A2);
				MUL_ND_N(n2, dig, A2, &n4, &answer);
				SUB_NDN_N(answer, A1, n1, n4, D, &A5, &n5);

				printf("�����: ");

				for (int i = 0; i<n5; i++)
				{
					printf("%d", A5[i]);
				}

				free(A1);
				free(A2);
				free(answer);
				free(A5);

				puts("");
				system("pause");
				break;

			case 9:
				// ����� �����, ������ 7307
				n6 = 1;
				n11 = 1;
				puts("���������� ������ ����� ������� �������� ������������ �� �������, ����������� �� 10 ^ k, \n"
					"��� k - ����� ������� ���� �����(����� ��������� � ����)");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				inputNumber(sign, n2, A2);

				D = COM_NN_D(n1, n2, A1, A2);

				DIV_NN_Dk(n1, n2, A1, A2, D, &A11, &n11);
				if (A11 != NULL)
				{
					printf("\n����� = ");
					printf("%d", A11[0]);
				}
				else
				{
					printf("������!");
				}

				free(A1);
				free(A2);
				free(A6);
				free(A11);

				puts("");
				system("pause");
				break;

			case 10:
				// ������ �������, ������ 7305
				puts("������� �� ������� �������� ������������ ����� �� ������� ��� ������ ����������� � ��������(�������� ������� �� ����)");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				notZero(sign, n2, A2);

				DIV_NN_N(n1, A1, n2, A2, nresult, result);

				cout << "�����: ";
				for (int i = 0; i < nresult; i++)
					cout << *(result + i);

				puts("");
				system("pause");
				break;

			case 11:
				// ������ �������, ������ 7305
				puts("������� �� ������� �������� ������������ ����� �� ������� ��� ������ ����������� � ��������(�������� ������� �� ����))");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				notZero(sign, n2, A2);

				MOD_NN_N(n1, A1, n2, A2, nresult, result);

				cout << "�����: ";
				if (nresult == 0)
					cout << 0;
				else
					for (int i = 0; i < nresult; i++)
						cout << *(result + i);

				puts("");
				system("pause");
				break;

			case 12:
				// ������� �������, ������ 7305
				puts("��� ����������� �����");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				inputNumber(sign, n2, A2);

				GCF_NN_N(n1, n2, A1, A2, nresult, result);

				cout << "�����: ";
				for (int i = 0; i < nresult; i++)
					cout << *(result + i);

				puts("");
				system("pause");
				break;

			case 13:
				// ������� �������, ������ 7305
				puts("��� ����������� �����");

				printf("������� ������ �����: ");
				inputNumber(sign, n1, A1);
				printf("������� ������ �����: ");
				inputNumber(sign, n2, A2);

				LCM_NN_N(n1, n2, A1, A2, nresult, result);

				cout << "�����: ";
				for (int i = 0; i < nresult; i++)
					cout << *(result + i);

				puts("");
				system("pause");
				break;

			}
			break;
		}
#ifdef __APPLE__
	} while (tmp != 'q');
#else
} while (tmp != 27);
#endif
}

void totalNum() // ������, � ������� ��� ������ � ������ �������
{
	string module[10] = { "1. ���������� �������� �����",
		"2. ����������� ��������������� �����...",
		"3. ��������� ������ �� (-1)",
		"4. �������������� ������������ � �����",
		"5. �������������� ������ ���������������� � �����������",
		"6. �������� ����� �����",
		"7. ��������� ����� �����",
		"8. ��������� ����� �����",
		"9. ������� �� ������� �������� ������ ����� �� �������...",
		"10. ������� �� ������� �������� ������ ����� �� �������..." };

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� ������
	int *A = NULL, *arr = NULL, *first = NULL, *second = NULL, *result = NULL, *sum1 = NULL, *sum2 = NULL, *sum3 = NULL, *arr1 = NULL, *arr2 = NULL, *arr3 = NULL, *sign1, *sign2, *sign3,
		b = 0, n = 0,
		sign = 0, sum, sign11, tmpCase, sizeFirst, sizeSecond, markFisrt, markSecond, sizeResult, markResult;



	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������, ������ ����� �����, ���������� ������������� ������ �������.");
			puts("��������! ��������� ��������, ��� ������ ����� ������� �� ����������.\n"
				"��� ��������� ������� ������ �������� ��������������� ����� ����.\n"
				"�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 10; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}
		tmp = __getch();
		switch (tmp)
		{
		case 72:
			if (index > 0)
				index--;
			break;

		case 80:
			if (index < 9)
				index++;
			break;

#ifdef __APPLE__
		case 49:
			index = 0;
			break;
		case 50:
			index = 1;
			break;
		case 51:
			index = 2;
			break;
		case 52:
			index = 3;
			break;
		case 53:
			index = 4;
			break;
		case 54:
			index = 5;
			break;
		case 55:
			index = 6;
			break;
		case 56:
			index = 7;
			break;
		case 57:
			index = 8;
			break;
		case 65:
			index = 9;
			break;
		case 'f':
#endif
		case 13:
			prevIndex = -1;

			system("cls");
			switch (index)
			{
			case 0:
				// ���� �������, ������ 7301
				puts("���������� �������� �����, ��������� - �����������");

				printf("������� �����: ");
				inputNumber(b, n, A);

				ABS_Z_N(b, n, A);

				cout << "���������� �����: ";
				for (int i = 0; i < n; i++)
					cout << *(A + i);

				puts("");
				system("pause");
				break;

			case 1:
				// �������� ��������, ������ 7301
				puts("����������� ��������������� ����� (2 - �������������, 0 � ������ ����, 1 - �������������)");

				printf("������� �����: ");
				inputNumber(sign, sum, arr);

				sign11 = POZ_Z_D(sign, sum, arr);
				cout << "\n";
				cout << "���� �����: " << sign11 << "\n";

				free(arr);
				system("pause");
				break;

			case 2:
				// ��������� ��������, ������ 7301
				puts("��������� ������ �� (-1)");

				cout << "������� ����� �����: ";
				inputNumber(sign, sum, arr);

				MUL_ZM_Z(&sign, sum, arr);

				free(arr);
				system("pause");
				break;

			case 3:
				// ���� �������, ������ 7301
				puts("������� �� ������������ ����� � �����, ��������� - ���� �����");

				cout << "������� ����� �����: ";
				inputNumber(b, n, A);

				if (TRANS_N_Z(b, n, A) == 2)
					cout << "����� ������� �����������, �.�. ��� ������ ���� �����������";
				else
				{
					cout << "��������� - ���� �����: " << TRANS_N_Z(b, n, A);
					puts(" ");
					cout << "�����: ";
					for (int i = 0; i < n; i++)
						cout << A[i];
					cout << endl;
				}

				puts("");
				free(A);

				system("pause");
				break;

			case 4:
				// ���� �������, ������ 7301
				puts("������� �� ������ ���������������� ����� � �����������, ��������� - ����������� �����");

				cout << "������� ����� �����: ";
				inputNumber(b, n, A);

				tmpCase = TRANS_Z_N(b, n, A);
				if (tmpCase == -1)
					cout << "����� ������� �����������, �.�. ��� ������ ���� �����������";
				if (tmpCase == -2)
					cout << "����� ������� �����������, �.�. ����� 0 ������ ��������� � �����������";
				if ((tmpCase != -1) && (tmpCase != -2))
				{
					cout << "��������� - ������ � ������� � ������� �������: ";
					for (int i = 0; i < n; i++)
						cout << A[i];
					cout << endl;
					cout << "������� ����� - " << n << endl;
				}

				free(A);
				puts("");
				system("pause");
				break;

			case 5:
				// ��������� ��������, ������ 7301
				sum1 = (int*)malloc(1 * sizeof(int));
				sum2 = (int*)malloc(sizeof(int) * 1);
				sum3 = (int*)malloc(sizeof(int) * 1);
				sign1 = (int*)malloc(sizeof(int) * 1);
				sign2 = (int*)malloc(sizeof(int) * 1);
				sign3 = (int*)malloc(sizeof(int) * 1);
				*sum1 = 0;
				*sum2 = 0;
				*sum3 = 0;

				puts("�������� ����� �����");
				cout << "������� ������ ����� �����: ";
				inputNumber(*sign1, *sum1, arr1);
				cout << "������� ������ ����� �����: ";
				inputNumber(*sign2, *sum2, arr2);

				ADD_ZZ_Z(sum1, arr1, sign1, sum2, arr2, sign2, sum3, arr3, sign3);
				cout << "���������: ";

				if (*sign3 == 1) {
					cout << "-";
				}
				for (int i = 0; i < (*sum3); i++) {
					cout << arr3[i];
				}

				cout << "\n\n";
				system("pause");
				break;

			case 6:
				// ��������� ��������, ������ 7301
				sum1 = (int*)malloc(1 * sizeof(int));
				sum2 = (int*)malloc(sizeof(int) * 1);
				sum3 = (int*)malloc(sizeof(int) * 1);
				sign1 = (int*)malloc(sizeof(int) * 1);
				sign2 = (int*)malloc(sizeof(int) * 1);
				sign3 = (int*)malloc(sizeof(int) * 1);
				*sum1 = 0;
				*sum2 = 0;
				*sum3 = 0;

				cout << "������� ������ ����� �����: ";
				inputNumber(*sign1, *sum1, arr1);
				cout << "������� ������ ����� �����: ";
				inputNumber(*sign2, *sum2, arr2);

				SUB_ZZ_Z(sum1, arr1, sign1, sum2, arr2, sign2, sum3, arr3, sign3);
				cout << "���������: ";

				if (*sign3 == 1) {
					cout << "-";
				}
				for (int i = 0; i < (*sum3); i++) {
					cout << arr3[i];
				}

				cout << "\n\n";
				system("pause");
				break;

			case 7:
				// ������ �������, ������ 7301
				puts("��������� ����� �����");

				cout << "������� ������ ����� �����: ";
				inputNumber(markFisrt, sizeFirst, first);
				cout << "������� ������ ����� �����: ";
				inputNumber(markSecond, sizeSecond, second);

				sizeResult = 0;
				result = NULL;
				MUL_ZZ_Z(sizeFirst, sizeSecond, first, second, markFisrt, markSecond, sizeResult, result, markResult);

				cout << "�����: ";
				if (markResult)
					cout << "-";

				for (int i = 0; i < sizeResult; i++)
					cout << *(result + i);

				free(result);
				free(first);
				free(second);

				puts("");
				system("pause");
				break;

			case 8:
				// ������� �������, ������ 7305
				puts("������� �� ������� �������� ������ ����� �� ������� ��� ������ ����������� � �������� (�������� ������� �� ����)");

				cout << "������� ������ ����� �����: ";
				inputNumber(markFisrt, sizeFirst, first);
				cout << "������� ������ ����� �����: ";
				markSecond = -1;
				notZero(markSecond, sizeSecond, second);
				markSecond = 0;

				DIV_ZZ_Z(markFisrt, markSecond, sizeFirst, sizeSecond, first, second, markResult, sizeResult, result);

				cout << "�����: ";
				if (markResult)
					cout << "-";

				for (int i = 0; i < sizeResult; i++)
					cout << *(result + i);

				free(result);
				free(first);
				free(second);

				puts("");
				system("pause");

				break;

			case 9:
				// ������� �������, ������ 7305
				puts("������� �� ������� �������� ������ ����� �� ������� ��� ������ ����������� � �������� (�������� ������� �� ����)");

				cout << "������� ������ ����� �����: ";
				inputNumber(markFisrt, sizeFirst, first);
				cout << "������� ������ ����� �����: ";
				markSecond = -1;
				notZero(markSecond, sizeSecond, second);
				markSecond = 0;

				MOD_ZZ_Z(markFisrt, markSecond, sizeFirst, sizeSecond, first, second, markResult, sizeResult, result);

				cout << "�����: ";
				if (markResult)
					cout << "-";

				for (int i = 0; i < sizeResult; i++)
					cout << *(result + i);

				puts("");
				system("pause");
				break;
			}
			break;
		}
#ifdef __APPLE__
	} while (tmp != 'q');
#else
} while (tmp != 27);
#endif
}

void fractionNum() // ������, � ������� ��� ������ � �������
{
	string module[8] = { "1. ���������� �����",
		"2. �������� �� �����",
		"3. �������������� ������ � �������",
		"4. �������������� �������� � �����",
		"5. �������� ������",
		"6*. ��������� ������",
		"7. ��������� ������",
		"8. ������� ������ (�������� ������� �� ����)" };

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� ������
	int *A0_1, *A1_1, *A0_result, *A1_result, *A = NULL, *A0 = NULL, *A1 = NULL, **result = NULL,
		b = 0, b1, b2, b_1, n0, n0_1, n1_1, n0_result, n1_result, b_result, b0_result, b1_result, n = -1, n1 = -1, skipSign = -1;
	int markResult, sizeResultNumer, sizeResultDeno, *numerResult, *denoResult;

	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������, ������ ����� �����, ���������� ������������� ������ �������.");
			puts("�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 8; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}

		tmp = __getch();
		switch (tmp)
		{
		case 72:
			if (index > 0)
				index--;
			break;

		case 80:
			if (index < 7)
				index++;
			break;

#ifdef __APPLE__
		case 49:
			index = 0;
			break;
		case 50:
			index = 1;
			break;
		case 51:
			index = 2;
			break;
		case 52:
			index = 3;
			break;
		case 53:
			index = 4;
			break;
		case 54:
			index = 5;
			break;
		case 55:
			index = 6;
			break;
		case 56:
			index = 87;
			break;
		case 'f':
#endif
		case 13:
			prevIndex = -1;

			system("cls");
			switch (index)
			{
			case 0:
				// ������� �������, ������ 7305
				puts("���������� �����");

				printf("����������, ������� ���������: ");
				inputNumber(b1, n, A);
				printf("����������, ������� �����������: ");
				notZero(b2, n1, A1);

				RED_QQ_Q(b1, b2, n, n1, A, A1, markResult, sizeResultNumer, sizeResultDeno, numerResult, denoResult);

				puts("���������� ��������� �����:");
				cout << "���������:   ";

				if (markResult)
					cout << "-";

				for (int i = 0; i < sizeResultNumer; i++)
					cout << *(numerResult + i);

				cout << "\n�����������: ";
				for (int i = 0; i < sizeResultDeno; i++)
					cout << *(denoResult + i);

				puts("");
				system("pause");

				free(A);
				free(A1);
				break;

			case 1:
				// ������ ������, ������ 7307
				puts("�������� �� �����, ���� ������������ ����� �������� �����, �� ���, ����� ����");
				printf("������� ���������: ");
				inputNumber(b1, n, A);

				do
				{
					printf("������� �����������: ");
					inputNumber(b2, n1, A1);
					if (*(A1) == 0)
						puts("������� �����������, �������� �� ����!");
				} while (*(A1) == 0);

				if (b1 == b2)
					b = 0;
				else
					b = 1;

				if (INT_Q_B(b, n, A, n1, A1) == 1)//�� ���� ���� ��� ��� ��������
					puts("��, ����� �����");
				else
					puts("���, ����� �� �����");

				free(A); //������������ ������
				free(A1);

				puts("");
				system("pause");
				break;

			case 2:
				// ���� �������, ������ 7301
				puts("�������������� ������ � �������");

				cout << "������� �����:";
				inputNumber(b, n, A);

				A1 = (int*)malloc((n + 1) * sizeof(int));

				cout << "��������� - �����: " << endl;
				cout << "��������� : ";
				if (b == 1) cout << "-";
				for (int i = 0; i < n; i++)
					cout << A[i];
				cout << endl;
				cout << "����������� : ";
				cout << TRANS_Z_Q(b, n, A, n1, A1);
				free(A);
				free(A1);

				puts("\n");
				system("pause");
				break;

			case 3:
				// ������ ������, ������ 7307
				puts("�������������� �������� � ����� (���� ����������� ����� 1)");

				printf("����������, ������� ���������: ");
				inputNumber(b, n, A);
				printf("����������, ������� �����������: ");
				notZero(b, n1, A1);

				TRANS_Q_Z(b, n, A, n1, A1);//�� ���� ���� ��� ��� ��������
				free(A); //������������ ������
				free(A1);

				system("pause");
				break;

			case 4:

				// ������� �������, 7305
				printf("����������, ������� ��������� ������ �����: ");
				inputNumber(b1, n0, A0);
				printf("����������, ������� ����������� ������ �����: ");
				notZero(b2, n0_1, A0_1);


				printf("����������, ������� ��������� ������ �����: ");
				inputNumber(b, n1, A1);
				printf("����������, ������� ����������� ������ �����: ");
				notZero(b_1, n1_1, A1_1);

				if (b1 != b2)
					b1 = 1;
				else
					b1 = 0;

				if (b != b_1)
					b = 1;
				else
					b = 0;

				ADD_QQ_Q(b1, b, n0, n0_1, A0, A0_1, n1, n1_1, A1, A1_1, markResult, sizeResultNumer, sizeResultDeno, numerResult, denoResult);

				puts("���������� ��������� �����:");
				cout << "���������:   ";

				if (markResult)
					cout << "-";

				for (int i = 0; i < sizeResultNumer; i++)
					cout << *(numerResult + i);

				cout << "\n�����������: ";
				for (int i = 0; i < sizeResultDeno; i++)
					cout << *(denoResult + i);

				puts("");
				system("pause");

				free(A);
				free(A1);
				break;
			case 5:
				break;

			case 6:
				// ���� �������, ������ 7307
				puts("��������� ������");

				printf("������� ��������� ������ �����: ");
				inputNumber(b, n0, A0);
				printf("������� ����������� ������ �����: ");
				notZero(skipSign, n1, A1);

				printf("\n������� ��������� ������ �����: ");
				inputNumber(b_1, n0_1, A0_1);
				printf("������� ����������� ������ �����: ");
				notZero(skipSign, n1_1, A1_1);

				MUL_QQ_Q(b, n0, n1, A0, A1, b_1, n0_1, n1_1, A0_1, A1_1, b_result, n0_result, n1_result, A0_result, A1_result); //��������� ������

				printf("\n���������: ");

				if (b != b_1)
					cout << "-";

				for (int i = 0; i<n0_result; i++)
					printf("%d", A0_result[i]);
				printf("/");
				for (int i = 0; i<n1_result; i++)
					printf("%d", A1_result[i]);

				free(A0);
				free(A1);
				free(A0_result);
				free(A1_result);
				free(A1_1);
				free(A0_1);

				puts("");
				system("pause");
				break;

			case 7:
				// ���� �������, ������ 7307
				puts("������� ������");
				printf("������� ��������� ������ �����: ");
				notZero(b, n0, A0);
				printf("������� ����������� ������ �����: ");
				inputNumber(skipSign, n1, A1);

				printf("\n������� ��������� ������ �����: ");
				inputNumber(b_1, n0_1, A0_1);
				printf("������� ����������� ������ �����: ");
				notZero(skipSign, n1_1, A1_1);

				DIV_QQ_Q(b, n0, n1, A0, A1, b_1, n0_1, n1_1, A0_1, A1_1, b0_result, b1_result, n0_result, n1_result, A0_result, A1_result);  //������� ������

				printf("\n���������: ");
				if (b0_result != b1_result)
					printf("-");

				for (int i = 0; i<n0_result; i++)
					printf("%d", A0_result[i]);
				printf("/");
				for (int i = 0; i<n1_result; i++)
					printf("%d", A1_result[i]);

				free(A0);
				free(A1);
				free(A0_result);
				free(A1_result);
				free(A1_1);
				free(A0_1);

				puts("");
				system("pause");
				break;
			}
			break;
		}
#ifdef __APPLE__
	} while (tmp != 'q');
#else
} while (tmp != 27);
#endif

}

void polyNum() // ������, � ������� ��� ������ � ������������
{
	string module[13] = { "1*. �������� �����������",
		"2*. ��������� �����������",
		"3*. ��������� ���������� �� ������������ �����",
		"4. ��������� ���������� �� x^k",
		"5. ������� ����������� ����������",
		"6*. ������� ����������",
		"7*. ��������� �� ���������� ��� ������������...",
		"8*. ��������� �����������",
		"9*. ������� �� ������� ���������� �� ���������...",
		"10*. �������� �� ������� ���������� �� ��������� ...",
		"11*. ��� �����������",
		"12. ����������� ����������",
		"13*. �������������� ���������� � ������� ����� � �������" };

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	// ���������� ��� case
	int m,
		*C = NULL;
	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("��������, ������ ����� �����, ���������� ������������� ������ �������.");
			puts("��������! ��������� ��������, ��� ������ ����� ������� �� ����������.\n"
				"��� ��������� ������� ������ �������� ��������������� ����� ����.\n"
				"�������� �������, ������� ������ ���������:\n");

			for (int i = 0; i < 13; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}

		tmp = __getch();
		switch (tmp)
		{
		case 72:
			if (index > 0)
				index--;
			break;

		case 80:
			if (index < 12)
				index++;
			break;

#ifdef __APPLE__
		case 49:
			index = 0;
			break;
		case 50:
			index = 1;
			break;
		case 51:
			index = 2;
			break;
		case 52:
			index = 3;
			break;
		case 53:
			index = 4;
			break;
		case 54:
			index = 5;
			break;
		case 55:
			index = 6;
			break;
		case 56:
			index = 7;
			break;
		case 57:
			index = 8;
			break;
		case 65:
			index = 9;
			break;
		case 66:
			index = 10;
			break;
		case 67:
			index = 11;
			break;
		case 68:
			index = 12;
			break;
		case 'f':
#endif
		case 13:
			prevIndex = -1;

			system("cls");
			switch (index)
			{
			case 0:
				break;

			case 1:
				break;

			case 2:
				break;

			case 3:
				// ������ ������, ������ 7307
				break;

			case 4:
				// ������� ��������, ������ 7307
				puts("������� ����������� ����������");
				cout << "������� ������� ����������: ";
				cin >> m;
				cout << "������� ������������: \n";
				C = (int*)realloc(C, (m + 1) * sizeof(int));
				for (int i = 0; i<m; i++)
				{
					cout << "c[" << i + 1 << "] = ";
					cin >> *(C + i);
				}
				LED_P_Q(m, C);
				system("pause");
				break;

			case 5:
				break;

			case 6:
				break;

			case 7:
				break;

			case 8:
				break;

			case 9:
				break;

			case 10:
				break;

			case 11:
				// ����� ���������, ������ 7307
				printf("������� ������� ������� ����������: ");
				_scanf("%d", &m);

				C = (int*)realloc(C, (2 * m + 2) * sizeof(int));

				printf("������� ������������ ����������:\n");

				for (int i = 2 * m + 1; i >= 0; i = i - 2) // ���� ���������� � ������������ ������� ����������
				{
					printf("���������: %");
					_scanf("%d", &C[i - 1]);
					printf("�����������: ");
					do
					{
						_scanf("%d", &C[i]);
						if (&C[i] == 0)
							cout << "����� ������ ���� �� ����� ����!";
					} while (&C[i] == 0);

					_scanf("%d", &C[i]);
				}
				DER_PP_P(m, C);

				puts("");
				system("pause");
				break;

			case 12:
				break;
			}
			break;
		}
#ifdef __APPLE__
	} while (tmp != 'q');
#else
} while (tmp != 27);
#endif
}

void modulePick() // ����� ������
{
	string module[4] = { "1. ����������� ����� � �����",
		"2. ����� �����",
		"3. ������������ ����� (�����)",
		"4. ��������� � ������������� ��������������" };

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("�������� ������, � ������� �� ������ ���������� ����������:\n");

			for (int i = 0; i < 4; i++)
			{
				if (i != index)
					cout << " " << module[i] << "\n";
				else
					cout << ">" << module[i] << "\n";
			}

			puts("\n��� �������� � ������� ���� ������� Esc.");
		}
		tmp = __getch();
		switch (tmp)
		{
		case 72:
			if (index > 0)
				index--;
			break;

		case 80:
			if (index < 3)
				index++;
			break;

#ifdef __APPLE__
		case 49:
			index = 0;
			break;
		case 50:
			index = 1;
			break;
		case 51:
			index = 2;
			break;
		case 52:
			index = 3;
			break;
		case 'f':
#endif
		case 13:
			prevIndex = -1;

			switch (index)
			{
			case 0:
				naturalNum();
				break;

			case 1:
				totalNum();
				break;

			case 2:
				fractionNum();
				break;

			case 3:
				polyNum();
				break;

			}
			break;
		}
#ifdef __APPLE__
	} while (tmp != 'q');
#else
} while (tmp != 27);
#endif
}

void devTeam() // ������� �������������
{
	system("cls");
	puts("������ �����, ��������������� ���� ������:\n"
		"����������:                      ������������:\n"
		"������� �������, ������ 7305     ����� �����, ������ 7307\n"
		"                                 ������� �������, ������ 7307\n"
		"                                 ������� ��������, ������ 7307\n"
		"                                 ������ ������, ������ 7307\n"
		"������������� �� ��������:       ���� �������, ������ 7307\n"
		"������ �������, ������ 7305      ��������� �������, ������ 7307\n"
		"                                 ����� ���������, ������ 7307\n"
		"                                 ��������� ��������, ������ 7301\n"
		"                                 ������ �������, ������ 7301\n"
		"                                 ��������� �������, ������ 7301\n\n"
		"��� �������� � ������� ���� ������� Esc.");
	do
	{
#ifdef __APPLE__
	} while (__getch() != 'q');
#else
} while (__getch() != 27);
#endif
}

void fixJournal() // ������ ���� �����������
{
	system("cls");
	puts("������ 1.0 BETA - ������ ���������: \n"
		"1. ������ ���������� �������\n"
		"2. ������� ������ � �������������\n"
		"3. ����� ��� ���������� ���������\n"
		"4. ������� �������:\n"
		"I  ������ (����) - ����� ����, ������� �������������, ������ �����������\n"
		"II ������ (������) - ����������� �����, ����� �����, ������������ �����, ���������� \n"
		"����� ������� 30.03.2018 � 15:15 \n\n"

		"������ 1.0.1 - ������ ���������: \n"
		"1. ������� ������� I ������ '������'\n"
		"2. ����������� ������ ������\n"
		"3. ����������� ��������� \n"
		"4. ������� ������ ����������� \n"
		"5. ����������� ����������� ����� ��� ��������� ������(������ ��� ��������� �������) \n"
		"����� ������� 30.03.2018 � 17:20 \n\n"

		"������ 1.1.0 - ������ ���������: \n"
		"1. �������� ���� ����, ���������� �� �������� ������� \n"
		"2. ��������� ������� N - 1 (III �������) \n"
		"3. ��������� ������� N - 2 (III �������) \n"
		"4. ��������� ������� N - 7 (III �������) \n"
		"5. ��������� ������� Z - 1 (III �������) \n"
		"6. ��������� ������� Q - 4 (III �������) \n"
		"����� ������� 30.03.2018 � 23:30 \n\n"

		"������ 1.2.0 - ������ ���������: \n"
		"1. ��������� ��������� ������������ � ����� ���� \n"
		"2. ��������� ����������� �� ���� ���������"
		"3. ��������� ������� N - 6 (III �������) \n"
		"4. ��������� ������� P - 5 (III �������) \n"
		"5. ������������ ����������� ����� ���� \n"
		"����� ������� 03.04.2018 � 00:30 \n\n"

		"������ 1.2.1 - ������ ���������: \n"
		"1. ��������� ������� N - 5 (III �������) \n"
		"2. ����������� ������ ������ \n"
		"����� ������� 03.04.2018 � 13:30 \n\n"

		"������ 1.2.2 - ������ ���������: \n"
		"1. ��������� ������� N - 9 (III �������) \n"
		"2. ���������� �������� ��� ������ ������ ���� \n"
		"2.1 ���������� �������� �� ������ ������������ ������ ��� ������� ������� ����, ������� �������� ������ \n"
		"3. ����������� ������ ������ \n"
		"����� ������� 03.04.2018 � 16:30 \n\n"

		"������ 1.2.3 - ������ ���������: \n"
		"1. ��������� ������� Z - 2 (III �������) \n"
		"2. ��������� ������� Z - 3 (III �������) \n"
		"3. ����������� ������ ������ \n"
		"����� ������� 04.04.2018 � 20:00 \n\n"

		"������ 1.2.4 - ������ ���������: \n"
		"1. ��������� ������� N - 3 (III �������) \n"
		"2. ��������� ������� Z - 4 (III �������) \n"
		"3. ��������� ������� Z - 5 (III �������) \n"
		"4. ����������� ������ ������ \n"
		"����� ������� 05.04.2018 � 12:30 \n\n"

		"������ 1.2.5 - ������ ���������: \n"
		"1. ��������� ������� N - 7 (III �������) \n"
		"2. ��������� ������� N - 10 (III �������) \n"
		"3. ����������� ������ ������ \n"
		"����� ������� 05.04.2018 � 20:30 \n\n"

		"������ 1.2.6 - ������ ���������: \n"
		"1. ��������� ������� N - 4 (III �������) \n"
		"2. ��������� ������� Q - 2 (III �������) \n"
		"3. ����������� ������ ������ \n"
		"����� ������� 06.04.2018 � 19:00 \n\n"

		"������ 1.2.7 - ������ ���������: \n"
		"1. ���������� ������� N - 4 (III �������) \n"
		"2. ��������� ������� Q - 3 (III �������) \n"
		"3. ����������� ������ ������ \n"
		"����� ������� 08.04.2018 � 02:00 \n\n"

		"������ 1.2.8 - ������ ���������: \n"
		"1. ��������� ������� N - 8 (III �������) \n"
		"2. ���������� ������� Z - 1 (III �������) \n"
		"3. ��������� ������� Z - 8 (III �������) \n"
		"4. ����������� ������ ������ \n"
		"����� ������� 08.04.2018 � 17:30 \n\n"

		"������ 1.2.9 RELEASE - ������ ���������: \n"
		"1. ��������� ������� N - 4 (III �������) \n"
		"2. ��������� ������� N - 10 (III �������) \n"
		"3. ��������� ������� P - 12 (III �������) \n"
		"4. ����������� ������ ������ \n"
		"����� ������� 10.04.2018 � 22:30 \n\n"

		"������ 1.2.10 RELEASE - ������ ���������: \n"
		"1. ��������� ������� Z - 6 (III �������) \n"
		"2. ��������� ������� Z - 7 (III �������) \n"
		"3. ��������� ������� N - 5 (III �������) \n"
		"4. ��������� ������� Q - 7 (III �������) \n"
		"5. ��������� ������� Q - 8 (III �������) \n"
		"6. ����������� ������ ������ \n"
		"����� ������� 11.04.2018 � 17:00 \n\n"

		"(����������) ������ 1.3.0 RELEASE - ������ ���������: \n"
		"1. ����������� ������� ���� ����� �� ���� �������� \n"
		"1.1 ���� ���� ����������� ������� \n"
		"1.2 ������ ������ ����� ������ ����� ��� ���� ����� \n"
		"2. ��������� ������� N - 3 (III �������) \n"
		"3. ��������� ������� N - 5 (III �������) \n"
		"4. ��������� ������� N - 11 (III �������) \n"
		"5. ��������� ������� N - 12 (III �������) \n"
		"6. ��������� ������� N - 13 (III �������) \n"
		"7. ��������� ������� N - 14 (III �������) \n"
		"9. ��������� ������� Z - 9 (III �������) \n"
		"10. ��������� ������� Z - 10 (III �������) \n"
		"11. ��������� ������� Q - 1 (III �������) \n"
		"12. ��������� ������� Q - 2 (III �������) \n"
		"13. ��������� �������������� �������, ����������� ������������� ��� \n"
		"14. ����������� ������ ������ \n"
		"15. ����������� ��������� ������ \n"
		"����� ������� 13.04.2018 � 00:00 \n\n"

		"������ ������� ������������ (��� ���������������� �������):\n"
		"1. ���������� ���� ������� �� ���� ������� (III �������) \n"
		"2. ����������� ���������\n"
		"3. �������� ����� ������������\n"
		"4. (���������) �������� '�����-������', ���������� �� ��������� ������\n"
		"4.1 (���������) �������� ����������� �������������� ���� ��������� ��������� ������\n"
		"5. (���������) ��������� ������������ ���������� ��������� \n"
		"����� ������� 30.03.2018 � 16:30 \n\n"

		"��� �������� � ������� ���� ������� Esc.");
	do
	{
#ifdef __APPLE__
	} while (__getch() != 'q');
#else
} while (__getch() != 27);
#endif
}

void help() // ������
{
	system("cls");
	puts("��� ������������� ��������, ����� � ����������� - ���������� �� �����:\n"
		"dimon@kezling.ru\n\n"
		"��� �������� � ������� ���� ������� Esc.");
	do
	{
#ifdef __APPLE__
	} while (__getch() != 'q');
#else
} while (__getch() != 27);
#endif
}

void menuPick() // ����� ����
{
	string mainMenu[4] = { "1. ������� � �������� ����� ���������",
		"2. ������� �������������",
		"3. ������ ����������",
		"4. ������" };

	// ���������� ��� ������ ������
	int index = 0, tmp, prevIndex = -1;

	do
	{
		if (prevIndex != index)
		{
			prevIndex = index;
			system("cls");
			puts("������ ���������: 1.3.0 RELEASE \n\n"
				"������������!\n"
				"��� ���������� ���������� ����������� ������� �����/���� �� ����������\n"
				"��� ����� � ����� ���� ����������� Enter, ��� ������ - Esc.\n"
				"��������� �������������!\n");

			for (int i = 0; i < 4; i++)
			{
				if (i != index)
					cout << " " << mainMenu[i] << "\n";
				else
					cout << ">" << mainMenu[i] << "\n";
			}

			puts("\n��� ������ �� ��������� ������� Esc.");
		}

		tmp = __getch();
		switch (tmp)
		{
		case 72:
			if (index > 0)
				index--;
			break;

		case 80:
			if (index < 3)
				index++;
			break;

#ifdef __APPLE__
		case 49:
			index = 0;
			break;
		case 50:
			index = 1;
			break;
		case 51:
			index = 2;
			break;
		case 52:
			index = 3;
			break;
		case 'f':
#endif
		case 13:
			prevIndex = -1;

			switch (index)
			{
			case 0:
				modulePick();
				break;

			case 1:
				devTeam();
				break;

			case 2:
				fixJournal();
				break;

			case 3:
				help();
				break;
			}
			break;
		}
#ifdef __APPLE__
	} while (tmp != 'q');
#else
} while (tmp != 27);
#endif
}

int main() // �������� �������
{
	setlocale(LC_ALL, "RUS"); // ����������� ������� �����������

							  /*int b = 0;
							  do
							  {
							  b = _getch();
							  cout << (int)b << "\n";
							  } while ((char)b != 'j'); */

	menuPick();

	system("cls");
	puts("������� ������������� ���������� ��� �� ������������� ����� ����������! \n"
		"�������� ������� ��� �����! \n"
		"�� ��������!");
	system("pause");
	return 0;
}
