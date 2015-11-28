#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

/* �m�[�h�̍\���� */
typedef struct _n {
	int id;              /* �Y�� */
	int num;             /* �l */
	struct _n *left;     /* �� -- ���ȎQ�� */
	struct _n *right;    /* �E -- ���ȎQ�� */
} _node;

/* �T����̔z�� */
int arry[] = { 3, 2, 9, 6, 1, 4, 7 };

/* �z��̒l��\�� */
void showarray(void)
{
	int i;

	printf("�T���� :");
	for (i = 0; i<7; i++) {
		printf("%d ", arry[i]);
	}
	printf("?n");
}

/* �񕪒T���؂̐��� -- �ċA�𗘗p*/
void maketree(_node *p1, int id, int num)
{
	_node *p2;

	/* �l�̑召�ɂ���č��E�ɐU�蕪���� */
	if (p1->num <= num) {    /* ��m�[�h���傫���Ƃ� */
							 /* �E��NULL�Ȃ炻���ɐV���ȃm�[�h���Ԃ牺���� */
		if (p1->right == NULL) {
			p2 = (_node*)malloc(sizeof(_node));
			p2->id = id;
			p2->num = num;
			p2->left = NULL;
			p2->right = NULL;
			p1->right = p2;
		}
		else {  /* NULL�łȂ���ΉE���̃m�[�h�Ɉړ� */
			maketree(p1->right, id, num);
		}
	}
	else {
		/* ����NULL�Ȃ炻���ɐV���ȃm�[�h���Ԃ牺���� */
		if (p1->left == NULL) {
			p2 = (_node*)malloc(sizeof(_node));
			p2->id = id;
			p2->num = num;
			p2->left = NULL;
			p2->right = NULL;
			p1->left = p2;
		}
		else {  /* NULL�łȂ���΍����̃m�[�h�Ɉړ� */
			maketree(p1->left, id, num);
		}
	}
}

/* �؍\�������ǂ��ĒT�� */
int search(_node *p, int n)
{
	while (p != NULL) {
		if (n == p->num) {
			printf("%d �� %d �ԖڂɌ��t����܂����B?n", n, p->id + 1);
			return(0);  /* �l�����t����ΏI�� */
		}
		else if (n <= p->num) {
			p = p->left;
		}
		else {
			p = p->right;
		}
	}
	/* ���[�v�𔲂��o���Ƃ������Ƃ͌��t����Ȃ������Ƃ������� */
	printf("%d �͌��t����܂���ł����B?n", n);
	return(-1);
}

/* ---------------------------------------------
main
---------------------------------------------- */
void main(void)
{
	_node *start, *p1;
	int i, n;

	/* �z��̒l��\�� */
	showarray();

	/* �T������l����� */
	printf("input number : ");
	scanf("%d", &n);

	printf("?n");

	/* �擪�̃m�[�h�������� */
	start = (_node*)malloc(sizeof(_node));
	start->id = 0;
	start->num = arry[0];
	start->left = NULL;
	start->right = NULL;
	p1 = start;

	/* �c��l����؍\���𐶐� */
	for (i = 1; i<7; i++) {
		maketree(p1, i, arry[i]);
	}

	/* �؍\�������ǂ��ĒT�� */
	search(p1, n);
	getchar();
	getchar();
}