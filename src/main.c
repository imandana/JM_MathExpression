/* The MIT License

   JM_MathExpression
	
   Copyright (c) 2022, by Imandana Rahimaswara <jenggotmalamdev@gmail.com>

   Permission is hereby granted, free of charge, to any person obtaining
   a copy of this software and associated documentation files (the
   "Software"), to deal in the Software without restriction, including
   without limitation the rights to use, copy, modify, merge, publish,
   distribute, sublicense, and/or sell copies of the Software, and to
   permit persons to whom the Software is furnished to do so, subject to
   the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

/* kvec.h Licence
   See at "kvec.h"
*/

#include <stdio.h>
#include <stdlib.h>

#include "kvec.h"

int Mul(int val1, int val2)
{
    return val1 * val2;
}
int Div(int val1, int val2)
{
    return val1 / val2;
}
int Add(int val1, int val2)
{
     return val1 + val2;
}
int Sub(int val1, int val2)
{
     return val1 - val2;
}

typedef struct ASTBase
{
    struct ASTBase* parent;
	
	int (*Operator)(int, int);

	struct ASTBase* left;
	struct ASTBase* right;
	
	int visited;
	int value;
	
	char* name;
	
} ASTBase;

int main()
{
	// Remove the White space before use...
	char* theFormula="2*3+10/2;";
	
	printf("%s \n", theFormula);
	int sizeStr = strlen(theFormula);
	
	printf("%d \n", sizeStr);
	
	kvec_t(ASTBase*) astCollection;
	kv_init( astCollection );
	kv_resize(ASTBase*, astCollection, sizeStr);
	
	int changePos = 0;
	
	int theNumber = 0;
	int gap = 1;
	
	int numberGap = 0;
	ASTBase* temp = (ASTBase*)calloc(sizeStr, sizeof(ASTBase) );
	
	ASTBase* theRoot = temp;
	
	kv_push(ASTBase*, astCollection, temp );
	int parentHolder = kv_size( astCollection ) - 1;
	
	for(int i =0; i < sizeStr; i++)
	{
		
		// if number
		if( theFormula[ i ] > 47 && theFormula[ i ] < 58 )
		{
			theNumber = (theNumber*gap) + (theFormula[ i ] - '0');
			gap *= 10;

			numberGap ++;
			continue;
		}
		if( theFormula[i] == '+' )
		{	
			// Right
			temp++;
			kv_push( ASTBase*, astCollection, temp );
			
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->Operator = Add;
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->name = "Add";
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->right = astCollection.a[ kv_size( astCollection ) - 1 ];
			
			// Left
			temp++;
			kv_push( ASTBase*, astCollection, temp );

			astCollection.a[ kv_size( astCollection ) -1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) -1 ]->value = theNumber;
			astCollection.a[ kv_size( astCollection ) - 2 ]->parent->left = astCollection.a[ kv_size( astCollection ) -1 ];
			
			// Rotate?
			if(changePos == 1)
			{
				ASTBase* tempParent3x = astCollection.a[ kv_size( astCollection ) - 1 ]->parent->parent->parent;
				ASTBase* tempParent2x = astCollection.a[ kv_size( astCollection ) - 1 ]->parent->parent;
				ASTBase* tempParent = astCollection.a[ kv_size( astCollection ) - 1 ]->parent;
				
				theRoot = tempParent;
				
				astCollection.a[ kv_size( astCollection ) - 1 ]->parent->parent->right = 
				astCollection.a[ kv_size( astCollection ) - 1 ];
				
				astCollection.a[ kv_size( astCollection ) - 1 ]->parent = tempParent2x;
				
				tempParent->left = tempParent2x;
				tempParent->parent = tempParent3x;
				
				
				tempParent2x->parent = tempParent;
				///////////////////
				
				changePos = 0;
				
			}
			// Sementara parentHolder kita pake kanan dulu
			parentHolder = kv_size( astCollection ) - 2;

			theNumber = 0;
			gap = 1;
			
			continue;
		}
		if ( theFormula[i] == '-')
		{
			// Right
			temp++;
			kv_push( ASTBase*, astCollection, temp );
			
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->Operator = Sub;
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->name = "Sub";
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->right = astCollection.a[ kv_size( astCollection ) - 1 ];
			
			// Left
			temp++;
			kv_push( ASTBase*, astCollection, temp );

			astCollection.a[ kv_size( astCollection ) -1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) -1 ]->value = theNumber;
			astCollection.a[ kv_size( astCollection ) - 2 ]->parent->left = astCollection.a[ kv_size( astCollection ) -1 ];
			
			// Rotate?
			if(changePos == 1)
			{
				ASTBase* tempParent3x = astCollection.a[ kv_size( astCollection ) - 1 ]->parent->parent->parent;
				ASTBase* tempParent2x = astCollection.a[ kv_size( astCollection ) - 1 ]->parent->parent;
				ASTBase* tempParent = astCollection.a[ kv_size( astCollection ) - 1 ]->parent;
				
				theRoot = tempParent;
				
				astCollection.a[ kv_size( astCollection ) - 1 ]->parent->parent->right = 
				astCollection.a[ kv_size( astCollection ) - 1 ];
				
				astCollection.a[ kv_size( astCollection ) - 1 ]->parent = tempParent2x;
				
				tempParent->left = tempParent2x;
				tempParent->parent = tempParent3x;
				
				
				tempParent2x->parent = tempParent;
				///////////////////
				
				changePos = 0;
				
			}
			// Sementara parentHolder kita pake kanan dulu
			parentHolder = kv_size( astCollection ) - 2;
			
			theNumber = 0;
			gap = 1;
			
			continue;
		}
		if ( theFormula[i] == '*')
		{
			// Right
			temp++;
			kv_push( ASTBase*, astCollection, temp );
			
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->Operator = Mul;
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->name = "Mul";
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->right = astCollection.a[ kv_size( astCollection ) - 1 ];
			
			
			// Left
			temp++;
			kv_push( ASTBase*, astCollection, temp );

			astCollection.a[ kv_size( astCollection ) -1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) -1 ]->value = theNumber;
			astCollection.a[ kv_size( astCollection ) - 2 ]->parent->left = astCollection.a[ kv_size( astCollection ) -1 ];
			
			// Sementara parentHolder kita pake kanan dulu
			parentHolder = kv_size( astCollection ) - 2;
			
			changePos = 1;
			
			theNumber = 0;
			gap = 1;
			continue;
		}
		if ( theFormula[i] == '/')
		{
			// Right
			temp++;
			kv_push( ASTBase*, astCollection, temp );
			
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->Operator = Div;
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->name = "Div";
			astCollection.a[ kv_size( astCollection ) - 1 ]->parent->right = astCollection.a[ kv_size( astCollection ) - 1 ];
			
			
			// Left
			temp++;
			kv_push( ASTBase*, astCollection, temp );

			astCollection.a[ kv_size( astCollection ) -1 ]->parent = astCollection.a[ parentHolder ];
			astCollection.a[ kv_size( astCollection ) -1 ]->value = theNumber;
			astCollection.a[ kv_size( astCollection ) - 2 ]->parent->left = astCollection.a[ kv_size( astCollection ) -1 ];
			
			// Sementara parentHolder kita pake kanan dulu
			parentHolder = kv_size( astCollection ) - 2;
			
			changePos = 1;
			
			theNumber = 0;
			gap = 1;
			continue;
		}
		if ( theFormula[i] == '(')
		{
			// Belum Implementasi
			
			
			continue;
		}
		astCollection.a[ parentHolder ]->value = theNumber;
	}
	
	/////////////////////////////////////
	//Lets Execute the AST
	ASTBase* lookUp = theRoot;
	
	if( lookUp->right )
		lookUp = lookUp->right;
	
	
	//Right side of Parent child
	while( lookUp->parent != 0 )
	{
		if( lookUp->right && !lookUp->right->visited )
		{	
			lookUp = lookUp->right;
			continue;
		}
		
		if( lookUp->left && !lookUp->left->visited )
		{
			lookUp = lookUp->left;
			continue;
		}

		lookUp->parent->value = lookUp->parent->Operator( lookUp->parent->left->value, lookUp->parent->right->value );
		
		printf("%d = %d %s %d\n", lookUp->parent->value, lookUp->parent->left->value, lookUp->parent->name, lookUp->parent->right->value);
		
		lookUp->parent->right->visited = 1;
		lookUp->parent->left->visited = 1;
		
		lookUp = lookUp->parent;
	}
	
	if( lookUp->left )
		lookUp = lookUp->left;

	
	//Left side of Parent child
	while( lookUp->parent != 0 )
	{
		if( lookUp->right && !lookUp->right->visited )
		{
			lookUp->parent;
			lookUp = lookUp->right;
			
			continue;
		}
		
		if( lookUp->left && !lookUp->left->visited )
		{
			lookUp = lookUp->left;
			continue;
		}
		
		lookUp->parent->value = lookUp->parent->Operator( lookUp->parent->left->value, lookUp->parent->right->value );
		
		printf("%d = %d %s %d\n", lookUp->parent->value, lookUp->parent->left->value, lookUp->parent->name, lookUp->parent->right->value);
		
		lookUp->parent->right->visited = 1;
		lookUp->parent->left->visited = 1;
		
		lookUp = lookUp->parent;
	}
	
	//////////////////////////////////////////////////////////////////
	
	printf("%d ", theRoot->value);
	
	kv_destroy( astCollection );
	
    return 0;
}

