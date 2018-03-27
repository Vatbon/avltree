/* АВЛ-дерево */
/*
** Убрать рекусрию из всех функций
** Организовать ввод и вывод дерева
*/

#include <stdlib.h>
#include <stdio.h>
#define POS_INPUTFILE 1
#define POS_OUTPUTFILE 2

/* Структура дерева */
struct Node {
	struct Node* left;
	struct Node* right;
	unsigned char height;
	int key;
	struct Node(int k){ key = k; left = right = 0; height = 1; }
};

/* balance factor */
int bfactor(struct Node* p) {
	return p->left - p->right;
}
/* Исправление высоты(корректировка) */
void fixheight(struct Node* p)
{
	unsigned char hl = p->left->height;
	unsigned char hr = p->right->height;
	p->height = (hl>hr ? hl : hr) + 1;
}
/* Правый поворот */
struct Node* rotateright(struct Node* p) {
	struct Node* q = p->left;
	p->left = q->right;
	q->right = p;
	fixheight(p);
	fixheight(q);
	return q;
}
/* Левый поворот */
struct Node* rotateleft(struct Node* p) {
	Node* q = p->right;
	p->right = q->left;
	q->left = p;
	fixheight(q);
	fixheight(p);
	return q;
}
/* Балансировка узла */
struct Node* balance(struct Node* p) {
	fixheight(p);
	if (bfactor(p) == 2)
	{
		if (bfactor(p->right) < 0)
			p->right = rotateright(p->right);
		return rotateleft(p);
	}
	if (bfactor(p) == -2)
	{
		if (bfactor(p->left) > 0)
			p->left = rotateleft(p->left);
		return rotateright(p);
	}
	return p;
}
/* Вставка элемента в дерево к корнем p */
struct Node* insert(struct Node* p, int k){
	if (!p) return new struct Node(k);
	if (k<p->key)
		p->left = insert(p->left, k);
	else
		p->right = insert(p->right, k);
	return balance(p);
}

/* поиск узла с минимальным ключом в дереве p*/
struct Node* findmin(struct Node* p) {
	return p->left ? findmin(p->left) : p;
}

/* удаление узла с минимальным ключом из дерева p */
struct Node* removemin(struct Node* p)
{
	if (p->left == 0)
		return p->right;
	p->left = removemin(p->left);
	return balance(p);
}
/* удаление ключа k из дерева p */
struct Node* remove(struct Node* p, int k)
{
	if (!p) return 0;
	if (k < p->key)
		p->left = remove(p->left, k);
	else if (k > p->key)
		p->right = remove(p->right, k);
	else
	{
		struct Node* q = p->left;
		struct Node* r = p->right;
		delete p;
		if (!r) return q;
		struct Node* min = findmin(r);
		min->right = removemin(r);
		min->left = q;
		return balance(min);
	}
	return balance(p);
}


int main(int argc, char* argv[]) {

	char* InputFileName = argv[POS_INPUTFILE];
	FILE* InputFile;
	fopen_s(&InputFile, InputFileName, "rb");
	if (!InputFile) {
		perror("Input file opening failed");
		return EXIT_FAILURE;
	}
	char* OutputFileName = argv[POS_OUTPUTFILE];
	FILE* OutputFile;
	fopen_s(&OutputFile, OutputFileName, "wb");
	if (!OutputFile) {
		perror("Output file opening failed");
		return EXIT_FAILURE;
	}

	return 0;
}