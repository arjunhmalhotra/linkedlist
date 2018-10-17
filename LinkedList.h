//====================== LINKED LIST CLASS [DEFINITIONS] ======================
// Arjun Malhotra
// LinkedList.h
// This program implements a linked list class. 
//=============================================================================

#include <iostream>
#include <stdlib.h>
#include "string.h"
#include <sstream>

using namespace std;

#ifndef LIST_H
#define LIST_H

//=============================================================================
// Linked List Class
//=============================================================================

template<class T>
class List
{			
	private:
		struct Node
		{
			T 		 data;			// data item in each link
			Node	*next;			// self referencing class
		};
		int 	len;
		Node	*head;				// node pointer for linked list
		
	public:
	
		List  ( void );							// default constructor
		List  ( const List<T> &l );				// copy constructor
	   ~List  ( void );							// destructor
	   
	int 		length ( void );				// number of links
	bool		isEmpty ( void );				// if head == NULL
	void		append ( T item );				// appends a link
	void		remove ( int n );				// removes a link
	List<T>	operator+ ( const List<T> &l ); 	// concatenator
	List<T>	operator= ( const List<T> &l );		// assignment operator
	void		clear ( void );					// clears all links
	T&			operator[] ( int n );			// modifies/accesses @ index
	string		toString ( void );
	void		insert ( T item, int posn );
	
			friend ostream & operator<< ( ostream &os, List<T> &l )
			{	
				Node *i = l.head;
				
				while ( i != NULL )
				{
					os << i->data << " ";
					i = i->next;
				}
				
				return os;
			}
					
};			

//=============================================================================
// Linked List Class
//=============================================================================

//=============================================================================
// CONSTRUCTORS & DESTRUCTOR
//=============================================================================
//-----------------------------------------------------------------------------
// Default Constructor 
// initializes a new list
//-----------------------------------------------------------------------------
template<class T>
					List<T>::List ( void )
{
			head = NULL;
			len = 0;
}
//-----------------------------------------------------------------------------
// Copy Constructor 
// initializes a new list
//-----------------------------------------------------------------------------
template<class T>
					List<T>::List ( const List<T> &l)
{
			len = 0;
			head = NULL;
			
			Node * ptr = l.head;				// initializes ptr location
			
			while ( ptr != NULL )
			{
				append(ptr->data);				// appends data in node
				ptr = ptr->next;				// shifts ptr
			}	
}
//-----------------------------------------------------------------------------
// Destructor
// initializes a new list
//-----------------------------------------------------------------------------
template<class T>
					List<T>::~List ( void )
{
			clear();
}
//-----------------------------------------------------------------------------

//=============================================================================
// ACCESSORS
//=============================================================================
//-----------------------------------------------------------------------------
// isEmpty
// returns true if the list is empty, false if not
//-----------------------------------------------------------------------------
template<class T>
bool					List<T>::isEmpty ( void )
{
		return ( len == 0 );
}
//-----------------------------------------------------------------------------
// length
// returns the number of items in the list
//-----------------------------------------------------------------------------
template<class T>
int						List<T>::length ( void )
{
		return len;
}
//-----------------------------------------------------------------------------
// operator[]
// accesses (by reference) the item at the specified index
//-----------------------------------------------------------------------------
template<class T>
T&						List<T>::operator[] ( int i )
{

		Node *ptr = head;
		 
		if ( i > len or i < 0 )
			{cout << "ERROR: accessed invalid index" << endl;
			exit(1);}						// fail switch
		else
			while ( i )
			{
				i--;						// counts down list
				ptr = ptr->next;			// shifts ptr
			}
			
		return ptr->data;
}
//-----------------------------------------------------------------------------
// toString
// "Prints" the list contents to a string and returns the string
//-----------------------------------------------------------------------------
template<class T>
string					List<T>::toString ( void )
{
		stringstream ss;					// includes ss to switch to string

		Node *ptr = head;

		while ( ptr != NULL )
		{
			ss << ptr->data << " ";			// adds data to stream
			ptr = ptr->next;
		}
		string str = ss.str();				// equates stream to string

		return str;
}
//-----------------------------------------------------------------------------

