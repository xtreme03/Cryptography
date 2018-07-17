//program to implement conventional cryptographic technique
#include<iostream>
#include<math.h>
#include<map>
#include<string>
#include<string.h>
using namespace std;
//class from which specific cipher classes will inherit
class master
{	protected:
	string plaintxt,ctxt;
	int choice;
	map <char,int> alpha;
	char letters[26];
	public:
		//function to create the map of alphabets and their postions 
		master()
		{
			char ch='a';
			for(int i=0;i<26;i++,ch++)
			{
			letters[i]=ch;
			alpha[ch]=i;
			}
		}
void removeSpace(string str)
{
string strr;

for(int i=0;i<str.length();i++)
{
	if(str.at(i)=='\x20')
	continue;
	else
	strr.push_back(str.at(i));
}

if(choice==1)
plaintxt=strr;
else if(choice==2)
ctxt=strr;
}
//convert upper case to lower case
void convert(string &str)
{
	
	
	for (int i=0;i<str.length();i++)
	{
		if(str.at(i)>=65&&str.at(i)<=90)
		str.at(i)+=32;
		else 
		continue;
	}
	
	
}
	
};
//class to implement shift cipher
class shift:public master
{
	
	int key,len;
	
	public:
		shift(int _op)
		{
			choice=_op;
			if(choice==1)
			{
			cout<<"ENTER PLAINTEXT";
			cin.ignore();
			getline(cin,plaintxt);
			removeSpace(plaintxt);
			convert(plaintxt);
			}
			else 
			
			{
			cout<<"ENTER CIPHER TEXT";
			cin.ignore();
			getline(cin,ctxt);
				removeSpace(ctxt);
			convert(ctxt);
			}
		
			cout<<"ENTER KEY";
			cin>>key;
			if(choice==1)
			encrypt();
			else 
			decrypt();
			
		}
		void encrypt()
		{
			char p,q,c;
			for(int i=0;i<plaintxt.length();i++)
			{
												//taking one alphabet at a time 
				c=plaintxt.at(i); 
				int w=(alpha[c]+key)%26;	//getting the integer from map emplyoing required mechanism 
				q=letters[w];				//converting back to alphabets
				ctxt.push_back(q);
				
				
			}
			
		cout<<ctxt;
		}
		void decrypt()
		{
		char c;	
		//reverse of encryption		
		for(int i=0;i<ctxt.length();i++)
		{c=ctxt.at(i);
		int w=(alpha[c]-key)%26;
	if(w<0)
		w=w+26;
		plaintxt.push_back(letters[w]);
		}
	cout<<plaintxt;
			
		}
		
};
class vigener:public master
{

	string key,ckey;
	int klen;
	public:
		
	
	vigener(int _op)
	
