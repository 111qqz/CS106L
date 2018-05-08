
#include <iostream>
#include <unordered_set>
#include <set>
#include <vector>
#include <queue>
#include <unordered_map>
#include "wikiscraper.h"


using std::cout;            using std::endl;
using std::string;          using std::vector;
using std::priority_queue;  using std::unordered_map;
using std::unordered_set;
using std::set;




/*
 * This is the function you will be implementing. It takes
 * two string representing the names of a start_page and
 * end_page and is supposed to return a ladder, represented
 * as a vector<string>, of links that can be followed from
 * start_page to get to the end_page.
 *
 * For the purposes of this algorithm, the "name" of a Wikipedia
 * page is what shows at the end of the URL when you visit that page
 * in your web browser. For ex. the name of the Stanford University
 * Wikipedia page is "Stanford_University" since the URL that shows
 * in your browser when you visit this page is:
 *
 *       https://en.wikipedia.org/wiki/Stanford_University
 */
vector<string> findWikiLadder(const string& start_page, const string& end_page) {
    // TODO: Fill in the findWikiLinks method in wikiscraper.cpp,
    //       then write this  function as per the handout.
    //
    //                Best of luck!
    WikiScraper scraper;
    auto target_set = scraper.getLinkSet(end_page);
    cout<<"target_set_size="<<target_set.size()<<endl;

    auto cmpFn = [&](const vector<string>& a, const vector<string>& b) -> bool {
           string page1 = a.back();
           string page2 = b.back();
           auto page1_set = scraper.getLinkSet(page1);
           auto page2_set = scraper.getLinkSet(page2);
           vector<string>v_inter1,v_inter2;
           std::set_intersection(page1_set.begin(),page1_set.end(),target_set.begin(),
                                  target_set.end(),std::back_inserter(v_inter1));
           std::set_intersection(page2_set.begin(),page2_set.end(),target_set.begin(),
                                  target_set.end(),std::back_inserter(v_inter2));
           int siz1 = v_inter1.size();
           int siz2 = v_inter2.size();
           if (siz1>0||siz2>0)
           cout<<page1<<" "<<siz1<<" "<<page2<<" "<<siz2<<endl;
           return  v_inter1.size() < v_inter2.size();

       };
    set<string>all_set;
    priority_queue<vector<string>, vector<vector<string>>,
    decltype(cmpFn)> ladderQueue(cmpFn);
    vector<string>X;
    X.push_back(start_page);
    all_set.insert(start_page);
    ladderQueue.push(X);
    while (!ladderQueue.empty())
    {
        auto pre = ladderQueue.top();
        ladderQueue.pop();
        auto lst_page = pre.back();
        cout<<"lst_page:"<<lst_page<<endl;
        auto lst_page_set = scraper.getLinkSet(lst_page);
        //check
        if (lst_page_set.count(end_page)){
            cout<<"We have found a ladder"<<endl;
            pre.push_back(end_page);
            return pre;
        }
        for ( auto &neighboor : lst_page_set){
            //cout<<"neightboor:"<<neighboor<<endl;
            if (all_set.count(neighboor)) continue;
            all_set.insert(neighboor);
            vector<string>tmp_vec(pre);
            tmp_vec.push_back(neighboor);
            ladderQueue.push(tmp_vec);
            // if we have found end page,we don't have to continue.
            if (neighboor==end_page) break;
        }


    }

    return {};
}



int main() {
    // this code is really slow due to some network reason.
    // As you know,people in china cannot visit wiki_page or only at a very low speed.
    // I think the code is good,but cannot get result in less than 60s.


    //auto ladder = findWikiLadder("Lion","Barack_Obama");
    //auto ladder = findWikiLadder("Hulunbuir_Hailar_Airport", "Anqing");
    auto ladder = findWikiLadder("Milkshake", "Gene");
    cout << endl;

    if(ladder.empty()) {
        cout << "No ladder found!" << endl;
    } else {
        cout << "Ladder found:" << endl;
        cout << "\t";
        for ( auto x : ladder){
            cout<<x<<",";
        }
        // Print the ladder here!
    }

    return 0;
}




