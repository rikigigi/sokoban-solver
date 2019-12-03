#ifndef BOXBOMB_H
#define BOXBOMB_H

#include <vector>
#include <array>
#include <utility>
#include <iostream>
#include "boxbombmove.h"

class BoxBombFrame
{
public:
    BoxBombFrame(const size_t  & lx,const size_t & ly):lx{lx},ly{ly},bombs(lx*ly,false),boxes(lx*ly,false),walls(lx*ly,false),aux(lx*ly,false),pos(0,0),move_list{ {{-1,0},{1,0},{0,-1},{0,1} }},generation{0},possible_moves_calculated{false} { }
    BoxBombFrame(const BoxBombFrame & r) = default;

    size_t idx(const size_t & x, const size_t & y) const noexcept{return lx*y+x;}
    size_t idx(const std::pair<size_t,size_t> & x) const noexcept{return idx(x.first,x.second);}
    void set_bomb(const size_t &x, const size_t & y) { bombs[idx(x,y)]=true;invalidate();}
    void set_wall(const size_t & x, const size_t & y) { walls[idx(x,y)]=true;invalidate();}
    void set_box(const size_t & x, const size_t & y) { boxes[idx(x,y)]=true;invalidate();}
    void set_pos(const size_t & x, const size_t & y) {pos.first=x;pos.second=y;invalidate();}
    bool is_free(const size_t & i)const{return !walls[i] && !boxes[i];}
    bool is_free(const size_t & x, const size_t & y) const{return is_free(idx(x,y));}
    bool is_free(const std::pair<size_t,size_t> & x) const {return is_free(x.first,x.second);}
    std::vector<BoxBombMove> get_possible_moves();
    void apply_move(const BoxBombMove & move) {
        auto i1=idx(move.pos);
        auto i2=idx(move.newpos);
        boxes[i1]=false;
        boxes[i2]=true;
        pos=move.pos;
        history.push_back(move);
        invalidate();
        get_possible_moves();
        ++generation;
    }
    std::vector<BoxBombFrame> generate_possible_frames();
    bool win() const {
        for (size_t i=0;i<lx*ly;++i){
            if (bombs[i] && !boxes[i]){
                return false;
            }
        }
        return true;
    }
    void print(std::ostream & out) const;
    void read(std::istream & in);
    bool operator == (const BoxBombFrame & rh) const {
        return boxes==rh.boxes && aux==rh.aux;
    }
    bool greater (const BoxBombFrame & rh) const {
        for (size_t i=0;i<lx*ly;++i) {
            if (boxes[i] && !rh.boxes[i]) {
                return false;
            } else if (!boxes[i] && rh.boxes[i]) {
                return true;
            }
            if (aux[i] && !rh.aux[i]) {
                return false;
            } else if (!aux[i] && rh.aux[i]) {
                return true;
            }
        }
        return false;
    }
    void invalidate(){possible_moves_calculated=false;}
    std::vector<BoxBombFrame> get_frames(const BoxBombFrame & initial)const ;
private:
    size_t lx,ly;
    std::vector<bool> bombs,boxes,walls,aux;
    std::pair<ssize_t,ssize_t> pos;
    const std::array<std::pair<ssize_t,ssize_t>,4> move_list;
    std::vector<BoxBombMove> history,possible_moves;
    bool possible_moves_calculated;
    int generation;
};

#endif // BOXBOMB_H
