#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_BOOKS 10
#define MAX_TITLE_LENGTH 50
#define MAX_AUTHOR_LENGTH 50
#define MAX_NAME_LENGTH 20
#define MAX_SRN_LENGTH 14
#define MAX_STUDENTS 20
#define MAX_BOOK_COUNT 2
#define QUEUESIZE 10
#define MAX_RESERVE 2


typedef struct SRNs //For book reservation
{
    char srn[MAX_SRN_LENGTH];
}SRNs ;


typedef struct Book 
{
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    int count;  // Count of Copies of book
    int avail; // To indicate the availability of the book

    SRNs  book_q[MAX_RESERVE]; // Book Reservation Queue
    int front; // Flag for the first element in the queue
    int rear;  // Flag for the last  element in the queue

    struct Book* left;
    struct Book* right;
}BOOK;

typedef struct Student 
{
    char name[MAX_NAME_LENGTH];
    char SRN[MAX_SRN_LENGTH];
    BOOK* books[MAX_BOOKS]; //Array of pointers to books
    int num_books; // Number of books that the studend has borrowed
}STUDENT;


struct Book* createBook(char title[], char author[]) 
{
    struct Book* newBook = (struct Book*)malloc(sizeof(struct Book));
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    newBook->count = MAX_BOOK_COUNT; 
    newBook->avail = 1;
    newBook->left = NULL;
    newBook->right = NULL;
    // Initializing the Queue
    newBook->front = -1;
    newBook->rear = -1;
    return newBook;
}

// Function to check if the queue is empty
int isQempty(BOOK* book) 
{
    return (book->front == -1 && book->rear == -1);
}

// Function to check the number of elements in the queue
int bookQsize(BOOK * book) {
    if (isQempty(book)) 
    {
        return 0;
    } 
    
    else 
    {
        return (book->rear - book->front + 1);
    }
}

// Function to check the first element of the queue
char* frontElement(BOOK * book) {
    if (isQempty(book)) 
    {
        printf("No Reservations so far.....\n");
        return NULL;
    } 
    else 
    {
        return (book->book_q[book->front].srn);
    }
}


// Function to enqueue an element into the queue
void enqueue_srn(BOOK * book,char* qSRN ) 
{
    if (book->rear == MAX_RESERVE - 1) {
        printf("Reservations full please visit later.....\n");
    } else {
        if (isQempty(book)) 
        {
            book->front = 0;
        }
        SRNs qStud;
        strcpy(qStud.srn,qSRN);
        book->rear++;
        book->book_q[book->rear] = qStud;
    }
}

// Function to dequeue an element from the queue
void dequeue_srn(BOOK * book) {
    if (isQempty(book)) {
        printf("Queue is empty. Cannot dequeue.\n");
    } 
    else {
        if (book->front == book->rear) // If deQing the last element in the Q then initialize the Q
        {
            book->front = book->rear = -1;
        } 
        else 
        {
            book->front++;
        }
    }
}

void displayBookQ(BOOK * book) {
    if (isQempty(book)) {
        printf("Book reservation Queue is empty.\n");
    } 
    else 
    {   
        if(!(isQempty(book)))
        printf("Book reservation SRNs:  ");
        for (int i = book->front; i <= book->rear; i++) 
        {
            printf("%s ", book->book_q[i].srn);
            
        }
        printf("\n");
        
    }
}


STUDENT *createstudent(char name[], char SRN[])
{
	STUDENT *newStudent=(STUDENT *)malloc(sizeof(STUDENT));
	strcpy(newStudent->name, name);
	strcpy(newStudent->SRN, SRN);
	for (int i=0; i<MAX_BOOKS; i++)
		newStudent->books[i]=NULL;
	newStudent->num_books=0;
	return newStudent;
}	

struct Book* insert(struct Book* root, struct Book* book) 
{
    if (root == NULL) {
        return book;
    }

    int cmp = strcmp(book->title, root->title);
    
    if (cmp < 0) 
    {
        root->left = insert(root->left, book);
    } 
    else if (cmp > 0) {
        root->right = insert(root->right, book);
    }
    return root;
}

struct Book* search(struct Book* root, char* title) 
{
    if (root == NULL || strcmp(root->title, title) == 0) 
    {
        return root;
    }

    int cmp = strcmp(title, root->title);
    if (cmp < 0) 
    {
        return search(root->left, title);
    } 
    else 
    {
        return search(root->right, title);
    }
}

