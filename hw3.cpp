#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "ArgumentManager.h"

using namespace std;

//Articles used for reference:
//www.geeksforgeeks.org/3-way-quicksort-dutch-national-flag/

struct node
{
	int data;
	node *next;
};

int *makeArray(string ipn, int &size) // used for making dynamic array for shell sort and quicksort and returns start of the array
{
	fstream infile(ipn);  
	string input_line; 

	int *arr = new int[1000];
	int count = 1000;
	int index = 0;
	int temp = 0;

	while (getline(infile, input_line))
	{
		if (input_line != "")
		{
			istringstream iss(input_line);
			while (iss >> temp)
			{
				if (index == count)
				{
					count *= 2;
					int *bigger = new int[count];
					for (int i = 0; i < (count / 2); i++)
					{
						bigger[i] = arr[i];
					}
					delete[] arr;
					arr = bigger;
				}
				arr[index] = temp;
				index++;
			}
			iss.str(""); 
		}
	}
	size = index;
	return arr;
}

node* makeLL(string ipn, node* head, int &size) 
{
	fstream infile(ipn); 
	string input_line; 

	int temp;

	while (getline(infile, input_line))
	{
		if (input_line != "")
		{
			istringstream iss(input_line);
			while (iss >> temp)
			{
				node* filler = new node;
				filler->data = temp;
				filler->next = head; 
				head = filler; 
				size++;
			}
		}
	}
	return head; 
}

int *ShellSort(int *arr, int arrSize)
{
	for (int gap = arrSize / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < arrSize; i += 1)
		{

			int temp = arr[i];
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];
			arr[j] = temp;
		}
	}
	return arr;
}


void swap(int *a, int *b)
{
	int t = *a;
	*a = *b;
	*b = t;
}
void partition(int *arr, int l, int r, int &i, int &j)
{
	i = l - 1, j = r;
	int p = l - 1, q = r;
	int v = arr[r];

	while (true)
	{
		
		while (arr[++i] < v);

		while (v < arr[--j])
		{
			if (j == l)
			{
				break;
			}
		}

		if (i >= j) 
		{ 
			break; 
		}

		swap(arr[i], arr[j]);

		if (arr[i] == v)
		{
			p++;
			swap(arr[p], arr[i]);
		}

		if (arr[j] == v)
		{
			q--;
			swap(arr[j], arr[q]);
		}
	}

	swap(arr[i], arr[r]);

	j = i - 1;
	for (int k = l; k < p; k++, j--)
	{
		swap(arr[k], arr[j]);
	}

	
	i = i + 1;
	for (int k = r - 1; k > q; k--, i++)
	{
		swap(arr[i], arr[k]);
	}
}
int* quickSort(int *arr, int l, int r)
{
	int *returnedArray = arr;
	
	if (r <= l) 
	{ 
		return returnedArray; 
	}

	int i, j;
	partition(arr, l, r, i, j);
	quickSort(arr, l, j);
	quickSort(arr, i, r);
}


void divideList(node* firstHead, node* &secondHead)
{
	node* middle; 
	node* current;
	if (firstHead == nullptr)
	{
		secondHead = nullptr;
	}
	else if (firstHead->next == nullptr)
	{
		secondHead = nullptr;
	}
	else
	{
		middle = firstHead;
		current = firstHead->next;
		if (current != nullptr)
		{
			current = current->next;
		}
		while (current != nullptr)
		{
			middle = middle->next;
			current = current->next;
			if (current != nullptr)
			{
				current = current->next;
			}
		} 
		secondHead = middle->next;
		middle->next = nullptr; 
	} 
}
node *mergeList(node* firstHead, node* secondHead)
{
	node* lastSmall; 
	node* newHead; 
	if (firstHead == nullptr) 
	{
		return secondHead;
	}
	else if (secondHead == nullptr) 
	{
		return firstHead;
	}
	else
	{
		if (firstHead->data < secondHead->data) 
		{
			newHead = firstHead;
			firstHead = firstHead->next;
			lastSmall = newHead;
		}
		else
		{
			newHead = secondHead;
			secondHead = secondHead->next;
			lastSmall = newHead;
		}
		while (firstHead != nullptr && secondHead != nullptr) 
		{
			if (firstHead->data < secondHead->data)
			{
				lastSmall->next = firstHead;
				lastSmall = lastSmall->next;
				firstHead = firstHead->next;
			}
			else
			{
				lastSmall->next = secondHead;
				lastSmall = lastSmall->next;
				secondHead = secondHead->next;
			}
		} 
		if (firstHead == nullptr) 
		{
			lastSmall->next = secondHead;
		}
		else 
		{
			lastSmall->next = firstHead;
		}
		return newHead;
	}
}
void MergeSort(node* &head)
{
	node *otherHead;
	if (head != nullptr) //if the list is not empty
	{
		if (head->next != nullptr) //if the list has more than one node
		{
			divideList(head, otherHead);
			MergeSort(head);
			MergeSort(otherHead);
			head = mergeList(head, otherHead);
		}
	}
}