		{
			choice=_op;
			if(choice==1)
			{
			cout<<"ENTER PLAINTEXT";
			cin.ignore();
			getline(cin,plaintxt);
			removeSpace(plaintxt);
			convert(plaintxt);
			}
				else if (choice==2)
				{
				cout<<"ENTER CHIPER TEXT";
				cin.ignore();
				getline(cin,ctxt);
				removeSpace(ctxt);
				convert(ctxt);
				}
				
			
			
			cout<<"ENTER KEY";
			cin>>key;
			keydtr(key);
			if(choice==1)
			encrypt();
			else if (choice==2)
			decrypt();
			
		}
		//convetrs key to corresponding integers
		void keydtr(string str)
		{
		char p;
		int n;
		klen=str.length();
		for(int i=0;i<klen;i++)
		{
			p=str.at(i);
			n=alpha[p];
			ckey.push_back(n);
			
		}	
		}
		//Encryption function
		void encrypt()
		{   int j=0,i;
		
			for( i=0;i<plaintxt.length();i++)
			{
				char p=plaintxt.at(i);
				int k=((alpha[p]+ckey[j])%26);
				ctxt.push_back(letters[k]);
				if(j<ckey.length()-1)
				j++;
				else 
				j=0;
				
			}
			cout<<ctxt;
			
		}
		//decryption function
		void decrypt()
		{
			 int j=0,i;
		
			for( i=0;i<ctxt.length();i++)
			{
				char p=ctxt.at(i);
				int k=((alpha[p]-ckey[j])%26);
				if(k<0)
				k=k+26;
				plaintxt.push_back(letters[k]);
				if(j<ckey.length()-1)
				j++;
				else 
				j=0;
		
			}
			cout<<plaintxt;
			
		}
	
};
//railfence
class railfence:public master
{
	string str,d,e;
	int k;
	public:
		railfence()
		{
			cout<<"enter string";
			cin.ignore();
			getline(cin,str);
			removeSpace(str);
			convert(str);
			cout<<"key";
			cin>>k;
			
		}


string encryptRailFence(string text, int key)
{
    // create the matrix to cipher plain text
    // key = rows , length(text) = columns
    char rail[key][(text.length())];
 
    // filling the rail matrix to distinguish filled
    // spaces from blank ones
    for (int i=0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';
 
    // to find the direction
    bool dir_down = false;
    int row = 0, col = 0;
 
    for (int i=0; i < text.length(); i++)
    {
        // check the direction of flow
        // reverse the direction if we've just
        // filled the top or bottom rail
        if (row == 0 || row == key-1)
            dir_down = !dir_down;
 
        // fill the corresponding alphabet
        rail[row][col++] = text[i];
 
        // find the next row using direction flag
        dir_down?row++ : row--;
    }
 
    //now we can construct the cipher using the rail matrix
    string result;
    for (int i=0; i < key; i++)
        for (int j=0; j < text.length(); j++)
            if (rail[i][j]!='\n')
                result.push_back(rail[i][j]);
 
    return result;
}
 
// This function receives cipher-text and key
// and returns the original text after decryption
string decryptRailFence(string cipher, int key)
{
    // create the matrix to cipher plain text
    // key = rows , length(text) = columns
    char rail[key][cipher.length()];
 
    // filling the rail matrix to distinguish filled
    // spaces from blank ones
    for (int i=0; i < key; i++)
        for (int j=0; j < cipher.length(); j++)
            rail[i][j] = '\n';
 
    // to find the direction
    bool dir_down;
 
    int row = 0, col = 0;
 
    // mark the places with '*'
    for (int i=0; i < cipher.length(); i++)
    {
        // check the direction of flow
        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;
 
        // place the marker
        rail[row][col++] = '*';
 
        // find the next row using direction flag
        dir_down?row++ : row--;
    }
 
    // now we can construct the fill the rail matrix
    int index = 0;
    for (int i=0; i<key; i++)
        for (int j=0; j<cipher.length(); j++)
            if (rail[i][j] == '*' && index<cipher.length())
                rail[i][j] = cipher[index++];
 
 
    // now read the matrix in zig-zag manner to construct
    // the resultant text
    string result;
 
    row = 0, col = 0;
    for (int i=0; i< cipher.length(); i++)
    {
        // check the direction of flow
        if (row == 0)
            dir_down = true;
        if (row == key-1)
            dir_down = false;
 
        // place the marker
        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);
 
        // find the next row using direction flag
        dir_down?row++: row--;
    }
    
    return result;
}
 //function to call the encrypt and decrypt functions and display them
 void display(int x)
 {
 	
 	if(x==1)
 {
 
 	e=encryptRailFence(str,k);
 	cout<<e;
 }
	 else if(x==2)
 {
	 	d=decryptRailFence(str,k);
 		cout<<d;
	 }
	 else 
 	cout<<"WRONG ENTRY";
 }
};
//affine cipher
class affine:public master
{

int k,e;

public:
affine(int _op)
{ choice=_op;
 	if(choice==1)
	{
cout<<"ENTER PLAINTEXT";
cin.ignore();
getline(cin,plaintxt);
removeSpace(plaintxt);
convert(plaintxt);

}
else
{
	cout<<"ENTER CIPHERTEXT";
	cin.ignore();
getline(cin,ctxt);
removeSpace(ctxt);
convert(ctxt);

}
	
label:
cout<<"ENTER KEY";
cin>>k>>e;
int y=gcd(k,26);
while(y!=1)
{
	goto label;
	cout<<"ENTER PROPER KEY THE GCD OF THE FIRST NUMBER AND 26 SHOULD BE ONE";
}
if(choice==1)

encrypt();
else if(choice ==2)
decrypt();
else 
cout<<"wrong entry"	;
}

 void decrypt()
{
int inverse, x ;
 inverse=modInverse(k, 26); //to get inverse modulo
 
 for( int i=0;i<ctxt.length();i++ )
 {
 	x=((inverse*(alpha[ctxt.at(i)]-e))%26);

 	plaintxt.push_back(letters[x]);
 	
 }
 cout<<plaintxt;
 
 
}
// Returns modulo inverse of a with respect to m using
// extended Euclid Algorithm
// Assumption: a and m are coprimes, i.e., gcd(a, m) = 1
int modInverse(int a, int m)
{
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
 
    if (m == 1)
      return 0;
 
    while (a > 1)
    {
        // q is quotient
        q = a / m;
  
        t = m;
 
        // m is remainder now, process same as
        // Euclid's algo
        m = a % m, a = t;
 
        t = x0;
 
        x0 = x1 - q * x0;
 
        x1 = t;
    }
 
    // Make x1 positive
    if (x1 < 0)
       x1 += m0;
 
    return x1;
}
int gcd(int n1, int n2)
{
    if (n2 != 0)
       return gcd(n2, n1 % n2);
    else 
       return n1;
}
void encrypt()
{
int w;
	for(int i=0;i<plaintxt.length();i++)
	{
		w=((alpha[plaintxt.at(i)]*k+e)%26);
		ctxt.push_back(letters[w]);
	}
	cout<<ctxt;
}
};
class playfair
{
string _txt; char _m[5][5];	
	
public:
    playfair( string k, string t, bool ij, bool e )
    {
	createMatrix( k, ij );
	 getTextReady( t, ij, e );
	if( e ) encrypt( 1 );
	 else encrypt( -1 );
	display();
    }
 
