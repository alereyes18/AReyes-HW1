/*
2. Test whether a recursive, iterative or linked-type binary search is faster by testing it on
arrays of sizes 1 million and 10 million with arrays that are filled with random numbers.
You will need to either fill it in a “sorted way” or sort it before doing the binary search.
*/

#include <iostream>
#include <time.h>
#include<algorithm>

//for timing
#include<functional>
#include <chrono>
using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;
//-----------
using namespace std;


//=================ITERATIVE AND RECURSIVE BINARY SEARCH ON ARRAYS=========================
//Fill an array with random numbers and sort the array
template<typename T>
void fillArray (T* array, const long long size){
    for (int i = 0; i<size; i++){ //iterate through array
        T random = rand()%1000/10.0; //generate random number and assign it to current positon in array
        array[i] = random;
        }
    sort(array, array+size);//sort the array
}//fillArray

template<typename T>
void printArray (T* array, const long size){
    for (int i = 0; i < size; i++)//iterate through array
    {
        cout << array[i] << "   ";//print each element in the array
    }
    cout << endl;
}//printArray

//Iterative binary search
template<typename arrType>
bool iterativeBinarySearch(arrType* array, int size, arrType target){
    int left, right, mid;
    left = 0; //set left to first element in array
    right = size-1; //set right to last element in array
    
    //using left+right/2 may cause overflow, resulting in a mid less than the minimum value (left)
    mid = left + ((right - left) / 2);  //calculate index of middle element considering overflow
    while (left <= right){ //loop until we search the entire list
        //find the middle value in the array and compare it with the target
        if ( array[mid] == target) { cout << target << " found in position " << mid << endl; return true; } //if the middle index holds the target, we have found the target in the array
        else if ( target > array[mid]) { //if the target is greater than mid, we need to search for it in the right half of the array
            left = mid+1; //set the left bound to mid+1 because we know array[mid] is not the target so we don't need to check it again
            mid = left + ((right - left) / 2);   //calculate new middle element
            } 
        else { //if the target is less than the middle element, we need to search for it in the left half of the array
            right = mid - 1;
            mid = left + ((right - left) / 2); //calculate new middle element
        } 
    }//while
    return false;
}//iterativeBinarySearch (for arrays)

//Recursive binary search
template <typename arrType>
bool recursiveBinarySearch(arrType* array, int left, int right, arrType target){
    static int counter = 0;
    counter++;
    int mid = left + ((right - left) / 2);

    if (left > right) {return 0;} //if we have exhausted the search space, target not found
    if( array[mid] == target) { 
        //cout << target << " found in position " << mid << endl; 
        return 1; 
        } //if array[mid] is equal to the target, the target was found

    else if ( target < array[mid]){ //if target is lower than value at array[mid], search left half of list
        return recursiveBinarySearch(array, left, mid-1, target); //call the function again with the same starting index, and mid as the ending index (instead of right as the ending index)
    }

    else if ( target > array[mid]){ //if target is higher than value at array[mid], we need to search the right half of the list
        return recursiveBinarySearch(array, mid+1, right, target); //call the function with mid as the new starting index (instead of low as the starting index) and right as the ending index
    }

    return 0;
}//recursiveBinarySearch (for arrays)
//=================END OF ITERATIVE AND RECURSIVE BINARY SEARCH ON ARRAYS=========================
 


//=================lINKED-LIST BINARY SEARCH=========================

template<typename nodeType>
class Node{
    public:
        nodeType data; //node has a data value
        Node<nodeType>* link; //node has a pointer to next node in list
        Node(nodeType value): data(value){ link = nullptr; }//default constructor
};//node templated class

template<typename nodeType>
class List{
protected:
    long long  nodeCount; //stores number of nodes in the list
public:
    Node<nodeType>* head;//first node in list
    Node<nodeType>* tail;//last node in list

    //a newly created list has an empty head and tail, and 0 elements
    List() { nodeCount = 0; head = nullptr; tail = nullptr; } //constructor

    //declare templated functions for objects of the List class
    void insertHead(nodeType val);          //inserts new node with specified value into the head of the list
    void insertTail(nodeType val);          //inserts new node with specified value into tail of the list
    void insert(int index, nodeType val);   //inserts new node with specified value into specified position
    Node<nodeType>* get(int index);         //returns pointer to node at selected index
    void printNode(Node<nodeType>* node);   //prints a list 
    void fillList(const long long size);    //fill list with random values
    bool binarySearch(nodeType target);     //binary search for list
    void fillListFromArray(nodeType* array, int size); //
};//linked list templated class

