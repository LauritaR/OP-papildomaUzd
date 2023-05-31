#include"fun.cpp"


int main() {
    SetConsoleOutputCP(CP_UTF8);

    string failas=uzklausa();
   
    int eilesIndx=0;
    string eile;
    vector<string> urls;
    map<string,zodis> sarasas;
    stringstream buffer=getBuffer(failas);

    while(getline(buffer,eile))
    {
        string word;
        istringstream iss(eile);
        while(iss>>word)
        {
            if(url(word)){urls.push_back(word);}
            else{word=removeNonWord(word); addWord(word,sarasas,eilesIndx);}
        }
    eilesIndx++;
    }

    
    print(sarasas,eilesIndx,"rezultatas.txt",urls);
} 

