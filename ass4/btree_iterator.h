#ifndef BTREE_ITERATOR_H
#define BTREE_ITERATOR_H

#include <iterator>

/**
 * You MUST implement the btree iterators as (an) external class(es) in this file.
 * Failure to do so will result in a total mark of 0 for this deliverable.
 **/

// iterator related interface stuff here; would be nice if you called your
// iterator class btree_iterator (and possibly const_btree_iterator)
template <typename T> class btree;
template <typename T> class btree_iterator;
template <typename T> class const_btree_iterator;




/*********************************************************************************************************************/
/************************************************ btree_iterator class ***********************************************/
/*********************************************************************************************************************/

template <typename T> class btree_iterator {
public:
    T& operator*() const;
    T* operator->() const { return & this->operator*(); }
    btree_iterator& operator++();
    btree_iterator& operator++(int);
    btree_iterator& operator--();
    btree_iterator& operator--(int);
    btree_iterator& operator=( const btree_iterator<T>& other );
    bool operator==( const btree_iterator<T>& other ) const;
    bool operator==( const const_btree_iterator<T>& other ) const;
    bool operator!=( const btree_iterator<T>& other ) const { return !operator==(other); }
    bool operator!=( const const_btree_iterator<T>& other ) const { return !operator==(other); }

    btree_iterator( typename btree<T>::Node* pointer= nullptr, size_t idx = 0, const btree<T> *btree = nullptr):
            _pointer(pointer), _idx(idx), _btree(btree) { }

private:
    /**
	 * helper functions
	 */
    void asc_up(const T& e);
    void asc_down();
    void desc_up(const T& e);
    void desc_down();

    typename btree<T>::Node* _pointer;
    size_t _idx;
    const btree<T>* _btree;
};



/********************************* Definition of the methods *********************************/

/******************************************* Overload operator: operator*() *******************************************/
template <typename T> T& btree_iterator<T>::operator*() const {
    return _pointer->_elem[_idx];
}


/****************** Overload operator: operator++() / operator(int) / operator--() / operator--(int) ******************/
// Note: tricky part for this iterator
template <typename T> btree_iterator<T>& btree_iterator<T>::operator++(){
    if( _pointer == nullptr ){
        _pointer = _btree->_head;
        _idx = 0;
    } else if( _btree._children[_idx+1] != nullptr ){
        // the pointed element have descendants after,
        // got down the tree to the left-most descendant node
        _pointee = _pointer->_children[_idx+1];
        idx_ = 0;
        asc_down();
    } else if( _idx < _pointer->_size-1 ){
        // point to the next element in current node;
        ++_idx;
    } else {
        // reaches the end of current node, will go up
        // to parent node.
        asc_up (operator *());
    }
    return *this;
}
template <typename T> btree_iterator<T>& btree_iterator<T>::operator++(int){
    btree_iterator ret = *this;
    operator++();
    return ret;
}


template <typename T> btree_iterator<T>& btree_iterator<T>::operator--() {
    if( _pointer == nullptr ){
        _pointer = _btree->_tail;
        _idx = _pointer->_size-1;
    } else if( _pointer->_children[_idx] != nullptr ){
        _pointer = _pointer->_children[_idx];
        desc_down();
    } else if( _idx > 0 ){
        --_idx;
    } else {
        desc_up( operator*() );
    }
    return *this;
}
template <typename T> btree_iterator<T>& btree_iterator<T>::operator--(int) {
    btree_iterator ret = *this;
    operator--();
    return ret;
}




template <typename T> btree_iterator& btree_iterator<T>::operator=( const btree_iterator<T>& other ){
    if( this == &other ){
        return *this;
    } else {
        this->_pointer = other._pointer;
        this->_btree = other._btree;
        this->_idx = other._idx;
        return *this;
    }
}


template <typename T> bool btree_iterator<T>::operator==( const btree_iterator<T>& other ) const{
    return (_pointer == other._pointer) && (_btree == other._btree) && (_idx == other._idx);
}
template <typename T> bool btree_iterator<T>::operator==( const const_btree_iterator<T>& other ) const{
    return (_pointer == other._pointer) && (_btree == other._btree) && (_idx == other._idx);
}


/************************** Helper methods: desc_down() / desc_up() / asc_down() / asc_up() **************************/
template <typename T> void btree_iterator<T>::desc_down() {
    _idx = _pointer->_size-1;
    if( _pointer->_children[_idx+1] != nullptr ){
        return;
    }
    _pointer = _pointer->_children[_idx+1];
    desc_down();
}
template <typename T> void btree_iterator<T>::desc_up( const T &value ) {
    if( _pointer->_parent == nullptr ){
        _pointer = nullptr;
        _idx = 0;
        return;
    } else {
        _pointer = _pointer->_parent;
        for(int i=_pointer->_size-1; i>-1; i--){
            if( _pointer->_elem[i] < value ){
                _idx = i;
                return;
            }
        }
        desc_up(value);
    }
}


template <typename T> void btree_iterator<T>::asc_down(){
    if( _pointer->_children.size() == 0 ){
        return;
    }
    _pointer = _pointer->_children[0];
    asc_down();
}
template <typename T> void btree_iterator<T>::asc_up( const T& value ){
    if( _pointer->_parent == nullptr ){
        // Already at the root node
        _pointer == nullptr;
        _idx = 0;
        return;
    } else {
        _pointer = _pointer->_parent;
        for( int i=0; i<_pointer->_size; i++ ){
            if( _pointer->_elem[i] > value ){
                _idx = i;
                return;
            }
        }
        asc_up(value);
    }
}







