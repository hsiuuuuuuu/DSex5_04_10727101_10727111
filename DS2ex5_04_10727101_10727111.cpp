//第四組_10727101_陳則叡_10727111_王文琇// 
#include <cstdlib>
#include<stdio.h>
#include<iostream>
#include<fstream> 
#include<vector> 
#include <cmath>
#include <stdlib.h>
#include <algorithm>
#include<queue>
#include<string >
#include <string.h> // c_str
#include <cstdio>
#include <time.h>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
struct AdjListNode{
  string sid2 ;     
  float weight ;
  AdjListNode *next = NULL ;
};

struct StudentPair {
  char sid1[10] ;
  char sid2[10] ;
  float weight ;
};


typedef AdjListNode* ANode;

struct student{
  string sid1;	
  ANode head = NULL ;
  float influenceValue  = 0 ;
  bool testrun = false;  
  float weight ;
};

bool compare1(  student sid1, student sid2  ){
	if( sid1.influenceValue == sid2.influenceValue  )
	  return sid1.sid1 < sid2.sid1;
	else
	  return sid1.influenceValue > sid2.influenceValue;
}

bool compare2(  vector<student> sid1, vector<student> sid2  ){
	  return sid1.size() >= sid2.size() ;
}


bool compare3(  student sid1, student sid2  ) {
	if( sid1.influenceValue == sid2.influenceValue  )
	  return sid1.sid1 < sid2.sid1;
	else	
	  return sid1.influenceValue < sid2.influenceValue ;
}

bool compare4(  student sid1, student sid2  ){
	return sid1.sid1 < sid2.sid1;
}

