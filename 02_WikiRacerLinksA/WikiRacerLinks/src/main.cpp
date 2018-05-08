#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_set>
#include <sstream>
using std::cout;            using std::endl;
using std::string;          using std::unordered_set;
using std::ifstream;         using std::ostringstream;
using std::cin;


string readFileIntoString(string  filename)
{
    ifstream ifile(filename);
    ostringstream buf;
    char ch;
    while(buf&&ifile.get(ch))
    buf.put(ch);
    return buf.str();
}

unordered_set<string> findWikiLinks(const string& page_html)
{
    unordered_set<string>res;
    string tar = "href=";
    auto it = std::search(page_html.begin(),page_html.end(),tar.begin(),tar.end());
    while (it!=page_html.end())
    {
        it+=6;

        string link;
        for (  ; it!=page_html.end() ; it++)
        {
            int ascii = int(*it);
            if (ascii==34) break; // char(")==34
            link+=*it;
        }

        string tmp = link.substr(0,6);

        if (tmp=="/wiki/"&&std::all_of(link.begin(),link.end(),[](char ch){ return ch!='#'&& ch!=':';}))
        {
            res.insert(link.substr(6));
        }
        it = std::search(it,page_html.end(),tar.begin(),tar.end());

    }
    return res;
}
int main() {
	
    /* TODO: Write code here! */
     string file;
     cin>>file;
     string html = readFileIntoString(file);
     auto it = findWikiLinks(html);
     //cout<<"length:"<<html<<endl;
     for ( auto x : it)
        cout<<x<<endl;
    /* Note if your file reading isn't working, please follow the
     * steps posted on the front page of the CS106L website. Essentially
     * go to the projects tab on the panel on the left, and in the run
     * section, uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */
}
