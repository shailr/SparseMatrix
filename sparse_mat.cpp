#include<iostream>
#include<conio.h>

using namespace std;

//Sparse Matrix Class Definition------------------------------------------------
class SMatrix
{
      public:
             //Sparse Matrix Data Node Definition-------------------------------
             struct SMatrixData
             {
                     int row;
                     int col;
                     int value;
                     
                     SMatrixData():row(0),col(0),value(0){}
                     ~SMatrixData(){}
                     
                     int printData()
                     {
                          cout<<" ["<<row<<", "<<col<<", "<<value<<"] ";
                          return 1;
                     }
                     
                     SMatrixData operator=(SMatrixData data)
                     {
                                 row=data.row;
                                 col=data.col;
                                 value=data.value;
                                 return data;
                     }
             };
             //Sparse Matrix Data Node Definition Ends here---------------------


        private:
                //Single Node Of Sparse Matrix object Definition----------------
                struct SMatrixNode
                {
                     SMatrixData data;
                     SMatrixNode* row_link;
                     SMatrixNode* col_link;
                     
                     SMatrixNode():data(),row_link(0),col_link(0){}
                     ~SMatrixNode(){}
                };
                //Single Node Of Sparse Matrix object Definition Ends here------
                
                //Sparse Matrix Iterator Base Class Definition------------------
                class SMatrixIter
                {
                    protected:
                              SMatrixNode* iterator;
                              SMatrixIter():iterator(0){}
                              explicit SMatrixIter(SMatrixNode* same_obj):iterator(same_obj){}
                              ~SMatrixIter(){}
                };
                //Sparse Matrix Iterator Base Class Definition Ends here--------
                
                //Sparse Matrix(SMatrix) Private Elements Declaration-----------
                SMatrixNode head;
                int max_rows;
                int max_cols;
                void insertNode(SMatrixNode* );
                int deleteNode(int, int );
                //Sparse Matrix(SMatrix) Private Elements Declaration Ends here-


        public:
               class SMatrixRowIter;
               class SMatrixColIter;
               
               //Sparse Matrix Row Iterator derived from Sparse Matrix Iterator-
               class SMatrixRowIter: private SMatrixIter
               {
                     friend class SMatrixColIter;
                     public:
                            SMatrixRowIter(){}
                            SMatrixRowIter(const SMatrixColIter& obj):SMatrixIter(obj.iterator){}
                            SMatrixRowIter(const SMatrix& same_obj):SMatrixIter(same_obj.head.col_link){}
                            ~SMatrixRowIter(){}
                            
                            //Checks for Iterator pointing NULL
                            int isNull()
                            {
                                if(iterator==NULL)
                                     return 1;
                                return 0;
                            }
                            
                            //"++"(Pre-Increament) Operator Overloading
                            SMatrixRowIter& operator++()
                            {
                                    try{
                                        if(iterator==NULL)
                                              throw 0;
                                        iterator=iterator->col_link;
                                        return *this;
                                    }
                                    catch(int i)
                                    {
                                            if(i==0)
                                                 cout<<"Iterator has reached the End. Cant point next.";
                                            else
                                                cout<<endl<<"ERROR:Unknown Error"<<endl;
                                    }
                            }
                            
                            //"*"(Dereference) Operator Overloading
                            SMatrixData& operator*()
                            {
                                    try{
                                        if(iterator==NULL)
                                              throw 0;
                                        return iterator->data;
                                    }
                                    catch(int i)
                                    {
                                            if(i==0)
                                                 cout<<"Iterator has reached the End. Cant read data.";
                                            else
                                                cout<<endl<<"ERROR:Unknown Error"<<endl;
                                    }
                            }
               };
               //Sparse Matrix Row Iterator definition Ends here----------------
               
               //Sparse Matrix Column Iterator derived from Sparse Matrix Iterator
               class SMatrixColIter: private SMatrixIter
               {
                     friend class SMatrixRowIter;
                     public:
                            SMatrixColIter(){}
                            SMatrixColIter(const SMatrixRowIter& obj):SMatrixIter(obj.iterator){}
                            SMatrixColIter(const SMatrix& same_obj):SMatrixIter(same_obj.head.row_link){}
                            ~SMatrixColIter(){}
                            
                            //Checks for Iterator pointing NULL
                            int isNull()
                            {
                                if(iterator==NULL)
                                     return 1;
                                return 0;
                            }
                            
