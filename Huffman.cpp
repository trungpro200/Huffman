#include<iostream>
#include<vector>
#include<map>
#include<stdlib.h>

using namespace std;

class Node{
public:
    char data = '\0';
    double p;
    Node* big = nullptr;
    Node* small = nullptr;

    Node operator+ (Node other){
        // Create a new node for merging
        Node res;
        res.p = this->p + other.p;

        //Init the leaves
        res.big = new Node;
        res.small = new Node;

        //Assign the values
        *res.big = *this;
        *res.small = other;

        return res;
    };
};

class Huffman
{
private:
    /* data */
    map<char,float> freq;
    vector<char> keys;
    vector<float> ps;    
    void swapNodes(Node&a, Node&b){
        Node c = a;
        a = b;
        b = c;
    }

public:
vector<Node> nodes;

    Huffman(map<char,double> f){
        buildNodes(f);
        // linkNodes();
    };

    void buildNodes(map<char,double> f){
        for (auto& pairs : f){
            Node curr;
            curr.data = pairs.first;
            curr.p = pairs.second;

            nodes.push_back(curr);
        }

        sortNodes();
    };

    void sortNodes(){
        for (int i = 0; i<nodes.size(); i++){
            for (int j = i + 1; j < nodes.size(); j++){
                if (nodes[i].p<nodes[j].p){
                    swapNodes(nodes[i], nodes[j]);
                }
            }
        }
    };

    void linkNodes(){
        while (nodes.size() > 1)
        {
            step();
        }
    }

    void step(){
        nodes[nodes.size()-2] = nodes[nodes.size()-2] + nodes[nodes.size()-1];
        //Pull the last node up
        for (int i = 0; i<nodes.size()-1;i++){
            if (nodes[i].p<nodes[nodes.size()-2].p){
                nodes.insert(nodes.begin()+i,nodes[nodes.size()-2]);
                nodes.pop_back();
                break;
            }
        }

        nodes.pop_back();
    }

    void encode(Node root, string stack = ""){
        if (root.data){
            printf("%c: %s\n", root.data, stack.c_str());
        }

        if (root.big){
            encode(*root.big, stack+"1");
            // cout<<"Got big boy stack is now: "<<stack+"1\n";
        }

        if (root.small){
            encode(*root.small, stack+"0");
            // cout<<"Got my child stack is now: "<<stack+"0\n";
        }
    }
};




int main(){
    map<char,double> freq = {
        {'N', 4.0/15},
        {'G', 2.0/15},
        {'U', 2.0/15},
        {'Y', 1.0/15},
        {'E', 1.0/15},
        {'D', 1.0/15},
        {'I', 1.0/15},
        {'H', 1.0/15},
        {'T', 1.0/15},
        {'R', 1.0/15}
    };
    Huffman encoder(freq);
    encoder.step();
    encoder.linkNodes();
    encoder.encode(encoder.nodes[0]);
}