class test{
public:
string fileNum, fileName ;
fstream inFile, outFile ;	
vector<student> adj;
vector<student> cnt;
vector<vector< student > > cc ;

int nodes = 0; 
string val1 ;
float n = 0.0;
void readFile() { // 讀檔 

  do{
    cout << "Input a real number in (0,1]:";
    
	cin >>val1; 
	n = atof(val1.c_str());
  } while(n < 0 || n > 1) ;
  cout << "Input a file number([0]Quit): " ;
  cin >> fileNum ;
  if( !fileNum.compare("0") ) {
    cout << endl ;
    return;
  } // if
  else {
    fileName = "pairs" + fileNum + ".bin" ;
    inFile.open(  fileName.c_str(), fstream::in ) ;
    adj.clear();
    cnt.clear();
    nodes = 0;
    if( inFile.is_open() ) {
        cout << endl ;
        inFile.close() ;
    } //if
    else {
        cout << "\n### " << fileName << " does not exist! ###\n\n" ;
    }// else
  } // else



  StudentPair oneSt ;
  int stNo = 0 ;

  inFile.open( fileName.c_str(), fstream::in | fstream::binary ) ;
  

  if( inFile.is_open() ) {
    inFile.seekg( 0, inFile.end ) ;     // 0~eof.
    stNo = inFile.tellg() / sizeof(oneSt) ;
    inFile.seekg( 0, inFile.beg ) ;
    
    float inweight ;
    for( int i = 0 ; i < stNo ; i++ ) {
      inFile.read( (char*)&oneSt, sizeof(oneSt) ) ;
      if( oneSt.weight <= n  )
        mission0( oneSt );
    }
  }


  writer(  adj, 0  )  ;
}
	
	
	
void mission0( StudentPair oneSt ){
	student sid, sid3; // 創檔用 收訊者、發訊者學號 
	string sid2 = oneSt.sid2; // 鍊結用 收訊者學號  
	sid.sid1 = oneSt.sid1;
	sid.weight = oneSt.weight ;
    createm0(  sid, sid2, oneSt.weight, 1 );   
	sid.sid1 = oneSt.sid2 ; 
	sid2 = oneSt.sid1 ;   
    createm0(  sid, sid2, oneSt.weight, 1 );

}// m0	


void linksid( string sid2, float  weight, ANode &temp ){ // 建檔用 鍊結學號 
	string temp1 = sid2;
	float temp2 = weight;
	if(  temp == NULL ){
		temp = new AdjListNode;
		temp->sid2 = sid2;
		temp->weight = weight;
		temp->next = NULL;
		nodes++;
	}// if
	else if(  temp->sid2 > sid2 ){
		sid2 = temp->sid2;
		weight = temp->weight;
		temp->sid2 = temp1;
		temp->weight = temp2;
		linksid( sid2, weight, temp->next );
	}// else if
	else
		linksid( sid2, weight, temp->next );
		
}// linksid



void createm0(  student sid, string sid2, float  weight, int times   ) { // 創檔ADJ 
	int i = 0;
	for(  i = 0; adj.size() > i; i++  ) {
		if( adj[i].sid1 ==  sid.sid1  ){
			if( sid.weight <= n )//加入收訊者學號 
			  linksid( sid2, weight,  adj.at(i).head);
			return;
	    }// if
		else if(  adj[i].sid1 > sid.sid1 ){
			if( sid.weight <= n  )//加入收訊者學號 
			  linksid( sid2, weight,  sid.head );				
			adj.insert( adj.begin()+i, sid  );
		
			return;			
		}// else
			
		
	}//for
	adj.push_back(sid);
	if( times == 1 )//加入收訊者學號 
		linksid( sid2, weight,  adj[i].head);
} //cm0

	
void reback(){
	for( int i = 0; adj.size() > i; i++ ){
      adj[i].influenceValue = 9999;
      adj[i].testrun = false;
    }// for
}// reback


void writer(  vector<student> test, int mission   ){ // 寫檔 
  if( mission == 0 )	
    fileName = "pairs" + fileNum + "_" + val1 + ".adj" ;
  
  outFile.open( fileName.c_str(), fstream::out ) ;

  if( outFile.is_open() ) {	
    outFile << "<<< There are " << test.size() << " IDs in total. >>>\n" ;
    for( int i = 0 ; i < test.size() ; i++ ) {
      if( mission == 0 )
        outFile << "[" << i+1 << "] " << test[i].sid1 << ": \n" ;
      else
        outFile << "[" << i+1 << "] " << test[i].sid1 << ": \n" ;
      ANode walk = test[i].head ;
      for( int j = 1 ; walk != NULL ; j++ ) {
        outFile << "\t("  << j << ") " << walk->sid2 ;
        if( mission == 0 ) {
        	outFile << ",\t"  << walk->weight ;
		}// if
          
        if( j % 10 == 0 ) {
          outFile << endl ;
        }//  if
        walk = walk->next ;
      }// for
      outFile << endl ;
    }// for
    
    if( mission == 0 )
      outFile << "<<< There are " << nodes << " nodes in total. >>>\n" ;
      
  }// if
  outFile.close() ;	
	
} // writer


void mission1() {
	nodes = 0;
    
	cnt.clear() ;
	cc.clear();
	if( adj.size()==0 ){
		cout << "\n### There is no graph and choose 0 first. ###\n\n" ;
		return;
	}// if
	

	for( int i = 0; adj.size() > i; i++ ){
	 if ( adj[i].head != NULL) {
	  
	  student sid;
	  sid.sid1 = adj[i].sid1 ;
	
	  
	  

	  
	  if ( adj[i].testrun == false ){
	  	

	  	createsid1( sid, adj[i].head,  n);
	  	sort( cnt.begin(), cnt.end(), compare1 );
	  	cc.push_back(cnt);
	  	cnt.clear() ;
	  }// if
    }
    else
      ;
	  
	
	}// for

	sort( cc.begin(), cc.end(), compare2 );

	writer1()  ;
    
		
}// m1

void createsid1(  student &sid, ANode head, float n){  

		findsidm1( head->sid2, sid, n) ;
		if ( head->next != NULL)
		  createsid1(  sid, head->next,n);
}// csid1
	
void findsidm1( string sid2, student &sid, float n ){ // 走訪主陣列
	for( int i = 0; adj.size() > i; i++ ){
      if(  adj[i].sid1 == sid2 ) {
      	if(  !adj[i].testrun  ){
      	  adj[i].testrun = true;
          cnt.push_back(adj[i]);
          
      	  createsid1(  sid, adj[i].head, n);    		
		}// if
      	return;
	  }// if
   }// for
}// fsid1	

void writer1(){ // 任務一寫檔 

  fileName = "pairs" + fileNum + "_" + val1 + ".cc" ;
  outFile.open( fileName.c_str(), fstream::out ) ;
  int size1 = cc.size();  
    if( outFile.is_open() ) { 
    outFile << "<<< There are " << size1 << " connected components in total. >>>" ;
    for( int i = 0 ; i < size1 ; i++ ) {
     
      int size3 =  cc[i].size();
      outFile << endl << "{" << i+1 << " }" << " Connected Component: size =  "<< size3 << " \n" ;
      for(int j = 0 ; j < cc[i].size() ; j++){ 
        cout << cc[i][j].sid1 << " \n";
        if( (j+1) % 10 == 0 ) {
          outFile << endl ;
        }// if
        outFile << "[" << j+1 << "] " << cc[i][j].sid1 << "   " ;
      
       } // for
      }// for   
  
    } // if
  outFile.close() ; 
} // writer1

void mission2 (){
	ANode walk = NULL;
	string str;
	student sid;
	float comparess = 0.0, comparess2 = 0.0;
    for ( int i = 0 ; adj.size() > i ; i++ ) {
      if ( (i+1)%8 == 0 )
	   cout << adj[i].sid1 << "\n";
	  else
	   cout << adj[i].sid1 << "  ";
	}
	cout << "\nInput student id : " ;
	cin >> str ;
	int j = 0 ;
	int i ;
	for ( i = 0 ; adj.size() > i  ; i++ ) {
	  if ( str == adj[i].sid1 )
		break;	
	}
	if( adj.size() == i ){
	  cout << "no student id " << endl;
	  return;
	}
    cnt.clear();
	reback();
	createsid1( sid, adj[i].head,  n);
	sort( cnt.begin(), cnt.end(), compare4 );    	
	findsid2( str,  0, 0 );
	walk = adj[i].head ;
	while( walk != NULL  ) {
	  findsid2( walk->sid2,  0, walk->weight );	
	  walk = walk->next;	
	}
	sort( cnt.begin(), cnt.end(), compare3 );	
	 i =1;
	while( cnt.size() > i  ) {
	  walk = cnt[i].head ;		
	  comparess2 = cnt[i].influenceValue;
	  while( walk != NULL  ){
	  	comparess = comparess2 + walk->weight;
	  	sort( cnt.begin(), cnt.end(), compare4 );
	    findsid2( walk->sid2,  0, comparess );	
	    walk = walk->next;	
	  }		
	  sort( cnt.begin(), cnt.end(), compare3 );
	  i++;
	}
	
	writer2();
}

void findsid2( string sid2,  int head, float weight ){ // 走訪 
    int high = cnt.size(), low = 0, mid = 0;
    AdjListNode sid3;
    while(  high >= low ){
      mid = (low + high)/2;	
      if(  cnt[mid].sid1 == sid2  ) {
        if( cnt[mid].influenceValue > weight ){
          cnt[mid].influenceValue = weight;
		}
        return;
	  }    	
      else if( cnt[mid].sid1 < sid2  )
      	low = mid+1;
      else
	    high = mid-1;	
	}

    return ;
}	

void writer2(){ // 任務二寫檔 
	fileName = "pairs" + fileNum + "_" + val1 + ".ds" ;
    outFile.open( fileName.c_str(), fstream::out ) ;
    int sizeintput = 0;
    int size1 = cnt.size();  
    if( outFile.is_open() ) {	
      outFile << " origin :  " << cnt[0].sid1 << endl;
      for( int i = 1 ; i < size1 ; i++ ) {
        outFile   << "(" << i << " )  " << cnt[i].sid1 << ", " << cnt[i].influenceValue << "\t" ;
        if( (i+1) % 10 == 0 ) {
          outFile << endl ;
        }
       
		    
       } 
    }   
 	outFile.close() ;	
}
 
 
}; // test