void inorder(struct Book* root) 
{
    if (root != NULL) {
        inorder(root->left);
        printf("-----------------------------------\nAvailability: %d\nCount: %d\nTitle: %s\nAuthor: %s\n",  root->avail,root->count, root->title, root->author);
        inorder(root->right);
    }
}

STUDENT* searchStudent(STUDENT* students,char SRN[],int no_of_students)
{
    for (int i=0;i<no_of_students;i++)
    {
        if (strcmp(SRN,students[i].SRN)==0)
        {
            return &students[i];
        }
    }
    return NULL;
}

void displayStudents(STUDENT* students,int total_students)
{
    for(int i=0;i<total_students;i++)
    {
        printf("Student Name: %s\n",students[i].name);
        printf("Student SRN :%s\n",students[i].SRN);
        printf("Number of Books borrowed %d\n",students[i].num_books);
        printf("-----------------------------------------------");
        printf("\n");
    }
}

void dispStudentinfo(STUDENT* students,int total_students)
{  
    if (total_students == 0)
    {
        printf("No students registered.....\n");
    }
     
    char SRN[MAX_SRN_LENGTH];
    printf("Enter the Student SRN: ");
    scanf("%s",SRN);
    STUDENT* student = searchStudent(students,SRN,total_students);
    if (student == NULL)
    {
        printf("Student Not found.....\n");
    }
    else
    {
        printf("Student Name: %s\n",student->name);
        printf("Student SRN: %s\n",student->SRN);
        printf("Number of books borrowed by the student: %d\n", student->num_books);
        {
            if(student->num_books>0)
            {   
                printf("Books:\n");
                for(int i =0;i<student->num_books;i++)
                {
                    printf("%s\n",student->books[i]->title);
                    printf("\n");
                }
            }
        }  
    }
    
}

void initBooks(struct Book **root) 
{
    struct Book* book1 = createBook("The Great Gatsby", "F. Scott Fitzgerald");
    struct Book* book2 = createBook("To Kill a Mockingbird", "Harper Lee");
    struct Book* book3 = createBook("1984", "George Orwell");
    struct Book* book4 = createBook("Pride and Prejudice", "Jane Austen");

    *root = insert(*root, book1);
    *root = insert(*root, book2);
    *root = insert(*root, book3);
    *root = insert(*root, book4);
}



void return_a_book(STUDENT *student, struct Book* root, char title[]) {
    int i;
    for (i = 0; i < student->num_books; i++) 
    {
        if (strcmp(student->books[i]->title, title) == 0) 
        {
            student->books[i]->count++; // Set the book's availability to 1 (available)
            if(student->books[i]->count==1)
            {
                    student->books[i]->avail = 1;
            }
            printf("Book '%s' returned successfully!\n", title);

            // Shifting the array elements to fill the gap created by returning the book
            for (int j = i; j < student->num_books - 1; j++) 
            {
                student->books[j] = student->books[j + 1];
            }
            student->num_books--;
            return;
        }
    }
    printf("You don't have the book '%s' to return.\n", title);
}