                            //"++"(Pre-Increament) Operator Overloading
                            SMatrixColIter& operator++()
                            {
                                    try{
                                        if(iterator==NULL)
                                              throw 0;
                                        iterator=iterator->row_link;
                                        return *this;
                                    }
                                    catch(int i)
                                    {
                                            if(i==0)
                                                cout<<"Iterator has reached the End. Cant point next.";
                                            else
                                                cout<<endl<<"ERROR:Unknown Error"<<endl;
                                    }
                            }
                            
                            //"*"(Dereference) Operator Overloading
                            SMatrixData& operator*()
                            {
                                    try{
                                        if(iterator==NULL)
                                              throw 0;
                                        return iterator->data;
                                    }
                                    catch(int i)
                                    {
                                            if(i==0)
                                                cout<<"Iterator has reached the End. Cant read data.";
                                            else
                                                cout<<endl<<"ERROR:Unknown Error"<<endl;
                                    }
                            }
               };
               //Sparse Matrix Column Iterator definition Ends here-------------
               
               //Sparse Matrix(SMatrix) Public Elements Declaration-------------
               SMatrix();
               SMatrix(int ,int );
               ~SMatrix();
               void setValue(int , int , int ) throw(int );
               void deleteList();
               int getMaxRows() const;
               int getMaxCols() const;
               void askData() throw(int );
               void printMatrix() const throw(int );
               const SMatrix& operator+(const SMatrix& rhs) throw(int );
               const SMatrix& operator*(const SMatrix& rhs) throw(int );
               void transpose();
               SMatrixRowIter rowBegin(int ) const;
               SMatrixRowIter rowEnd(int ) const;
               SMatrixColIter colBegin(int ) const;
               SMatrixColIter colEnd(int ) const;
               //Sparse Matrix(SMatrix) Public Elements declaration Ends here---
};
//Sparse Matrix Class Definition Ends here--------------------------------------

//Sparse Matrix Function Definition---------------------------------------------
SMatrix::SMatrix():head(),max_rows(0),max_cols(0){}

SMatrix::SMatrix(int no_rows, int no_cols):head(),max_rows(no_rows),max_cols(no_cols){}

SMatrix::~SMatrix()
{
         deleteList();
}

//InsertNode Function:To insert a node in matrix...
void SMatrix::insertNode(SMatrixNode* new_node)
{
     SMatrixNode *ptr=NULL, *prev=NULL;
     if(head.row_link==NULL && head.col_link==NULL)
     {
           head.row_link = new_node;
           head.col_link = new_node;
     }
     else
     {
           ptr=head.row_link;
           prev=NULL;
           while(ptr!=NULL && (ptr->data.row)<(new_node->data.row))
           {
                prev=ptr;
                ptr=ptr->row_link;
           }
           if(ptr==NULL)
           {
                new_node->row_link = prev->row_link;
                prev->row_link = new_node;
           }
           else
           {
               while(ptr!=NULL && (ptr->data.row)==(new_node->data.row) && (ptr->data.col)<(new_node->data.col))
               {
                    prev=ptr;
                    ptr=ptr->row_link;
               }
               if(ptr!=NULL)
               {
                       if((ptr->data.row)==(new_node->data.row) && (ptr->data.col)==(new_node->data.col))
                       {
                               new_node->row_link=ptr->row_link;
                               if(prev!=NULL)
                               {
                                    prev->row_link=new_node;
                               }
                               else
                               {
                                    head.row_link=new_node;
                               }
                               //Dont delete node here as it is required for 
                               //insertion in column, it is deleted over there
                               //delete(ptr);              
                               ptr=NULL;
                       }
                       else
                       {
                               new_node->row_link=ptr;
                               if(prev!=NULL)
                               {
                                             prev->row_link=new_node;
                               }
                               else
                               {
                                             head.row_link=new_node;
                               }
                       }
               }
               else
               {
                       new_node->row_link=prev->row_link;
                       prev->row_link=new_node;
               }
           }
           ptr=head.col_link;
           prev=NULL;
           while(ptr!=NULL && (ptr->data.col)<(new_node->data.col))
           {
                prev=ptr;
                ptr=ptr->col_link;
           }
           if(ptr==NULL)
           {
                new_node->col_link = prev->col_link;
                prev->col_link = new_node;
           }
           else
           {
               while(ptr!=NULL && (ptr->data.col)==(new_node->data.col) && (ptr->data.row)<(new_node->data.row))
               {
                    prev=ptr;
                    ptr=ptr->col_link;
               }
               if(ptr!=NULL)
               {
                       if((ptr->data.col)==(new_node->data.col) && (ptr->data.row)==(new_node->data.row))
                       {
                               new_node->col_link=ptr->col_link;
                               if(prev!=NULL)
                               {
                                    prev->col_link=new_node;
                               }
                               else
                               {
                                    head.col_link=new_node;
                               }
                               delete(ptr);
                               ptr=NULL;
                       }
                       else
                       {
                               new_node->col_link=ptr;
                               if(prev!=NULL)
                               {
                                             prev->col_link=new_node;
                               }
                               else
                               {
                                             head.col_link=new_node;
                               }
                       }
               }
               else
               {
                       new_node->col_link=prev->col_link;
                       prev->col_link=new_node;
               }
           }
     }
}

