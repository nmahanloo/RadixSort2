// Nima Mahanloo
// Radix Sort - CISP 430
#include <iostream>
#include <random>
#include <ctime>
using namespace std;
// Global int variable as program array size
const int arrSize = 10;
// A 2D node object as structure
struct node
{
    bool firstData = false;
    int number = 0;
    node* data = nullptr;
    node* next = nullptr;
    node* prev = nullptr;
};
// A module to initialize the program queue first dimension
void queueInitial(node* (&head))
{
    int counter;
    for (counter = 0; counter < 19; counter++)
    {
        head->next = new node;
        head->next->prev = head;
        head = head->next;
    }
}
/*
// A module to initial entire of 2D queue for test
void setQueue (node* (&tail))
{
    node* curr = tail;
    node* headData = nullptr;
    int counter, limit = 10;
    while (curr->next != nullptr)
    {
        curr->data = new node;
        headData = curr->data;
        for (counter = 0; counter < limit; counter++)
        {
           headData->number = counter;
           if (counter+1 < limit)
           {
                headData->next = new node;
                headData->next->prev = headData;
                headData = headData->next;
           }
        }
        curr = curr->next;
    }
}
*/
/*
// A module to display 2D queue contains for process check
void displayQueue (node* tail)
{
    node* curr = tail;
    while (curr->next != nullptr)
    {
        node* headData = curr->data;
        while (headData != nullptr)
        {
            cout << headData->number << " ";
            headData = headData->next;
        }
        cout << endl;
        curr = curr->next;
    }
    cout << endl;
}
*/
// A module to push data inside current dimension
void pushData(node* (&curr), int n)
{
    if (curr->data == nullptr)
    {
        curr->data = new node;
        curr->data->firstData = true;
    }
    node* headData = curr->data;
    while (headData->next != nullptr)
    {
        headData = headData->next;
    }
    if (headData->firstData == false)
    {
        headData->next = new node;
        headData->next->prev = headData;
        headData = headData->next;
    }
    headData->number = n;
    if (headData->firstData == true)
    {
        headData->firstData = false;
    }
}
// A module to display array contains
void displayArray (int arr[arrSize])
{
    int counter;
    for (counter = 0; counter < arrSize; counter++)
    {
        cout << arr[counter] << " ";
    }
    cout << endl << endl;
}
// A module to copy by priority queue data to array
void queueToArray(int(&arr)[arrSize], node* tail, bool arrange)
{
    int counter;
    node* curr;
    node* headData;
    // For ascending
    if (arrange == false)
    {
        curr = tail;
        counter = -1;
        while (curr->next != nullptr)
        {
            headData = curr->data;
            while (headData != nullptr)
            {
                counter++;
                arr [counter] = headData->number;
                headData = headData->next;
            }
            curr = curr->next;
        }
    }
    // For descending
    else
    {
        curr = tail;
        counter = 10;
        while (curr->next != nullptr)
        {
            headData = curr->data;
            while (headData != nullptr)
            {
                counter--;
                arr [counter] = headData->number;
                headData = headData->next;
            }
            curr = curr->next;
        }
    }
}
// A module to reset the queue second dimension
void clearQueue (node* (&tail))
{
    node* curr = tail;
    node* headData = nullptr;
    node* temp = nullptr;
    while(curr->next != nullptr)
    {
        headData = curr->data;
        if (headData != nullptr)
        {
            while (headData->next != nullptr)
            {
                temp = headData->next;
                if(headData->next->next != nullptr)
                {
                    headData->next->prev = headData;
                }
                headData->next = headData->next->next;
                delete temp;
                temp = nullptr;
            }
            delete headData;
            headData = nullptr;
            delete curr->data;
            curr->data = nullptr;
        }
        curr = curr->next;
    }
}
// A module to sort input array by radix sort algorithm
void radixSort(int (&arr)[arrSize], node* (&tail), bool arrangeReq)
{
    node* curr = tail;
    // A boolean variable to select ascending arrange in radix sort process rounds
    bool arrange = false;
    int round, counter = -1, outerCounter, innerCounter, endIndex;
    // Find maximum and minimum values in the array
    int maxValue = arr[0], minValue = arr[0];
    for (outerCounter = 1; outerCounter < arrSize; outerCounter++)
    {
        if (arr[outerCounter] > maxValue)
        {
            maxValue = arr[outerCounter];
        }
        else if (arr[outerCounter] < minValue)
        {
            minValue = arr[outerCounter];
        }
    }
    // Determine number of necessary rounds for radix sorting process
    if (((minValue > -10) && (minValue <= 0)) || ((maxValue >= 0) && (maxValue < 10)))
    {
        round = 1;
    }
    else if (((minValue > -100) && (minValue <= -10)) || ((maxValue >= 10) && (maxValue < 100)))
    {
        round = 2;
    }
    else if (((minValue > -1000) && (minValue <= -100)) || ((maxValue >= 100) && (maxValue < 1000)))
    {
        round = 3;
    }
    else if (((minValue > -10000) && (minValue <= -1000)) || ((maxValue >= 1000) && (maxValue < 10000)))
    {
        round = 4;
    }
    // A loop for radix sorting rounds
    for (outerCounter = 0; outerCounter < round; outerCounter++)
    {
        // A loop to explain each array member in ascending direction
        for (innerCounter = 0; innerCounter < arrSize; innerCounter++)
        {
            // Assign the queue first dimension first node to curr node
            curr = tail;
            // If the array current member number is between -1 and -9
            if ((arr[innerCounter] > -10) && (arr[innerCounter] < 0))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = 9-((-1)*arr[innerCounter]);
                    for(counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
            // If the array current member number is between -10 and -99
            else if ((arr[innerCounter] > -100) && (arr[innerCounter] < -9))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = 9-(((-1)*arr[innerCounter])%10);
                    for (counter = 0; counter <  endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = 9-(((-1)*arr[innerCounter])/10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first or second round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
            // If the array current member number is between -100 and -999
            else if ((arr[innerCounter] > -1000) && (arr[innerCounter] < -99))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = ((-1)*arr[innerCounter])%100;
                    endIndex = 9-(endIndex%10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = ((-1)*arr[innerCounter])%100;
                    endIndex = 9-(endIndex/10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = 9-(((-1)*arr[innerCounter])/100);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first, second or third round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
            // If the array current member number is between -1000 and -9999
            else if ((arr[innerCounter] > -10000) && (arr[innerCounter] < -999))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = ((-1)*arr[innerCounter])%1000;
                    endIndex = endIndex%100;
                    endIndex = 9-(endIndex%10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = ((-1)*arr[innerCounter])%1000;
                    endIndex = endIndex%100;
                    endIndex = 9-(endIndex/10);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = ((-1)*arr[innerCounter])%1000;
                    endIndex = 9-(endIndex/100);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at fourth round
                else if (outerCounter == 3)
                {
                    endIndex = 9-(((-1)*arr[innerCounter])/1000);
                    for (counter = 0; counter < endIndex; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first, second, third or fourth round
                else
                {
                    for(counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
            // If the array current member number is between 0 and 9
            else if ((arr[innerCounter] < 10) && (arr[innerCounter] > -1))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = arr[innerCounter];
                    for(counter = 0; counter <  endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
            // If the array current member number is between 10 and 99
            else if ((arr[innerCounter] < 100) && (arr[innerCounter] > 9))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = arr[innerCounter]%10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = arr[innerCounter]/10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first or second round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
            // If the array current member number is between 100 and 999
            else if ((arr[innerCounter] < 1000) && (arr[innerCounter] > 99))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = arr[innerCounter]%100;
                    endIndex = endIndex%10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = arr[innerCounter]%100;
                    endIndex = endIndex/10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = arr[innerCounter]/100;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first, second or third round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
            // If the array current member number is between 1000 and 9999
            else if ((arr[innerCounter] < 10000) && (arr[innerCounter] > 999))
            {
                // If radix sort is at first round
                if (outerCounter == 0)
                {
                    endIndex = arr[innerCounter]%1000;
                    endIndex = endIndex%100;
                    endIndex = endIndex%10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at second round
                else if (outerCounter == 1)
                {
                    endIndex = arr[innerCounter]%1000;
                    endIndex = endIndex%100;
                    endIndex = endIndex/10;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at third round
                else if (outerCounter == 2)
                {
                    endIndex = arr[innerCounter]%1000;
                    endIndex = endIndex/100;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is at fourth round
                else if (outerCounter == 3)
                {
                    endIndex = arr[innerCounter]/1000;
                    for (counter = 0; counter < endIndex+9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
                // If radix sort is not at first, second, third or fourth round
                else
                {
                    for (counter = 0; counter < 9; counter++)
                    {
                        curr = curr->next;
                    }
                    pushData (curr, arr[innerCounter]);
                }
            }
        }
        // Copy the queue contains to array
        queueToArray(arr, tail, arrange);
        if (outerCounter < round-1)
        {
            // Reset the queue 2nd dimension for next round
            clearQueue(tail);
        }
    }
    // If input request is for ascending sort
    if (arrangeReq == false)
    {
        // Show final result to user
        cout << "Sorted array (Asc):" << endl << endl;
        displayArray(arr);
    }
    // Else if input request is for descending sort
    else
    {
        // Show final result to user
        cout << "Sorted array (Desc):" << endl << endl;
        queueToArray(arr, tail, true);
        displayArray(arr);
    }
    // Reset the queue 2nd dimension
    clearQueue(tail);
}

int main()
{
    bool arrange;
    srand(time(0));
    node* Queue = new node;
    node* tail = Queue;
    node* head = Queue;
    queueInitial(head);
    int unsort[arrSize];
    int unsortCopy[arrSize];
    int counter;
    for (counter = 0; counter < arrSize; counter++)
    {
        unsort[counter] = rand() % 10000 - 5000;
        unsortCopy[counter] = unsort[counter];
    }
    cout << "<Radix Sort>" << endl << endl << endl;
    cout << "The random array is :" << endl << endl;
    displayArray(unsort);
    arrange = false;
    radixSort(unsort, tail, arrange);
    arrange = true;
    radixSort(unsortCopy, tail, arrange);
    return 0;
}
