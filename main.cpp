#include"fun.cpp"


int main() {
    SetConsoleOutputCP(CP_UTF8);

    string filePath=uzklausa();
   
    int eilesIndx=0;
    string eile;
    vector<string> urls;
    map<string,zodis> collection;
    stringstream buffer=getBuffer(filePath);

    while(getline(buffer,eile))
    {
        string word;
        istringstream iss(eile);
        while(iss>>word)
        {
            if(url(word)){urls.push_back(word);}
            else{word=removeNonWord(word); addWord(word,collection,eilesIndx);}
        }
    eilesIndx++;
    }

    
    print(collection,eilesIndx,"rezultatas.txt",urls);
} 

