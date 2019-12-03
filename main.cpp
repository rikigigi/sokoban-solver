#include <iostream>
#include <list>
#include <algorithm>
#include "boxbomb.h"

using namespace std;

int main()
{
    size_t lx,ly;
    std::cin >> lx >> ly;
    BoxBombFrame initial(lx,ly);
    initial.read(std::cin);
    initial.print(std::cout);
    std::cout<<endl;
    std::list<BoxBombFrame> list{initial};
    for (int cont=0;cont<100;cont++){
        std::list<BoxBombFrame>newlist;
        for (auto & f : list){
            auto next=f.generate_possible_frames();
            for (auto & n : next) {
                newlist.push_back(n);
                if (n.win()){
                    auto frames=n.get_frames(initial);
                    for (auto & f: frames) {
                        f.print(std::cout);
                        std::cout<<endl;
                    }
                    std::cout << endl<<"!!WIN"<<endl;
                    return 0;
                }
            }

        }
        list=std::move(newlist);
        list.sort([](const BoxBombFrame & a,const BoxBombFrame & b) {return a.greater(b);});
        //remove duplicates
        list.unique();
        std::cout<<"size    "<< list.size()<<" @ iteration " << cont << endl;
    }


}
