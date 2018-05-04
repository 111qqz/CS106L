#include <iostream>
#include "SimpleGraph.h"
#include <vector>
#include <fstream>
#include <sstream>
#include <cmath>
#include <cstring>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::stringstream;
using std::getline;

const double PI = 3.14159265358979323;
const double kRepel=1E-4;
const double kAttract=1E-4;
const int MAXN=1E2+7;
void Welcome();
void Gao();
void init_nodes();
void Input();
std::pair<double,double>delta[MAXN];
inline double SqrSum(Node a,Node b);
void GaoRepelForce();
void GaoAttractForce();
void Move();
 SimpleGraph graph;
int NodeNum;
// Main method
int main() {
    Welcome();
    Input();
    Gao();
    return 0;
}

/* Prints a message to the console welcoming the user and
 * describing the program. */
void Welcome() {
    cout << "Welcome to CS106L GraphViz!" << endl;
    cout << "This program uses a force-directed graph layout algorithm" << endl;
    cout << "to render sleek, snazzy pictures of various graphs." << endl;
    cout << endl;

}
void init_nodes(){
    for ( int i = 0 ; i < NodeNum ; i++){
        double x=cos(2*PI*i/NodeNum);
        double y=sin(2*PI*i/NodeNum);
        //cout<<"init_nodes  xx:"<<x<<" yy:"<<y<<endl;
        graph.nodes.push_back({x,y});
    }

}
void Input(){
    cout<<"Please input a file name"<<endl;

    string filename;
    cin>>filename;
    //filename = "../res/"+ filename;
    cout<<"filename:"<<filename<<endl;
    ifstream in(filename);
    if (!in){ cout<<"open input file failed"<<endl;}
    else {cout<<"open input file success" << endl;}
    string str;
    stringstream stream;
    getline(in,str);
    stream.str(str);
    stream>>NodeNum;
    stream>>std::ws;
    //cout<<"nodeNum:"<<NodeNum<<endl;
    while (getline(in,str)){
        //cout<<"str:"<<str<<endl;
        stream.clear(); // attention!
        stream.str(str);
        //cout<<"stream:"<<stream.str()<<endl;

        std::size_t u,v; // two nodes of an edge.
        stream>>u>>v;
         //stream>>std::ws;
       // cout<<"u:"<<u<<"v:"<<v<<endl;
        graph.edges.push_back({u,v});
    }
    init_nodes();
    InitGraphVisualizer(graph);
    DrawGraph(graph);


}
inline double SqrSum(Node a,Node b){
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
// Note:RepelForce is between each pair of nodes, no matter they are connected by an edge or not.
void GaoRepelForce(){
    for ( int i = 0 ; i < NodeNum ; i++){
        for ( int j = i + 1 ; j < NodeNum ; j++){
            auto node1 = graph.nodes[i];
            auto node2 = graph.nodes[j];
            double RepelForce = kRepel/std::sqrt(SqrSum(node1,node2));
            double theta = std::atan2(node2.y-node1.y,node2.x-node1.x);
            delta[i].first-=RepelForce*cos(theta);
            delta[i].second-=RepelForce*sin(theta);
            delta[j].first+=RepelForce*cos(theta);
            delta[j].second+=RepelForce*sin(theta);
        }
    }
}
// Note:AttractForce is only between nodes connected by an edge.
void GaoAttractForce(){
    for ( auto &edge: graph.edges){
        auto node1 = graph.nodes[edge.start];
        auto node2 = graph.nodes[edge.end];
        double AttractForce = kAttract*(SqrSum(node1,node2));
        double theta=std::atan2(node2.y-node1.y,node2.x-node1.x);
        delta[edge.start].first+=AttractForce*cos(theta);
        delta[edge.start].second+=AttractForce*sin(theta);
        delta[edge.end].first-=AttractForce*cos(theta);
        delta[edge.end].second-=AttractForce*sin(theta);
    }
}
void Move(){
    for ( int i = 0 ; i < NodeNum ; i++){
        graph.nodes[i].x += delta[i].first;
        graph.nodes[i].y += delta[i].second;
    }

}
void Gao(){

   int iterTimes;
   cout<<"please input iter times"<<endl;
   cin>>iterTimes;
   for ( int i = 1 ; i <= iterTimes ; i++){
       memset(delta,0,sizeof(delta));
       GaoAttractForce();
       GaoRepelForce();
       Move();
       cout<<" running for "<<i<<" times"<<endl;
       DrawGraph(graph);
   }


}
