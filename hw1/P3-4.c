/* Step 1: Get the length of list */
/*========================================*/
Ptr = Head;
Length = 1;

while( Ptr->Next != Head )
{
   Ptr = Ptr->Next;
   Length++;
}

/* Step 2: Sorting list with bubble sort */
/*========================================*/
itr_out = 0; /*iteration number of the outer loop*/
Stop = true; /*Do not enter the outer loop if Stop=false,
                      which can help the time complexity in the worst case down to O(n)*/
Ptr = Head;

while( Ptr->Next != Head && Stop )
{
   Ptr_in = Head;
   Stop = false;
   itr_in = 0;  /*iteration number of the inner loop*/

   while( Ptr_in->Next != Head && itr_in < Length - itr_out - 1 )
   {
      if ( Ptr_in->Next->Data  <  Ptr_in->Data )
      {
         swap( Ptr_in->Next->Data, Ptr_in->Data );
         /*swap data but pointers*/
         Stop = true;
      }
      Ptr_in = Ptr_in -> Next;

      itr_in++;
   }
   Ptr = Ptr->Next;
   itr_out++;
}

