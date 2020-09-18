#include <bits/stdc++.h>

using namespace std;

const int MAX = 26;

struct trie{

    struct trie* chd[MAX] = {};
    int freq;
    bool flag;

};

void insert_trie(struct trie * tree,char * wd){
    
    struct trie * curr=tree;// curr
    
    while(*wd!='\0'){
        if(curr->chd[*wd-'a']==NULL){
            curr->chd[*wd-'a']= (struct trie *) calloc(1, sizeof(struct trie));
        }

        curr=curr->chd[*wd-'a'];
        ++wd;
    }
    curr->flag=true;
}

struct trie* search_trie(struct trie* curr,char* wd){

    while(*wd!='\0'){
        if(curr->chd[*wd-'a']!=NULL){
            curr=curr->chd[*wd-'a'];
            ++wd;
        }
        else
            break;
    }

    if(*wd=='\0')
        return curr;
    else
        return NULL;
}

void autocomplete(struct trie* tree, vector<char> wd, char* prefix){
    
    bool nochild=true;
    if(tree->flag && wd.size()!=0){// if wd.size() is not kept here , it gonna print the prefix so keep this check
    // first print what is given as prefix
        cout<<prefix;// now after this print the things uu got in vector wd
        for(int i=0;i<wd.size();i++){
            cout<<wd[i];
        }
        cout<<endl;
    }

    for(int i=0;i<MAX;i++){
        if(tree->chd[i]!=nullptr){
       // nochild=false;// it has a child
        wd.push_back(i+'a');
        autocomplete(tree->chd[i],wd,prefix);
        wd.pop_back();
        }
    }
    wd.pop_back();
}


int main(){
   
    struct trie * tree = new trie();
    char filename[100];
    ifstream bad;
    printf("Name of WordList : ");
    cin.getline(filename, 100);
    bad.open(filename);
    if(!bad.is_open()){
        exit(EXIT_FAILURE);
    }
    char wd[50];
    bad >> wd;
    while(bad.good()){
        insert_trie(tree,wd);   // creating trie
        bad >> wd;
    }

    int chc = 1;
    vector<char> ch;
   
    ch.clear();
    cout << "Enter Word to Search : ";
    cin >> wd;
    
    trie* temp = search_trie(tree,wd);
    
    if(temp == nullptr)
        cout << "NO Word with this prefix in WordList."<< "\n";
    else{
        cout << "Your word could be : \n";
        autocomplete(temp, ch, wd);
    }
   
    return 0;
}