void issue_a_book(STUDENT *student, BOOK *root,STUDENT students[],int *total_students)
{
	
	printf("Enter the title of the book you want to issue: ");
    printf("\n----------------------------------\n");
    char bt[MAX_TITLE_LENGTH];
    getchar();
    fgets(bt, MAX_TITLE_LENGTH, stdin);
    bt[strcspn(bt, "\n")] = '\0'; //Removing \n from input if given
    BOOK *booktemp=search(root, bt);
    if (booktemp==NULL)
		printf("Book is not found in the library\n");
    
    STUDENT *studenttemp = NULL ;
    studenttemp = searchStudent(students,student->SRN,*total_students);
    
    if (studenttemp==NULL) // New student
    {
        
        // Adding the student to the students array
        students[(*total_students)] = *student; 
        strcpy((students[*total_students]).SRN,student->SRN);
        // Copy the SRN 
        strcpy((students[*total_students]).name,student->name);
        // Copy name 
        (*total_students)++;
    
    }
    studenttemp = searchStudent(students,student->SRN,*total_students);  // Reassigning the studenttemp pointer
    
    if (studenttemp!=NULL)
    {
        if (booktemp->count > 0) 
        {
            if (isQempty(booktemp)) // Issuing the book when there is no elements in Q 
            {
                if(studenttemp->num_books == MAX_BOOKS)
                {
                    printf("You have reached the max borrow count, hence cannot borrow");
                    return;
                }
                else
                {
                    if (studenttemp->num_books < MAX_BOOKS)
                    {
                        studenttemp->books[studenttemp->num_books++] = booktemp;
                        booktemp->count--;

                        if((booktemp->count == 0) && (booktemp->count > -1))
                        {
                            booktemp->avail = 0;
                        }
                        
                        printf("Book issued successfully!, Happy Learning\n----------------------------\n");
                    }
                    return;
                }
            }
            /* Issuing, when the book avail == 1, after someone has just retruned the book,
            and the person who is borrowing the book is first in the reserve Book Q
            */

            if(!(isQempty(booktemp))&& (booktemp->count >0))
            {
                int Qfirst = strcmp(studenttemp->SRN,frontElement(booktemp)); // Checking for first SRN in the Q
                if (Qfirst==0)
                {
                    studenttemp->books[studenttemp->num_books++] = booktemp;
                    
                    booktemp->count--;
                    if (booktemp->count == 0)
                    {
                        booktemp->avail = 0;
                    }
                    dequeue_srn(booktemp); // removing the SRN from the Q

                    printf("Book issued successfully!, Happy learning\n----------------------------\n");
                    // printf("Returned from second if\n");
                    return;
                }
                if (Qfirst != 0)
                {
                    printf("Sorry, the book is reserved......\n");
                }
                
            }  
        }

        /* Adding elements to the Q when the book avail == 0 */
            
        else if ((booktemp->count == 0) &&  (bookQsize(booktemp) < MAX_RESERVE))           
        {   
            // printf("In reserve\n");
            int reserve;
            printf("The book is not available. Do you want to reserve it (1/0)\n");
            scanf("%d",&reserve);
            while(getchar() != '\n'); // Clear the input buffer
            if (reserve)
            {
                enqueue_srn(booktemp,studenttemp->SRN);
                (*total_students)--;
            }
        }
        else
        {
            if (bookQsize(booktemp) ==  MAX_RESERVE)
                printf("Sorry, the book reservation Q is full please visit next time\n.....");
        }
    }        
}

struct Book* findMin(struct Book* node) 
{
    struct Book* current = node;
    while (current->left != NULL) 
	{
        current = current->left;
    }
    return current;
}

struct Book* delete(struct Book* root, char* title) 
{
    if (root == NULL) 
	{
        return root;
    }

    int cmp = strcmp(title, root->title);

    if (cmp < 0)
        root->left = delete(root->left, title);
    else if (cmp > 0) 
        root->right = delete(root->right, title);
    else 
	{
        // Book found, and we need to delete it
        if (root->left == NULL) 
		{
            struct Book* temp = root->right;
            free(root);
			printf("Book successfully deleted!!\n");
            return temp;
        } 
		else if (root->right == NULL) 
		{
            struct Book* temp = root->left;
            free(root);
			printf("Book successfully deleted!!\n");
            return temp;
        }

        // Book has two children, find the in-order successor (smallest node in the right sub-tree)
        struct Book* temp = findMin(root->right);

        // Copy the in-order successor's content to this node
        strcpy(root->title, temp->title);
        strcpy(root->author, temp->author);

        // Delete the in-order successor
        root->right = delete(root->right, temp->title);
    }
    return root;
}