void SMatrix::deleteList()
{
       SMatrixNode *ptr=head.row_link, *next;
       while(ptr!=NULL)
       {
             next=ptr->row_link;
             delete ptr;
             ptr=next;
       }
       head.row_link = NULL;
       head.col_link = NULL;
       max_rows = 0;
       max_cols = 0;
}

//Deletes the node with given parameters...
int SMatrix::deleteNode(int row, int col)
{
        SMatrixNode *ptr, *prev;
        int sc=1;
        if(head.row_link==NULL && head.col_link==NULL)
        {
               sc=0;
        }
        else
        {
               
               ptr=head.row_link;
               prev=NULL;
               while(ptr!=NULL && ptr->data.row<row)
               {
                    prev=ptr;
                    ptr=ptr->row_link;
               }
               if(ptr==NULL || ptr->data.row>row)
               {
                    sc=0;
               }
               else
               {
                       while(ptr!=NULL && ptr->data.row==row && ptr->data.col<col)
                       {
                                prev=ptr;
                                ptr=ptr->row_link;
                       }
                       if(ptr==NULL || ptr->data.row>row || ptr->data.col>col)
                       {
                                sc=0;
                       }
                       else
                       {
                                if(prev!=NULL)
                                {
                                            prev->row_link=ptr->row_link;
                                }
                                else
                                {
                                            head.row_link=ptr->row_link;
                                }
                                //Removed from row links.
                                //Node is not deleted, It is deleted 
                                //in column link.
                                ptr=NULL;
                       }
               }
               ptr=head.col_link;prev=NULL;
               while(ptr!=NULL && ptr->data.col<col)
               {
                    prev=ptr;
                    ptr=ptr->col_link;
               }
               if(ptr==NULL || ptr->data.col>col)
               {
                    sc=0;
               }
               else
               {
                       while(ptr!=NULL && ptr->data.col==col && ptr->data.row<row)
                       {
                                prev=ptr;
                                ptr=ptr->col_link;
                       }
                       if(ptr==NULL || ptr->data.col>col || ptr->data.row>row)
                       {
                                sc=0;
                       }
                       else
                       {
                                if(prev!=NULL)
                                {
                                            prev->col_link=ptr->col_link;
                                }
                                else
                                {
                                            head.col_link=ptr->col_link;
                                }
                                delete(ptr);
                                ptr=NULL;
                       }
               }
         }
         return sc;
}

//setValue Function: Wrapper for insertNode function...
void SMatrix::setValue(int row, int column, int value) throw(int )
{
        try
        {
                if(value==0)
                        throw 0;
                if(max_rows==0 && max_cols==0)
                        throw 2;
                if(row>=max_rows || column>=max_cols)
                        throw 1;
                if(row<0 || column<0)
                        throw -1;
                SMatrixNode* new_node=new SMatrixNode();
                new_node->data.row = row;
                new_node->data.col = column;
                new_node->data.value = value;
                insertNode(new_node);
        }
        catch(int i)
        {
                  if(i==0)
                  {
                          //No nodes with '0' value are actually added to Matrix.
                          //If Node already exists, then Delete the Node
                          //to set it to zero
                          deleteNode(row, column);
                  }
                  else
                  {
                       //Rethrow the exception...
                       throw;
                  }
        }
}

//Returns Max No. of Rows...
int SMatrix::getMaxRows() const
{
      return max_rows;
}
//Returns Max no. of Columns...
int SMatrix::getMaxCols() const
{
      return max_cols;
}

