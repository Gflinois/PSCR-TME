
using namespace pr;
namespace tools {
    template < typename iterator>
    size_t count (iterator begin , iterator end) {
        
        size_t c = 0;
        while (begin != end) {
            c++;
            begin++;
        } ;
        return c ;
    }

    template < typename iterator , typename T>
    size_t count_if_equal (iterator begin, iterator end, const T& val) {
        size_t c = 0;
        while (begin != end) {
            if ((*begin)=(*end)){
                c++;
                begin++;}

        } ;
        return c ;        
    }

}





class iterator
{
    chainon *cur;
    iterator (Chainon *cur) : cur(cur) {}
    T& operator* () {return cur->data;} //T& pck on ne veut pas faire de copies ca couterais beaucoup trop chers
    iterator& operator ++(){cur = cur->next; return *this}
    bool opeator != (cast iterator &o)const {return cur!=o.cur;}
};



iterator begin () {return iterator(tete);}
iterator end () {return iterator(nullptr);}




class iterator{

};