template<typename nodeType>
void List<nodeType>::insertHead(nodeType val){
    Node<nodeType>* node = new Node<nodeType>(val); //create a new node with the value to be inserted at the head
    node->link = head; //the link of the inserted node will be the current head
    head = node; //the inserted node is the new head of the list
    if (nodeCount == 0){ tail = head; } //if the list is empty, the inserted head will also be the tail
    nodeCount++;//we have added a node to the list, increment the node counter
}//insertHead template

template<typename nodeType>
void List<nodeType>::insertTail(nodeType val){
    if (nodeCount == 0){ insertHead(val); } //if the list is empty, the inserted tail will also be the head, so just invoke insertHead
    
    Node<nodeType>* node = new Node<nodeType>(val); //create a new node
    tail->link = node; //the current tail's link becomes the new tail
    tail = node; //the current tail is now the new tail
    nodeCount++; //increment node counter because a new node was inserted
}//insertTail template

template<typename nodeType>
void List<nodeType>::insert(int index, nodeType val){
    if (index < 0 || index > nodeCount) { return; }//check if index is out of bounds
    if ( index == 0) { insertHead(val); return;}//if list is empty, insert a head

    Node<nodeType>* prevNode = head; //begin searching for the node that comes before the selected index
    for (int i = 0; i < index-1; i++)//until find the selected index, traverse the nodes
    {
        prevNode = prevNode->link; //when loop finishes, prevNode will link to node at selected index 
    }
    Node<nodeType>* nextNode = prevNode->link; //next node links to node after selected index
    Node<nodeType>* node = new Node<nodeType>(val);//node to be inserted
    //insert node between previous and next node
    node->link = nextNode;//link of inserted will be node after selected index
    prevNode->link = node;//link of prevNode will be the node inserted into selected index
    nodeCount++; //increment node counter because a new node was inserted
}//insert template

template<typename nodeType>
Node<nodeType>* List<nodeType>::get(int index){ //returns pointer to node
    if (index < 0 || index > nodeCount ) { return NULL ;}//if index is out of bounds, node does not exist
    Node<nodeType>* node = head;//start from head node
    for (int i = 0; i < index; i++)
    {
        node = node->link;
    }
    return node;
}//return value at selected index in list

template<typename nodeType>
void printNode(Node<nodeType>* node){
    while (node!=NULL){//while node is linked to another node
    cout << node->data << "->";
    node = node->link;
    }
    cout << "NULL" << endl;
}

template<typename nodeType>
void List<nodeType>::fillList (const long long size){
    if (this->nodeCount != 0) { cout << "The list is not empty. Please fill an empty list." << endl; return;} //if list is not empty, we don't want to override it, and we dont want to fill it because it will be larger than the specified size
    this->insertHead(rand()%1000/10.0);
    for (int i = 1; i<size; i++){
        nodeType random = rand()%1000/10.0;
        this->sortedInsert(random);
        }
        cout << "List filled with random values" << endl;
}//fill list in a sorted way with random numbers


template<typename nodeType>
bool List<nodeType>::binarySearch(nodeType target){
    //cout << "Iterative Search" << endl;
    int left, right, mid;
    left = 0; //set left index to first element in list
    right = this->nodeCount - 1; //set right index to last element in list
    
    mid = left + ((right - left) / 2); //calculate index of middle element
    while (left <= right){ //loop until we search the entire list
        //find the middle value in the array and compare it with the target
        if ( (this->get(mid)->data) == target) { cout << target << " found in position " << mid << endl; return true; } //if the middle index holds the target, we have found the target in the array
        else if ( target > this->get(mid)->data) { //if the target is greater than mid, we need to search for it in the right half of the array
            left = mid+1; //set the left bound to mid+1 because we know array[mid] is not the target so we don't need to check it again
            mid = left + ((right - left) / 2); //calculate index of middle element
            } 
        else { 
            right = mid - 1;
            mid = left + ((right - left) / 2); //calculate index of middle element
        } //if the target is less than the middle element, we need to search for it in the left half of the array
    }
    //cout << target << " not found." << endl;
    return false;
}//List::binarySearch