//This function takes data from user and sets it in matrix...
void SMatrix::askData() throw(int )
{
        if(max_rows==0 && max_cols==0)
                throw 2;
        int row = 0, col = 0, val = 0;
        char c='y';
        while(c=='y')
        {
                cout<<endl<<"Enter Row no.:";
                cin>>row;
                cout<<endl<<"Enter Column no.:";
                cin>>col;
                cout<<endl<<"Enter Value:";
                cin>>val;
                setValue(row, col, val);
                cout<<endl<<"Press 'y' to Set more values, anything else to Exit to Main Menu.";
                c=getch();
        }
}

//This Function prints the Sparse Matrix in given form...
void SMatrix::printMatrix() const throw(int )
{
        if(max_rows==0 && max_cols==0)
                       throw 2;
        int r=0;
        //Row-Wise Printing
        //cout<<endl<<endl<<"Row-wise:"<<endl;
        SMatrixNode* ptr=head.row_link;
        cout<<endl<<"---------------------------------------------------------------"<<endl;
        while(ptr!=NULL)
        {
                if(r!=ptr->data.row)
                {
                        cout<<endl;
                }
                ptr->data.printData();
                r=ptr->data.row;
                ptr=ptr->row_link;
        }
        cout<<endl<<"---------------------------------------------------------------"<<endl;
                                    /*//Column-Wise Printing
                                    cout<<endl<<endl<<"Column-wise:"<<endl;
                                    ptr=head.col_link;
                                    while(ptr!=NULL)
                                    {
                                            if(r!=ptr->data.col)
                                            {
                                                    cout<<endl;
                                            }
                                            ptr->data.printData();
                                            r=ptr->data.col;
                                            ptr=ptr->col_link;
                                    }
                                    */
}

//'+'(Addition) Operator Overloading...
const SMatrix& SMatrix::operator+(const SMatrix& rhs) throw(int )
{
       if(max_rows!=rhs.getMaxRows() || max_cols!=rhs.getMaxCols())
       {
                throw 11;
       }
       else
       {
            int sum=0;
            SMatrixColIter lmat_iter(*this);
            SMatrixColIter rmat_iter(rhs);
            SMatrix *result= new SMatrix(max_rows,max_cols);
            //Adding till at least any one of them become null
            while(!lmat_iter.isNull() && !rmat_iter.isNull())
            {
                     if((*lmat_iter).row==(*rmat_iter).row && (*lmat_iter).col==(*rmat_iter).col)
                     {
                             if((sum=(*lmat_iter).value+(*rmat_iter).value)!=0)
                             {
                                    result->setValue((*lmat_iter).row,(*lmat_iter).col,((*lmat_iter).value+(*rmat_iter).value));
                             }
                             ++lmat_iter;
                             ++rmat_iter;
                     }
                     else if((*lmat_iter).row<(*rmat_iter).row || ((*lmat_iter).row==(*rmat_iter).row && (*lmat_iter).col<(*rmat_iter).col))
                     {
                             result->setValue((*lmat_iter).row,(*lmat_iter).col,(*lmat_iter).value);
                             ++lmat_iter;
                     }
                     else
                     {
                             result->setValue((*rmat_iter).row,(*rmat_iter).col,(*rmat_iter).value);
                             ++rmat_iter;
                     }
            }
            //Adding remains of left matrix if any
            while(!lmat_iter.isNull())
            {
                     result->setValue((*lmat_iter).row,(*lmat_iter).col,(*lmat_iter).value);
                     ++lmat_iter;
            }
            //Adding remains of right matrix if any
            while(!rmat_iter.isNull())
            {
                     result->setValue((*rmat_iter).row,(*rmat_iter).col,(*rmat_iter).value);
                     ++rmat_iter;
            }
            return *result;
       }
}