int main() {
    struct Book* root = NULL, *title;
    initBooks(&root);
    int ch;
    int ch2;
    STUDENT students[MAX_STUDENTS];
    STUDENT *ptr = NULL;
    int total_students = 0; 

   

    printf("------- Welcome to the libray -------\n");
    while(1)
	{
        printf("Choose login: \n1. Student \n2. Librarian\n3. Exit\n-----------------------------------\n");
        scanf("%d",&ch2);
        if (ch2==1)
        {
			do
			{
				printf("-----------------------------------\n1. Display Library Catalog\n2. Borrow a book\n3. Return a book\n4. Search a Book\n5. Exit\n-----------------------------------\nEnter your choice: ");
                
				scanf("%d",&ch);
				switch (ch) 
				{
					case 1:
                        printf("-----------------------------------\n"); 
						if (root==NULL)
							printf("No Books Available, Sorry for the inconvenience\n");
						else
							inorder(root);
						break;
					
                    case 2:
                        printf("-----------------------------------\n");
                        printf("Enter your name: ");
                        char name[MAX_NAME_LENGTH];
                        // scanf("%s", name);
                        getchar();
                        fgets(name, MAX_TITLE_LENGTH, stdin);
                        name[strcspn(name, "\n")] = '\0';

                        printf("Enter your SRN: ");
                        char SRN[MAX_SRN_LENGTH];
                        scanf("%s", SRN);
                        
                        ptr = createstudent(name, SRN); // Initializing ptr with the created student
                        issue_a_book(ptr,root,students ,&total_students);
                        printf("----------------------------------\n");
                        printf("Number of students with books: %d\n", total_students);
                        
                        for (int i = 0; i < total_students; i++) 
                        {
                            printf("----------------------------------\n");
                            printf("Student %d SRN: %s\n", i + 1, students[i].SRN);
                            printf("Books the student has borrowed: ");
                            for (int j=0; j<students[i].num_books; j++)
                            {
                                printf("%s, ", students[i].books[j]->title);
                            }
                            printf("\n");
                        }
                        
                        break;
                        
                        

                    case 3:
                        printf("-----------------------------------\n");
                        printf("Enter your SRN: ");
                        char returnSRN[MAX_SRN_LENGTH];
                        scanf("%s", returnSRN);

                        STUDENT* temp = searchStudent(students,returnSRN,total_students);
                        printf("Enter the title of book you want to return: \n");
                        char returntitle[MAX_TITLE_LENGTH];
                        getchar();
                        fgets(returntitle, MAX_TITLE_LENGTH, stdin);
                        returntitle[strcspn(returntitle, "\n")] = '\0'; //Removing \n from input if given
                        if(temp!=NULL)
                            return_a_book(temp,root,returntitle);
                        else
                            printf("Sorry, Student not found\n");
                        break;
						
					case 4:

						printf("Enter title of the book you want to search: ");
						char title2[MAX_TITLE_LENGTH];
                        getchar();
                        fgets(title2, MAX_TITLE_LENGTH, stdin);
                        title2[strcspn(title2, "\n")] = '\0'; //Removing \n from input if given
						struct Book* result = search(root,title2);
						if (result != NULL)
							printf("Book found: Availability: %d; Title: %s; Author; %s\n", result->avail, result->title, result->author);
						else 
							printf("Book not found.\n");
						break;
				}
			}while(ch<5);
		}
        else if (ch2==2)
        {
            do{
				printf("-----------------------------------\n1. Add A Book\n2. Search a Book \n3. Display Library \n4. Delete Book\n5. Display Students record\n6. Search Student\n7. View a Book Queue\n8. Exit\nEnter your choice:");
				scanf("%d",&ch);
				switch (ch) 
				{
                
					case 1:

                        printf("-----------------------------------\n");
						printf("Enter title ");
						char title[MAX_TITLE_LENGTH];
                        getchar(); // Clear the newline character from the input buffer
                        scanf("%[^\n]", title);

                        printf("Enter author ");
						char author[MAX_AUTHOR_LENGTH];
                        getchar();
					    scanf("%[^\n]", author);
                        
                        
                        
						struct Book* newBook = createBook(title, author);
						root = insert(root, newBook);
						break;

					case 2: 
                        printf("-----------------------------------\n");
                       printf("Enter title of the book you want to search: ");
						char title6[MAX_TITLE_LENGTH];
                        getchar(); // Clear the newline character from the input buffer
                        scanf("%[^\n]", title6);
						struct Book* result = search(root,title6);
						if (result != NULL)
							printf("Book found: Availability: %d; Title: %s; Author; %s\n", result->avail, result->title, result->author);
						else 
							printf("Book not found.\n");
						break;
						
					case 3: 
                        printf("-----------------------------------\n");
						if (root==NULL)
							printf("No Books Available, Sorry for the inconvenience\n");
						else
							inorder(root);
						break;
					
					case 4:
                        printf("-----------------------------------\n");
						printf("Enter the title of the book to be deleted:");
						scanf("%s", title);
						root=delete(root, title);
						break;

                    case 5:
                        printf("-----------------------------------\n");
                        displayStudents(students,total_students);
                        break;
                    
                    case 6:
                        printf("-----------------------------------\n");
                        dispStudentinfo(students,total_students);
                        break;
                    
                    case 7:
                    printf("-----------------------------------\n");
                       printf("Enter title of the book you want to search: ");
						char title4[MAX_TITLE_LENGTH];
                        getchar(); // Clear the newline character from the input buffer
                        scanf("%[^\n]", title4);
						struct Book* result2 = search(root,title4);
						
						if (result2 != NULL)
							displayBookQ(result2);
                        else 
							printf("Book not found.\n");
						break;
                    
                    case 8:
                        printf("\n-----------------------------------\n");
                    break;
                        
}
			}while(ch<8); 
		}
        else if(ch2==3)
			exit(1);
		
		else
            printf("Choose a valid login!!\n");         
    } 
    
    return 0;
}