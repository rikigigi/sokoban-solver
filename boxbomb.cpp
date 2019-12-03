#include "boxbomb.h"
#include <stack>

std::vector<BoxBombMove> BoxBombFrame::get_possible_moves(){
    if (possible_moves_calculated)
        return possible_moves;
    possible_moves.clear();
    std::stack<std::pair<ssize_t,ssize_t> > to_check;
    to_check.push(pos);
    aux.assign(lx*ly,false);
    aux[idx(pos)]=true;
    while (!to_check.empty()) {
        auto posc = to_check.top();
        to_check.pop();
        for (auto & delta : move_list ){
            std::pair<ssize_t,ssize_t> newpos{posc.first+delta.first,posc.second+delta.second};
            if (newpos.first>=0&& newpos.first<lx && newpos.second>=0 && newpos.second<ly){
                auto i=idx(newpos.first,newpos.second);
                if (is_free(i) && !aux[i]){
                    aux[i]=true;
                    to_check.push(newpos);
                } else if (!is_free(i)) {
                    //check if a move is possible
                    if (boxes[i] && !walls[i]) {
                        //check the next cell
                        std::pair<ssize_t,ssize_t> boxmovepos{newpos.first+delta.first, newpos.second+delta.second};
                        if (is_free(boxmovepos)) {
                            //this is a possible move
                            possible_moves.push_back({newpos,boxmovepos});
                        }
                    }
                }
            }
        }

    }
    possible_moves_calculated=true;
    return possible_moves;
}

std::vector<BoxBombFrame> BoxBombFrame::generate_possible_frames(){
    std::vector<BoxBombFrame> res;
    auto moves=get_possible_moves();
    for (auto & m : moves) {
        res.push_back(BoxBombFrame(*this));
        res.back().apply_move(m);
    }
    return res;
}

std::vector<BoxBombFrame> BoxBombFrame::get_frames(const BoxBombFrame & initial)const {
    std::vector<BoxBombFrame> res{initial};
    for (auto & m : history) {
        res.push_back(res.back());
        res.back().apply_move(m);
    }
    return res;
}

void BoxBombFrame::print(std::ostream & out) const {
    for (size_t y=0;y<ly;++y){
        for (size_t x=0;x<lx;++x){
            auto i = idx(x,y);
            if (walls[i]) {
                out << "# ";
            } else if (idx(pos)==i) {
                if (bombs[i]) {
                    out  <<"X ";
                } else {
                    out << "% ";
                }
            } else if (boxes[i]) {
                if (bombs[i]) {
                    out << "O ";
                } else {
                    out << "o ";
                }
            } else if (bombs[i]) {
                out << "x ";
            } else {
                out << "  ";
            }
        }
        out << std::endl;
    }
}

void BoxBombFrame::read(std::istream & in) {
    for (size_t y=0;y<ly;++y){
        for (size_t x=0;x<lx;++x){
            auto i = idx(x,y);
            bool t1,t2,t3;
            in >> t1 >> t2 >> t3;
            walls[i]=t1; bombs[i]=t2; boxes[i]=t3;
        }
    }
    in >> pos.first >> pos.second;
    invalidate();
    get_possible_moves();
}