/*********************************************************************************************************************/
/********************************************* const_btree_iterator class ********************************************/
/*********************************************************************************************************************/

template <typename T> class const_btree_iterator {
public:
    T& operator*() const;
    T* operator->() const { return & this->operator*(); }
    btree_iterator& operator++();
    btree_iterator& operator--();
    btree_iterator& operator=( const btree_iterator<T>& other );
    bool operator==( const btree_iterator<T>& other ) const;
    bool operator==( const const_btree_iterator<T>& other ) const;
    bool operator!=( const btree_iterator<T>& other ) const { return !operator==(other); }
    bool operator!=( const const_btree_iterator<T>& other ) const { return !operator==(other); }

    const_btree_iterator( typename btree<T>::Node* pointer= nullptr, size_t idx = 0, const btree<T> *btree = nullptr):
            _pointer(pointer), _idx(idx), _btree(btree) { }
    const_btree_iterator( const btree_iterator<T>& rhs ):
            _pointer(rhs._pointer), _idx(rhs._idx), _btree(rhs._btree) { }

private:
    /**
	 * helper functions
	 */
    void asc_up(const T& e);
    void asc_down();
    void desc_up(const T& e);
    void desc_down();

    typename btree<T>::Node* _pointer;
    size_t _idx;
    const btree<T>* _btree;
};


/********************************* Definition of the methods *********************************/

/******************************************* Overload operator: operator*() *******************************************/
template <typename T> T& const_btree_iterator<T>::operator*() const {
    return _pointer->_elem[_idx];
}


/****************** Overload operator: operator++() / operator(int) / operator--() / operator--(int) ******************/
// Note: tricky part for this iterator
template <typename T> const_btree_iterator<T>& const_btree_iterator<T>::operator++(){
    if( _pointer == nullptr ){
        _pointer = _btree->_head;
        _idx = 0;
    } else if( _btree._children[_idx+1] != nullptr ){
        // the pointed element have descendants after,
        // got down the tree to the left-most descendant node
        _pointee = _pointer->_children[_idx+1];
        idx_ = 0;
        asc_down();
    } else if( _idx < _pointer->_size-1 ){
        // point to the next element in current node;
        ++_idx;
    } else {
        // reaches the end of current node, will go up
        // to parent node.
        asc_up (operator *());
    }
    return *this;
}
template <typename T> const_btree_iterator<T>& const_btree_iterator<T>::operator++(int){
    const_btree_iterator ret = *this;
    operator++();
    return ret;
}


template <typename T> const_btree_iterator<T>& const_btree_iterator<T>::operator--() {
    if( _pointer == nullptr ){
        _pointer = _btree->_tail;
        _idx = _pointer->_size-1;
    } else if( _pointer->_children[_idx] != nullptr ){
        _pointer = _pointer->_children[_idx];
        desc_down();
    } else if( _idx > 0 ){
        --_idx;
    } else {
        desc_up( operator*() );
    }
    return *this;
}
template <typename T> const_btree_iterator<T>& const_btree_iterator<T>::operator--(int) {
    const_btree_iterator ret = *this;
    operator--();
    return ret;
}




template <typename T> const_btree_iterator& const_btree_iterator<T>::operator=( const const_btree_iterator<T>& other ){
    if( this == &other ){
        return *this;
    } else {
        this->_pointer = other._pointer;
        this->_btree = other._btree;
        this->_idx = other._idx;
        return *this;
    }
}


template <typename T> bool const_btree_iterator<T>::operator==( const const_btree_iterator<T>& other ) const{
    return (_pointer == other._pointer) && (_btree == other._btree) && (_idx == other._idx);
}
template <typename T> bool const_btree_iterator<T>::operator==( const const_btree_iterator<T>& other ) const{
    return (_pointer == other._pointer) && (_btree == other._btree) && (_idx == other._idx);
}


/************************** Helper methods: desc_down() / desc_up() / asc_down() / asc_up() **************************/
template <typename T> void const_btree_iterator<T>::desc_down() {
    _idx = _pointer->_size-1;
    if( _pointer->_children[_idx+1] != nullptr ){
        return;
    }
    _pointer = _pointer->_children[_idx+1];
    desc_down();
}
template <typename T> void const_btree_iterator<T>::desc_up( const T &value ) {
    if( _pointer->_parent == nullptr ){
        _pointer = nullptr;
        _idx = 0;
        return;
    } else {
        _pointer = _pointer->_parent;
        for(int i=_pointer->_size-1; i>-1; i--){
            if( _pointer->_elem[i] < value ){
                _idx = i;
                return;
            }
        }
        desc_up(value);
    }
}


template <typename T> void const_btree_iterator<T>::asc_down(){
    if( _pointer->_children.size() == 0 ){
        return;
    }
    _pointer = _pointer->_children[0];
    asc_down();
}
template <typename T> void const_btree_iterator<T>::asc_up( const T& value ){
    if( _pointer->_parent == nullptr ){
        // Already at the root node
        _pointer == nullptr;
        _idx = 0;
        return;
    } else {
        _pointer = _pointer->_parent;
        for( int i=0; i<_pointer->_size; i++ ){
            if( _pointer->_elem[i] > value ){
                _idx = i;
                return;
            }
        }
        asc_up(value);
    }
}



#include "btree_iterator.tem"

#endif