int main(){
    int command = 0 ;
    int num = 0 ;
    char input[500] ;
    test user ;
    cout << endl << "******* Graph data applications ******" ;
    cout << endl << "* [Any other key: QUIT]              *" ; 
    cout << endl << "* 0. Create adjacency lists          *" ;              
    cout << endl << "* 1. Build connected components      *" ;
    cout << endl << "* 2. Find shortest paths by Dijkstra *" ;     
    cout << endl << "**************************************" ;
    cout << endl << "Input a command(0, 1, 2): [Any other key: QUIT] :";
    cin >> command ;
    while ( command != 0 || command != 1 || command != 2 ){
      if ( command == 0 ){
      	user.readFile();
	  }
      else if ( command == 1 ){
        user.mission1() ;
      } // if
      else if ( command == 2 ){
        user.mission2() ;
      } // else if
      else {
        cout << endl << "Command does not exist!" ;
      } // else*/


    cout << endl << "******* Graph data applications ******" ;
    cout << endl << "* [Any other key: QUIT]              *" ; 
    cout << endl << "* 0. Create adjacency lists          *" ;              
    cout << endl << "* 1. Build connected components      *" ;
    cout << endl << "* 2. Find shortest paths by Dijkstra *" ;     
    cout << endl << "**************************************" ;
    cout << endl << "Input a command(0, 1, 2): [Any other key: QUIT] :";
    cin >> command ;
    strcpy(input,"");
    } // while

return 0 ;
	
} // main()