void printList(node* head, string sortType, string opn, int* indexes, int ListSize, int n) 
{
	ofstream outfile(opn); 
	if (head == nullptr)
	{
		return;
	}
	else if (sortType == "ascending")
	{
		if (ListSize == 1)
		{
			node *curr = head;
			outfile << curr->data << " ";
		}
		else
		{
			for (int i = 0; i < n; i++) 
			{
				while (indexes[i] < 0 || indexes[i] >= ListSize) 
				{
					i++; 
				}
				node* curr = head;
				int j = 0;
				while (curr->next != nullptr)
				{
					if (j == indexes[i])
					{
						outfile << curr->data << " ";
					}
					j++;
					curr = curr->next;
				}
			}
		}
	}
	else if (sortType == "descending")
	{
		if (ListSize == 1)
		{
			node *curr = head;
			outfile << curr->data << " ";
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				while (indexes[i] < 0 || indexes[i] >= ListSize) // checking bounds of index
				{
					i++; // going to next index of out of bounds 
				}
				node* curr = head;
				int j = ListSize - 1;
				int pos = j - i;
				for (int k = 0; k < pos; k++)
				{
					curr = curr->next;
				}
				outfile << curr->data << " ";
			}
		}
	}
}

void printArray(int *arr, string sortType, string output, int *indexes, int arrSize, int n)
{
	ofstream outfile(output); 

	if (sortType == "ascending")
	{
		if (arrSize == 1) 
		{
			outfile << arr[0] << " ";
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				while (indexes[i] < 0 || indexes[i] >= arrSize)
				{
					i++;
				}
				outfile << arr[indexes[i]] << " ";
			}
		}
	}
	else if (sortType == "descending")
	{
		if (arrSize == 1)
		{
			outfile << arr[0] << " ";
		}
		else
		{
			for (int i = 0; i < n; i++)
			{
				while (indexes[i] < 0 || indexes[i] >= arrSize)
				{
					i++;
				}
				outfile << arr[(arrSize - 1) - indexes[i]] << " ";
			}
		}
	}
}

int main(int argc, char *argv[])
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string command = am.get("command");
	string opn = am.get("output");

	fstream cmdfile(command); 

	string instruction; 
	string sortOrder;

	node* head = nullptr;

	int *dynamicArray;
	int *indexKey; 
	int index_count;

	char key; // determines sort to be used 

	getline(cmdfile, instruction); // reads from command file 
	istringstream iss(instruction); // places entire command line in string stream 
	string commandType; //to store sort method to be used 
	iss >> commandType; 
	key = commandType[0]; //stores first letter because each letter is distinct
	iss >> commandType >> commandType; 

	if (commandType[0] == 'a' || commandType[0] == 'A' || commandType[0] == 'd' || commandType[0] == 'D') 
	{
		sortOrder = commandType; 
		getline(iss, commandType); 
		istringstream iss(commandType);

		int count = 0;
		int index = 0;
		int temp;

		indexKey = new int[10];

		while (iss >> temp)
		{
			indexKey[index] = temp;
			index++;
			count++;
			if (index == count)
			{
				int size = count * 2;
				int *bigger = new int[size];
				for (int i = 0; i < count; i++)
				{
					bigger[i] = indexKey[i];
				}
				delete[] indexKey;
				indexKey = bigger;
			}
		}
		index_count = index;
	}
	else 
	{
		sortOrder = "ascending";
		iss.unget(); // moves iss back one word
		getline(iss, commandType); 
		istringstream iss(commandType);
		int count = 0, index = 0, temp;
		indexKey = new int[10];
		while (iss >> temp)
		{
			indexKey[index] = temp;
			index++;
			count++;
			if (index == count)
			{
				int size = count * 2;
				int *bigger = new int[size];
				for (int i = 0; i < count; i++)
				{
					bigger[i] = indexKey[i];
				}
				delete[] indexKey;
				indexKey = bigger;
			}
		}
		index_count = index;
	}

	if (key == 'm' || key == 'M') 
	{
		int sizeofList = 0;
		head = makeLL(input, head, sizeofList);
		MergeSort(head);
		printList(head, sortOrder, opn, indexKey, sizeofList, index_count);
	}
	else if (key == 's' || key == 'S') 
	{
		int arrSize;
		dynamicArray = makeArray(input, arrSize);
		dynamicArray = ShellSort(dynamicArray, arrSize);
		printArray(dynamicArray, sortOrder, opn, indexKey, arrSize, index_count);
	}
	else if (key == 'q' || key == 'Q') 
	{
		int arrSize;
		dynamicArray = makeArray(input, arrSize);
		dynamicArray = quickSort(dynamicArray, 0, arrSize - 1);
		printArray(dynamicArray, sortOrder, opn, indexKey, arrSize, index_count);
	}
	return 0;
}