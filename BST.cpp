#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Node {
	char name[50];
	int key;
	Node *left;
	Node *right;
} *root = NULL;

Node *initNode(char name[], int key){
	Node *temp = (Node *)malloc(sizeof(Node));
	// isi data
	strcpy(temp->name, name);
	temp->key = key;
	temp->left = temp->right = NULL;
	return temp;
}

Node *insertNode(Node *curr, char name[], int key){
	// ketemu tempat kosong
	if(!curr) return initNode(name, key);
	// key < curr->key
	else if(key < curr->key){
		curr->left = insertNode(curr->left, name, key);
	}
	// key > curr->key
	else if(key > curr->key){
		curr->right = insertNode(curr->right, name, key);
	}
}

Node *del(Node *curr, int key){
	// data ga ketemu
	if(!curr) return NULL;
	else if(key < curr->key){
		curr->left = del(curr->left, key);
	}
	else if(key > curr->key){
		curr->right = del(curr->right, key);
	}
	else{
		// ketemu data yang mau di delete
		// case 1 -> leaf node
		if(curr->left == NULL && curr->right == NULL){
			free(curr);
			curr = NULL;
		}
		// case 2 -> cuma punya anak kiri
		else if(curr->left != NULL && curr->right == NULL){
			Node *temp = curr->left;
			*curr = *temp;
			free(temp);
		}
		// case 3 -> cuma punya anak kanan
		else if(curr->left == NULL && curr->right != NULL){
			Node *temp = curr->right;
			*curr = *temp;
			free(temp);
		}
		// case 4 -> punya 2 anak
		else{
			Node *temp = curr->left;
			while(temp->right != NULL){
				temp = temp->right;
			}
			// disini kita udah dapet largest node dari left subtree
			strcpy(curr->name, temp->name);
			curr->key = temp->key;
			curr->left = del(curr->left, temp->key);
		}
	}
	return curr;
}

/*
pre
root left right

in
left root right

post
left right root
*/

void inorder(Node *curr){
	if(curr){
		inorder(curr->left);
		printf("%s %d\n", curr->name, curr->key);
		inorder(curr->right);
	}
}

Node *search(Node *curr, int key){
	if(!curr){
		return NULL;
	}
	else if(curr->key == key){
		return curr;
	}
	else if(key < curr->key){
		search(curr->left, key);
	}
	else if(key > curr->key){
		search(curr->right, key);
	}
}

int main(){
	root = insertNode(root, "Andi", 16);
	root = insertNode(root, "Abi", 15);
	root = insertNode(root, "Rendy", 14);
	root = insertNode(root, "Kevyn", 13);
	root = insertNode(root, "Dylan", 12);
	root = insertNode(root, "Rafael", 11);
	root = insertNode(root, "Vinson", 10);
	
	inorder(root);
	
	Node *searchResult = search(root, 10);
	if(searchResult){
		printf("Found data with key %d, name = %s\n", searchResult->key, searchResult->name);
	}
	else{
		puts("No Data");
	}
	
	puts("");
	root = del(root, 13);
	inorder(root);
	return 0;
}