    void encrypt( int dir )
    {
	int a, b, c, d; string ntxt;
	for( string::const_iterator ti = _txt.begin(); ti != _txt.end(); ti++ )
	{
	    if( getCharPos( *ti++, a, b ) )
		if( getCharPos( *ti, c, d ) )
		{
		    if( a == c )     { ntxt += getChar( a, b + dir ); ntxt += getChar( c, d + dir ); }
		    else if( b == d ){ ntxt += getChar( a + dir, b ); ntxt += getChar( c + dir, d ); }
		    else             { ntxt += getChar( c, b ); ntxt += getChar( a, d ); }
		}
	}
	_txt = ntxt;
    }
 
    void display()
    {
	cout << "\n\n OUTPUT:\n=========" << endl;
	string::iterator si = _txt.begin(); int cnt = 0;
	while( si != _txt.end() )
	{
	    cout << *si; si++; cout << *si << " "; si++;
	    if( ++cnt >= 26 ) cout << endl, cnt = 0;
	}
	cout << endl << endl;
    }
 
    char getChar( int a, int b )
    {
	return _m[ (b + 5) % 5 ][ (a + 5) % 5 ];
    }
 
    bool getCharPos( char l, int &a, int &b )
    {
	for( int y = 0; y < 5; y++ )
	    for( int x = 0; x < 5; x++ )
		if( _m[y][x] == l )
		{ a = x; b = y; return true; }
 
	return false;
    }
 
    void getTextReady( string t, bool ij, bool e )
    {
	for( string::iterator si = t.begin(); si != t.end(); si++ )
	{
	    *si = toupper( *si ); if( *si < 65 || *si > 90 ) continue;
	    if( *si == 'J' && ij ) *si = 'I';
	    else if( *si == 'Q' && !ij ) continue;
	    _txt += *si;
	}
	if( e )
	{
	    string ntxt = ""; size_t len = _txt.length();
	    for( size_t x = 0; x < len; x += 2 )
	    {
		ntxt += _txt[x];
		if( x + 1 < len )
		{
		    if( _txt[x] == _txt[x + 1] ) ntxt += 'X';
		    ntxt += _txt[x + 1];
		}
	    }
	    _txt = ntxt;
	}
	if( _txt.length() & 1 ) _txt += 'X';
    }
 
    void createMatrix( string k, bool ij )
    {
	if( k.length() < 1 ) k = "KEYWORD"; 
	k += "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; string nk = "";
	for( string::iterator si = k.begin(); si != k.end(); si++ )
	{
	    *si = toupper( *si ); if( *si < 65 || *si > 90 ) continue;
	    if( ( *si == 'J' && ij ) || ( *si == 'Q' && !ij ) )continue;
	    if( nk.find( *si ) == -1 ) nk += *si;
	}
	copy( nk.begin(), nk.end(), &_m[0][0] );
    }
 
    
};
#include<iostream>
#include<math.h>
#include<map>
#include<string>
#include<string.h>
using namespace std;
class hill:public master
{
	string key;
	float q;
	int choice,No;
	map<char,int> hil;
		char letters[26];
	public:
	hill(int _op)
	{
		choice =_op;
		char ch='a';
		if(choice==1)
		{
		
		cout<<"ENTER PLAIN TEXT";
		cin.ignore();
		getline(cin,plaintxt);
		removeSpace(plaintxt);
		convert(plaintxt);
	}
		else if(choice==2)
		{
		
		cout<<"ENTER CIPHER TEXT";
	cin.ignore();
		getline(cin,ctxt);
		removeSpace(ctxt);
		convert(ctxt);
	}
		cout<<"ENTER KEY";
		cin>>key;
			for(int i=0;i<26;i++,ch++)
			{
			letters[i]=ch;
			hil[ch]=i;
			}
			keyencrypt();
		
	}

	void keyencrypt()
	{
		char c='x';
		int k=key.length();
		while (k>0)				//to make the key a square no
		{
	q=sqrt(k);
	if(q-(int)q!=0)
	{
	k++;
	key.push_back(c);
	}
	else
	{
	break;
	}
	}
	while(true)
	{
		if(plaintxt.length()%(int)q==0)
		break;
		else 
		plaintxt.push_back(c);
		
	}
	
	}
	
