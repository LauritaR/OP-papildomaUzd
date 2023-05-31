#include"fun.h"

bool failasYra(const string& file)
{
    ifstream failas(file);
    return failas.good();
}

string uzklausa()
{
    string file;
    cout<<"Įveskite failo pavadinimą: "; 
    cin >> file;

    return file.empty()? "tekstas.txt":file;
}


void addWord(const string& w, map<string,zodis>& collection, int eilesIndx)
{
    if(w.empty()||w=="  "){return; }

    auto iterator=collection.find(w);
    if(iterator==collection.end()){collection.insert({w,zodis(eilesIndx)});}
    else{
        if(eilesIndx!=iterator->second.eilesIndx.back())
        {iterator->second.eilesIndx.push_back(eilesIndx);
        
        } iterator->second.cnt++;
    }
   
}


stringstream getBuffer(const string& filePath)
{
    ifstream failas;

    failas.open(filePath);
    if(!failas)
    {
        throw std::runtime_error("Failas: "+filePath+" negali būti atidarytas");
    }

    stringstream buffer;
    buffer<<failas.rdbuf();

    return buffer;
}

void saveBuffer(const string& filePath, stringstream& buffer)
{
    ofstream failas;
    failas.open(filePath);

    if(!failas)
    {
        throw std::runtime_error("Failas: "+filePath+" negali būti atidarytas");
    }

    failas<<buffer.str();
    failas.close();
}

int getDistance (int previous, int current)
{
    int prevNumDIgits=to_string(previous).length();
    int currentNumDigits=to_string(current).length();

    if(prevNumDIgits==currentNumDigits)
    {
        int diff=current-previous;
        return diff==0?0:diff+(diff*currentNumDigits)-1;
    }

    int sum=0;
    for(int i=currentNumDigits;i>prevNumDIgits;i--)
    {
        int base=pow(10,i-1);
        sum+=getDistance(base,current);
        sum+=(current==base)?i+1:i+2;
        current=base-1;
    }
        return sum + getDistance(previous,current);
}

void print(map<string, zodis>& collection, int eiliuSK, const string& filePath,const vector<string> &urls) {
    stringstream outputBuffer;
    outputBuffer << left << setw(15) << "žodis "<<right<<setw(10);
    for (int i = 0; i < eiliuSK; i++) {
        outputBuffer<< (i + 1) << " ";
    }
    outputBuffer << endl;

    outputBuffer << string(15 + eiliuSK * 4, '-') << endl;

    for (auto key : collection) {
        if (key.second.cnt > 1) {
            outputBuffer << left << setw(23) << key.first;
            for (int i = 0; i < key.second.eilesIndx.size(); i++) {
                int prevIndx = (i == 0) ? 0 : key.second.eilesIndx[i - 1] + 1;
                int lineIndx = key.second.eilesIndx[i] + 1;
                int dist = getDistance(prevIndx, lineIndx);
                outputBuffer << string(dist,' ') << "*";
            }
            outputBuffer << endl;
        }
    }

    outputBuffer<<"\nŽodžių pasikartojimas: \n";
    outputBuffer << left << setw(25) << "žodis" << "kiekis" << endl;
    outputBuffer << string(50, '-') << endl;

    for (auto key : collection) {
        if (key.second.cnt > 1) {
            outputBuffer << left << setw(25) << key.first << right<<key.second.cnt << endl;
        }
    }

    outputBuffer<<"\nURL\n";
    for(const string& url: urls)
    {
        outputBuffer<<url<<endl;
    }

    saveBuffer(filePath, outputBuffer);
}

void urls(vector<string>& urls, const string& filePath)
{
    stringstream buffer;
    for(string url: urls){buffer<<url<<endl;} saveBuffer(filePath,buffer);
}


bool url(const string& word){return(regex_match(word,regex("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&//=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&//=]*)")));}
string removeNonWord(const string& word){return regex_replace(word, regex("[-.%,?!/;:\"'()\\]\\[*0-9]"),"");}

string toLower(string& word)
{
    for_each(word.begin(),word.end(),[](char& c){c=::tolower(c);});
    return word;
} 