//=============================================================================
// MODIFIERS
//=============================================================================
//-----------------------------------------------------------------------------
// Append
// appends a new int onto the back of the list
//-----------------------------------------------------------------------------
template<class T>
void					List<T>::append ( T item )
{
		Node * ptr = new Node;
		ptr->data = item;
		ptr->next = NULL;

		if ( head == NULL )
		{
			head = ptr;						// if list is empty
		}
		else
		{
			Node *qtr = head;				
			while ( qtr->next != NULL )		
				qtr = qtr->next;
			qtr->next = ptr;
		}
		len++;
								
}
//-----------------------------------------------------------------------------
// Insert
// inserts a new value at the specified position and reallocates head & next
//-----------------------------------------------------------------------------
template<class T>
void					List<T>::insert ( T item, int posn )
{
		//cout << "CHECK" << endl;
		Node *ptr = head;
		Node *temp = new Node;
		temp->data = item;
		int i = 0;
		
		if ( posn > len or posn < 0 )
			{cout << "ERROR: accessed invalid index" << endl;
			exit(1);}				// fail switch

		else if ( posn == 0 )			// case for beginning of list
		{
			temp->next = ptr;
			head = temp;
		}
		
		else if ( posn == len )			// case for starting of list
		{
			append(item);				// adds item to back of list
		}				

		else							// for in between the list
		{
			while ( i < posn - 1 ) 
			{	
				ptr = ptr->next;
				i++;
			}	
			temp->next = ptr->next;
			ptr->next = temp;
		}

		len++;
}
//-----------------------------------------------------------------------------
// Remove
// removes an int at a specified location 
//-----------------------------------------------------------------------------
template<class T>
void					List<T>::remove ( int n )
{		
		Node *ptr = head;
		Node *qtr = head;
		
		if ( n > len or n < 0 )
			{cout << "ERROR: accessed invalid index" << endl;
			exit(1);}							// fail switch		
			
		else if ( n == 0 )				// if removing first link
		{
			qtr = ptr->next;
			delete ptr;
			head = qtr;
		}
		
		else if ( n == len )			// last link
		{
			n = n - 1;
			while ( n )
			{
				qtr = qtr->next;
				ptr = ptr->next;
				n--;
			}
			ptr = ptr->next;
			delete ptr;
			qtr->next = NULL;
		}
		
		else							// some link in between
		{
			n = n - 1;
			while ( n )
			{
				qtr = qtr->next;
				ptr = ptr->next;
				n--;
			}
			ptr = ptr->next;
			qtr->next = ptr->next;
			delete ptr;			
		}
		
		len--;			
}	
//-----------------------------------------------------------------------------
// operator+
// concatenates two lists into a new list. doesn't change either existing list.
//-----------------------------------------------------------------------------
template<class T>
List<T>					List<T>::operator+ ( const List<T> &l )
{
		List<T> ret;
		
		Node *ptr = head;
		Node *qtr = l.head;

		while ( ptr != NULL )			// appends first list
			{
				ret.append(ptr->data);
				ptr = ptr->next;
			}		
			
		while ( qtr != NULL )			// appends second list
			{
				ret.append(qtr->data);
				qtr = qtr->next;
			}
		return ret;
}		
//-----------------------------------------------------------------------------
// operator=
// assigns one list as another list
//-----------------------------------------------------------------------------
template<class T>
List<T>					List<T>::operator= ( const List<T> &l )
{
		clear();
		
		Node * ptr = l.head;
		
		while ( ptr != NULL )
		{
			append(ptr->data);			// appends old list
			ptr = ptr->next;
		}
		return *this;		
}
//-----------------------------------------------------------------------------
// clear
// removes all items from the list
//-----------------------------------------------------------------------------
template<class T>
void					List<T>::clear ( void )
{
	Node *ptr, *qtr;
	ptr = qtr = head;

	while ( ptr != NULL )			// while loop to delete all links
	{
		qtr = qtr->next;
		delete ptr;
		ptr = qtr;
		len--;
	}
	head = NULL;
}
//-----------------------------------------------------------------------------

//================================= END =======================================
#endif	