	void encrypt()
	{	int m=0;
	No=(int)q;
		char c;
		int karry[(int)q][(int)q];//array for key
		int parry[(int)q][1];
		for(int i=0;i<q;i++)
		for(int j=0;j<q;j++)
		{
		c=key.at(m);
		karry[i][j]=hil[c];
		}
		char txt[(int)q][1];
		for(int cnt=0;cnt<plaintxt.length();cnt++)
		{
		
		for(int i=0;i<q;i++)
		for(int j=0;j<1;j++)
		{
			parry[i][j]=hil[plaintxt.at(m)];
			
			if(q==m)
			{
				
			for(int i=0;i<q;i++)
			for(int j=0;j<1;j++)
			for(int k = 0; k < q; ++k)
            {
                txt[i][j] += karry[i][k] * parry[k][j];
                ctxt.push_back(letters[((txt[i][j])%26)]);
            }
            m++;
			}
			else if(m>plaintxt.length())
			break;
			else 
			m++;
		}
	}
	}
	
/*	void decrypt()
	{int m=0,adj[No][No];
	char c;
		int karry[(int)q][(int)q];//array for key
		for(int i=0;i<q;i++)
		for(int j=0;j<q;j++)
		{
		c=key.at(m);
		karry[i][j]=hil[c];
		}
		adjoint(No,karry);
			
}
	

	void adjoint(int N,int *ptr)
{ 
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }
 
    // temp is used to store cofactors of A[][]
    int sign = 1, temp[N][N];
 
    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, N);
 
            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;
 
            // Interchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}*/

		
		
		void display()
		{
			cout<<ctxt;
		}
		
	};
	//substitution cipher
class substitution:public master
{
		
	int key,len;
	map <char,int> subs;
	char letters[26];

	public:
		substitution(int choice)
		{
			char ch='a',chr='z';
			for(int i=0;i<26;i++,ch++,chr--)
			{
			letters[i]=chr;
			subs[ch]=i;
			
			}
			if(choice==1)
			{
			cout<<"ENTER PLAINTEXT";
			
				cin.ignore();
		getline(cin,plaintxt);
		removeSpace(plaintxt);
		convert(plaintxt);
			encrypt();

			}
			else if(choice==2)
			
			{
			cout<<"ENTER CIPHER TEXT";
			cin.ignore();
		getline(cin,plaintxt);
		removeSpace(plaintxt);
		convert(plaintxt);
			decrypt();
			}
		
		}
		
			void encrypt()
			{	
			char c;
			int j;
				for(int i=0;i<plaintxt.length();i++)
				{
					c=plaintxt.at(i);
					
					j=subs[c];
					
				
					ctxt.push_back(letters[j]);
					
				}
			
			cout<<ctxt;	
			}
	void decrypt()
	{	
	char c;
			int j;
				for(int i=0;i<ctxt.length();i++)
				{
					c=ctxt.at(i);
					
					j=subs[c];
					
				
					plaintxt.push_back(letters[j]);
					
				}
				cout<<plaintxt;
		
	}
	};


int encryptionsystem()
{	int n;
	cout<<"1.SHIFT CIPHER"<<endl<<"2.VIGENERE CIPHER"<<endl<<"3.RAILFENCE CIPHER"<<endl<<"4.AFFINE CIPHER"<<endl;
	cout<<"5.PLAYFAIR CIPHER"<<endl<<"6.HILL CIPHER"<<endl<<"7.SUBSTITUTION CIPHER"<<endl;
	cin>>n;
	return n;
}

int main()
{
int option,k;
char ans;
do{

k=encryptionsystem();
cout<<"1.ENCRYPT"<<endl<<"2.DECRYPT"<<endl;
cin>>option;
if(k==1)
shift ob1(option);
else if(k==2)
vigener ob1(option);
else if(k==3)
{
railfence ob1;
ob1.display(option);
}
else if(k==4)
affine ob1(option);
else if(k==5)
{
	 string key, i, txt; bool ij, e;
    if(option==1)
	i='e' ;
	e = ( i[0] == 'e' || i[0] == 'E' );
    cout << "Enter a en/decryption key: "; 
    cin.ignore();
	getline( cin, key ); 
    cout << "I <-> J (Y/N): "; 
	getline( cin, i );
	 ij = ( i[0] == 'y' || i[0] == 'Y' );
    cout << "Enter the text: "; 
	getline( cin, txt ); 
    playfair pf( key, txt, ij, e ); 
	return system( "pause" );
}
else if(k==6)
{
	hill ob1(option);
}
else if(k==7)
substitution ob1(option);
cout<<endl<<"Do you want to continue(Y/N)";
cin>>ans;
}while(ans=='y'||ans=='Y');
return 0;
}