//'*'(Multiplication) Operator Overloading...
const SMatrix& SMatrix::operator*(const SMatrix& rhs) throw(int )
{
       if((*this).getMaxCols()!=rhs.getMaxRows())
       {
                throw 12;
       }
       else
       {
                      //cout<<"Inside mult";
                //Left Matrix Column Iterator
                SMatrixColIter l_col_iter;
                //Left Matrix Column Iterator End
                SMatrixColIter l_col_iter_end;
                //Right Matrix Row Iterator
                SMatrixRowIter r_row_iter;
                //Right Matrix Column Iterator End
                SMatrixRowIter r_row_iter_end;
                SMatrix *result = new SMatrix((*this).getMaxRows(),rhs.getMaxCols());
                for(int row=0; row<(*this).getMaxRows(); row++)
                {
                               //cout<<"Inside 1st for loop";
                        for(int col=0; col<rhs.getMaxCols(); col++)
                        {
                                        //cout<<"Inside 2nd for loop";
                                int sum = 0;
                                        //cout<<"creating colbegin";
                                l_col_iter = (*this).colBegin(row);
                                        //cout<<"creating colend";
                                l_col_iter_end = (*this).colEnd(row);
                                        //cout<<"creating rowbegin";
                                r_row_iter = rhs.rowBegin(col);
                                        //cout<<"creating rowend";
                                r_row_iter_end = rhs.rowEnd(col);
                                        //cout<<"All iterators are initialised";
                                while(!l_col_iter.isNull() && !r_row_iter.isNull() && (l_col_iter_end.isNull() || ((*l_col_iter).row<(*l_col_iter_end).row)) && (r_row_iter_end.isNull() || (*r_row_iter).col<(*r_row_iter_end).col))
                                {
                                                           //cout<<"Inside while";
                                        if((*l_col_iter).col==(*r_row_iter).row)
                                        {
                                                           //cout<<"Inside while if 1";
                                                sum += (*l_col_iter).value * (*r_row_iter).value;
                                                ++l_col_iter;
                                                ++r_row_iter;
                                        }
                                        else if((*l_col_iter).col<(*r_row_iter).row)
                                        {
                                                           //cout<<"Inside while if 2";
                                                //sum += (*l_col_iter).value * 0;
                                                ++l_col_iter;
                                        }
                                        else
                                        {
                                                           //cout<<"Inside while if 3";
                                                //sum += 0 * (*r_row_iter).value;
                                                ++r_row_iter;
                                        }
                                }
                                                           //cout<<"outside while ending for loop 2";
                                result->setValue(row, col, sum);
                        }
                                //cout<<"outside for 2 inside for 1";
                }
                        //cout<<"Exit from all loop";
                return *result;
       }
}

//Transpose Sparse Matrix...
void SMatrix::transpose()
{
        if(max_rows==0 && max_cols==0)
                       throw 2;
        SMatrix* transpose = new SMatrix(max_cols,max_rows);
        SMatrixColIter iter(*this);
        while(!iter.isNull())
        {
                transpose->setValue((*iter).col,(*iter).row,(*iter).value);
                ++iter;
        }
        deleteList();
        head = transpose->head;
        max_rows = transpose->max_rows;
        max_cols = transpose->max_cols;
}

//Row Begin...
SMatrix::SMatrixRowIter SMatrix::rowBegin(int column) const
{
        SMatrixRowIter row_iter(*this);
        while(!row_iter.isNull() && (*row_iter).col<column)
        {
               ++row_iter;
        }
        return row_iter;
}

//Row End...
SMatrix::SMatrixRowIter SMatrix::rowEnd(int column) const
{
        SMatrixRowIter row_iter = this->rowBegin(column);
        while(!row_iter.isNull() && (*row_iter).col==column)
        {
                ++row_iter;
        }
        return row_iter;
}

//Column Begin...
SMatrix::SMatrixColIter SMatrix::colBegin(int row) const
{
        SMatrixColIter col_iter(*this);
        while(!col_iter.isNull() && (*col_iter).row<row)
        {
               ++col_iter;
        }
        return col_iter;
}

//Column End...
SMatrix::SMatrixColIter SMatrix::colEnd(int row) const
{
        SMatrixColIter col_iter = this->colBegin(row);
        while(!col_iter.isNull() && (*col_iter).row==row)
        {
                ++col_iter;
        }
        return col_iter;
}
//-------------------------------------------End of Sparse Matrix-----------------------------------------------------

int commandPage();
void switchControl(SMatrix ,SMatrix ,SMatrix );
int main()
{
      cout<<"-------------------------------------------------------------------------------\n";
      cout<<"                      |           WELCOME           |                          \n";
      cout<<"-------------------------------------------------------------------------------\n\n";
      SMatrix matrix1, matrix2, matrix3;
      switchControl(matrix1, matrix2, matrix3);
      cout<<"-------------------------------------------------------------------------------\n";
      cout<<"                      |          THANK YOU!!!       |                          \n";
      cout<<"-------------------------------------------------------------------------------\n";
      cout<<"                      |           THE END           |                          \n";
      cout<<"-------------------------------------------------------------------------------\n\n";
      getch();
      return 0;
}

