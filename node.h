/***********************************************************************
 * Header:
 *    NODE
 * Summary:
 *    One node in a linked list (and the functions to support them).
 *      __      __     _______        __
 *     /  |    /  |   |  _____|   _  / /
 *     `| |    `| |   | |____    (_)/ /
 *      | |     | |   '_.____''.   / / _
 *     _| |_   _| |_  | \____) |  / / (_)
 *    |_____| |_____|  \______.' /_/
 *
 *    This will contain the class definition of:
 *        Node         : A class representing a Node
 *    Additionally, it will contain a few functions working on Node
 * Author
 *    Joel Jossie & Gergo Medveczky
 ************************************************************************/

#pragma once

#include <cassert>     // for ASSERT
#include <iostream>    // for NULL

/*************************************************
 * NODE
 * the node class.  Since we do not validate any
 * of the setters, there is no point in making them
 * private.  This is the case because only the
 * List class can make validation decisions
 *************************************************/
template <class T>
class Node
{
public:
   //
   // Construct
   //
   //
   // Construct
   //

   Node(): pNext(nullptr), pPrev(nullptr) { }
   
   Node(const T& data) : pNext(nullptr), pPrev(nullptr), data(data) {}

   Node(T&& data) :data(data)  {  pNext = pPrev = nullptr;  }

   //
   // Member variables
   //

   T data;                 // user data
   Node <T> * pNext;       // pointer to next node
   Node <T> * pPrev;       // pointer to previous node
};

/***********************************************
 * COPY
 * Copy the list from the pSource and return
 * the new list
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline Node <T> * copy(const Node <T> * pSource) 
{
   Node <T>* pDestination = nullptr;
   
   if(pSource != nullptr)
   {
      pDestination = new Node<T>(pSource->data);
      Node <T>* destCurrent = pDestination;
      for (auto p = pSource->pNext;p;p=p->pNext)
         destCurrent = insert(destCurrent, p->data, true);
   }
   return pDestination;
}

/***********************************************
 * Assign
 * Copy the values from pSource into pDestination
 * reusing the nodes already created in pDestination if possible.
 *   INPUT  : the list to be copied
 *   OUTPUT : return the new list
 *   COST   : O(n)
 **********************************************/
template <class T>
inline void assign(Node <T> * & pDestination, const Node <T> * pSource)
{
   auto pDes = pDestination;
   auto pSrc = pSource;
   auto pDesPrevious = pDes;
   while (pSrc != nullptr && pDes != nullptr)
   {
      pDes->data = pSrc->data;
      pDesPrevious = pDes;
      pDes = pDes->pNext;
      pSrc = pSrc->pNext;
   }
   
   if (pSrc != nullptr)
   {  // Source list is longer than destination list
      pDes = pDesPrevious;
      
      while (pSrc != nullptr)
      {
         pDes = insert(pDes, pSrc->data, true);
         if (pDestination == nullptr)
            pDestination = pDes;
         pSrc = pSrc->pNext;
      }
      
   }
   else if (pSrc == nullptr && pDes != nullptr)
   {  // Destination list is longer than source list
      bool setToNull = false;
      
      if (pDes->pPrev != nullptr)
      {
         pDes->pPrev->pNext = nullptr;
      }
      else
      {
         setToNull = true;
      }
      
      clear(pDes);
   
      if (setToNull)
         pDestination = nullptr;
   }
}

/***********************************************
 * SWAP
 * Swap the list from LHS to RHS
 *   COST   : O(1)
 **********************************************/
template <class T>
inline void swap(Node <T>* &pLHS, Node <T>* &pRHS) { std::swap(pLHS, pRHS); }

/***********************************************
 * REMOVE
 * Remove the node pSource in the linked list
 *   INPUT  : the node to be removed
 *   OUTPUT : the pointer to the parent node
 *   COST   : O(1)
 **********************************************/
template <class T>
inline Node <T> * remove(const Node <T> * pRemove) 
{
   
   if (pRemove == nullptr)
      return nullptr;
   if (pRemove->pPrev)
      pRemove->pPrev->pNext = pRemove->pNext;
   if (pRemove->pNext)
      pRemove->pNext->pPrev = pRemove->pPrev;
   
   Node<T> * pReturn;
   if (pRemove->pPrev)
      pReturn = pRemove->pPrev;
   else
      pReturn = pRemove->pNext;
   
   delete pRemove;
   pRemove = nullptr;
   return pReturn;
}


/**********************************************
 * INSERT 
 * Insert a new node the the value in "t" into a linked
 * list immediately before the current position.
 *   INPUT   : t - the value to be used for the new node
 *             pCurrent - a pointer to the node before which
 *                we will be inserting the new node
 *             after - whether we will be inserting after
 *   OUTPUT  : return the newly inserted item
 *   COST    : O(1)
 **********************************************/
template <class T>
inline Node <T> * insert(Node <T> * pCurrent,
                  const T & t,
                  bool after = false)
{
   Node <T>*newElement = new Node<T>(t);
   if (pCurrent != nullptr)
   {
      
   
   if(after == true)
   {
      if (pCurrent->pNext == nullptr)
      {
         // Simple Add After
         newElement->pPrev = pCurrent;
         pCurrent->pNext = newElement;
      }
      else
      {
         // Fancy Insert After
         newElement->pNext = pCurrent->pNext;
         newElement->pPrev = pCurrent;
         pCurrent->pNext = newElement;
         newElement->pNext->pPrev = newElement;
      }
      
   }
   else
   {
      if (pCurrent->pPrev == nullptr)
      {
         // Simple Add Before
         newElement->pNext = pCurrent;
         pCurrent->pPrev = newElement;
      }
      else
      {
         // Fancy insert before
         newElement->pNext = pCurrent;
         newElement->pPrev = pCurrent->pPrev;
         pCurrent->pPrev = newElement;
         newElement->pPrev->pNext = newElement;
      }
      
   }
   }
   return newElement;
}

/******************************************************
 * SIZE
 * Find the size an unsorted linked list.  
 *  INPUT   : a pointer to the head of the linked list
 *            the value to be found
 *  OUTPUT  : number of nodes
 *  COST    : O(n)
 ********************************************************/
template <class T>
inline size_t size(const Node <T> * pHead)
{
   unsigned int size = 0;
   while(pHead != nullptr)
   {
      size++;
      pHead = pHead->pNext;
   }
   return size;
}

/***********************************************
 * DISPLAY
 * Display all the items in the linked list from here on back
 *    INPUT  : the output stream
 *             pointer to the linked list
 *    OUTPUT : the data from the linked list on the screen
 *    COST   : O(n)
 **********************************************/
template <class T>
inline std::ostream & operator << (std::ostream & out, const Node <T> * pHead)
{
   return out;
}

/*****************************************************
 * FREE DATA
 * Free all the data currently in the linked list
 *   INPUT   : pointer to the head of the linked list
 *   OUTPUT  : pHead set to NULL
 *   COST    : O(n)
 ****************************************************/
template <class T>
inline void clear(Node <T> * & pHead)
{
   while (pHead != nullptr)
   {
      auto pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
}