template<typename nodeType>
void List<nodeType>::fillListFromArray(nodeType* array, int size){
    for (int i = size-1; i >=0 ; i--) //begin from last element in the value array
    {
        this->insertHead(array[i]);//insert a node with current element to the beginning of the list
    }//this loop inserts values from a sorted array into a list so that the list nodes are ordered by value
    cout << "List filled." << endl;
}//List::fillListFromArray

//========TIMING=========
template <typename Func>
long long TimeFunc(size_t iterations, Func f)
{

	auto begin = chrono::steady_clock::now(); //start the timer
    for (size_t i = 0; i < iterations; i++) { f(); } //run the function the specified amount of times
    
	auto end = chrono::steady_clock::now(); //end the timer

	return duration_cast<chrono::nanoseconds>((end - begin) / iterations).count(); //calculate average runtime 
}

int main(){
    int size1 = 1000000;
    int size2 = 10000000;
    int iterations = 100000;
    int iterationsList = 10;//insertion on the list takes a long time, so we must limit the number of times we run the search
    int searchValue = 999999;//search for a value that gives us the worst-case scenario runtime
   
    //Iterative search set-up
    int* array1 = new int[size1];//iterative search, size1
    int* array2 = new int[size2];//iterative search, size2
    fillArray<int>(array1, size1); //fill first array
    fillArray<int>(array2, size2); //fill second array

    //SIZE 1,000,000-ITERATIVE
    auto iterative_milliseconds = TimeFunc(iterations, [&]() {iterativeBinarySearch<int>(array1, size1, searchValue); }); //time the search considering the worst-case scenario(value not found)
    cout << "The average iterative binary search time on an array of size " << size1 << " over " << iterations <<" iterations is: " << iterative_milliseconds << " nanoseconds." << endl;
    
    //SIZE 10,000,000- ITERATIVE
    iterative_milliseconds = TimeFunc(iterations, [&]() {iterativeBinarySearch<int>(array2, size2, searchValue); }); //time the search considering the worst-case scenario(value not found)
    cout << "The average iterative binary search time on an array of size " << size2 << " over " << iterations << " iterations is: " << iterative_milliseconds << " nanoseconds." << endl;
        
    //Recursive search set-up
    int* array3 = new int[size1];//recursive, size1
    int* array4 = new int[size2];//recursive, size2
    fillArray<int>(array3, size1); //fill first array
    fillArray<int>(array4, size2); //fill second array
    
    //SIZE 1,000,000-RECURSIVE
    auto recursive_milliseconds = TimeFunc(iterations, [&]() {recursiveBinarySearch<int>(array3, 0, size1-1, searchValue); }); //time the search considering the worst-case scenario(value not found)
    cout << "The average recursive binary search time on an array of size " << size1 <<  " over " << iterations << " iterations is: "  << recursive_milliseconds << " nanoseconds." << endl;
    

    //SIZE 10,000,000- RECURSIVE
     recursive_milliseconds = TimeFunc(iterations, [&]() {recursiveBinarySearch<int>(array4, 0, size2-1, searchValue); }); //time the search considering the worst-case scenario(value not found)
    cout << "The average recursive binary search time on an array of size " << size2 << " over " << iterations << " iterations is: "  << recursive_milliseconds << " nanoseconds." << endl;
 
    //List search set-up
    List<int> list1, list2;
    int* listArray1 = new int[size1];
    int* listArray2 = new int[size2];
    fillArray<int>(listArray1, size1); //fill first array
    fillArray<int>(listArray2, size2); //fill second array
    list1.fillListFromArray(listArray1, size1); //fill first list
    list2.fillListFromArray(listArray2, size2); //fill second list

    auto list_milliseconds = TimeFunc(iterationsList, [&]() {list1.binarySearch(searchValue); }); //time the search considering the worst-case scenario(value not found)
    cout << "The average iterative binary search time on an list of size " << size1 << " over " << iterationsList << " iterations is: " <<list_milliseconds << " nanoseconds, or "<< list_milliseconds/100000000.0 << " seconds." << endl;

    list_milliseconds = TimeFunc(iterationsList, [&]() {list2.binarySearch(searchValue); }); //time the search considering the worst-case scenario(value not found)
    cout << "The average iterative binary search time on an list of size " << size2 << " over " << iterationsList << " iterations is: " <<list_milliseconds << " nanoseconds, or "<< list_milliseconds/100000000.0 << " seconds." << endl;

    return 0;
}