//Instructions...
int commandPage()
{
            int c=0;
            cout<<"Press '1' to set Size of the Matrix.\n";
            cout<<"Press '2' to set data in the list.\n";
            cout<<"Press '3' to Add two Matrices.(matrix3=matrix1+matrix2)\n";
            cout<<"Press '4' to Multiply two Matrices.(matrix3=matrix1*matrix2)\n";
            cout<<"Press '5' to do the Transpose.\n";
            cout<<"Press '6' to Print the Matrix.\n";
            cout<<"Press '0' to Exit.\n";
            cout<<"\n\n";
            cout<<"Choice:";
            cin>>c;
            return c;
}

//Main Switch which manages all operations...
//Matrix1 & 2 takes data from user. Matrix3 is result matrix...
void switchControl(SMatrix matrix1, SMatrix matrix2, SMatrix matrix3)
{
            int c=-1, row=0, col=0;
            int m=0;
            while(c!=0)
            {
                  try
                  {
                        c=commandPage();
                        switch(c)
                        {
                                case 1: 
                                     cout<<endl<<"Enter the matrix no.(1/2):";
                                     cin>>m;
                                     if(m==1)
                                     {
                                             cout<<endl<<"Enter the order of matrix:";
                                             cin>>row>>col;
                                             matrix1.deleteList();
                                             matrix1=SMatrix(row, col);
                                             cout<<endl<<"Matrix1 Initialized";
                                     }
                                     else if(m==2)
                                     {
                                             cout<<endl<<"Enter the order of matrix:";
                                             cin>>row>>col;
                                             matrix2.deleteList();
                                             matrix2=SMatrix(row, col);
                                             cout<<endl<<"Matrix2 Initialized";
                                     }
                                     else
                                             cout<<endl<<"No such matrix exist.\n";
                                     break;
                                case 2:
                                     cout<<endl<<"Enter the matrix no.(1/2):";
                                     cin>>m;
                                     if(m==1)
                                                  matrix1.askData();
                                     else if(m==2)
                                                  matrix2.askData();
                                     else
                                                  cout<<endl<<"No such matrix exist.\n";
                                     break;
                                case 3:
                                     matrix3.deleteList();
                                     matrix3 = matrix1 + matrix2;
                                     cout<<endl<<"Result is stored in Matrix3";
                                     break;
                                case 4:
                                     matrix3.deleteList();
                                     matrix3 = matrix1 * matrix2;
                                     cout<<endl<<"Result is stored in Matrix3";
                                     break;
                                case 5:
                                     cout<<endl<<"Enter the matrix no.(1/2/3):";
                                     cin>>m;
                                     if(m==1)
                                             matrix1.transpose();
                                     else if(m==2)
                                             matrix2.transpose();
                                     else if(m==3)
                                             matrix3.transpose();
                                     else
                                             cout<<endl<<"No such matrix exist.\n";
                                     break;
                                case 6:
                                     cout<<endl<<"Enter the matrix no.(1/2/3):";
                                     cin>>m;
                                     if(m==1)
                                             matrix1.printMatrix();
                                     else if(m==2)
                                             matrix2.printMatrix();
                                     else if(m==3)
                                             matrix3.printMatrix();
                                     else
                                             cout<<endl<<"No such matrix exist.\n";
                                     break;
                                default:
                                        break;
                        }
                  }
                  catch(int i)
                  {
                          switch(i)
                          {
                               case 1:
                                    cout<<endl<<"ERROR: Index out of Bound(Note: It's a Zero Based Matrix.)"<<endl;
                                    break;
                               case 2:
                                    cout<<endl<<"ERROR: Matrix is not yet Initialized\nNOTE: Use option '1' to initialize."<<endl;
                                    break;
                               case -1:
                                    cout<<endl<<"ERROR: Invalid Index(Index can not be Negative)"<<endl;
                                    break;
                               case 11:
                                    cout<<endl<<"ERROR: Sizes are not same"<<endl;
                                    break;
                               case 12:
                                    cout<<endl<<"ERROR: Sizes are not multipliable"<<endl;
                                    break;
                               default:
                                       cout<<endl<<"ERROR:Unknown Error"<<endl;;
                          }
                  }
                  cout<<"\n\n";
            }
}
